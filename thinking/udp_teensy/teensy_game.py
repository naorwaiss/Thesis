
import socket
import struct
import threading


class TeensyClient:
    def __init__(self, ip, port):
        """
        Initializes the client with the given IP and port for socket communication.
        """
        self.ip = ip
        self.port = port
        self.client_socket = None
        self.receive_thread = None
        self.running = False

        # Connect to Teensy server on initialization
        self.connect()

    def connect(self):
        """
        Connects to the Teensy server.
        """
        try:
            self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.client_socket.connect((self.ip, self.port))
            self.running = True
            print(f"Connected to Teensy server at {self.ip}:{self.port}")
            self.start_receiving()
        except Exception as e:
            print(f"Error connecting to the server: {e}")
            self.client_socket = None

    def start_receiving(self):
        """
        Starts a new thread to receive messages from the server.
        """
        self.receive_thread = threading.Thread(target=self.receive_messages)
        self.receive_thread.start()

    def receive_messages(self):
        """
        Receives messages from the server.
        """
        while self.running:
            try:
                # Read the message length (4 bytes, big-endian)
                length_bytes = self.client_socket.recv(4)
                if length_bytes:
                    message_length = struct.unpack('<I', length_bytes)[0]
                    print(message_length)
                    # Read the message data based on the length
                    message = self.client_socket.recv(message_length).decode('utf-8')
                    print(f"Received message: {message}")
                else:
                    # No data received, connection might be closed
                    print("Server closed the connection.")
                    self.running = False
            except Exception as e:
                print(f"Error receiving message: {e}")
                self.running = False

    def close(self):
        """
        Closes the connection to the Teensy server.
        """
        self.running = False
        if self.client_socket:
            self.client_socket.close()
            self.client_socket = None
            print("Connection closed.")
        if self.receive_thread:
            self.receive_thread.join()




    def send_message(self, message):
        """
        Sends a message to the Teensy server (need to incode all the massages)
        """
        if self.client_socket:
            try:
                # Convert the message to bytes
                message_bytes = message.encode('utf-8')
                # Calculate the length of the message
                message_length = len(message_bytes)
                # Pack the length into 4 bytes (big-endian format)
                length_prefix = struct.pack('>I', message_length)
                # Send the length prefix followed by the actual message
                self.client_socket.sendall(length_prefix + message_bytes)
                print(f"Sent message: Length = {message_length}, Data = {message_bytes}")
            except Exception as e:
                print(f"Error sending message: {e}")
        else:
            print("Not connected to the server.")


def main():
    # Configuration
    teensy_ip = "192.168.1.177"  # IP of the Teensy
    teensy_port = 5000           # Port of the Teensy

    # Create TeensyClient instance
    client = TeensyClient(teensy_ip, teensy_port)

    try:
        while True:
            # Prompt the user to enter a message
            message = input("Enter a message to send to Teensy (or type 'exit' to quit): ")
            if message.lower() == "exit":
                print("Exiting...")
                break

            # Send the formatted message to Teensy
            client.send_message(message)
    except KeyboardInterrupt:
        print("Shutting down.")
    finally:
        # Ensure proper cleanup
        client.close()


if __name__ == "__main__":
    main()
