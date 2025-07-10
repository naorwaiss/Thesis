#!/usr/bin/env python3

import sys
import signal
import rclpy
from rclpy.node import Node
from PyQt5.QtWidgets import (
    QApplication, QLabel, QWidget, QVBoxLayout,
    QTableWidget, QTableWidgetItem, QHBoxLayout, QHeaderView, QPushButton,
    QMessageBox
)
from PyQt5.QtCore import QTimer, pyqtSignal, QObject
from PyQt5.QtGui import QCloseEvent
from drone_c.msg import PidConsts, DroneHeader,Filter
from std_msgs.msg import String
import struct

import yaml
import os
from ament_index_python.packages import get_package_share_directory


class DroneConfigYaml:
    """
    Class to load and manage the drone configuration from multiple YAML files.
    Provides methods to access different configuration parameters for drone filters and modes.
    """

    def __init__(self):
        self.drone_config = None
        self.drone_mac = None
        self.load_configs()

    def load_configs(self):
        """
        Load configuration files and validate their contents.
        The second config file is optional.
        """
        try:
            # Get package share directory
            package_share_dir = get_package_share_directory('drone_tunner')
            
            # Set paths to config files
            self.drone_config = os.path.join(package_share_dir, 'config', 'drone_config.yaml')
            self.drone_mac = os.path.join(package_share_dir, 'config', 'drone_mac.yaml')

            # Load first config (required)
            with open(self.drone_config, 'r') as file:
                self.drone_config = yaml.safe_load(file)

            # Try to load second config (optional)
            try:
                with open(self.drone_mac, 'r') as file:
                    self.drone_mac = yaml.safe_load(file)
            except FileNotFoundError:
                print(f"Warning: Second configuration file not found at {self.drone_mac}")
                self.drone_mac = None

            # Validate configs
            if not self.validate_configs():
                raise ValueError("Configuration validation failed")

        except FileNotFoundError as e:
            raise FileNotFoundError(f"Required configuration file not found: {str(e)}")
        except yaml.YAMLError as e:
            raise ValueError(f"Error parsing YAML file: {str(e)}")

    def validate_configs(self):
        """
        Validate that configuration files are loaded correctly and contain required fields.
        The second config file is optional.

        Returns:
            bool: True if validation passes, False otherwise
        """
        try:
            # Check if first config is loaded and has required fields
            if not self.drone_config:
                print("Error: First configuration file is empty")
                return False

            if 'drone_filter' not in self.drone_config or 'drone_mode' not in self.drone_config:
                print("Error: First configuration missing required fields (drone_filter or drone_mode)")
                return False

            if not self.drone_mac:
                print("Error: Second configuration file is empty")
                return False
            return True

        except Exception as e:
            print(f"Error during configuration validation: {str(e)}")
            return False

    def get_drone_name(self, mac_adress) -> str:
        """
        Get the drone name from the MAC address.
        """
        try:
            if not self.drone_mac:
                return None
                
            # Convert numpy array to list if needed
            if hasattr(mac_adress, 'tolist'):
                mac_bytes = mac_adress.tolist()
            else:
                mac_bytes = mac_adress
                
            # Look for matching MAC address
            for drone_name, drone_info in self.drone_mac.items():
                if 'mac_adress' in drone_info:
                    # Convert stored MAC address to list if it's not already
                    stored_mac = drone_info['mac_adress']
                    if hasattr(stored_mac, 'tolist'):
                        stored_mac = stored_mac.tolist()
                    
                    # Compare the MAC addresses
                    if stored_mac == mac_bytes:
                        return drone_name
            return None
            
        except Exception as e:
            print(f"Error getting drone name: {str(e)}")
            return None

    def get_mode_name(self, mode_value) -> str:
        """
        Get the mode name from its numeric value.
        
        Args:
            mode_value (int): The numeric mode value
            
        Returns:
            str: The mode name if found, None otherwise
        """
        try:
            if not self.drone_config or 'drone_mode' not in self.drone_config:
                return None
                
            # Look for matching mode value
            for mode_name, value in self.drone_config['drone_mode'].items():
                if value == mode_value:
                    return mode_name
            return None
            
        except Exception as e:
            print(f"Error getting mode name: {str(e)}")
            return None

    def get_filter_name(self, filter_value) -> str:
        """
        Get the filter name from its numeric value.
        
        Args:
            filter_value (int): The numeric filter value
            
        Returns:
            str: The filter name if found, None otherwise
        """
        try:
            if not self.drone_config or 'drone_filter' not in self.drone_config:
                return None
                
            # Look for matching filter value
            for filter_name, value in self.drone_config['drone_filter'].items():
                if value == filter_value:
                    return filter_name
            return None
            
        except Exception as e:
            print(f"Error getting filter name: {str(e)}")
            return None


