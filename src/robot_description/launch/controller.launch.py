from launch import LaunchDescription
from launch_ros.actions import Node
import os
from launch_ros.parameter_descriptions import ParameterValue
from launch.substitutions import Command
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    
    robot_description = ParameterValue(
        Command([
            'xacro ',
            os.path.join(get_package_share_directory("robot_description"), 'urdf', 'main.urdf.xacro')
        ]),
        value_type=str
    )
    
    robot_state_publisher = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        name='robot_state_publisher',
        output='screen',
        parameters=[{'robot_description': robot_description,
                     "use_sim_time": True}]
    )
    
    controller_manager = Node(
        package="controller_manager",
        executable="ros2_control_node",
        parameters=[{'robot_description': robot_description},
                   os.path.join(get_package_share_directory("robot_controller"), 
                               "config", 
                               "controller_config.yaml"),
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
        robot_state_publisher,
        controller_manager,
        joint_state_broadcaster_spawner,
        propeller_controllers_spawner,
        imu_broadcaster_spawner
    ])