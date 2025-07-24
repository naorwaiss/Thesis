#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Vector3
from sensor_msgs.msg import Imu
from tf_transformations import euler_from_quaternion
import math


class ImuToEulerNode(Node):
    def __init__(self):
        super().__init__('imu_to_euler_node')

        # Subscriber to Imu
        self.subscription = self.create_subscription(
            Imu,
            '/imu',
            self.imu_callback,
            10
        )

        # Publisher for Euler angles
        self.publisher_ = self.create_publisher(
            Vector3,
            '/swing_drone/euler_angles',
            10
        )

        self.get_logger().info('Imu to Euler node has been started.')

    def imu_callback(self, msg):
        # Extract quaternion
        q = msg.orientation
        quaternion = [q.x, q.y, q.z, q.w]
        roll, pitch, yaw = euler_from_quaternion(quaternion)
        euler_msg = Vector3()
        euler_msg.x = float(roll)
        euler_msg.y = float(pitch)
        euler_msg.z = float(yaw)
        self.publisher_.publish(euler_msg)


def main(args=None):
    rclpy.init(args=args)
    node = ImuToEulerNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
