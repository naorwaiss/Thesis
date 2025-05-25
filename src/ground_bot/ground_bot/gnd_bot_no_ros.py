#!/usr/bin/env python3

import struct
import rclpy
from rclpy.node import Node
from rtcom import *

FLOAT_SIZE = struct.calcsize('f')
INT_SIZE = struct.calcsize('i')

class UDPSocketClient(Node):
    def __init__(self):
        super().__init__('udp_socket_client')
        self.client = RTComClient()
        self.client.connect(address=('192.168.1.177', 8888), reconnect=True, block=True)

        self.client.on('r', self.roller_data)


    def roller_data(self, message: bytes):
        messages_struct_float = struct.unpack("f" * (len(message) // FLOAT_SIZE), message)
        tension = messages_struct_float[0]
        dis_tension = messages_struct_float[1]
        error = messages_struct_float[2]
        error_sum = messages_struct_float[3]
        print("tension: ", tension)
        print("dis_tension: ", dis_tension)
        print("error: ", error)
        print("error_sum: ", error_sum)
        print("--------------------------------")




def main(args=None):
    rclpy.init(args=args)
    client = UDPSocketClient()
    rclpy.spin(client)  # Spin the ROS node
    client.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()
