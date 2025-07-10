#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Imu
import math

class ImuSubscriber(Node):
    def __init__(self):
        super().__init__('imu_subscriber')
        
        # Create subscription to imu_data topic
        self.subscription = self.create_subscription(
            Imu,
            'imu_data',
            self.imu_callback,
            10
        )
        
        self.get_logger().info('IMU Subscriber started - listening to imu_data topic')

    def imu_callback(self, msg):
        """Callback function that processes incoming IMU messages"""
        
        # Extract linear acceleration (m/s²)
        accel_x = msg.linear_acceleration.x
        accel_y = msg.linear_acceleration.y
        accel_z = msg.linear_acceleration.z
        
        # Extract angular velocity (rad/s)
        gyro_x = msg.angular_velocity.x
        gyro_y = msg.angular_velocity.y
        gyro_z = msg.angular_velocity.z
        
        # Extract orientation (quaternion)
        quat_x = msg.orientation.x
        quat_y = msg.orientation.y
        quat_z = msg.orientation.z
        quat_w = msg.orientation.w
        
        # Convert quaternion to Euler angles (simplified conversion)
        # Roll (x-axis rotation)
        roll = math.atan2(2 * (quat_w * quat_x + quat_y * quat_z), 
                          1 - 2 * (quat_x * quat_x + quat_y * quat_y))
        
        # Pitch (y-axis rotation)
        pitch = math.asin(2 * (quat_w * quat_y - quat_z * quat_x))
        
        # Yaw (z-axis rotation)
        yaw = math.atan2(2 * (quat_w * quat_z + quat_x * quat_y), 
                         1 - 2 * (quat_y * quat_y + quat_z * quat_z))
        
        # Convert to degrees
        roll_deg = math.degrees(roll)
        pitch_deg = math.degrees(pitch)
        yaw_deg = math.degrees(yaw)
        
        # Print the data
        self.get_logger().info(
            f'IMU Data:\n'
            f'  Acceleration (m/s²): X={accel_x:.3f}, Y={accel_y:.3f}, Z={accel_z:.3f}\n'
            f'  Angular Velocity (rad/s): X={gyro_x:.3f}, Y={gyro_y:.3f}, Z={gyro_z:.3f}\n'
            f'  Orientation (quaternion): X={quat_x:.3f}, Y={quat_y:.3f}, Z={quat_z:.3f}, W={quat_w:.3f}\n'
            f'  Euler Angles (deg): Roll={roll_deg:.2f}, Pitch={pitch_deg:.2f}, Yaw={yaw_deg:.2f}'
        )

def main(args=None):
    rclpy.init(args=args)
    
    imu_subscriber = ImuSubscriber()
    
    try:
        rclpy.spin(imu_subscriber)
    except KeyboardInterrupt:
        pass
    finally:
        imu_subscriber.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main() 