import socket
import struct
import threading
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Joy
from queue import Queue, Empty

class TeensyClient(Node):
    def __init__(self, ip, port):
        super().__init__('joy_listener')
        self.subscription = self.create_subscription(
            Joy,
            'joy',
            self.joy_callback,
            10)
        self.subscription  # prevent unused variable warning

        self.ip = ip
        self.port = port
        self.client_socket = None
        self.receive_thread = None
        self.process_thread = None
        self.joy_queue = Queue()
        self.running = True

        # Connect to Teensy server on initialization
        self.connect()
        self.start_process_thread()

    def joy_callback(self, msg):
        # Non-blocking queue to handle joy data
        self.joy_queue.put(msg)

    def start_process_thread(self):
        """Starts a thread to process joy data and manage network communication."""
        self.process_thread = threading.Thread(target=self.process_data)
        self.process_thread.start()

    def process_data(self):
        """Processes data from the joy_queue and handles network communication."""
        while self.running:
            try:
                joy_msg = self.joy_queue.get(timeout=1)  # Adjust timeout as needed
                self.handle_joy_data(joy_msg)
            except Empty:
                continue  # Continue loop if no joy data is available

    def handle_joy_data(self, joy_msg):
        """Logs and potentially sends joy data over the network."""
        # self.get_logger().info('Received joy data: Axes %s Buttons %s' % (joy_msg.axes, joy_msg.buttons))
        
        # Example: Convert joy_msg to a string and send via network
        message = f"{joy_msg.axes},{joy_msg.buttons}"
        self.send_message(message)

    def connect(self):
        try:
            self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.client_socket.settimeout(1)  # Non-blocking socket
            self.client_socket.connect((self.ip, self.port))
            print(f"Connected to Teensy server at {self.ip}:{self.port}")
            self.start_receiving()
        except Exception as e:
            print(f"Error connecting to the server: {e}")
            self.client_socket = None

    def start_receiving(self):
        """Starts a thread for receiving data from the network."""
        self.receive_thread = threading.Thread(target=self.receive_messages)
        self.receive_thread.start()

    def receive_messages(self):
        """Non-blocking receive method for network data."""
        while self.running:
            try:
                length_bytes = self.client_socket.recv(4)
                if length_bytes:
                    message_length = struct.unpack('<I', length_bytes)[0]
                    message = self.client_socket.recv(message_length).decode('utf-8')
                    print(f"Received message: {message}")
                else:
                    print("Server closed the connection.")
                    self.running = False
            except socket.timeout:
                continue  # Continue if no data received within the timeout

    def close(self):
        """Closes all network connections and threads."""
        self.running = False
        if self.client_socket:
            self.client_socket.close()
            self.client_socket = None
        self.process_thread.join()
        self.receive_thread.join()

    def send_message(self, message):
        """Sends a message to the server non-blockingly."""
        if self.client_socket:
            try:
                message_bytes = message.encode('utf-8')
                print(message_bytes)
                message_length = len(message_bytes)
                length_prefix = struct.pack('>I', message_length)
                self.client_socket.sendall(length_prefix + message_bytes)
                print(length_prefix + message_bytes)
                # print(f"Sent message: {message}")
            except Exception as e:
                print(f"Error sending message: {e}")

def main():
    rclpy.init()
    client = TeensyClient('192.168.1.177', 5000)
    rclpy.spin(client)
    client.close()
    rclpy.shutdown()

if __name__ == "__main__":
    main()
