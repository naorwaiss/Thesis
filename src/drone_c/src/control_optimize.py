import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Imu
from std_msgs.msg import Float32MultiArray, Int32MultiArray



import time

class RateControlMonitor(Node):
    def __init__(self):
        super().__init__('rate_control_monitor')

        # Buffers
        self.buffer_time = []
        self.buffer_input = []
        self.buffer_output = []

        self.last_desired_x = None

        # Subscribers
        self.create_subscription(Imu, '/imu_data', self.imu_callback, 10)
        self.create_subscription(Float32MultiArray, '/desire_rate', self.desired_callback, 10)

    def desired_callback(self, msg: Float32MultiArray):
        # Store latest desired rate (input)
        self.last_desired_x = msg.data[0] 

    def imu_callback(self, msg: Imu):
        if self.last_desired is None:
            return  # Wait for desired data

        # Get timestamp and values
        timestamp = self.get_clock().now().nanoseconds * 1e-9
        desired_rate = self.last_desired_x
        measured_rate = msg.angular_velocity.x

        self.buffer_time.append(timestamp)
        self.buffer_input.append(desired_rate)
        self.buffer_output.append(measured_rate)
        window = 3.0
        
        while self.buffer_time and (timestamp - self.buffer_time[0]) > window:
            self.buffer_time.pop(0)
            self.buffer_input.pop(0)
            self.buffer_output.pop(0)

        # Here you can run system identification or monitoring
        self.get_logger().info(f't={timestamp:.2f}s | Desired: {desired_rate:.2f}, Measured: {measured_rate:.2f}')

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
