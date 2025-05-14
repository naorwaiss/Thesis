import struct
import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32MultiArray
from rtcom import *
import time
import math

FLOAT_SIZE = struct.calcsize('f')
INT_SIZE = struct.calcsize('i')


class UDPSocketClient(Node):
    def __init__(self):
        super().__init__('udp_socket_client')
        self.client = RTComClient()
        time.sleep(0.05)  # Add small delay before connection
        self.client.connect(address=('192.168.1.177', 8888), reconnect=True, block=True)

      
        self.tension_data = self.create_publisher(Float32MultiArray, 'tension_data', 10)

        # Register callbacks for each message type using RTComClient's `on` method
   
        self.client.on('p', self.handle_tension)


    def handle_tension(self, message: bytes):
        messages_struct_float = struct.unpack("f" * (len(message) // FLOAT_SIZE), message)
        tension_msg = Float32MultiArray()
        tension_msg.data = messages_struct_float
        self.tension_data.publish(tension_msg)




def main(args=None):
    rclpy.init(args=args)
    client = UDPSocketClient()
    rclpy.spin(client)  # Spin the ROS node
    client.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
