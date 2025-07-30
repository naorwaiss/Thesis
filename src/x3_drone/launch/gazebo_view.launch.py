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
    
    # Get the package directory for x3_drone
    robot_description_path = get_package_share_directory('x3_drone')
    
    # Use the SDF model
    model_arg = DeclareLaunchArgument(name='model',
                                      default_value=os.path.join(robot_description_path, 'model.sdf'),
                                      description='Absolute path to robot SDF file'
    )
    
    # World file argument
    world_arg = DeclareLaunchArgument(name='world',
                                      default_value=os.path.join(robot_description_path, 'worlds', 'empty.sdf'),
                                      description='World file path (empty for default empty world)'
    )
    
    # Set up Gazebo resource paths to include the model directory
    gazebo_resource_path = SetEnvironmentVariable(name='GZ_SIM_RESOURCE_PATH',
                                                  value=[
                                                    str(Path(robot_description_path).resolve()),
                                                    os.pathsep,
                                                    str(Path(robot_description_path).parent.resolve())
                                                ]
    )
    
    # Set Gazebo model path for SDF models
    gazebo_model_path = SetEnvironmentVariable(name='GAZEBO_MODEL_PATH',
                                               value=[
                                                 str(Path(robot_description_path).resolve()),
                                                 os.pathsep,
                                                 str(Path(robot_description_path).parent.resolve())
                                               ]
    )

    # Launch Gazebo with world file support
    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(
                get_package_share_directory("ros_gz_sim"),
                'launch'
            ),  '/gz_sim.launch.py']
        ),
        launch_arguments=[
            ('gz_args', [' -r -v 4 ', LaunchConfiguration('world')])
        ]
    )
    
    # Spawn the X3 drone entity using the SDF file
    gz_spawn_entity = Node(package='ros_gz_sim',
                           executable='create',
                           name='x3_drone_spawner',  # Custom node name
                           arguments=['-file', LaunchConfiguration('model'),
                                      '-name', 'x3_drone',
                                      '-x', '0.0',
                                      '-y', '0.0', 
                                      '-z', '0.5'],
                           output='screen'
    )
    
    # Bridge for communication between Gazebo and ROS2 - focusing on IMU and essential sensors
    gz_ros2_bridge = Node(
        package='ros_gz_bridge',
        executable='parameter_bridge',
        arguments=[
            "/clock@rosgraph_msgs/msg/Clock[gz.msgs.Clock",
            "/world/empty/model/x3_drone/link/base_link/sensor/imu_sensor/imu@sensor_msgs/msg/Imu[gz.msgs.IMU",
            "/world/empty/model/x3_drone/link/base_link/sensor/air_pressure/air_pressure@sensor_msgs/msg/FluidPressure[gz.msgs.FluidPressure",
            "/world/empty/model/x3_drone/link/base_link/sensor/magnetometer/magnetometer@sensor_msgs/msg/MagneticField[gz.msgs.Magnetometer",
            "/x3_drone/gazebo/command/motor_speed@actuator_msgs/msg/Actuators]gz.msgs.Actuators",
        ],
        remappings=[
            ('/world/empty/model/x3_drone/link/base_link/sensor/imu_sensor/imu', '/imu'),
            ('/world/empty/model/x3_drone/link/base_link/sensor/air_pressure/air_pressure', '/air_pressure'),
            ('/world/empty/model/x3_drone/link/base_link/sensor/magnetometer/magnetometer', '/magnetometer')
        ],
        output='screen'
    )

    euiler_node = Node(
        package='x3_drone',
        executable='quart_euilr.py',
        output='screen'
    )
    joy_node = Node(
        package='joy',
        executable='joy_node',
        output='screen'
    )
    
    return LaunchDescription([
        euiler_node,
        # joy_node,
        model_arg,
        world_arg,
        gazebo_resource_path,
        gazebo_model_path,
        gazebo,
        gz_spawn_entity,
        gz_ros2_bridge,
    ]) 