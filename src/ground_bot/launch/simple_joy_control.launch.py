from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='joy',
            executable='joy_node',
            name='joy_node',
            output='screen'
        ),
        Node(
            package='ground_bot',
            executable='joy_twist_node',
            name='joy_twist_node',
            output='screen'
        )
    ])
