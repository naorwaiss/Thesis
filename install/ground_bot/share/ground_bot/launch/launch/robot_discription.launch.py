import os
from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import Command, LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():

    robot_description_path = get_package_share_directory('ground_bot')

    model_arg = DeclareLaunchArgument(name='model',
                                      default_value=os.path.join(robot_description_path, 'urdf', 'robot.urdf'),
                                      description='Absolute path to robot urdf file'
                                      )

    robot_description = ParameterValue(Command([
        'xacro ',
        LaunchConfiguration('model')
    ]),
        value_type=str
    )

    robot_state_publisher = Node(package='robot_state_publisher',
                                 executable='robot_state_publisher',
                                 name='robot_state_publisher',
                                 parameters=[{'robot_description': robot_description,
                                              'use_sim_time': True}]
                                 )

    return LaunchDescription([
        model_arg,
        robot_state_publisher,
    ])
