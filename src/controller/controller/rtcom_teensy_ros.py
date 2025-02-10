import struct
import rclpy
from rclpy.node import Node
from rtcom import *
from sensor_msgs.msg import Joy

class UDPSocketClient(Node):
    def __init__(self):
        super().__init__('udp_socket_client')
        
        # Initialize RTComClient
        self.client = RTComClient()
        self.client.connect(address=('192.168.1.199', 8888), reconnect=True, block=False)
    
        # Add subscribers for all joysticks
        self.create_subscription(
            Joy,
            '/logitech_gamepad_f710_12',
            lambda msg: self.joystick_callback(msg, 'f710'),
            10
        )
        self.create_subscription(
            Joy,
            '/edgetx_radiomaster_pocket_joystick_27',
            lambda msg: self.joystick_callback(msg, 'radiomaster'),
            10
        )
        self.create_subscription(
            Joy,
            '/logitech_extreme_3d_pro_7',
            lambda msg: self.joystick_callback(msg, 'extreme3d'),
            10
        )
        self.create_subscription(
            Joy,
            '/logitech_gamepad_f310',
            lambda msg: self.joystick_callback(msg, 'f310'),
            10
        )
        
        self.get_logger().info('Subscribed to all joystick topics')


    
    def joystick_callback(self, msg, joystick_type):
        # Log received joystick data with identifier
        self.get_logger().info(f'Received {joystick_type} joystick data: axes={msg.axes}, buttons={msg.buttons}')

        # Pack data with joystick identifier
        identifier = {
            'f710': 'a',
            'radiomaster': 'E',
            'extreme3d': 'J',
            'f310': 'b'
        }.get(joystick_type, 'X')
        
        axes_data = struct.pack(f'8f', *msg.axes[:8])
        buttons_data = struct.pack(f'8i', *msg.buttons[:8])
        data = axes_data+buttons_data
        print(data)
        self.client.emit_typed(data=data, first_byte=identifier)



def main(args=None):
    rclpy.init(args=args)
    client = UDPSocketClient()
    rclpy.spin(client)
    client.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()