class ROS2Listener(QObject):
    message_received = pyqtSignal(object)  # Signal to emit the received message
    filter_received = pyqtSignal(object)   # Signal to emit the received filter message

    def __init__(self, node):
        super().__init__()
        self.pid_old_msg = None
        self.filter_old_msg = None
        self.node = node
        
        # PID subscription and publisher
        self.pid_subscription = self.node.create_subscription(
            PidConsts,
            'pid_loaded',
            self.pid_callback,
            10
        )
        self.pid_publisher = self.node.create_publisher(PidConsts, 'pid_to_flash', 10)
        
        # Filter subscription and publisher
        self.filter_subscription = self.node.create_subscription(
            Filter,
            'current_magwick_return_data',
            self.filter_callback,
            10
        )
        self.filter_publisher = self.node.create_publisher(Filter, 'filter_to_flash', 10)

    def pid_callback(self, msg):
        # Emit the entire message object
        self.message_received.emit(msg)
        
    def filter_callback(self, msg):
        # Emit the entire filter message object
        self.filter_received.emit(msg)




class DroneHeaderWidget(QWidget):
    def __init__(self, node, drone_config):
        super().__init__()
        self.node = node  # Store node reference first
        self.drone_config = drone_config  # Store drone_config reference
        
        # Initialize subscription
        self.drone_mac_sub = self.node.create_subscription(
            DroneHeader,  # Using String message type
            'drone_header',
            self.drone_header_callback,
            10
        )
        self.node.get_logger().info('DroneHeader subscription created to /drone_header')
        
        # Initialize variables
        self.drone_mac = None
        self.drone_mac_prev = None
        self.drone_mode = None
        self.drone_filter = None
        self.drone_name = None
        self.arm_state = None
        self.voltage = None
        self.current = None

        self.setWindowTitle("Drone Header")
        
        # Create layouts
        main_layout = QHBoxLayout()
        
        # Mode layout
        mode_layout = QVBoxLayout()
        mode_label = QLabel("Drone Mode:")
        self.mode_value = QLabel("Unknown")
        mode_layout.addWidget(mode_label)
        mode_layout.addWidget(self.mode_value)
        
        # Filter layout
        filter_layout = QVBoxLayout()
        filter_label = QLabel("Filter:")
        self.filter_value = QLabel("Unknown")
        filter_layout.addWidget(filter_label)
        filter_layout.addWidget(self.filter_value)
        
        # Name layout
        name_layout = QVBoxLayout()
        name_label = QLabel("Drone Name:")
        self.name_value = QLabel("Unknown")
        name_layout.addWidget(name_label)
        name_layout.addWidget(self.name_value)

        # State layout
        state_layout = QVBoxLayout()
        state_label = QLabel("Arm State:")
        self.state_value = QLabel("Unknown")
        state_layout.addWidget(state_label)
        state_layout.addWidget(self.state_value)
        
        # Add layouts to main layout in desired order
        main_layout.addLayout(mode_layout)
        main_layout.addLayout(filter_layout)
        main_layout.addLayout(name_layout)
        main_layout.addLayout(state_layout)
        
        self.setLayout(main_layout)

    def get_arm_state(self, arm_state)->str:
        if arm_state == False:
            return "Disarmed"
        elif arm_state == True:
            return "Armed"

    def drone_header_callback(self, msg):
        self.drone_mac = msg.mac_adress
        self.drone_mode = msg.drone_mode
        self.drone_filter = msg.drone_filter
        self.arm_state = msg.is_armed
        self.voltage = round(msg.voltage,1)
        self.current = round(msg.current,1)

        # Get names from config if available
        try:
            if self.drone_config:
                # Get drone name
                if self.drone_config.drone_mac:
                    self.drone_name = self.drone_config.get_drone_name(self.drone_mac)
                
                # Get mode name
                mode_name = self.drone_config.get_mode_name(self.drone_mode)
                if mode_name:
                    self.drone_mode = mode_name
                
                # Get filter name
                filter_name = self.drone_config.get_filter_name(self.drone_filter)
                if filter_name:
                    self.drone_filter = filter_name
                    
        except Exception as e:
            print(f"Error getting names from config: {str(e)}")
            self.drone_name = None
        
        # Update UI labels
        self.mode_value.setText(str(self.drone_mode))
        self.filter_value.setText(str(self.drone_filter))
        self.name_value.setText(str(self.drone_name if self.drone_name else self.drone_mac))
        self.state_value.setText(self.get_arm_state(self.arm_state))
        
        # Update voltage and current in main window if available
        if hasattr(self.parent(), 'voltage_value') and hasattr(self.parent(), 'current_value'):
            self.parent().voltage_value.setText(f"{self.voltage}V")
            self.parent().current_value.setText(f"{self.current}A")

