#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from std_msgs.msg import Bool
from sensor_msgs.msg import JointState
import time
import math

class JointMovementTest(Node):
    def __init__(self):
        super().__init__('joint_movement_test')
        
        # Publisher for joint control
        self.joint_control_pub = self.create_publisher(Bool, 'joint_control', 10)
        
        # Subscriber for joint states
        self.joint_state_sub = self.create_subscription(
            JointState, 'arm_joint_states', self.joint_state_callback, 10)
        
        self.latest_joint_data = None
        self.get_logger().info('Joint Movement Test Node Started')
        
    def joint_state_callback(self, msg):
        """Store the latest joint state data"""
        self.latest_joint_data = msg
        
    def set_joints_free(self):
        """Set joints to free mode"""
        msg = Bool()
        msg.data = True
        self.joint_control_pub.publish(msg)
        self.get_logger().info('Joints set to FREE mode')
        
    def set_joints_fixed(self):
        """Set joints to fixed mode"""
        msg = Bool()
        msg.data = False
        self.joint_control_pub.publish(msg)
        self.get_logger().info('Joints set to FIXED mode')
        
    def print_joint_data(self):
        """Print current joint data"""
        if self.latest_joint_data:
            self.get_logger().info('Current Joint States:')
            for i, name in enumerate(self.latest_joint_data.name):
                pos = self.latest_joint_data.position[i] if i < len(self.latest_joint_data.position) else 0.0
                vel = self.latest_joint_data.velocity[i] if i < len(self.latest_joint_data.velocity) else 0.0
                eff = self.latest_joint_data.effort[i] if i < len(self.latest_joint_data.effort) else 0.0
                self.get_logger().info(f'  {name}: pos={pos:.6f}, vel={vel:.6f}, eff={eff:.6f}')
        else:
            self.get_logger().info('No joint data received yet')

def main(args=None):
    rclpy.init(args=args)
    
    try:
        node = JointMovementTest()
        
        print("\n=== Joint Movement Test ===")
        print("Commands:")
        print("1. Setting joints to FREE mode")
        print("2. In Gazebo, try to manually move the robot arms")
        print("3. Watch the position values change")
        print("4. Press Ctrl+C to exit\n")
        
        # Set joints to free
        node.set_joints_free()
        
        # Monitor joint data
        start_time = time.time()
        while rclpy.ok():
            rclpy.spin_once(node, timeout_sec=0.1)
            
            # Print joint data every 2 seconds
            if time.time() - start_time > 2.0:
                node.print_joint_data()
                start_time = time.time()
        
    except KeyboardInterrupt:
        print("\nShutting down Joint Movement Test")
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main() 