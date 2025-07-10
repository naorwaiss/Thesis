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

        self.accel_x_tuple = [0.0, 0]  # [sum, count]
        self.accel_y_tuple = [0.0, 0]
        self.accel_z_tuple = [0.0, 0]
        self.gyro_x_tuple = [0.0, 0]
        self.gyro_y_tuple = [0.0, 0]
        self.gyro_z_tuple = [0.0, 0]

    def imu_callback(self, msg):
        """Callback function that processes incoming IMU messages"""
        
        # Extract linear acceleration (m/s²)
        self.accel_x = msg.linear_acceleration.x
        self.accel_y = msg.linear_acceleration.y
        self.accel_z = msg.linear_acceleration.z
        
        # Extract angular velocity (rad/s)
        self.gyro_x = msg.angular_velocity.x
        self.gyro_y = msg.angular_velocity.y
        self.gyro_z = msg.angular_velocity.z

        print(f"accel_x: {self.find_data(self.accel_x, self.accel_x_tuple)}")
        print(f"accel_y: {self.find_data(self.accel_y, self.accel_y_tuple)}")
        print(f"accel_z: {self.find_data(self.accel_z, self.accel_z_tuple)}")
        print(f"gyro_x: {self.find_data(self.gyro_x, self.gyro_x_tuple)}")
        print(f"gyro_y: {self.find_data(self.gyro_y, self.gyro_y_tuple)}")
        print(f"gyro_z: {self.find_data(self.gyro_z, self.gyro_z_tuple)}")
    
    def find_data(self, data, tuple_data):
        tuple_data[0] += data
        tuple_data[1] += 1
        return tuple_data[0] / tuple_data[1]

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