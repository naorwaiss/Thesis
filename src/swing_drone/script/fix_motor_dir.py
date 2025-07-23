#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, DurabilityPolicy, HistoryPolicy
from std_msgs.msg import Float64MultiArray


class AbsFloatProcessor(Node):
    def __init__(self):
        super().__init__('abs_float_processor')
        self.dir_factor = [1, -1, 1, -1, 1, -1, 1, -1]

        # Create QoS profile compatible with PlotJuggler
        qos_profile = QoSProfile(
            reliability=ReliabilityPolicy.RELIABLE,
            durability=DurabilityPolicy.VOLATILE,
            history=HistoryPolicy.KEEP_LAST,
            depth=10
        )

        # Subscriber to input Float64MultiArray
        self.subscription = self.create_subscription(
            Float64MultiArray,
            '/drone/motor_speed',
            self.float_array_callback,
            qos_profile
        )

        # Publisher for processed Float64MultiArray with compatible QoS
        self.publisher_ = self.create_publisher(
            Float64MultiArray,
            '/propellors/commands',
            qos_profile
        )


    def float_array_callback(self, msg):
        # Create output message
        output_msg = Float64MultiArray()
        output_msg.layout = msg.layout
        output_msg.data = [abs(float_val) for float_val in msg.data]
        if len(output_msg.data) < 8:
            output_msg.data.extend([0.0] * (8 - len(output_msg.data)))
        elif len(output_msg.data) > 8:
            output_msg.data = output_msg.data[:8]
        output_msg.data = [output_msg.data[i] * self.dir_factor[i] for i in range(8)]
        self.publisher_.publish(output_msg)


def main(args=None):
    rclpy.init(args=args)
    node = AbsFloatProcessor()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main() 