class Tunner(QWidget):
    def __init__(self, node):
        super().__init__()
        self.setWindowTitle("Drone Tuner GUI")
        self.node = node  # Store node reference for cleanup

        # Initialize pid_old_msg
        self.pid_old_msg = None
        self.filter_old_data = None
        self.values_updated = False

        # Create header widget
        self.drone_config = DroneConfigYaml()
        self.header = DroneHeaderWidget(node, self.drone_config)
        # Message Label with initial color
        self.label = QLabel("Waiting for messages...")
        self.label.setStyleSheet("color: black;")  # Initial color
        self.verification_timer = QTimer()
        self.verification_timer.timeout.connect(self.reset_verification_color)

        # PID Table
        self.table = QTableWidget(5, 3)  # 4 rows, 3 columns
        self.table.setHorizontalHeaderLabels(["P Gain", "I Gain", "D Gain"])
        self.table.setVerticalHeaderLabels([
            "rate_roll",
            "rate_pitch",
            "rate_yaw",
            "stable_roll",
            "stable_pitch",
        ])
        self.table.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.table.verticalHeader().setSectionResizeMode(QHeaderView.Stretch)
        
        # Beta Table for filter values
        self.beta_table = QTableWidget(3, 1)  # 3 rows, 1 column
        self.beta_table.setHorizontalHeaderLabels(["Value"])
        self.beta_table.setVerticalHeaderLabels([
            "std_beta",
            "low_beta",
            "high_beta",
        ])
        self.beta_table.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.beta_table.verticalHeader().setSectionResizeMode(QHeaderView.Stretch)
        
        self.verification_status = QLabel()
        self.verification_status.setFixedSize(20, 20)
        self.verification_status.setStyleSheet("background-color: gray; border-radius: 10px;")

        # Create horizontal layout for status and button
        status_layout = QHBoxLayout()
        status_layout.addWidget(self.verification_status)
        status_layout.addWidget(QLabel("Status:"))
        status_layout.addStretch()

        # Create buttons
        self.pid_button = QPushButton("Flash New Pid")
        self.pid_button.clicked.connect(self.on_pid_button_clicked)
        
        self.filter_button = QPushButton("Flash New Filter")
        self.filter_button.clicked.connect(self.on_filter_button_clicked)

        # Create voltage and current layout
        voltage_current_layout = QVBoxLayout()
        
        # Voltage layout
        voltage_layout = QHBoxLayout()
        voltage_label = QLabel("Voltage:")
        self.voltage_value = QLabel("Unknown")
        voltage_layout.addWidget(voltage_label)
        voltage_layout.addWidget(self.voltage_value)
        
        # Current layout
        current_layout = QHBoxLayout()
        current_label = QLabel("Current:")
        self.current_value = QLabel("Unknown")
        current_layout.addWidget(current_label)
        current_layout.addWidget(self.current_value)
        
        # Add voltage and current to horizontal layout
        voltage_current_layout.addLayout(voltage_layout)
        voltage_current_layout.addLayout(current_layout)
        voltage_current_layout.addStretch()  # Add stretch to push them to the left

        # Create horizontal layout for buttons
        button_layout = QHBoxLayout()
        button_layout.addWidget(self.pid_button)
        button_layout.addWidget(self.filter_button)

        # Layout
        layout = QVBoxLayout()
        layout.addWidget(self.header)  # Add header at the top
        layout.addWidget(self.table)
        layout.addWidget(self.beta_table)  # Add beta table
        layout.addWidget(self.label)
        layout.addLayout(status_layout)
        layout.addLayout(button_layout)  # Add both buttons
        layout.addLayout(voltage_current_layout)  # Add voltage/current at the bottom
        self.setLayout(layout)

        # ROS Listener
        self.listener = ROS2Listener(node)
        self.listener.message_received.connect(self.update_label_ros)
        self.listener.filter_received.connect(self.update_filter_ros)

        # Connect table cell changed signal
        self.table.cellChanged.connect(self.on_table_changed)
        self.beta_table.cellChanged.connect(self.on_table_changed)

    def closeEvent(self, event: QCloseEvent):
        """
        Override closeEvent to show confirmation dialog before closing via GUI
        """
        reply = QMessageBox.question(
            self, 
            'Exit Application', 
            'Are you sure you want to exit the Drone Tuner?',
            QMessageBox.Yes | QMessageBox.No,
            QMessageBox.No
        )
        
        if reply == QMessageBox.Yes:
            event.accept()
        else:
            event.ignore()

    def cleanup(self):
        if hasattr(self, 'node'):
            self.node.destroy_node()
        rclpy.shutdown()

    def compere_pid_data(self, msg) -> bool:
        if self.pid_old_msg is None or self.pid_old_msg != msg:
            self.pid_old_msg = msg
            return True
        return False

    def compere_filter_data(self, msg) -> bool:
        if self.filter_old_data is None or self.filter_old_data != msg:
            self.filter_old_data = msg
            return True
        return False

    def on_table_changed(self):
        """Called when any cell in the table is changed"""
        if self.values_updated:
            self.values_updated = False
            self.label.setStyleSheet("color: black;")
            self.label.setText("Waiting for messages...")

    def reset_verification_color(self):
        """Reset verification status color to gray"""
        self.verification_status.setStyleSheet("background-color: gray; border-radius: 10px;")
        self.verification_timer.stop()

    def set_verification_status(self, success: bool):
        """Set verification status color based on status"""
        if success:
            self.verification_status.setStyleSheet("background-color: green; border-radius: 10px;")
        else:
            self.verification_status.setStyleSheet("background-color: red; border-radius: 10px;")

        # Start timer to reset color after 3 seconds
        self.verification_timer.start(3000)  # 3000 ms = 3 seconds

    def update_label_ros(self, msg):
        if not self.compere_pid_data(msg):
            return
        try:
            # Update rate_roll
            self.table.setItem(0, 0, QTableWidgetItem(str(msg.rate_roll[0])))
            self.table.setItem(0, 1, QTableWidgetItem(str(msg.rate_roll[1])))
            self.table.setItem(0, 2, QTableWidgetItem(str(msg.rate_roll[2])))
            self.table.setItem(1, 0, QTableWidgetItem(str(msg.rate_pitch[0])))
            self.table.setItem(1, 1, QTableWidgetItem(str(msg.rate_pitch[1])))
            self.table.setItem(1, 2, QTableWidgetItem(str(msg.rate_pitch[2])))
            self.table.setItem(2, 0, QTableWidgetItem(str(msg.rate_yaw[0])))
            self.table.setItem(2, 1, QTableWidgetItem(str(msg.rate_yaw[1])))
            self.table.setItem(2, 2, QTableWidgetItem(str(msg.rate_yaw[2])))
            self.table.setItem(3, 0, QTableWidgetItem(str(msg.stablize_roll[0])))
            self.table.setItem(3, 1, QTableWidgetItem(str(msg.stablize_roll[1])))
            self.table.setItem(3, 2, QTableWidgetItem(str(msg.stablize_roll[2])))
            self.table.setItem(4, 0, QTableWidgetItem(str(msg.stablize_pitch[0])))
            self.table.setItem(4, 1, QTableWidgetItem(str(msg.stablize_pitch[1])))
            self.table.setItem(4, 2, QTableWidgetItem(str(msg.stablize_pitch[2])))

            self.label.setText("PID values updated!")
            self.set_verification_status(True)
        except Exception as e:
            print(f"Error updating values: {e}")
            self.set_verification_status(False)

    def get_row_values(self, row):
        try:
            return [float(self.table.item(row, col).text()) for col in range(self.table.columnCount()) if self.table.item(row, col) is not None]
        except ValueError as e:
            print(f"Error converting value to float: {e}")
            self.set_verification_status(False)
            raise ValueError(f"Invalid value in row {row}. Please enter valid numbers.")

    def get_beta_values(self):
        try:
            beta_values = []
            for row in range(self.beta_table.rowCount()):
                item = self.beta_table.item(row, 0)
                if item is not None:
                    beta_values.append(float(item.text()))
                else:
                    beta_values.append(0.0)  # Default value if cell is empty
            return beta_values
        except ValueError as e:
            print(f"Error converting beta value to float: {e}")
            self.set_verification_status(False)
            raise ValueError(f"Invalid beta value. Please enter valid numbers.")

    def on_pid_button_clicked(self):
        try:
            self.label.setText("pid was flash!")
            retrun_rate_roll = self.get_row_values(0)
            retrun_rate_pitch = self.get_row_values(1)
            retrun_stablize_pitch = self.get_row_values(2)
            retrun_stablize_roll = self.get_row_values(3)
            retrun_rate_yaw = self.get_row_values(4)
            
            msg = PidConsts()
            msg.rate_roll = retrun_rate_roll
            msg.rate_pitch = retrun_rate_pitch
            msg.stablize_pitch = retrun_stablize_pitch
 

            self.set_verification_status(True)
        except ValueError as e:
            self.label.setText(f"Error: {str(e)}")
            self.set_verification_status(False)

    def on_filter_button_clicked(self):
        try:
            # Get beta values
            beta_values = self.get_beta_values()
            
            # Create and publish filter message
            filter_msg = Filter()
            filter_msg.std_beta = beta_values[0]
            filter_msg.low_beta = beta_values[1]
            filter_msg.high_beta = beta_values[2]
            self.listener.filter_publisher.publish(filter_msg)
            
            self.label.setText("Filter values updated!")
            self.set_verification_status(True)
        except ValueError as e:
            self.label.setText(f"Error: {str(e)}")
            self.set_verification_status(False)

    def update_filter_ros(self, msg):
        if not self.compere_filter_data(msg):
            return
        try:
            # Update beta table with new values
            self.beta_table.setItem(0, 0, QTableWidgetItem(str(msg.std_beta)))
            self.beta_table.setItem(1, 0, QTableWidgetItem(str(msg.low_beta)))
            self.beta_table.setItem(2, 0, QTableWidgetItem(str(msg.high_beta)))
            
            self.label.setText("Filter values updated!")
            self.set_verification_status(True)
        except Exception as e:
            print(f"Error updating filter values: {e}")
            self.set_verification_status(False)
        


def signal_handler(signum, frame):
    """
    Handle Ctrl+C signal to gracefully exit the application
    """
    print("\nCtrl+C detected. Shutting down gracefully...")
    if 'app' in globals():
        app.quit()
    sys.exit(0)

def main(args=None):
    # Set up signal handler for Ctrl+C
    signal.signal(signal.SIGINT, signal_handler)
    
    rclpy.init(args=args)
    node = rclpy.create_node('drone_tunner_gui_node')
    app = QApplication(sys.argv)
    
    # Create the combined GUI window
    gui = Tunner(node)

    # Timer to call ROS spin once
    timer = QTimer()
    timer.timeout.connect(lambda: rclpy.spin_once(node, timeout_sec=0.01))
    timer.start(10)

    # Show the window
    gui.show()
    
    exit_code = app.exec_()

    # Cleanup
    gui.cleanup()
    sys.exit(exit_code)


if __name__ == '__main__':
    main()
