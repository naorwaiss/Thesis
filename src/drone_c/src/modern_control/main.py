import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Imu
from std_msgs.msg import Float32MultiArray
from drone_c.msg import EulerAngles,  DroneHeader
from collections import deque
from enum import IntEnum
import time
import threading
from src.control import ControlAnalyzer
from src.yaml_operation import *
import glob
import os
import torch


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

        # Use parent class parameters
        self.buffer_size = self.buffer_time * self.data_hz
        yaml_files = glob.glob(os.path.join("**", "config", "data.yaml"), recursive=True)
        if yaml_files:
            yaml_path = yaml_files[0]  # Take the first match
        else:
            yaml_path = os.path.join("config", "data.yaml")  # Fallback/default
        self.yaml_flash = yaml_flash(yaml_path)
        # Buffers as tensors
        self.buffer_desired_rate_x = torch.zeros(self.buffer_size)
        self.buffer_desired_rate_y = torch.zeros(self.buffer_size)
        self.buffer_actual_rate_x = torch.zeros(self.buffer_size)
        self.buffer_actual_rate_y = torch.zeros(self.buffer_size)
        self.buffer_euler_angles_roll = torch.zeros(self.buffer_size)
        self.buffer_euler_angles_pitch = torch.zeros(self.buffer_size)
        self.buffer_desired_stab_x = torch.zeros(self.buffer_size)
        self.buffer_desired_stab_y = torch.zeros(self.buffer_size)
        # Pointers and full flags
        self.full_desired_rate_x = False
        self.full_desired_rate_y = False
        self.full_actual_rate_x = False
        self.full_actual_rate_y = False
        self.full_euler_angles_roll = False
        self.full_euler_angles_pitch = False
        self.full_desired_stab_x = False
        self.full_desired_stab_y = False
        self.control_analyzer_rate_X = ControlAnalyzer(data_hz=self.data_hz)
        self.control_analyzer_rate_Y = ControlAnalyzer(data_hz=self.data_hz)
        self.control_analyzer_stab_X = ControlAnalyzer(data_hz=self.data_hz)
        self.control_analyzer_stab_Y = ControlAnalyzer(data_hz=self.data_hz)

    def _append_tensor(self, tensor, ptr, value, full_flag_name):
        tensor[ptr] = value
        ptr += 1
        if ptr >= self.buffer_size:
            ptr = 0
            setattr(self, full_flag_name, True)
        return ptr

    def clear_buffer_rate(self):
        self.buffer_desired_rate_x.zero_()
        self.buffer_desired_rate_y.zero_()
        self.buffer_actual_rate_x.zero_()
        self.buffer_actual_rate_y.zero_()
        self.ptr_desired_rate_x = 0
        self.ptr_desired_rate_y = 0
        self.ptr_actual_rate_x = 0
        self.ptr_actual_rate_y = 0
        self.full_desired_rate_x = False
        self.full_desired_rate_y = False
        self.full_actual_rate_x = False
        self.full_actual_rate_y = False

    def clear_buffer_stab(self):
        self.buffer_desired_stab_x.zero_()
        self.buffer_desired_stab_y.zero_()
        self.buffer_euler_angles_pitch.zero_()
        self.buffer_euler_angles_roll.zero_()
        self.ptr_desired_stab_x = 0
        self.ptr_desired_stab_y = 0
        self.ptr_euler_angles_pitch = 0
        self.ptr_euler_angles_roll = 0
        self.full_desired_stab_x = False
        self.full_desired_stab_y = False
        self.full_euler_angles_pitch = False
        self.full_euler_angles_roll = False

    def _get_tensor_data(self, tensor, ptr, full):
        if full:
            return torch.cat((tensor[ptr:], tensor[:ptr])).tolist()
        else:
            return tensor[:ptr].tolist()

    def check_full(self) -> Take_data:
        length = self.buffer_size
        # Check based on current drone mode
        if self.drone_mode == DroneMode.MODE_RATE:
            if (self.full_desired_rate_x or self.full_desired_rate_y or self.full_actual_rate_x or self.full_actual_rate_y):
                return Take_data.DONT_TAKE
        elif self.drone_mode == DroneMode.MODE_STABILIZE:
            if (self.full_desired_stab_x or self.full_desired_stab_y or self.full_euler_angles_roll or self.full_euler_angles_pitch or self.full_desired_rate_x or self.full_desired_rate_y or self.full_actual_rate_x or self.full_actual_rate_y):
                return Take_data.DONT_TAKE
        return Take_data.TAKE

    def get_rate_data(self):
        if self.last_desired_rate_x is not None:
            self.ptr_desired_rate_x = self._append_tensor(self.buffer_desired_rate_x, self.ptr_desired_rate_x, self.last_desired_rate_x, 'full_desired_rate_x')
        if self.last_desired_rate_y is not None:
            self.ptr_desired_rate_y = self._append_tensor(self.buffer_desired_rate_y, self.ptr_desired_rate_y, self.last_desired_rate_y, 'full_desired_rate_y')
        if self.last_actual_x is not None:
            self.ptr_actual_rate_x = self._append_tensor(self.buffer_actual_rate_x, self.ptr_actual_rate_x, self.last_actual_x, 'full_actual_rate_x')
        if self.last_actual_y is not None:
            self.ptr_actual_rate_y = self._append_tensor(self.buffer_actual_rate_y, self.ptr_actual_rate_y, self.last_actual_y, 'full_actual_rate_y')

    def get_stab_data(self):
        if self.last_desired_stab_x is not None:
            self.ptr_desired_stab_x = self._append_tensor(self.buffer_desired_stab_x, self.ptr_desired_stab_x, self.last_desired_stab_x, 'full_desired_stab_x')
        if self.last_desired_stab_y is not None:
            self.ptr_desired_stab_y = self._append_tensor(self.buffer_desired_stab_y, self.ptr_desired_stab_y, self.last_desired_stab_y, 'full_desired_stab_y')
        if self.last_euler_angles_pitch is not None:
            self.ptr_euler_angles_pitch = self._append_tensor(self.buffer_euler_angles_pitch, self.ptr_euler_angles_pitch, self.last_euler_angles_pitch, 'full_euler_angles_pitch')
        if self.last_euler_angles_roll is not None:
            self.ptr_euler_angles_roll = self._append_tensor(self.buffer_euler_angles_roll, self.ptr_euler_angles_roll, self.last_euler_angles_roll, 'full_euler_angles_roll')

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
            #when dont have taking data 
            # match self.drone_mode:
            #     case DroneMode.MODE_RATE:
            #         self.yaml_flash_rate()
            #     case DroneMode.MODE_STABILIZE:
            #         self.yaml_flash_stab()
            control_operation_thread = threading.Thread(target=self.control_operation)
            control_operation_thread.start()
            self.start_timer()
            control_operation_thread.join()
            self.data_take = Take_data.TAKE
            return

        if self.is_drone_armed == True and self.data_take == Take_data.TAKE:
            #the drone at arm and i can take the data 
            match self.drone_mode:
                case DroneMode.MODE_RATE:
                    self.get_rate_data()
                    self.data_take = self.check_full()
                case DroneMode.MODE_STABILIZE:
                    self.get_stab_data()
                    self.get_rate_data()
                    self.data_take = self.check_full()
        else:
            print("cleanup the buffer the drone dont armed")
            self.cleanup()


    def control_operation(self):
        match self.drone_mode:
            case DroneMode.MODE_RATE:
                print("Analyzing rate mode data...")
                self.control_analyzer_rate_X.secend_response_Data(
                    self.buffer_desired_rate_x, self.buffer_actual_rate_x, "rate_x")
                self.control_analyzer_rate_Y.secend_response_Data(
                    self.buffer_desired_rate_y, self.buffer_actual_rate_y, "rate_y")
            case DroneMode.MODE_STABILIZE:
                print("Analyzing stabilize mode data...")
                self.control_analyzer_stab_X.secend_response_Data(
                    self.buffer_desired_stab_x, self.buffer_euler_angles_roll, "stab_x")
                self.control_analyzer_stab_Y.secend_response_Data(
                    self.buffer_desired_stab_y, self.buffer_euler_angles_pitch, "stab_y")
                self.control_analyzer_rate_X.secend_response_Data(
                    self.buffer_desired_rate_x, self.buffer_actual_rate_x, "rate_stab_x")
                self.control_analyzer_rate_Y.secend_response_Data(
                    self.buffer_desired_rate_y, self.buffer_actual_rate_y, "rate_stab_y")

    def cleanup(self):
        """Cleanup method for proper shutdown"""
        self.clear_buffer_rate()
        self.clear_buffer_stab()
    
    def yaml_flash_rate(self):
        rate_x_data = self._get_tensor_data(self.buffer_desired_rate_x, self.ptr_desired_rate_x, self.full_desired_rate_x)
        rate_y_data = self._get_tensor_data(self.buffer_desired_rate_y, self.ptr_desired_rate_y, self.full_desired_rate_y)
        print("Flashing rate data to YAML...")
        self.yaml_flash.write_data("rate_x", rate_x_data, len(rate_x_data))
        self.yaml_flash.write_data("rate_y", rate_y_data, len(rate_y_data))
    
    def yaml_flash_stab(self):
        self.yaml_flash_rate()
        stab_x_data = self._get_tensor_data(self.buffer_desired_stab_x, self.ptr_desired_stab_x, self.full_desired_stab_x)
        stab_y_data = self._get_tensor_data(self.buffer_desired_stab_y, self.ptr_desired_stab_y, self.full_desired_stab_y)
        print("Flashing stab data to YAML...")
        self.yaml_flash.write_data("stab_x", stab_x_data, len(stab_x_data))
        self.yaml_flash.write_data("stab_y", stab_y_data, len(stab_y_data))

    def loop(self):
        """Run the case_switcher at the specified frequency (data_hz)"""
        rate = self.create_rate(self.data_hz)  # Create a rate object for 50 Hz
        while rclpy.ok():
            self.case_switcher()
            rate.sleep()  # Sleep to maintain the specified frequency


def main(args=None):
    rclpy.init(args=args)
    buffer_manager = make_buffer()
    thread = threading.Thread(target=buffer_manager.loop)
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
