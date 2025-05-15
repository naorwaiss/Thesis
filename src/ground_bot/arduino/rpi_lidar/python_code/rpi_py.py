import struct
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import LaserScan
from rtcom import *
import time
import numpy as np

FLOAT_SIZE = struct.calcsize('f')
INT_SIZE = struct.calcsize('i')


class UDPSocketClient(Node):
    def __init__(self):
        super().__init__('udp_socket_client')
        self.client = RTComClient()
        time.sleep(0.05)  # Add small delay before connection
        self.client.connect(address=('192.168.1.199', 8888), reconnect=True, block=True)
        self.lidar_pub = self.create_publisher(LaserScan, 'rpi_lidar_data', 10)
        self.client.on('L', self.handle_lidar)            

    # Callback methods for specific message types


def handle_lidar(self, message: bytes):
    messages_struct_float = struct.unpack("ff", message)
    angle = messages_struct_float[0]
    distance = messages_struct_float[1]

    angle = angle % (2 * np.pi)
    index = int(angle / (np.pi / 360))
    if 0 <= index < self.num_bins:
        self.ranges[index] = distance
    lidar_msg = LaserScan()
    lidar_msg.header.stamp = self.get_clock().now().to_msg()
    lidar_msg.header.frame_id = 'lidar_frame'
    lidar_msg.angle_min = 0.0
    lidar_msg.angle_max = 2 * np.pi
    lidar_msg.range_min = 0.1
    lidar_msg.range_max = 12.0
    lidar_msg.angle_increment = np.pi / 360
    lidar_msg.ranges = self.ranges
    self.lidar_pub.publish(lidar_msg)


def main(args=None):
    rclpy.init(args=args)
    client = UDPSocketClient()
    rclpy.spin(client)  # Spin the ROS node
    client.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
