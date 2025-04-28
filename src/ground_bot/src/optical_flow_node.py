#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from std_msgs.msg import Float32MultiArray
import cv2
import numpy as np
from cv_bridge import CvBridge

class OpticalFlowNode(Node):
    def __init__(self):
        super().__init__('optical_flow_node')
        
        # Declare input topic parameter
        self.declare_parameter('input_topic', '/robot_cam_left')
        self.input_topic = self.get_parameter('input_topic').value
        
        self.get_logger().info(f'Subscribing to topic: {self.input_topic}')
        
        # Create subscriber for camera image
        self.image_sub = self.create_subscription(
            Image,
            self.input_topic,
            self.image_callback,
            10
        )
        
        # Create publisher for velocity array (x, y)
        self.velocity_pub = self.create_publisher(
            Float32MultiArray,
            '/optical_flow_velocity_left',
            10
        )
        
        # Initialize CV bridge
        self.bridge = CvBridge()
        
        # Initialize previous frame and features
        self.prev_gray = None
        self.prev_points = None
        
        # Parameters for Lucas-Kanade optical flow
        self.feature_params = dict(
            maxCorners=100,        # Maximum number of points to track
            qualityLevel=0.3,      # Minimum quality of corner below which everyone is rejected
            minDistance=7,         # Minimum possible Euclidean distance between corners
            blockSize=7            # Size of average block for computing correlation matrix
        )
        
        self.lk_params = dict(
            winSize=(15, 15),      # Size of search window for each pyramid level
            maxLevel=2,            # Number of pyramid levels
            criteria=(cv2.TERM_CRITERIA_EPS | cv2.TERM_CRITERIA_COUNT, 10, 0.03)  # Termination criteria
        )
        
    def image_callback(self, msg):
        try:
            # Convert ROS image to OpenCV format
            current_frame = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
            
            if current_frame is None:
                self.get_logger().warn('Empty frame received')
                return
                
            # Resize to speed up processing
            current_frame = cv2.resize(current_frame, (160, 120))
            
            # Convert to grayscale
            current_gray = cv2.cvtColor(current_frame, cv2.COLOR_BGR2GRAY)
            
            if self.prev_gray is not None:
                if self.prev_points is None:
                    # Detect features to track
                    self.prev_points = cv2.goodFeaturesToTrack(
                        self.prev_gray,
                        mask=None,
                        **self.feature_params
                    )
                    
                if self.prev_points is not None and len(self.prev_points) > 0:
                    # Calculate optical flow
                    curr_points, status, err = cv2.calcOpticalFlowPyrLK(
                        self.prev_gray,
                        current_gray,
                        self.prev_points,
                        None,
                        **self.lk_params
                    )
                    
                    # Select good points
                    if curr_points is not None:
                        good_curr = curr_points[status == 1]
                        good_prev = self.prev_points[status == 1]
                        
                        # Calculate velocities
                        if len(good_curr) > 0 and len(good_prev) > 0:
                            # Calculate point differences
                            point_diff = good_curr - good_prev
                            
                            # Calculate average velocity
                            avg_velocity_x = np.mean(point_diff[:, 0])*1000
                            avg_velocity_y = np.mean(point_diff[:, 1])*1000
                            
                            # Create and publish message
                            msg_out = Float32MultiArray()
                            msg_out.data = [float(avg_velocity_x), float(avg_velocity_y)]
                            self.velocity_pub.publish(msg_out)
                            
                            self.get_logger().info(
                                f'Published velocities - x: {avg_velocity_x:.3f}, y: {avg_velocity_y:.3f} '
                                f'(tracking {len(good_curr)} points)'
                            )
                            
                            # Update feature points for next iteration
                            self.prev_points = good_curr.reshape(-1, 1, 2)
                        else:
                            self.prev_points = None
                    else:
                        self.prev_points = None
                else:
                    self.prev_points = None
            
            # Save current frame as previous for next callback
            self.prev_gray = current_gray.copy()
            
        except Exception as e:
            self.get_logger().error(f'Exception in image_callback: {str(e)}')
            self.prev_points = None

def main(args=None):
    rclpy.init(args=args)
    node = OpticalFlowNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main() 