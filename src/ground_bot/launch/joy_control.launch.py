import launch
from launch_ros.actions import Node


def generate_launch_description():
    joy_node = Node(
        package='joy',
        executable='joy_node',
        name='joy_node'
    )
    
    joint_twist_node = Node(
        package='ground_bot',
        executable='joint_twist_node',
        name='joint_twist_node'
    )

    return launch.LaunchDescription([
        joy_node,
        joint_twist_node
    ])
    
    
