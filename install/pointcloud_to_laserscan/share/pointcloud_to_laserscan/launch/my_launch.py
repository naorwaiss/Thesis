import launch
from launch_ros.actions import Node

def generate_launch_description():
    return launch.LaunchDescription([
        # Map to Base Link (Identity Quaternion: 0 0 0 1)
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            name='map_to_base_link',
            arguments=['0', '0', '0', '0', '0', '0', '1', 'map', 'base_link']
        ),
        # Base Link to Camera Link
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            name='base_link_to_camera_link',
            arguments=['0', '0', '0.3', '0', '0', '0', '1', 'base_link', 'camera_link']
        ),
        # Camera Link to Camera Depth Frame
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            name='camera_link_to_depth_frame',
            arguments=['0', '0', '0', '0', '0', '0', '1', 'camera_link', 'camera_depth_frame']
        ),
        # Camera Depth Frame to Camera Depth Optical Frame
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            name='depth_frame_to_depth_optical_frame',
            arguments=['0', '0', '0', '0', '0', '0', '1', 'camera_depth_frame', 'camera_depth_optical_frame']
        ),
        # Pointcloud to Laserscan Node
        Node(
            package='pointcloud_to_laserscan',
            executable='pointcloud_to_laserscan_node',
            name='pointcloud_to_laserscan',
            parameters=[
                {
                    'target_frame': 'camera_depth_optical_frame',
                    'transform_tolerance': 0.2,
                    'min_height': -1.0,
                    'max_height': 1.0,
                    'angle_min': -3.14,
                    'angle_max': 3.14,
                    'angle_increment': 0.01,
                    'scan_time': 0.1,
                    'range_min': 0.1,
                    'range_max': 10.0,
                    'use_inf': True,
                    'queue_size': 200,
                    'qos_reliability': 'reliable'
                }
            ],
            remappings=[
                ('cloud_in', '/camera/camera/depth/color/points'),
                ('scan', '/scan'),
            ]
        )
    ])
