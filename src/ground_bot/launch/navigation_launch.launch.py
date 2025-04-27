import launch
from launch_ros.actions import Node
from launch.actions import (
    ExecuteProcess,
    DeclareLaunchArgument,
    LogInfo,
    RegisterEventHandler,
    TimerAction,
)
from launch.conditions import IfCondition
from launch.substitutions import (
    LaunchConfiguration,
    PathJoinSubstitution,
    NotSubstitution,
)
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.substitutions import FindPackageShare
from launch.events.process import ProcessIO
from launch.event_handlers import OnProcessIO
from launch import LaunchDescription

def generate_launch_description():
    bringup = ExecuteProcess(
        name="launch_bringup",
        cmd=[
            "ros2",
            "launch",
            PathJoinSubstitution(
                [
                    FindPackageShare("ground_bot"),
                    "launch",
                    "hamma_bot.launch.py",
                ]
            ),
        ],
        shell=False,
        output="screen",
    )

    toolbox = ExecuteProcess(
        name="launch_slam_toolbox",
        cmd=[
            "ros2",
            "launch",
            PathJoinSubstitution(
                [
                    FindPackageShare("slam_toolbox"),
                    "launch",
                    "online_async_launch.py",
                ]
            ),
        ],
        shell=False,
        output="screen",
    )

    nav2 = ExecuteProcess(
        name="launch_nav2",
        cmd=[
            "ros2",
            "launch",
            PathJoinSubstitution(
                [
                    FindPackageShare("nav2_bringup"),
                    "launch",
                    "navigation_launch.py",
                ]
            ),
        ],
        shell=False,
        output="screen",
    )

    rviz = ExecuteProcess(
        name="launch_rviz",
        cmd=[
            "ros2",
            "launch",
            PathJoinSubstitution(
                [
                    FindPackageShare("nav2_bringup"), 
                    "launch",
                    "rviz_launch.py",
                ]
            ),
        ],
        shell=False,
        output="screen",
    )

    # Create delayed launches using TimerAction
    delayed_toolbox = TimerAction(
        period=5.0,  # Wait 5 seconds after bringup
        actions=[
            LogInfo(msg="Starting SLAM Toolbox..."),
            toolbox
        ]
    )

    delayed_nav2 = TimerAction(
        period=10.0,  # Wait 10 seconds after bringup
        actions=[
            LogInfo(msg="Starting Nav2..."),
            nav2
        ]
    )

    delayed_rviz = TimerAction(
        period=15.0,  # Wait 15 seconds after bringup
        actions=[
            LogInfo(msg="Starting RViz..."),
            rviz
        ]
    )

    return LaunchDescription([
        bringup,
        delayed_toolbox,
        delayed_nav2,
        delayed_rviz
    ])






