import os
from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource

from launch_ros.actions import Node


def generate_launch_description():
    
    robot_description_path = get_package_share_directory('robot_description')
    
    # Load the simple URDF file (not xacro)
    urdf_file = os.path.join(robot_description_path, 'urdf', 'simple_drone.urdf')
    
    # Read the URDF file content
    with open(urdf_file, 'r') as file:
        robot_description = file.read()
    
    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(
                get_package_share_directory("ros_gz_sim"),
                'launch'
            ),  '/gz_sim.launch.py']
        ),
        launch_arguments=[
            ('gz_args', ['-v 4 -r empty.sdf']),
        ]
    )
    
    # Robot State Publisher
    robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        output='screen',
        parameters=[{'robot_description': robot_description}]
    )
    
    # Spawn the robot
    spawn_robot = Node(
        package='ros_gz_sim',
        executable='create',
        arguments=[
            '-topic', 'robot_description',
            '-name', 'simple_drone',
            '-x', '0.0',
            '-y', '0.0',
            '-z', '2.0'
        ],
        output='screen'
    )

    return LaunchDescription([
        gazebo,
        robot_state_publisher,
        spawn_robot
    ]) 