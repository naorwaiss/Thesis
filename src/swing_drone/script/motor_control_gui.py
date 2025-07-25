#!/usr/bin/env python3

import sys
import numpy as np
import rclpy
from rclpy.node import Node
from actuator_msgs.msg import Actuators
from PyQt5.QtWidgets import (QApplication, QMainWindow, QVBoxLayout, QHBoxLayout, 
                             QWidget, QSlider, QSpinBox, QLabel, QPushButton, QGroupBox)
from PyQt5.QtCore import Qt, QTimer
from PyQt5.QtGui import QFont


class MotorControlNode(Node):
    def __init__(self):
        super().__init__('motor_control_gui')
        self.publisher_ = self.create_publisher(
            Actuators,
            '/swing_drone/gazebo/command/motor_speed',
            10
        )
        
    def publish_motor_speeds(self, speeds):
        msg = Actuators()
        msg.velocity = [float(speed) for speed in speeds]
        self.publisher_.publish(msg)
        self.get_logger().info(f'Published motor speeds: {speeds}')


class MotorControlGUI(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Drone Motor Control")
        self.setGeometry(100, 100, 800, 600)
        
        # Initialize ROS2
        rclpy.init()
        self.ros_node = MotorControlNode()
        
        # Timer for ROS2 spinning
        self.ros_timer = QTimer()
        self.ros_timer.timeout.connect(self.spin_ros)
        self.ros_timer.start(10)  # 100Hz
        
        # Motor speed limits
        self.min_speed = -1000
        self.max_speed = 1000
        
        # Motor controls storage
        self.motor_sliders = []
        self.motor_spinboxes = []
        self.motor_speeds = [np.float32(0.0)] * 8
        
        self.init_ui()
        
    def init_ui(self):
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        
        main_layout = QVBoxLayout()
        central_widget.setLayout(main_layout)
        
        # Title
        title_label = QLabel("Drone Motor Control Interface")
        title_label.setAlignment(Qt.AlignCenter)
        title_font = QFont()
        title_font.setPointSize(16)
        title_font.setBold(True)
        title_label.setFont(title_font)
        main_layout.addWidget(title_label)
        
        # Motor controls group
        motors_group = QGroupBox("Motor Controls")
        motors_layout = QVBoxLayout()
        motors_group.setLayout(motors_layout)
        
        # Create controls for each motor
        for i in range(8):
            motor_layout = self.create_motor_control(i)
            motors_layout.addLayout(motor_layout)
            
        main_layout.addWidget(motors_group)
        
        # Control buttons
        buttons_layout = QHBoxLayout()
        
        stop_all_btn = QPushButton("STOP ALL MOTORS")
        stop_all_btn.setStyleSheet("QPushButton { background-color: #ff4444; color: white; font-weight: bold; padding: 10px; }")
        stop_all_btn.clicked.connect(self.stop_all_motors)
        buttons_layout.addWidget(stop_all_btn)
        
        reset_btn = QPushButton("Reset to Zero")
        reset_btn.setStyleSheet("QPushButton { background-color: #4444ff; color: white; font-weight: bold; padding: 10px; }")
        reset_btn.clicked.connect(self.reset_all_motors)
        buttons_layout.addWidget(reset_btn)
        
        test_btn = QPushButton("Test Pattern")
        test_btn.setStyleSheet("QPushButton { background-color: #44ff44; color: white; font-weight: bold; padding: 10px; }")
        test_btn.clicked.connect(self.test_pattern)
        buttons_layout.addWidget(test_btn)
        
        main_layout.addLayout(buttons_layout)
        
        # Status
        self.status_label = QLabel("Status: Ready")
        self.status_label.setAlignment(Qt.AlignCenter)
        main_layout.addWidget(self.status_label)
        
    def create_motor_control(self, motor_index):
        layout = QHBoxLayout()
        
        # Motor label
        motor_label = QLabel(f"Motor {motor_index + 1}:")
        motor_label.setMinimumWidth(80)
        layout.addWidget(motor_label)
        
        # Slider
        slider = QSlider(Qt.Horizontal)
        slider.setMinimum(self.min_speed)
        slider.setMaximum(self.max_speed)
        slider.setValue(0)
        slider.valueChanged.connect(lambda value, idx=motor_index: self.update_motor_from_slider(idx, value))
        self.motor_sliders.append(slider)
        layout.addWidget(slider)
        
        # Spin box
        spinbox = QSpinBox()
        spinbox.setMinimum(self.min_speed)
        spinbox.setMaximum(self.max_speed)
        spinbox.setValue(0)
        spinbox.valueChanged.connect(lambda value, idx=motor_index: self.update_motor_from_spinbox(idx, value))
        self.motor_spinboxes.append(spinbox)
        layout.addWidget(spinbox)
        
        # Current value label
        value_label = QLabel("0")
        value_label.setMinimumWidth(60)
        value_label.setAlignment(Qt.AlignCenter)
        value_label.setStyleSheet("QLabel { border: 1px solid gray; padding: 5px; }")
        layout.addWidget(value_label)
        
        return layout
        
    def update_motor_from_slider(self, motor_index, value):
        self.motor_speeds[motor_index] = np.float32(value)
        # Update corresponding spinbox without triggering its signal
        self.motor_spinboxes[motor_index].blockSignals(True)
        self.motor_spinboxes[motor_index].setValue(value)
        self.motor_spinboxes[motor_index].blockSignals(False)
        
        # Update value label
        value_label = self.centralWidget().findChildren(QLabel)[motor_index + 2]  # +2 to skip title and first label
        value_label.setText(str(value))
        
        self.publish_speeds()
        
    def update_motor_from_spinbox(self, motor_index, value):
        self.motor_speeds[motor_index] = np.float32(value)
        # Update corresponding slider without triggering its signal
        self.motor_sliders[motor_index].blockSignals(True)
        self.motor_sliders[motor_index].setValue(value)
        self.motor_sliders[motor_index].blockSignals(False)
        
        # Update value label
        value_labels = [w for w in self.centralWidget().findChildren(QLabel) if w.text().isdigit() or w.text().startswith('-')]
        if motor_index < len(value_labels):
            value_labels[motor_index].setText(str(value))
        
        self.publish_speeds()
        
    def publish_speeds(self):
        self.ros_node.publish_motor_speeds(self.motor_speeds)
        self.status_label.setText(f"Published: {[f'{speed:.0f}' for speed in self.motor_speeds]}")
        
    def stop_all_motors(self):
        for i in range(8):
            self.motor_speeds[i] = np.float32(0.0)
            self.motor_sliders[i].setValue(0)
            self.motor_spinboxes[i].setValue(0)
        self.publish_speeds()
        self.status_label.setText("Status: ALL MOTORS STOPPED")
        
    def reset_all_motors(self):
        self.stop_all_motors()
        
    def test_pattern(self):
        # Alternate pattern for testing
        test_speeds = [np.float32(200), np.float32(-200), np.float32(200), np.float32(-200), 
                      np.float32(200), np.float32(-200), np.float32(200), np.float32(-200)]
        for i in range(8):
            self.motor_speeds[i] = test_speeds[i]
            self.motor_sliders[i].setValue(int(test_speeds[i]))
            self.motor_spinboxes[i].setValue(int(test_speeds[i]))
        self.publish_speeds()
        self.status_label.setText("Status: Test pattern applied")
        
    def spin_ros(self):
        rclpy.spin_once(self.ros_node, timeout_sec=0)
        
    def closeEvent(self, event):
        # Stop all motors before closing
        self.stop_all_motors()
        # Cleanup ROS2
        self.ros_node.destroy_node()
        rclpy.shutdown()
        event.accept()


def main():
    app = QApplication(sys.argv)
    
    # Set application style
    app.setStyle('Fusion')
    
    window = MotorControlGUI()
    window.show()
    
    try:
        sys.exit(app.exec_())
    except KeyboardInterrupt:
        print("Application interrupted")
        window.close()


if __name__ == '__main__':
    main() 




