#!/usr/bin/env python3

import sys
import rclpy
from rclpy.node import Node
from PyQt5.QtWidgets import (
    QApplication, QLabel, QWidget, QVBoxLayout,
    QTableWidget, QTableWidgetItem, QHBoxLayout, QHeaderView, QPushButton
)
from PyQt5.QtCore import QTimer, pyqtSignal, QObject
from drone_c.msg import PidConsts


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


class DroneTunnerWindow(QWidget):
    def __init__(self, node):
        super().__init__()
        self.setWindowTitle("Drone Tuner GUI")

        # Initialize last_new_msg
        self.last_new_msg = None
        self.values_updated = False

        # Create header widget
        self.header = DroneHeader(node)

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


class DroneHeader(QWidget):
    def __init__(self, node):
        super().__init__()
        self.setWindowTitle("Drone Header")
        
        main_layout = QHBoxLayout()
        
        name_layout = QVBoxLayout()
        name_label = QLabel("Drone Name:")
        self.name_value = QLabel("Unknown")
        name_layout.addWidget(name_label)
        name_layout.addWidget(self.name_value)
        mode_layout = QVBoxLayout()
        mode_label = QLabel("Drone Mode:")
        self.mode_value = QLabel("Unknown")
        mode_layout.addWidget(mode_label)
        mode_layout.addWidget(self.mode_value)
        filter_layout = QVBoxLayout()
        filter_label = QLabel("Filter:")
        self.filter_value = QLabel("Unknown")
        filter_layout.addWidget(filter_label)
        filter_layout.addWidget(self.filter_value)
        main_layout.addLayout(name_layout)
        main_layout.addLayout(mode_layout)
        main_layout.addLayout(filter_layout)
        
        # Set the main layout
        self.setLayout(main_layout)
        self.node = node


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
