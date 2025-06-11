#!/usr/bin/env python3

import sys
import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from PyQt5.QtWidgets import (
    QApplication, QLabel, QWidget, QVBoxLayout,
    QTableWidget, QTableWidgetItem, QHBoxLayout, QHeaderView
)
from PyQt5.QtCore import QTimer, pyqtSignal, QObject
from drone_c.msg import PidConsts


class ROS2Listener(QObject):
    message_received = pyqtSignal(object)  # Signal to emit the received message

    def __init__(self, node):
        super().__init__()
        self.node = node
        self.subscription = self.node.create_subscription(
            PidConsts,
            'pid_loaded',
            self.listener_callback,
            10
        )

    def listener_callback(self, msg):
        # Emit the entire message object
        self.message_received.emit(msg)


class DroneTunnerWindow(QWidget):
    def __init__(self, node):
        super().__init__()
        self.setWindowTitle("Drone Tuner GUI")

        # Message Label
        self.label = QLabel("Waiting for messages...")

        # PID Table
        self.table = QTableWidget(5, 3)  # 4 rows, 3 columns
        self.table.setHorizontalHeaderLabels(["P Gain", "I Gain", "D Gain"])
        self.table.setVerticalHeaderLabels([
            "rate_roll",
            "rate_pitch",
            "stable_roll",
            "stable_pitch",
            "rate_yaw",
        ])
        self.table.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.table.verticalHeader().setSectionResizeMode(QHeaderView.Stretch)

        # Fill with default values (optional)
        for row in range(4):
            for col in range(3):
                self.table.setItem(row, col, QTableWidgetItem("0.0"))

        # Layout
        layout = QVBoxLayout()
        layout.addWidget(self.table)
        layout.addWidget(self.label)
        self.setLayout(layout)

        # ROS Listener
        self.listener = ROS2Listener(node)
        self.listener.message_received.connect(self.update_label)

    def update_label(self, msg):
        
        # Update rate_roll
        self.table.setItem(0, 0, QTableWidgetItem(str(msg.rate_roll[0])))
        self.table.setItem(0, 1, QTableWidgetItem(str(msg.rate_roll[1])))
        self.table.setItem(0, 2, QTableWidgetItem(str(msg.rate_roll[2])))
        
        # Update rate_pitch
        self.table.setItem(1, 0, QTableWidgetItem(str(msg.rate_pitch[0])))
        self.table.setItem(1, 1, QTableWidgetItem(str(msg.rate_pitch[1])))
        self.table.setItem(1, 2, QTableWidgetItem(str(msg.rate_pitch[2])))
        
        # Update stable_roll
        self.table.setItem(2, 0, QTableWidgetItem(str(msg.stablize_roll[0])))
        self.table.setItem(2, 1, QTableWidgetItem(str(msg.stablize_roll[1])))
        self.table.setItem(2, 2, QTableWidgetItem(str(msg.stablize_roll[2])))
        
        # Update stable_pitch
        self.table.setItem(3, 0, QTableWidgetItem(str(msg.stablize_pitch[0])))
        self.table.setItem(3, 1, QTableWidgetItem(str(msg.stablize_pitch[1])))
        self.table.setItem(3, 2, QTableWidgetItem(str(msg.stablize_pitch[2])))
        
        self.table.setItem(4, 0, QTableWidgetItem(str(msg.rate_yaw[0])))
        self.table.setItem(4, 1, QTableWidgetItem(str(msg.rate_yaw[1])))
        self.table.setItem(4, 2, QTableWidgetItem(str(msg.rate_yaw[2])))




        self.label.setText("PID values updated!")


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

