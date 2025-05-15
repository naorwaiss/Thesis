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
    default_model_path = os.path.join(robot_description_path, 'urdf', 'ground_bot_descriptor.urdf')
    default_rviz_config_path = os.path.join(robot_description_path, 'rviz', 'urdf_config.rviz')



    use_sim_time = LaunchConfiguration('use_sim_time')
    # use_localization = LaunchConfiguration('use_localization')
    use_rviz = LaunchConfiguration('use_rviz')
    log_level = LaunchConfiguration('log_level')
    gz_verbosity = LaunchConfiguration('gz_verbosity')
    run_headless = LaunchConfiguration('run_headless')
    world_file_name = LaunchConfiguration('world_file')
    gz_models_path = ":".join([robot_description_path, os.path.join(robot_description_path, "models")])
    world_path = PathJoinSubstitution([robot_description_path, "worlds", world_file_name])

    # Set Gazebo environment variables
    gz_env = {
        'GZ_SIM_SYSTEM_PLUGIN_PATH': ':'.join([
            os.environ.get('GZ_SIM_SYSTEM_PLUGIN_PATH', default=''),
            os.environ.get('LD_LIBRARY_PATH', default='')
        ]),
        'IGN_GAZEBO_SYSTEM_PLUGIN_PATH': ':'.join([
            os.environ.get('IGN_GAZEBO_SYSTEM_PLUGIN_PATH', default=''),
            os.environ.get('LD_LIBRARY_PATH', default='')
        ])
    }

    robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        parameters=[{
            'robot_description': Command(['xacro ', LaunchConfiguration('model')]),
        }]
    )

    rviz_node = Node(
        condition=IfCondition(AndSubstitution(NotSubstitution(run_headless), use_rviz)),
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        output='screen',
        arguments=['-d', LaunchConfiguration('rvizconfig')],
        parameters=[{'queue_size': 100}]
    )

    load_joint_state_controller = ExecuteProcess(
        name='activate_joint_state_broadcaster',
        cmd=[
            'ros2',
            'control',
            'load_controller',
            '--set-state',
            'active',
            'joint_state_broadcaster'
        ],
        shell=True,
        output='screen'
    )

    load_diff_drive_controller = ExecuteProcess(
        name='activate_diff_drive_controller_velocity',
        cmd=[
            'ros2',
            'control',
            'load_controller',
            '--set-state',
            'active',
            'diff_drive_base_controller'
        ],
        shell=True,
        output='screen'
    )
    spawn_entity = Node(
        package='ros_gz_sim',
        executable='create',
        arguments=[
            '-name', 'hamma_bot',
            '-topic', 'robot_description',
            '-z', '1.0',
            '-x', '-1.0',
            '--ros-args',
            '--log-level', log_level
        ],
        output='screen',
        parameters=[{'use_sim_time': use_sim_time}]
    )
    gz_ros2_bridge = Node(
        package='ros_gz_bridge',
        executable='parameter_bridge',
        arguments=[
            # '/scan@sensor_msgs/msg/LaserScan[ignition.msgs.LaserScan',
            # '/robot_cam_right@sensor_msgs/msg/Image@ignition.msgs.Image',
            # '/robot_cam_left@sensor_msgs/msg/Image@ignition.msgs.Image',
            # '/camera_info_right@sensor_msgs/msg/CameraInfo@ignition.msgs.CameraInfo',
            # '/camera_info_left@sensor_msgs/msg/CameraInfo@ignition.msgs.CameraInfo',
            '/imu@sensor_msgs/msg/Imu[ignition.msgs.IMU',
            '/clock@rosgraph_msgs/msg/Clock@gz.msgs.Clock'
        ],
        output='screen'
    )
    gazebo = [
        ExecuteProcess(
            condition=IfCondition(run_headless),
            cmd=['ruby', FindExecutable(name="ign"), 'gazebo', '-r', '-v', gz_verbosity, '-s', '--headless-rendering', world_path],
            output='screen',
            additional_env=gz_env,
            shell=False,
        ),
        ExecuteProcess(
            condition=UnlessCondition(run_headless),
            cmd=['ruby', FindExecutable(name="ign"), 'gazebo', '-r', '-v', gz_verbosity, world_path],
            output='screen',
            additional_env=gz_env,
            shell=False,
        )
    ]

    return LaunchDescription([
        SetEnvironmentVariable(
            name='IGN_GAZEBO_RESOURCE_PATH',
            value=gz_models_path
        ),
        DeclareLaunchArgument(
            name='use_rviz',
            default_value='True',
            description='Start RViz'
        ),
        DeclareLaunchArgument(
            name='model',
            default_value=default_model_path,
            description='Absolute path to robot urdf file'
        ),
        DeclareLaunchArgument(
            name='run_headless',
            default_value='False',
            description='Start GZ in headless mode and don\'t start RViz (overrides use_rviz)'
        ),
        DeclareLaunchArgument(
            name='world_file',
            default_value='empty.sdf'
        ),
        DeclareLaunchArgument(
            name='rvizconfig',
            default_value=default_rviz_config_path,
            description='Absolute path to rviz config file'
        ),
        DeclareLaunchArgument(
            name='use_sim_time',
            default_value='True',
            description='Flag to enable use_sim_time'
        ),
        DeclareLaunchArgument(
            name='gz_verbosity',
            default_value='3',
            description='Verbosity level for Gazebo (0~4)'
        ),
        DeclareLaunchArgument(
            name='log_level',
            default_value='warn',
            description='The level of logging that is applied to all ROS 2 nodes launched by this script'
        ),
 robot_state_publisher,
        spawn_entity,
        rviz_node,
        gz_ros2_bridge,
        RegisterEventHandler(
            event_handler=OnProcessExit(
                target_action=spawn_entity,
                on_exit=[load_joint_state_controller]
            )
        ),
        RegisterEventHandler(
            event_handler=OnProcessExit(
                target_action=load_joint_state_controller,
                on_exit=[load_diff_drive_controller]
            )
        ),
    ]+gazebo)
