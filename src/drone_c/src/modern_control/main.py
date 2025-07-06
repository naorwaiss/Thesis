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
from src.control import ControlAnalyzer


class DroneMode(IntEnum):
    MODE_RATE = 1
    MODE_STABILIZE = 2


class Take_data(IntEnum):
    TAKE = 1
    DONT_TAKE = 2


class DataBuffer(Node):
    """Class responsible for data collection and buffer management"""

    def __init__(self, buffer_time=10, wait_time=3, data_hz=50):
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
        self.last_desired_rate_x = None
        self.last_desired_rate_y = None
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
    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        # Extract parameters for local use
        buffer_time = kwargs.get('buffer_time', 5)
        data_hz = kwargs.get('data_hz', 50)

        self.buffer_desired_rate_x = deque(maxlen=buffer_time * data_hz)
        self.buffer_desired_rate_y = deque(maxlen=buffer_time * data_hz)
        self.buffer_actual_rate_x = deque(maxlen=buffer_time * data_hz)
        self.buffer_actual_rate_y = deque(maxlen=buffer_time * data_hz)
        self.buffer_euler_angles_roll = deque(maxlen=buffer_time * data_hz)
        self.buffer_euler_angles_pitch = deque(maxlen=buffer_time * data_hz)
        self.buffer_desired_stab_x = deque(maxlen=buffer_time * data_hz)
        self.buffer_desired_stab_y = deque(maxlen=buffer_time * data_hz)

        self.control_analyzer_rate_X = ControlAnalyzer(data_hz=data_hz)
        self.control_analyzer_rate_Y = ControlAnalyzer(data_hz=data_hz)
        self.control_analyzer_stab_X = ControlAnalyzer(data_hz=data_hz)
        self.control_analyzer_stab_Y = ControlAnalyzer(data_hz=data_hz)

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

    def check_full(self) -> Take_data:
        length = self.buffer_time * self.data_hz

        # Check based on current drone mode
        if self.drone_mode == DroneMode.MODE_RATE:
            # For rate mode, check rate buffers
            if (len(self.buffer_desired_rate_x) == length or
                len(self.buffer_desired_rate_y) == length or
                len(self.buffer_actual_rate_x) == length or
                    len(self.buffer_actual_rate_y) == length):
                return Take_data.DONT_TAKE
        elif self.drone_mode == DroneMode.MODE_STABILIZE:
            # For stabilize mode, check both stab and rate buffers
            if (len(self.buffer_desired_stab_x) == length or
                len(self.buffer_desired_stab_y) == length or
                len(self.buffer_euler_angles_roll) == length or
                len(self.buffer_euler_angles_pitch) == length or
                len(self.buffer_desired_rate_x) == length or
                len(self.buffer_desired_rate_y) == length or
                len(self.buffer_actual_rate_x) == length or
                    len(self.buffer_actual_rate_y) == length):
                return Take_data.DONT_TAKE

        return Take_data.TAKE

    def get_rate_data(self):
        if self.last_desired_rate_x is not None:
            self.buffer_desired_rate_x.append(self.last_desired_rate_x)
        if self.last_desired_rate_y is not None:
            self.buffer_desired_rate_y.append(self.last_desired_rate_y)
        if self.last_actual_x is not None:
            self.buffer_actual_rate_x.append(self.last_actual_x)
        if self.last_actual_y is not None:
            self.buffer_actual_rate_y.append(self.last_actual_y)

    def get_stab_data(self):
        if self.last_desired_stab_x is not None:
            self.buffer_desired_stab_x.append(self.last_desired_stab_x)
        if self.last_desired_stab_y is not None:
            self.buffer_desired_stab_y.append(self.last_desired_stab_y)
        if self.last_euler_angles_pitch is not None:
            self.buffer_euler_angles_pitch.append(self.last_euler_angles_pitch)
        if self.last_euler_angles_roll is not None:
            self.buffer_euler_angles_roll.append(self.last_euler_angles_roll)

    def start_timer(self):
        print("start timer")
        timer = time.time()
        while time.time() - timer < self.buffer_time:
            time.sleep(0.01)
        self.cleanup()
        self.data_take = Take_data.TAKE

    def case_switcher(self):
        """Switch between different drone modes and handle data collection"""
        if self.data_take == Take_data.DONT_TAKE:
            control_operation_thread = threading.Thread(target=self.control_operation)
            control_operation_thread.start()
            self.start_timer()
            control_operation_thread.join()
            self.data_take = Take_data.TAKE
            return

        match self.drone_mode:
            case DroneMode.MODE_RATE:
                self.get_rate_data()
                self.data_take = self.check_full()
            case DroneMode.MODE_STABILIZE:
                self.get_stab_data()
                self.get_rate_data()
                self.data_take = self.check_full()

    def run(self):
        """Run the case_switcher at the specified frequency (data_hz)"""
        rate = self.create_rate(self.data_hz)  # Create a rate object for 50 Hz
        while rclpy.ok():
            self.case_switcher()
            rate.sleep()  # Sleep to maintain the specified frequency

    def control_operation(self):
        match self.drone_mode:
            case DroneMode.MODE_RATE:
                self.control_analyzer_rate_X.analyze_step_response(
                    self.buffer_desired_rate_x, self.buffer_actual_rate_x, "rate_x")
                self.control_analyzer_rate_Y.analyze_step_response(
                    self.buffer_desired_rate_y, self.buffer_actual_rate_y, "rate_y")
            case DroneMode.MODE_STABILIZE:
                self.control_analyzer_stab_X.analyze_step_response(
                    self.buffer_desired_stab_x, self.buffer_euler_angles_roll, "stab_x")
                self.control_analyzer_stab_Y.analyze_step_response(
                    self.buffer_desired_stab_y, self.buffer_euler_angles_pitch, "stab_y")
                self.control_analyzer_rate_X.analyze_step_response(
                    self.buffer_desired_rate_x, self.buffer_actual_rate_x, "rate_stab_x")
                self.control_analyzer_rate_Y.analyze_step_response(
                    self.buffer_desired_rate_y, self.buffer_actual_rate_y, "rate_stab_y")

    def cleanup(self):
        """Cleanup method for proper shutdown"""
        print("Cleaning up buffers...")
        self.clear_buffer_rate()
        self.clear_buffer_stab()
        print("Cleanup complete.")


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
