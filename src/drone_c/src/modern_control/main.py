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


class DataBuffer(Node):
    """Class responsible for data collection and buffer management"""

    def __init__(self, buffer_time=5, wait_time=3, data_hz=100):
        super().__init__('data_buffer')

        # Configuration
        self.buffer_time = buffer_time
        self.wait_time = wait_time
        self.data_hz = data_hz

        # State tracking
        self.is_drone_armed = None
        self.drone_mode = None
        self.buffer_delay_active = False
        self.last_buffer_full_time = None

        # Threading control
        self.wait_thread = None
        self.wait_thread_active = False
        self.wait_thread_lock = threading.Lock()

        # Initialize last values
        self.last_desired_x = 0.0
        self.last_desired_y = 0.0
        self.last_desired_stab_x = 0.0
        self.last_desired_stab_y = 0.0
        self.last_actual_x = 0.0
        self.last_actual_y = 0.0
        self.last_euler_angles_roll = 0.0
        self.last_euler_angles_pitch = 0.0

        # Subscribers
        self.create_subscription(Float32MultiArray, '/desire_rate', self.desired_rate_callback, 10)
        self.create_subscription(Float32MultiArray, '/desire_stab', self.desired_stab_callback, 10)
        self.create_subscription(Float32MultiArray, '/estimated_rate', self.estimated_rate_callback, 10)
        self.create_subscription(EulerAngles, '/euler_angles_data', self.euler_angles_callback, 10)
        self.create_subscription(DroneHeader, '/drone_header', self.drone_header_callback, 10)

        # Buffers
        self.buffer_desired_rate_x = deque(maxlen=buffer_time * data_hz)
        self.buffer_desired_rate_y = deque(maxlen=buffer_time * data_hz)
        self.buffer_actual_rate_x = deque(maxlen=buffer_time * data_hz)
        self.buffer_actual_rate_y = deque(maxlen=buffer_time * data_hz)
        self.buffer_euler_angles_roll = deque(maxlen=buffer_time * data_hz)
        self.buffer_euler_angles_pitch = deque(maxlen=buffer_time * data_hz)
        self.buffer_desired_stab_x = deque(maxlen=buffer_time * data_hz)
        self.buffer_desired_stab_y = deque(maxlen=buffer_time * data_hz)


    def desired_rate_callback(self, msg: Float32MultiArray):
        self.last_desired_x = msg.data[0]
        self.last_desired_y = msg.data[1]

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

    def is_buffer_full_rate(self) -> bool:
        """Check if any of the rate data buffers are full"""
        return (len(self.buffer_desired_rate_x) >= self.buffer_desired_rate_x.maxlen or
                len(self.buffer_desired_rate_y) >= self.buffer_desired_rate_y.maxlen or
                len(self.buffer_actual_rate_x) >= self.buffer_actual_rate_x.maxlen or
                len(self.buffer_actual_rate_y) >= self.buffer_actual_rate_y.maxlen)

    def is_buffer_full_stab(self) -> bool:
        """Check if any of the stabilize data buffers are full"""
        return (len(self.buffer_desired_stab_x) >= self.buffer_desired_stab_x.maxlen or
                len(self.buffer_desired_stab_y) >= self.buffer_desired_stab_y.maxlen or
                len(self.buffer_euler_angles_roll) >= self.buffer_euler_angles_roll.maxlen or
                len(self.buffer_euler_angles_pitch) >= self.buffer_euler_angles_pitch.maxlen)

    def free_all_buffers(self):
        """Clear all buffers"""
        self.buffer_desired_rate_x.clear()
        self.buffer_desired_rate_y.clear()
        self.buffer_actual_rate_x.clear()
        self.buffer_actual_rate_y.clear()
        self.buffer_euler_angles_roll.clear()
        self.buffer_euler_angles_pitch.clear()
        self.buffer_desired_stab_x.clear()
        self.buffer_desired_stab_y.clear()

    def wait_thread_function(self):
        """Thread function that handles the wait period"""
        self.get_logger().info(f"Wait thread started - waiting {self.wait_time} seconds")
        time.sleep(self.wait_time)

        with self.wait_thread_lock:
            self.wait_thread_active = False
            self.free_all_buffers()
            self.get_logger().info("Wait period complete, buffers cleared and ready for new data")

    def start_wait_thread(self):
        """Start the wait thread if not already running"""
        with self.wait_thread_lock:
            if not self.wait_thread_active:
                self.wait_thread_active = True
                self.wait_thread = threading.Thread(target=self.wait_thread_function, daemon=True)
                self.wait_thread.start()
                self.get_logger().info("Buffer full, starting wait thread")

    def should_collect_data(self, is_buffer_full: bool) -> bool:
        """
        Determine if we should collect data based on buffer state and threading
        Returns True if we should collect data, False if we should wait
        """
        if is_buffer_full:
            # Buffer is full, start wait thread if not already running
            self.start_wait_thread()
            return False  # Don't collect data during wait
        else:
            # Check if wait thread is still active
            with self.wait_thread_lock:
                if self.wait_thread_active:
                    return False  # Still waiting
                else:
                    return True   # Ready to collect data

    def case_rate(self):
        """Handle rate control mode data collection"""
        if self.should_collect_data(self.is_buffer_full_rate()):
            self.buffer_desired_rate_x.append(self.last_desired_x)
            self.buffer_desired_rate_y.append(self.last_desired_y)
            self.buffer_actual_rate_x.append(self.last_actual_x)
            self.buffer_actual_rate_y.append(self.last_actual_y)

            # Check if buffer just became full
            if self.is_buffer_full_rate() and not self.rate_buffer_full:
                self.rate_buffer_full = True
                self.last_rate_analysis_time = time.time()

    def case_stab(self):
        """Handle stabilize mode data collection"""
        if self.should_collect_data(self.is_buffer_full_stab() or self.is_buffer_full_rate()):
            self.buffer_desired_stab_x.append(self.last_desired_stab_x)
            self.buffer_desired_stab_y.append(self.last_desired_stab_y)
            self.buffer_euler_angles_roll.append(self.last_euler_angles_roll)
            self.buffer_euler_angles_pitch.append(self.last_euler_angles_pitch)

            # Check if buffer just became full
            if self.is_buffer_full_stab() and not self.stab_buffer_full:
                self.stab_buffer_full = True
                self.last_stab_analysis_time = time.time()

    def case_switcher(self) -> DroneMode:
        """Switch between different drone modes and handle data collection"""
        if self.is_drone_armed:
            match self.drone_mode:
                case DroneMode.MODE_RATE:
                    self.case_rate()
                case DroneMode.MODE_STABILIZE:
                    self.case_stab()
            return self.drone_mode

    def get_rate_data(self):
        """Get rate control data for analysis"""
        return {
            'desired_x': list(self.buffer_desired_rate_x),
            'desired_y': list(self.buffer_desired_rate_y),
            'actual_x': list(self.buffer_actual_rate_x),
            'actual_y': list(self.buffer_actual_rate_y),
            'is_full': self.rate_buffer_full,
            'is_armed': self.is_drone_armed
        }

    def get_stab_data(self):
        """Get stabilize control data for analysis"""
        return {
            'desired_x': list(self.buffer_desired_stab_x),
            'desired_y': list(self.buffer_desired_stab_y),
            'actual_roll': list(self.buffer_euler_angles_roll),
            'actual_pitch': list(self.buffer_euler_angles_pitch),
            'is_full': self.stab_buffer_full,
            'is_armed': self.is_drone_armed
        }


class REPLAY_BUFFER(Node):

    def __init__(self, buffer_time=5, wait_time=3, data_hz=100):
        super().__init__('replay_buffer')

        # Initialize the data buffer and analyzer
        self.data_buffer = DataBuffer(buffer_time, wait_time, data_hz)

    def main_loop(self):
        drone_mode = self.data_buffer.case_switcher()
        match drone_mode:
            case DroneMode.MODE_RATE:
                rate_data = self.data_buffer.get_rate_data()
                print(rate_data)
            case DroneMode.MODE_STABILIZE:
                stab_data = self.data_buffer.get_stab_data()
                print(stab_data)


def main(args=None):
    rclpy.init(args=args)
    node = REPLAY_BUFFER()
    print(node.get_rate_data())
    thread = threading.Thread(target=node.main_loop)
    thread.start()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        print("\nShutting down...")
    rclpy.shutdown()


if __name__ == '__main__':
    main()
