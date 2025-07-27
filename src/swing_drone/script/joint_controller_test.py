#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from std_msgs.msg import Bool
from sensor_msgs.msg import JointState
import time

class JointControllerTest(Node):
    def __init__(self):
        super().__init__('joint_controller_test')
        
        # Publisher for joint control
        self.joint_control_pub = self.create_publisher(Bool, 'joint_control', 10)
        
        # Subscriber for joint states
        self.joint_state_sub = self.create_subscription(
            JointState, 'arm_joint_states', self.joint_state_callback, 10)
        
        # Timer for automatic testing
        self.timer = self.create_timer(5.0, self.toggle_joint_control)
        
        self.joints_free = True
        self.get_logger().info('Joint Controller Test Node Started')
        self.get_logger().info('Publishing to /joint_control topic to toggle joint behavior')
        self.get_logger().info('Subscribing to /arm_joint_states to monitor joint data')
        
    def joint_state_callback(self, msg):
        """Callback to display joint state information"""
        if len(msg.name) > 0:
            self.get_logger().info('Joint States:')
            for i, name in enumerate(msg.name):
                pos = msg.position[i] if i < len(msg.position) else 0.0
                vel = msg.velocity[i] if i < len(msg.velocity) else 0.0
                eff = msg.effort[i] if i < len(msg.effort) else 0.0
                self.get_logger().info(f'  {name}: pos={pos:.3f}, vel={vel:.3f}, eff={eff:.3f}')
    
    def toggle_joint_control(self):
        """Toggle joint control between free and fixed"""
        self.joints_free = not self.joints_free
        
        msg = Bool()
        msg.data = self.joints_free
        self.joint_control_pub.publish(msg)
        
        state = "FREE SPINNING" if self.joints_free else "FIXED"
        self.get_logger().info(f'Joints set to: {state}')
    
    def manual_control(self, free_spinning):
        """Manually set joint control state"""
        msg = Bool()
        msg.data = free_spinning
        self.joint_control_pub.publish(msg)
        
        state = "FREE SPINNING" if free_spinning else "FIXED"
        self.get_logger().info(f'Manually set joints to: {state}')

def main(args=None):
    rclpy.init(args=args)
    
    try:
        node = JointControllerTest()
        
        # Example of manual control
        print("\nJoint Controller Test Started!")
        print("The joints will automatically toggle between FREE and FIXED every 5 seconds")
        print("You can also manually control by modifying the script")
        print("Press Ctrl+C to exit\n")
        
        # Start with joints free
        node.manual_control(True)
        
        rclpy.spin(node)
        
    except KeyboardInterrupt:
        print("\nShutting down Joint Controller Test")
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main() 