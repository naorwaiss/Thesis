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
    
    robot_description_path = get_package_share_directory('swing_drone')
    
    model_arg = DeclareLaunchArgument(name='model',
                                      default_value=os.path.join(robot_description_path, 'urdf', 'main.urdf.xacro'),
                                      description='Absolute path to robot urdf file'
    )
    
   
    
    gazebo_resource_path = SetEnvironmentVariable(name='GZ_SIM_RESOURCE_PATH',
                                                  value=[
                                                    str(Path(robot_description_path).parent.resolve())
                                                ]
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

    sdf_file_path = os.path.join(
        get_package_share_directory('swing_drone'),
        'worlds',
        'worlds.sdf'
    )
    
    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(
                get_package_share_directory("ros_gz_sim"),
                'launch'
            ),  '/gz_sim.launch.py']
        ),
        launch_arguments=[
            ('gz_args', [' -r -v 4 ', sdf_file_path])
        ]
    )
    
    gz_spawn_entity = Node(package='ros_gz_sim',
                           executable='create',
                           arguments=['-topic', 'robot_description',
                                      '-name', 'swing_drone',
                                      '-z', '0.5'],
                           output='screen'
    )
    
    gz_ros2_bridge = Node(
        package='ros_gz_bridge',
        executable='parameter_bridge',
        arguments=[
            "/clock@rosgraph_msgs/msg/Clock[gz.msgs.Clock",
            "/imu@sensor_msgs/msg/Imu[gz.msgs.IMU",
            "/swing_drone/gazebo/command/motor_speed@actuator_msgs/msg/Actuators]gz.msgs.Actuators"
        ],
        output='screen'
    )
    imu_to_euler = Node(
        package="swing_drone",
        executable="quart_euilr.py",
    )
    return LaunchDescription([
        imu_to_euler,
        gz_ros2_bridge,
        model_arg,
        gazebo_resource_path,
        robot_state_publisher,
        gazebo,
        gz_spawn_entity,
    ])


