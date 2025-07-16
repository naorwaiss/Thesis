import rclpy
from rclpy.node import Node
from geometry_msgs.msg import PoseStamped, Vector3
from tf_transformations import euler_from_quaternion
import math

class PoseToEulerNode(Node):
    def __init__(self):
        super().__init__('pose_to_euler_node')

        # Subscriber to PoseStamped
        self.subscription = self.create_subscription(
            PoseStamped,
            '/naor/pose',
            self.pose_callback,
            10
        )

        # Publisher for Euler angles
        self.publisher_ = self.create_publisher(
            Vector3,
            '/euler_angles_camera',
            10
        )

        self.get_logger().info('Pose to Euler node has been started.')

    def pose_callback(self, msg):
        # Extract quaternion
        q = msg.pose.orientation
        quaternion = [q.x, q.y, q.z, q.w]

        # Convert to Euler angles (in radians)
        roll, pitch, yaw = euler_from_quaternion(quaternion)

        # Publish Euler angles
        euler_msg = Vector3()
        euler_msg.x = float(roll*(180/3.14))
        euler_msg.y = float(pitch*(180/3.14))
        euler_msg.z = float(yaw*(180/3.14))

        self.publisher_.publish(euler_msg)
        self.get_logger().info(
            f'Published Euler angles: Roll={roll:.2f}, Pitch={pitch:.2f}, Yaw={yaw:.2f}'
        )


def main(args=None):
    rclpy.init(args=args)
    node = PoseToEulerNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
