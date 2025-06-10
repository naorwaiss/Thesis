#!/usr/bin/env python3

import struct
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Imu, MagneticField
from std_msgs.msg import Float32MultiArray, Int32MultiArray
from geometry_msgs.msg import Quaternion, PoseWithCovariance, TwistWithCovariance  # Import Twist message
from nav_msgs.msg import Odometry

from ground_bot.msg import Pwm,MotorData,RollerData
from rtcom import *

FLOAT_SIZE = struct.calcsize('f')
INT_SIZE = struct.calcsize('i')

class UDPSocketClient(Node):
    def __init__(self):
        super().__init__('udp_socket_client')
        self.client = RTComClient()
        self.client.connect(address=('192.168.1.177', 8888), reconnect=True, block=True)

        # Define ROS 2 Publishers
        
        self.linear_dot_pub = self.create_publisher(MotorData, 'linear_velo', 10)
        self.wheel_rotation_speed_pwm = self.create_publisher(MotorData, 'imu_filter', 10)
        self.motor_pwm_pub = self.create_publisher(Pwm, 'gnd_bot_pwm', 10)
        self.roller_data_pub = self.create_publisher(RollerData, 'roller_data', 10)
        self.odom_pub = self.create_publisher(Odometry, 'odom', 10)
        self.imu_pub = self.create_publisher(Imu, 'imu_data', 10)



        # Register callbacks for each message type using RTComClient's `on` method
        self.client.on('L', self.linear_dot)
        self.client.on('O', self.wheel_rotation_speed)
        self.client.on('P', self.motor_pwm)
        self.client.on('T', self.odom)
        self.client.on('r', self.roller_data)



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

    def roller_data(self, message: bytes):
        print("roller_data", message)
        messages_struct_float = struct.unpack("f" * (len(message) // FLOAT_SIZE), message)
        roller_data = RollerData()
        roller_data.tension = messages_struct_float[0]
        roller_data.dis_tension = messages_struct_float[1]
        roller_data.error = messages_struct_float[2]
        roller_data.error_sum = messages_struct_float[3]
        self.roller_data_pub.publish(roller_data)

    def imu_data(self,message: bytes):
        messages_struct_float = struct.unpack("f" * (len(message) // FLOAT_SIZE), message)
        imu_data= Imu()
        imu_data.linear_acceleration.x = messages_struct_float[0]
        imu_data.linear_acceleration.y = messages_struct_float[1]
        imu_data.linear_acceleration.z = messages_struct_float[2]
        imu_data.angular_velocity.x = messages_struct_float[3]
        imu_data.angular_velocity.y = messages_struct_float[4]
        imu_data.angular_velocity.z = messages_struct_float[5]
        imu_data.orientation.x = messages_struct_float[6]
        imu_data.orientation.y = messages_struct_float[7]
        imu_data.orientation.z = messages_struct_float[8]
        imu_data.orientation.w = messages_struct_float[9]
        self.imu_pub.publish(imu_data)









def main(args=None):
    rclpy.init(args=args)
    client = UDPSocketClient()
    rclpy.spin(client)  # Spin the ROS node
    client.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()
