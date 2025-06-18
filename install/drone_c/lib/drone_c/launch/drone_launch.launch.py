from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='rtcom_teensy_ros',
            executable='rtcom_teensy_ros',
            name='rtcom_teensy_ros',
            output='screen'
        ),
        Node(
            package='drone_tunner',
            executable='drone_tunner',
            name='drone_tunner',
            output='screen'
        )
    ])
