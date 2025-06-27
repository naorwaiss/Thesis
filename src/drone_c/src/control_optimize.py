import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Imu
from std_msgs.msg import Float32MultiArray
from drone_c.msg import EulerAngles,  DroneHeader
from collections import deque
from enum import IntEnum
import time

class DroneMode(IntEnum):
    MODE_RATE = 1
    MODE_STABILIZE = 2

class RateControlMonitor(Node):
    def __init__(self,buffer_time=5 ,wait_time=3, data_hz = 100):
        super().__init__('rate_control_monitor')

        # Buffers
        self.buffer_time = []
        self.buffer_input = []
        self.buffer_output = []
        self.is_drone_armed = None
        self.drone_mode = None
        self.wait_timer = 0
        self.last_buffer_full_time = 0
        self.buffer_delay_active = False
        

        # Subscribers
        # self.create_subscription(Imu, '/imu_data', self.imu_callback, 10)
        self.create_subscription(Float32MultiArray, '/desire_rate', self.desired_rate_callback, 10)
        self.create_subscription(Float32MultiArray, '/desire_stab', self.desired_stab_callback, 10)
        self.create_subscription(Float32MultiArray, '/estimated_rate', self.estimated_rate_callback, 10)
        self.create_subscription(EulerAngles, '/euler_angles_data', self.euler_angles_callback, 10)
        self.create_subscription(DroneHeader, '/drone_header', self.drone_header_callback, 10)

        self.buffer_desired_rate_x = deque(maxlen=buffer_time * data_hz)
        self.buffer_desired_rate_y = deque(maxlen=buffer_time * data_hz)
        self.buffer_actual_rate_x = deque(maxlen=buffer_time * data_hz)
        self.buffer_actual_rate_y = deque(maxlen=buffer_time * data_hz)

    def desired_callback(self, msg: Float32MultiArray):
        self.last_desired_x = msg.data[0] 

    def drone_header_callback(self, msg: DroneHeader):
        self.is_drone_armed = msg.is_armed
        self.drone_mode = msg.drone_mode
    
    def is_buffer_full(self):
        """Check if any of the main data buffers are full"""
        return (len(self.buffer_desired_rate_x) >= self.buffer_desired_rate_x.maxlen or
                len(self.buffer_desired_rate_y) >= self.buffer_desired_rate_y.maxlen or
                len(self.buffer_actual_rate_x) >= self.buffer_actual_rate_x.maxlen or
                len(self.buffer_actual_rate_y) >= self.buffer_actual_rate_y.maxlen)



    def case_rate(self):
        pass
    def case_stab(self):
        pass

    def case_switcher(self):
        if self.is_drone_armed:
            match self.drone_mode:
                case DroneMode.MODE_RATE:
                    self.case_rate()
                case DroneMode.MODE_STABILIZE:
                    self.case_stab()

def main(args=None):
    rclpy.init(args=args)
    node = RateControlMonitor()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    rclpy.shutdown()

if __name__ == '__main__':
    main()
