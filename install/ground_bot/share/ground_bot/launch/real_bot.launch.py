##real bot launch file
import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.substitutions import Command
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.event_handlers import OnProcessExit
from launch.actions import RegisterEventHandler

def generate_launch_description():
    robot_description_path = get_package_share_directory('ground_bot')
    default_model_path = os.path.join(robot_description_path, 'urdf', 'ground_bot_descriptor.urdf')
    default_rviz_config_path = os.path.join(robot_description_path, 'rviz', 'urdf_real_bot.rviz')

    robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        parameters=[{
            'robot_description': open(default_model_path).read()
        }]
    )

    rviz = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        output='screen',
        arguments=['-d', default_rviz_config_path],
    )

    realsense_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(
                get_package_share_directory('realsense2_camera'),
                'launch',
                'rs_launch.py'
            )
        ]),
        launch_arguments={
            'depth_module.depth_profile': '1280x720x30',
            'pointcloud.enable': 'true'
        }.items()
    )


    pointcloud_to_laserscan_node = Node(
        package='pointcloud_to_laserscan',
        executable='pointcloud_to_laserscan_node',
        name='pointcloud_to_laserscan',
        output='screen',
    )
    static_tf_node = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        name='static_transform_publisher',
        output='screen',
        arguments=['0', '0', '0', '0', '0', '0', '1', 'real_sense_link', 'camera_depth_optical_frame']
    )
    return LaunchDescription([
        realsense_launch,
        pointcloud_to_laserscan_node,
        robot_state_publisher,  
        rviz,
    ])
