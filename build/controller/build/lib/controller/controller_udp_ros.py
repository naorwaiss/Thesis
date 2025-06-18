from rclpy.node import Node
import rclpy
from controller.rtcom import RTComClient
from sensor_msgs.msg import Joy
from rclpy.qos import QoSProfile
import struct

class ControllerUdpRos(Node):
    def __init__(self):
        super().__init__('controller_udp_ros')
        self.client = RTComClient()
        self.sub_controller = self.create_subscription(Joy, 'joy', self.controller_callback, 10)
        self.client.connect(address=('192.168.1.199', 8888), reconnect=True, block=True)

    def controller_callback(self, msg: Joy):
        # Convert Joy message to bytes
        axes_bytes = struct.pack('f' * len(msg.axes), *msg.axes)
        buttons_bytes = struct.pack('f' * len(msg.buttons), *msg.buttons)
        print(axes_bytes)
        print(buttons_bytes)
        data = axes_bytes + buttons_bytes
        self.client.emit_typed(data,'j')
        # Send the data to the server
def main(args=None):
    rclpy.init(args=args)
    controller_udp_ros = ControllerUdpRos()
    rclpy.spin(controller_udp_ros)
    controller_udp_ros.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()