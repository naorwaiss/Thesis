import struct
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Imu, MagneticField
from std_msgs.msg import Float32MultiArray, Int32MultiArray
from geometry_msgs.msg import Quaternion
from drone_c.msg import Pid, Motors, EulerAngles, ImuFilter, PidConsts
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
        self.client.connect(address=('192.168.1.199', 8888), reconnect=True, block=True)

        # Define ROS 2 Publishers
        self.mag_pub = self.create_publisher(MagneticField, 'magnetometer_data', 10)
        self.quaternion_pub = self.create_publisher(Quaternion, 'quaternion_data', 10)
        self.euler_pub = self.create_publisher(EulerAngles, 'euler_angles_data', 10)
        self.imu_pub_pololu = self.create_publisher(Imu, 'pololu_imu_data', 10)
        self.rc_pub = self.create_publisher(Int32MultiArray, 'rc_channel_data', 10)
        self.desire_rate_pub = self.create_publisher(Float32MultiArray, 'desire_rate', 10)
        self.desire_stab_pub = self.create_publisher(Float32MultiArray, 'desire_stab', 10)
        self.motor_pwm_pub = self.create_publisher(Motors, 'motor_pwm', 10)
        self.estimated_rate_pub = self.create_publisher(Float32MultiArray, 'estimated_rate', 10)
        self.PID_stab_pub_modifide = self.create_publisher(Pid, 'PID_stab', 10)
        self.PID_rate_pub_modifide = self.create_publisher(Pid, 'PID_rate', 10)
        self.Imu_Filter_Pub = self.create_publisher(ImuFilter, 'imu_filter', 10)
        self.Pid_consts_pub = self.create_publisher(PidConsts, 'pid_loaded', 10)

        # Register callbacks for each message type using RTComClient's `on` method
        self.client.on('a', self.handle_magnetometer)
        self.client.on('b', self.handle_imu)
        self.client.on('c', self.handel_imu_filter)
        self.client.on('d', self.handle_euler)
        self.client.on('e', self.handle_rc)
        self.client.on('f', self.handle_quaternion)
        self.client.on('g', self.handle_desire_rate)
        self.client.on('h', self.handle_desire_stab)
        self.client.on('i', self.handle_motor_pwm)
        self.client.on('j', self.handle_estimated_rate)
        self.client.on('k', self.handle_pid_stab)
        self.client.on('l', self.handle_pid_rate)
        self.client.on('m', self.handle_pid_consts)

    def handle_magnetometer(self, message: bytes):
        messages_struct_float = struct.unpack("f" * (len(message) // FLOAT_SIZE), message)
        mag_msg = MagneticField()
        mag_msg.magnetic_field.x = messages_struct_float[0]
        mag_msg.magnetic_field.y = messages_struct_float[1]
        mag_msg.magnetic_field.z = messages_struct_float[2]
        self.mag_pub.publish(mag_msg)

    def handle_quaternion(self, message: bytes):
        messages_struct_float = struct.unpack("f" * (len(message) // FLOAT_SIZE), message)
        quaternion_msg = Quaternion()
        quaternion_msg.x = messages_struct_float[0]
        quaternion_msg.y = messages_struct_float[1]
        quaternion_msg.z = messages_struct_float[2]
        quaternion_msg.w = messages_struct_float[3]
        self.quaternion_pub.publish(quaternion_msg)

    def handle_euler(self, message: bytes):
        messages_struct_float = struct.unpack("f" * (len(message) // FLOAT_SIZE), message)
        euler_msg = EulerAngles()
        euler_msg.pitch = messages_struct_float[0]
        euler_msg.roll = messages_struct_float[1]
        euler_msg.yaw = messages_struct_float[2]
        self.euler_pub.publish(euler_msg)

    def handle_imu(self, message: bytes):
        messages_struct_float = struct.unpack("f" * (len(message) // FLOAT_SIZE), message)
        imu_msg = Imu()
        imu_msg.linear_acceleration.x = messages_struct_float[0]
        imu_msg.linear_acceleration.y = messages_struct_float[1]
        imu_msg.linear_acceleration.z = messages_struct_float[2]
        imu_msg.angular_velocity.x = messages_struct_float[3]
        imu_msg.angular_velocity.y = messages_struct_float[4]
        imu_msg.angular_velocity.z = messages_struct_float[5]
        self.imu_pub_pololu.publish(imu_msg)

    def handle_rc(self, message: bytes):
        message_struct_int = struct.unpack("i" * (len(message) // INT_SIZE), message)
        rc_msg = Int32MultiArray()
        rc_msg.data = message_struct_int[:16]
        self.rc_pub.publish(rc_msg)

    def handle_desire_rate(self, message: bytes):
        messages_struct_float = struct.unpack("f" * (len(message) // FLOAT_SIZE), message)
        desire_rate_msg = Float32MultiArray()
        desire_rate_msg.data = messages_struct_float[:3]
        self.desire_rate_pub.publish(desire_rate_msg)

    def handle_desire_stab(self, message: bytes):
        messages_struct_float = struct.unpack("f" * (len(message) // FLOAT_SIZE), message)
        desire_stab_msg = Float32MultiArray()
        desire_stab_msg.data = messages_struct_float[:3]
        self.desire_stab_pub.publish(desire_stab_msg)

    def handle_motor_pwm(self, message: bytes):
        messages_struct_float = struct.unpack("f" * (len(message) // FLOAT_SIZE), message)
        motor_pwm_msg = Motors()
        motor_pwm_msg.front_right = messages_struct_float[0]
        motor_pwm_msg.back_right = messages_struct_float[1]
        motor_pwm_msg.back_left = messages_struct_float[2]
        motor_pwm_msg.front_left = messages_struct_float[3]
        self.motor_pwm_pub.publish(motor_pwm_msg)

    def handle_estimated_rate(self, message: bytes):
        messages_struct_float = struct.unpack("f" * (len(message) // FLOAT_SIZE), message)
        estimated_rate_msg = Float32MultiArray()
        estimated_rate_msg.data = messages_struct_float[:3]
        self.estimated_rate_pub.publish(estimated_rate_msg)

    def handle_pid_stab(self, message: bytes):
        messages_struct_float = struct.unpack("f" * (len(message) // FLOAT_SIZE), message)
        pid_msg = Pid()
        pid_msg.error_pitch = messages_struct_float[0]
        pid_msg.error_roll = messages_struct_float[1]
        pid_msg.error_yaw = messages_struct_float[2]
        pid_msg.p_pitch = messages_struct_float[3]
        pid_msg.p_roll = messages_struct_float[4]
        pid_msg.p_yaw = messages_struct_float[5]
        pid_msg.i_pitch = messages_struct_float[6]
        pid_msg.i_roll = messages_struct_float[7]
        pid_msg.i_yaw = messages_struct_float[8]
        pid_msg.d_pitch = messages_struct_float[9]
        pid_msg.d_roll = messages_struct_float[10]
        pid_msg.d_yaw = messages_struct_float[11]
        pid_msg.sum_pitch = messages_struct_float[12]
        pid_msg.sum_roll = messages_struct_float[13]
        pid_msg.sum_yaw = messages_struct_float[14]
        self.PID_stab_pub_modifide.publish(pid_msg)

    def handle_pid_rate(self, message: bytes):
        messages_struct_float = struct.unpack("f" * (len(message) // FLOAT_SIZE), message)
        pid_msg = Pid()
        pid_msg.error_pitch = messages_struct_float[0]
        pid_msg.error_roll = messages_struct_float[1]
        pid_msg.error_yaw = messages_struct_float[2]
        pid_msg.p_pitch = messages_struct_float[3]
        pid_msg.p_roll = messages_struct_float[4]
        pid_msg.p_yaw = messages_struct_float[5]
        pid_msg.i_pitch = messages_struct_float[6]
        pid_msg.i_roll = messages_struct_float[7]
        pid_msg.i_yaw = messages_struct_float[8]
        pid_msg.d_pitch = messages_struct_float[9]
        pid_msg.d_roll = messages_struct_float[10]
        pid_msg.d_yaw = messages_struct_float[11]
        pid_msg.sum_pitch = messages_struct_float[12]
        pid_msg.sum_roll = messages_struct_float[13]
        pid_msg.sum_yaw = messages_struct_float[14]
        self.PID_rate_pub_modifide.publish(pid_msg)

    def handel_imu_filter(self, message: bytes):
        messages_struct_float = struct.unpack("f" * (len(message) // FLOAT_SIZE), message)
        imu_filter_msg = ImuFilter()
        imu_filter_msg.acc_lpf_x = messages_struct_float[0]
        imu_filter_msg.acc_lpf_y = messages_struct_float[1]
        imu_filter_msg.acc_lpf_z = messages_struct_float[2]
        imu_filter_msg.gyro_hpf_x = messages_struct_float[3]*(180/math.pi)
        imu_filter_msg.gyro_hpf_y = messages_struct_float[4]*(180/math.pi)
        imu_filter_msg.gyro_hpf_z = messages_struct_float[5]*(180/math.pi)
        imu_filter_msg.gyro_lpf_x = messages_struct_float[6]
        imu_filter_msg.gyro_lpf_y = messages_struct_float[7]
        imu_filter_msg.gyro_lpf_z = messages_struct_float[8]
        imu_filter_msg.mag_lpf_x = messages_struct_float[9]
        imu_filter_msg.mag_lpf_y = messages_struct_float[10]
        imu_filter_msg.mag_lpf_z = messages_struct_float[11]
        self.Imu_Filter_Pub.publish(imu_filter_msg)

    def handle_pid_consts(self, message: bytes):
        messages_struct_float = struct.unpack("f" * (len(message) // FLOAT_SIZE), message)
        pid_consts_msg = PidConsts()
        pid_consts_msg.rate_pitch[0] = messages_struct_float[0]
        pid_consts_msg.rate_pitch[1] = messages_struct_float[1]
        pid_consts_msg.rate_pitch[2] = messages_struct_float[2]
        pid_consts_msg.rate_roll[0] = messages_struct_float[3]
        pid_consts_msg.rate_roll[1] = messages_struct_float[4]
        pid_consts_msg.rate_roll[2] = messages_struct_float[5]
        pid_consts_msg.stablize_pitch[0] = messages_struct_float[6]
        pid_consts_msg.stablize_pitch[1] = messages_struct_float[7]
        pid_consts_msg.stablize_pitch[2] = messages_struct_float[8]
        pid_consts_msg.stablize_roll[0] = messages_struct_float[9]
        pid_consts_msg.stablize_roll[1] = messages_struct_float[10]
        pid_consts_msg.stablize_roll[2] = messages_struct_float[11]
        pid_consts_msg.rate_yaw[0] = messages_struct_float[12]
        pid_consts_msg.rate_yaw[1] = messages_struct_float[13]
        pid_consts_msg.rate_yaw[2] = messages_struct_float[14]
        self.Pid_consts_pub.publish(pid_consts_msg)


def main(args=None):
    rclpy.init(args=args)
    client = UDPSocketClient()
    rclpy.spin(client)  # Spin the ROS node
    client.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
