##real bot launch file

import os
from ament_index_python.packages import get_package_share_directory
from pathlib import Path
from launch import LaunchDescription
from launch.substitutions import Command, LaunchConfiguration, NotSubstitution, AndSubstitution
from launch_ros.actions import Node
from launch.actions import (
    ExecuteProcess,
    DeclareLaunchArgument,
    RegisterEventHandler,
    SetEnvironmentVariable,
    TimerAction,
)
import launch_ros
from launch.conditions import IfCondition, UnlessCondition
from launch_ros.parameter_descriptions import ParameterValue
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.event_handlers import OnProcessExit
from launch.substitutions import FindExecutable, PathJoinSubstitution



def generate_launch_description():
    pkg_share = launch_ros.substitutions.FindPackageShare(
        package="ground_bot"
    ).find("ground_bot")
    robot_description_path = get_package_share_directory('ground_bot')
    default_model_path = os.path.join(robot_description_path, 'urdf', 'robot_description.urdf')
    default_rviz_config_path = os.path.join(robot_description_path, 'rviz', 'urdf_config.rviz')
