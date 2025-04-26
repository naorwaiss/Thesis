import os
from ament_index_python.packages import get_package_share_directory
from pathlib import Path
from launch import LaunchDescription
from launch.substitutions import Command, LaunchConfiguration
from launch_ros.actions import Node

from launch.actions import (
    ExecuteProcess,
    DeclareLaunchArgument,
    RegisterEventHandler,
    SetEnvironmentVariable,
    IncludeLaunchDescription
)
from launch_ros.parameter_descriptions import ParameterValue
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.event_handlers import OnProcessExit

def generate_launch_description():

    robot_description_path = get_package_share_directory('ground_bot')
    gazebo_resource_path = SetEnvironmentVariable(name='GZ_SIM_RESOURCE_PATH',
                                                  value=[
                                                    str(Path(robot_description_path).parent.resolve())
                                                ]
    )
    model_arg = DeclareLaunchArgument(name='model',
                                      default_value=os.path.join(robot_description_path, 'urdf', 'robot_description.urdf'),
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




    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(
                get_package_share_directory("ros_gz_sim"),
                'launch'
            ),  '/gz_sim.launch.py']
        ),
        launch_arguments=[
            ('gz_args', [' -v 4 -r empty.sdf ']),
            ('world', os.path.join(robot_description_path, 'worlds', 'empty.sdf'))
        ]
    )
    gz_spawn_entity = Node(package='ros_gz_sim',
                           executable='create',
                           arguments=['-topic', 'robot_description',
                                      '-name', 'hamma_bot',],
                           output='screen'
    )
    gz_ros2_bridge = Node(
        package='ros_gz_bridge',
        executable='parameter_bridge',
        arguments=[
            # '/model/x8_bot/cmd_vel@geometry_msgs/msg/Twist[gz.msgs.Twist]',
            # '/model/x8_bot/odometry@nav_msgs/msg/Odometry[gz.msgs.Odometry]'
            # "/model/x8_bot/depth_camera@sensor_msgs/msg/Image@ignition.msgs.Image",
            # '/model/x8_bot/depth_camera/camera_info@sensor_msgs/msg/CameraInfo[gz.msgs.CameraInfo]',
            "/scan@sensor_msgs/msg/LaserScan[ignition.msgs.LaserScan",
            "/imu@sensor_msgs/msg/Imu[ignition.msgs.IMU",
            '/clock@rosgraph_msgs/msg/Clock[gz.msgs.Clock]',

        ],
        output='screen'
    )
    load_joint_state_controller = ExecuteProcess(
        name="activate_joint_state_broadcaster",
        cmd=[
            "ros2",
            "control",
            "load_controller",
            "--set-state",
            "active",
            "joint_state_broadcaster",
        ],
        shell=False,
        output="screen",
    )


    load_ackermann_controller = ExecuteProcess(
        name="activate_ackermann_controller_velcoity",
        cmd=[
            "ros2",
            "control",
            "load_controller",
            "--set-state",
            "active",
            "ackermann_controller_velocity",
        ],
        shell=False,
        output="screen",
    )

    relay_odom = Node(
        name="relay_odom",
        package="topic_tools",
        executable="relay",
        parameters=[
            {
                "input_topic": "/ackermann_controller_velocity/odometry",
                "output_topic": "/odom",
            }
        ],
        output="screen",
    )

    # relay_cmd_vel = Node(
    #     name="relay_cmd_vel",
    #     package="topic_tools",
    #     executable="relay",
    #     parameters=[
    #         {
    #             "input_topic": "/cmd_vel",
    #             "output_topic": "/diff_drive_base_controller/cmd_vel_unstamped",
    #         }
    #     ],
    #     output="screen",
    # )



    return LaunchDescription([
        gz_ros2_bridge,
        model_arg,
        gazebo_resource_path,
        robot_state_publisher,
        gazebo,
        gz_spawn_entity,

        RegisterEventHandler(
            event_handler=OnProcessExit(
                target_action=gz_spawn_entity,
                on_exit=[load_joint_state_controller],
            )
        ),
        RegisterEventHandler(
            event_handler=OnProcessExit(
                target_action=load_joint_state_controller,
                on_exit=[load_ackermann_controller],
            )
        ),
        relay_odom,
    ])
