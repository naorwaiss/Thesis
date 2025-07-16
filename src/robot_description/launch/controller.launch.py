from launch import LaunchDescription
from launch.actions import TimerAction
from launch_ros.actions import Node
import os
from launch_ros.parameter_descriptions import ParameterValue
from launch.substitutions import Command
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():  
    
    controller_manager = Node(
        package="controller_manager",
        executable="ros2_control_node",
        parameters=[os.path.join(get_package_share_directory("controller"), 
                                "config", 
                                "robot_controllers.yaml"),
                   {"use_sim_time": True}],
        output="screen",
    )
    
    joint_state_broadcaster_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=['joint_state_broadcaster',
                   '--controller-manager',
                   '/controller_manager'
        ]
    )
    
    propeller_controllers_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=['propeller_controllers',
                   '--controller-manager',
                   '/controller_manager'
        ]
    )
    
    imu_broadcaster_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=['imu_broadcaster',
                   '--controller-manager',
                   '/controller_manager'
        ]
    )
    
    return LaunchDescription([
        controller_manager,
        TimerAction(
            period=2.0,
            actions=[joint_state_broadcaster_spawner]
        ),
        TimerAction(
            period=4.0,
            actions=[propeller_controllers_spawner]
        ),
        TimerAction(
            period=6.0,
            actions=[imu_broadcaster_spawner]
        )
    ])