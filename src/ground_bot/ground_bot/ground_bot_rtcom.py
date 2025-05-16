#!/usr/bin/env python3

import struct
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Imu, MagneticField
from std_msgs.msg import Float32MultiArray, Int32MultiArray
from geometry_msgs.msg import Quaternion, PoseWithCovariance, TwistWithCovariance  # Import Twist message
from nav_msgs.msg import Odometry

from ground_bot.msg import Pwm,MotorData
from ground_bot.rtcom import *

FLOAT_SIZE = struct.calcsize('f')
INT_SIZE = struct.calcsize('i')

class UDPSocketClient(Node):
    def __init__(self):
        super().__init__('udp_socket_client')
        self.client = RTComClient()
        self.client.connect(address=('192.168.1.198', 8888), reconnect=True, block=True)

        # Define ROS 2 Publishers
        self.linear_dot_pub = self.create_publisher(MotorData, 'linear_velo', 10)
        self.wheel_rotation_speed_pwm = self.create_publisher(MotorData, 'imu_filter', 10)
        self.motor_pwm_pub = self.create_publisher(Pwm, 'gnd_bot_pwm', 10)
        self.odom_pub = self.create_publisher(Odometry, 'odom', 10)


        # Register callbacks for each message type using RTComClient's `on` method
        self.client.on('L', self.linear_dot)
        self.client.on('O', self.wheel_rotation_speed)
        self.client.on('P', self.motor_pwm)
        self.client.on('T', self.odom)


    def linear_dot(self, message: bytes):
        messages_struct_float = struct.unpack("f" * (len(message) // FLOAT_SIZE), message)
        linear_velo = MotorData()
        linear_velo.left_motor = messages_struct_float[0]
        linear_velo.right_motor = messages_struct_float[1]
        self.linear_dot_pub.publish(linear_velo)


    def motor_pwm(self, message: bytes):
        message_struct_int = struct.unpack("i" * (len(message) // INT_SIZE), message)
        pwm_data = Pwm()
        pwm_data.pwm_left_motor = message_struct_int[0]
        pwm_data.pwm_right_motor = message_struct_int[1]

        self.motor_pwm_pub.publish(pwm_data)

  
    def wheel_rotation_speed(self, message: bytes):
        messages_struct_float = struct.unpack("f" * (len(message) // FLOAT_SIZE), message)
        omega_speed = MotorData()
        omega_speed.left_motor = messages_struct_float[0]
        omega_speed.right_motor = messages_struct_float[1]
        self.wheel_rotation_speed_pwm.publish(omega_speed)

    def odom(self, message: bytes):
        messages_struct_float = struct.unpack("f" * (len(message) // FLOAT_SIZE), message)
        odom = Odometry()
        odom.pose.pose.position.x = messages_struct_float[0]
        odom.pose.pose.position.y = messages_struct_float[1]
        odom.pose.pose.position.z = messages_struct_float[2]
        odom.twist.twist.linear.x = messages_struct_float[3]
        odom.twist.twist.angular.z = messages_struct_float[4]
        self.odom_pub.publish(odom)


def main(args=None):
    rclpy.init(args=args)
    client = UDPSocketClient()
    rclpy.spin(client)  # Spin the ROS node
    client.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()
