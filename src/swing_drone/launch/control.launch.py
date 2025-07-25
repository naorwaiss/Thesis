from launch import LaunchDescription
from launch_ros.actions import Node
import os
from launch_ros.parameter_descriptions import ParameterValue
from launch.substitutions import Command
from ament_index_python.packages import get_package_share_directory
from launch.actions import TimerAction


def generate_launch_description():

    robot_description = ParameterValue(
        Command([
            'xacro ',
            os.path.join(get_package_share_directory("swing_drone"), 'urdf', 'main.urdf.xacro')
        ]),
        value_type=str
    )

    controller_manager = Node(
        package="controller_manager",
        executable="ros2_control_node",
        parameters=[{'robot_description': robot_description},
                    os.path.join(get_package_share_directory("swing_drone"),
                                 "config",
                                 "drone_controller.yaml"),
                    {"use_sim_time": False}],
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

    propellors_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=['propellors',
                   '--controller-manager',
                   '/controller_manager'
                   ]
    )


    return LaunchDescription([
        controller_manager,
        TimerAction(period=2.0, actions=[joint_state_broadcaster_spawner]),
        TimerAction(period=4.0, actions=[propellors_spawner]),
    ])
