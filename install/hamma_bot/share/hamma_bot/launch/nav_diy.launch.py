import os
from launch import LaunchDescription
from launch.actions import ExecuteProcess


def generate_launch_description():
    return LaunchDescription([
        ExecuteProcess(
            cmd=[
                'ros2', 'launch', 'slam_toolbox', 'online_async_launch.py',
                'params_file:=./config/mapper_params_online_async.yaml',
                'use_sim_time:=true'
            ],
            shell=False,
            output='screen',
        )
    ])
