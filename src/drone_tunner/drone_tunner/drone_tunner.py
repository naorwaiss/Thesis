#!/usr/bin/env python3

import sys
import rclpy
from rclpy.node import Node
from PyQt5.QtWidgets import (
    QApplication, QLabel, QWidget, QVBoxLayout,
    QTableWidget, QTableWidgetItem, QHBoxLayout, QHeaderView, QPushButton
)
from PyQt5.QtCore import QTimer, pyqtSignal, QObject
from drone_c.msg import PidConsts, DroneHeader
from std_msgs.msg import String
import struct

import yaml
import os


class DroneConfigYaml:
    """
    Class to load and manage the drone configuration from multiple YAML files.
    Provides methods to access different configuration parameters for drone filters and modes.
    """

    def __init__(self):
        self.drone_config = None
        self.drone_config = os.path.join(os.path.dirname(os.path.dirname(__file__)), 'config', 'drone_config.yaml')
        self.second_config = None
        self.drone_mac = os.path.join(os.path.dirname(os.path.dirname(__file__)), 'config', 'drone_mac.yaml')
        self.load_configs()

    def load_configs(self):
        """
        Load configuration files and validate their contents.
        The second config file is optional.
        """
        try:
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

    def __init__(self, node):
        super().__init__()
        self.last_new_msg = None
        self.node = node
        self.subscription = self.node.create_subscription(
            PidConsts,
            'pid_loaded',
            self.listener_callback,
            10
        )
        self.pid_to_flash_pub = self.node.create_publisher(PidConsts, 'pid_to_flash', 10)

    def listener_callback(self, msg):
        # Emit the entire message object
        self.message_received.emit(msg)


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
        
        # Add layouts to main layout in desired order
        main_layout.addLayout(mode_layout)
        main_layout.addLayout(filter_layout)
        main_layout.addLayout(name_layout)
        
        self.setLayout(main_layout)

    def drone_header_callback(self, msg):
        self.drone_mac = msg.mac_adress
        self.drone_mode = msg.drone_mode
        self.drone_filter = msg.drone_filter
        
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


class DroneTunnerWindow(QWidget):
    def __init__(self, node):
        super().__init__()
        self.setWindowTitle("Drone Tuner GUI")

        # Initialize last_new_msg
        self.last_new_msg = None
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
        self.verification_status = QLabel()
        self.verification_status.setFixedSize(20, 20)
        self.verification_status.setStyleSheet("background-color: gray; border-radius: 10px;")

        # Create horizontal layout for status and button
        status_layout = QHBoxLayout()
        status_layout.addWidget(self.verification_status)
        status_layout.addWidget(QLabel("Status:"))
        status_layout.addStretch()

        # Create button
        self.button = QPushButton("Flash New Pid")
        self.button.clicked.connect(self.on_button_clicked)

        # Layout
        layout = QVBoxLayout()
        layout.addWidget(self.header)  # Add header at the top
        layout.addWidget(self.table)
        layout.addWidget(self.label)
        layout.addLayout(status_layout)
        layout.addWidget(self.button)
        self.setLayout(layout)

        # ROS Listener
        self.listener = ROS2Listener(node)
        self.listener.message_received.connect(self.update_label_ros)

        # Connect table cell changed signal
        self.table.cellChanged.connect(self.on_table_changed)

    def compere_data(self, msg) -> bool:
        """
        Returns True if the data is different from the last message, False if it's the same
        """
        if self.last_new_msg is None or self.last_new_msg != msg:
            self.last_new_msg = msg
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
        if not self.compere_data(msg):
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

    def on_button_clicked(self):
        try:
            self.label.setText("Button was clicked!")
            retrun_rate_roll = self.get_row_values(0)
            retrun_rate_pitch = self.get_row_values(1)
            retrun_stablize_pitch = self.get_row_values(2)
            retrun_stablize_roll = self.get_row_values(3)
            retrun_rate_yaw = self.get_row_values(4)
            msg = PidConsts()
            msg.rate_roll = retrun_rate_roll
            msg.rate_pitch = retrun_rate_pitch
            msg.stablize_pitch = retrun_stablize_pitch
            msg.stablize_roll = retrun_stablize_roll
            msg.rate_yaw = retrun_rate_yaw
            self.listener.pid_to_flash_pub.publish(msg)
            self.set_verification_status(True)
        except ValueError as e:
            self.label.setText(f"Error: {str(e)}")
            self.set_verification_status(False)


def main(args=None):
    rclpy.init(args=args)
    node = rclpy.create_node('drone_tunner_gui_node')
    app = QApplication(sys.argv)
    gui = DroneTunnerWindow(node)

    # Timer to call ROS spin once
    timer = QTimer()
    timer.timeout.connect(lambda: rclpy.spin_once(node, timeout_sec=0.01))
    timer.start(10)

    gui.show()
    exit_code = app.exec_()

    node.destroy_node()
    rclpy.shutdown()
    sys.exit(exit_code)


if __name__ == '__main__':
    main()
