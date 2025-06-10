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
    message_received = pyqtSignal(str)

    def __init__(self, node):
        super().__init__()
        self.node = node
        self.subscription = self.node.create_subscription(
            String,
            'chatter',
            self.listener_callback,
            10
        )

    def listener_callback(self, msg):
        self.message_received.emit(msg.data)


class DroneTunnerWindow(QWidget):
    def __init__(self, node):
        super().__init__()
        self.setWindowTitle("Drone Tuner GUI")

        # Message Label
        self.label = QLabel("Waiting for messages...")

        # PID Table
        self.table = QTableWidget(4, 3)  # 4 rows, 3 columns
        self.table.setHorizontalHeaderLabels(["P Gain", "I Gain", "D Gain"])
        self.table.setVerticalHeaderLabels([
            "rate_roll",
            "rate_pitch",
            "stable_roll",
            "stable_pitch"
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
        self.label.setText(f"Received: {msg}")


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

