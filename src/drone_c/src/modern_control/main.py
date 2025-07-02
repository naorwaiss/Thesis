import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Imu
from std_msgs.msg import Float32MultiArray
from drone_c.msg import EulerAngles,  DroneHeader
from collections import deque
from enum import IntEnum
import time
import threading
import numpy as np
from scipy.optimize import curve_fit
from control import ControlAnalyzer


class DroneMode(IntEnum):
    MODE_RATE = 1
    MODE_STABILIZE = 2


class Take_data(IntEnum):
    TAKE = 1
    DONT_TAKE = 2


class DataBuffer(Node):
    """Class responsible for data collection and buffer management"""

    def __init__(self, buffer_time=5, wait_time=3, data_hz=50):
        super().__init__('data_buffer')

        # Configuration
        self.buffer_time = buffer_time
        self.wait_time = wait_time
        self.data_hz = data_hz
        self.wait_flag = False

        # State tracking
        self.is_drone_armed = None
        self.drone_mode = None
        self.buffer_delay_active = False
        self.last_buffer_full_time = None

        # Buffer state tracking
        self.rate_buffer_full = False
        self.stab_buffer_full = False
        self.last_rate_analysis_time = None
        self.last_stab_analysis_time = None

        # Threading control
        self.wait_thread = None
        self.wait_thread_active = False

        # Subscribers
        self.create_subscription(Float32MultiArray, '/desire_rate', self.desired_rate_callback, 10)
        self.create_subscription(Float32MultiArray, '/desire_stab', self.desired_stab_callback, 10)
        self.create_subscription(Float32MultiArray, '/estimated_rate', self.estimated_rate_callback, 10)
        self.create_subscription(EulerAngles, '/euler_angles_data', self.euler_angles_callback, 10)
        self.create_subscription(DroneHeader, '/drone_header', self.drone_header_callback, 10)

        # Initialize callback data attributes
        self.last_desired_x = None
        self.last_desired_y = None
        self.last_desired_stab_x = None
        self.last_desired_stab_y = None
        self.last_actual_x = None
        self.last_actual_y = None
        self.last_euler_angles_roll = None
        self.last_euler_angles_pitch = None

        # Buffers

    def desired_rate_callback(self, msg: Float32MultiArray):
        self.last_desired_rate_x = msg.data[0]
        self.last_desired_rate_y = msg.data[1]

    def desired_stab_callback(self, msg: Float32MultiArray):
        self.last_desired_stab_x = msg.data[0]
        self.last_desired_stab_y = msg.data[1]

    def estimated_rate_callback(self, msg: Float32MultiArray):
        self.last_actual_x = msg.data[0]
        self.last_actual_y = msg.data[1]

    def euler_angles_callback(self, msg: EulerAngles):
        self.last_euler_angles_roll = msg.roll
        self.last_euler_angles_pitch = msg.pitch

    def drone_header_callback(self, msg: DroneHeader):
        self.is_drone_armed = msg.is_armed
        self.drone_mode = msg.drone_mode


class make_buffer(DataBuffer):
    def __init__(self, buffer_time=5, wait_time=3, data_hz=50):
        super().__init__(buffer_time, wait_time, data_hz)

        self.buffer_desired_rate_x = deque(maxlen=buffer_time * data_hz)
        self.buffer_desired_rate_y = deque(maxlen=buffer_time * data_hz)
        self.buffer_actual_rate_x = deque(maxlen=buffer_time * data_hz)
        self.buffer_actual_rate_y = deque(maxlen=buffer_time * data_hz)
        self.buffer_euler_angles_roll = deque(maxlen=buffer_time * data_hz)
        self.buffer_euler_angles_pitch = deque(maxlen=buffer_time * data_hz)
        self.buffer_desired_stab_x = deque(maxlen=buffer_time * data_hz)
        self.buffer_desired_stab_y = deque(maxlen=buffer_time * data_hz)

    def check_full_rate(self):
        return
    
    def check_full_stab(self):
        return
        

    def case_rate(self):
        print("case_rate")
        self.buffer_desired_rate_x.append(self.last_desired_rate_x)
        self.buffer_desired_rate_y.append(self.last_desired_rate_y)
        self.buffer_actual_rate_x.append(self.last_actual_x)
        self.buffer_actual_rate_x.append(self.last_actual_y)



    def case_stab(self):
        print("case stab")
        self.buffer_desired_stab_x.append(self.last_desired_stab_x)
        self.buffer_desired_stab_y.append(self.last_desired_stab_y)
        self.buffer_euler_angles_pitch.append(self.last_euler_angles_pitch)
        self.buffer_euler_angles_roll.append(self.last_euler_angles_roll)


        

        

    def take_buffer_control(self):

        return

    def case_switcher(self):
        """Switch between different drone modes and handle data collection"""
        match self.drone_mode:
             case DroneMode.MODE_RATE:
              self.case_rate()
             case DroneMode.MODE_STABILIZE:
              self.case_stab()

    def run(self):
        while rclpy.ok():
            self.case_switcher()

def main(args=None):
    rclpy.init(args=args)
    buffer_manager = make_buffer()
    thread = threading.Thread(target=buffer_manager.run)
    thread.start()
    try:
        rclpy.spin(buffer_manager)
    except KeyboardInterrupt:
        print("\nShutting down...")
    rclpy.shutdown()


if __name__ == '__main__':
    main()
