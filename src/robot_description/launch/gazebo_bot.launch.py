import os
from pathlib import Path
from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, SetEnvironmentVariable
from launch.substitutions import Command, LaunchConfiguration
from launch.launch_description_sources import PythonLaunchDescriptionSource

from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    
    robot_description_path = get_package_share_directory('robot_description')
    
    # Load the URDF file
    urdf_file = os.path.join(robot_description_path, 'urdf', 'main.urdf.xacro')
    
    robot_description = ParameterValue(
        Command(['xacro ', urdf_file]),
        value_type=str
    )
    
    gazebo_resource_path = SetEnvironmentVariable(name='GZ_SIM_RESOURCE_PATH',
                                                  value=[
                                                    str(Path(robot_description_path).parent.resolve())
                                                ]
    )
    
    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(
                get_package_share_directory("ros_gz_sim"),
                'launch'
            ),  '/gz_sim.launch.py']
        ),
        launch_arguments=[
            ('gz_args', [' -v 4 -r multicopter.sdf ']),
            ('world', os.path.join(robot_description_path, 'worlds', 'multicopter.sdf'))
        ]
    )
    
    # Include the controller launch file
    controller_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(robot_description_path, 'launch', 'controller.launch.py')
        ])
    )
    
    # Robot State Publisher to publish URDF
    robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        output='screen',
        parameters=[{'robot_description': robot_description}]
    )
    
    # Spawn the robot from URDF
    spawn_robot = Node(
        package='ros_gz_sim',
        executable='create',
        arguments=[
            '-topic', 'robot_description',
            '-name', 'sim_drone',
            '-x', '0.0',
            '-y', '0.0',
            '-z', '0.1'
        ],
        output='screen'
    )
    
    gz_ros2_bridge = Node(package='ros_gz_bridge',
                           executable='parameter_bridge',
                           arguments=[
                               '/clock@rosgraph_msgs/msg/Clock[gz.msgs.Clock',
                               '/sim_drone/cmd_vel@geometry_msgs/msg/Twist@gz.msgs.Twist',
                               '/sim_drone/odom@nav_msgs/msg/Odometry@gz.msgs.Odometry'
                            ]
    )
    

    return LaunchDescription([
        gazebo_resource_path,
        gazebo,
        controller_launch,
        robot_state_publisher,
        spawn_robot,
        gz_ros2_bridge
    ])