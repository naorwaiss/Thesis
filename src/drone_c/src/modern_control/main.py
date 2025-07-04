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

        # Buffer state tracking
        self.rate_buffer_full = False
        self.stab_buffer_full = False
        self.last_rate_analysis_time = None
        self.last_stab_analysis_time = None

        # Threading control
        self.wait_thread = None
        self.wait_thread_active = False
        self.data_take = Take_data.TAKE

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
        
        # Timer thread management
        self.timer_thread = None
        self.timer_active = False

    def clear_buffer_rate(self):
        self.buffer_desired_rate_x.clear()
        self.buffer_desired_rate_y.clear()
        self.buffer_actual_rate_x.clear()
        self.buffer_actual_rate_y.clear()
    
    def clear_buffer_stab(self):
        self.buffer_desired_stab_x.clear()
        self.buffer_desired_stab_y.clear()
        self.buffer_euler_angles_pitch.clear()
        self.buffer_euler_angles_roll.clear()

    def check_full_rate(self) -> Take_data:
        length = self.buffer_time * self.data_hz
        if len(self.buffer_desired_rate_x) == length or len(self.buffer_desired_rate_y) == length or len(self.buffer_actual_rate_x) == length or len(self.buffer_actual_rate_y) == length:
            self.clear_buffer_rate()
            return Take_data.DONT_TAKE
        else:
            return Take_data.TAKE

    def check_full_stab(self) -> Take_data:
        length = self.buffer_time * self.data_hz
        if len(self.buffer_desired_stab_x) == length or len(self.buffer_desired_stab_y) == length or len(self.buffer_euler_angles_roll) == length or len(self.buffer_euler_angles_pitch) == length:
            self.clear_buffer_stab()
            return Take_data.DONT_TAKE
        else:
            return Take_data.TAKE

    def case_rate(self):
        self.buffer_desired_rate_x.append(self.last_desired_rate_x)
        self.buffer_desired_rate_y.append(self.last_desired_rate_y)
        self.buffer_actual_rate_x.append(self.last_actual_x)
        self.buffer_actual_rate_x.append(self.last_actual_y)

    def case_stab(self):
        self.buffer_desired_stab_x.append(self.last_desired_stab_x)
        self.buffer_desired_stab_y.append(self.last_desired_stab_y)
        self.buffer_euler_angles_pitch.append(self.last_euler_angles_pitch)
        self.buffer_euler_angles_roll.append(self.last_euler_angles_roll)
        
    def time_buffer_control(self):
        """Timer thread function that waits for buffer_time seconds then resets data_take"""
        time.sleep(self.buffer_time)
        if self.timer_active:  # Only execute if timer is still active
            self.clear_buffer_rate()
            self.clear_buffer_stab()
            self.data_take = Take_data.TAKE
            print("Timer finished - cleared the data and resumed data collection")
            self.timer_active = False
            self.timer_thread = None

    def start_timer(self):
        """Start the timer thread if not already running"""
        if not self.timer_active and self.timer_thread is None:
            self.timer_active = True
            self.timer_thread = threading.Thread(target=self.time_buffer_control, daemon=True)
            self.timer_thread.start()
            print(f"Started timer for {self.buffer_time} seconds")

    def case_switcher(self):
        """Switch between different drone modes and handle data collection"""

        if self.data_take == Take_data.DONT_TAKE:
            self.start_timer()
            return

        match self.drone_mode:
            case DroneMode.MODE_RATE:
                self.data_take = self.check_full_rate()
                self.case_rate()
            case DroneMode.MODE_STABILIZE:
                self.data_take = self.check_full_stab()
                self.case_rate()
                self.case_stab()

    def run(self):
        """Run the case_switcher at the specified frequency (data_hz)"""
        rate = self.create_rate(self.data_hz)  # Create a rate object for 50 Hz
        while rclpy.ok():
            self.case_switcher()
            rate.sleep()  # Sleep to maintain the specified frequency
    
    def cleanup(self):
        """Clean up threads and resources"""
        self.timer_active = False
        if self.timer_thread and self.timer_thread.is_alive():
            self.timer_thread.join(timeout=1.0)  # Wait up to 1 second for thread to finish
            if self.timer_thread.is_alive():
                print("Warning: Timer thread did not finish within timeout")
        print("Cleanup completed")


def main(args=None):
    rclpy.init(args=args)
    buffer_manager = make_buffer()
    thread = threading.Thread(target=buffer_manager.run)
    thread.start()
    try:
        rclpy.spin(buffer_manager)
    except KeyboardInterrupt:
        print("\nShutting down...")
        buffer_manager.cleanup()
    finally:
        rclpy.shutdown()


if __name__ == '__main__':
    main()
