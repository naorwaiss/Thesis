import os
from pathlib import Path
from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, TimerAction
from launch.substitutions import LaunchConfiguration
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.conditions import IfCondition

from launch_ros.actions import Node


def generate_launch_description():
    
    # Get package directory
    package_dir = get_package_share_directory('swing_drone')
    
    # Declare launch arguments
    use_sim_time_arg = DeclareLaunchArgument(
        'use_sim_time',
        default_value='true',
        description='Use simulation (Gazebo) clock if true'
    )
    
    start_gazebo_arg = DeclareLaunchArgument(
        'start_gazebo',
        default_value='true',
        description='Whether to start Gazebo simulation'
    )
    
    start_control_arg = DeclareLaunchArgument(
        'start_control',
        default_value='true',
        description='Whether to start control system'
    )
    
    # Include Gazebo launch file
    gazebo_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(package_dir, 'launch', 'gazebo_view.launch.py')
        ]),
        condition=IfCondition(LaunchConfiguration('start_gazebo'))
    )
    
    # Include control launch file with a delay to ensure Gazebo is ready
    control_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(package_dir, 'launch', 'control.launch.py')
        ]),
        condition=IfCondition(LaunchConfiguration('start_control'))
    )
    
    return LaunchDescription([
        # Launch arguments
        use_sim_time_arg,
        start_gazebo_arg,
        start_control_arg,
        
        # Launch files
        gazebo_launch,
        TimerAction(period=5.0, actions=[control_launch]),  # Delay control to let Gazebo start
    ])
