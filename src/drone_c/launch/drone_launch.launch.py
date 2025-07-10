from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch.conditions import IfCondition
import os

def generate_launch_description():
    # Get the package share directory
    pkg_share = get_package_share_directory('drone_c')
    config_file = os.path.join(pkg_share, 'plotjuggler', 'plotjugller_save.xml')

    # Declare the launch argument
    plotjuggler_arg = DeclareLaunchArgument(
        'plotjuggler',
        default_value='false',
        description='Launch PlotJuggler with the configuration file'
    )

    rtcom_node = Node(
        #comunication betwwen the ros2 and the teensy
        package='drone_c',
        executable='rtcom_teensy_ros.py',
        name='rtcom_teensy_ros',
        output='screen'
    )

    drone_tuner_node = Node(
        #a qt applicatino base ros2 that allow tuning the drone parameters
        package='drone_tuner',
        executable='drone_tuner',
        name='drone_tuner',
        output='screen'
    )

    plotjuggler_node = Node(
        #a tool for visulizing the drone data
        package='plotjuggler',
        executable='plotjuggler',
        name='plotjuggler',
        arguments=['--layout', config_file],
        output='screen',
        condition=IfCondition(LaunchConfiguration('plotjuggler'))
    )

    return LaunchDescription([
        plotjuggler_arg,
        rtcom_node,
        drone_tuner_node,
        plotjuggler_node
    ])
