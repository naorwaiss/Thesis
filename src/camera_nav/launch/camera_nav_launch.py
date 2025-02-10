import os
import launch
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():
    pkg_nav2_bringup = FindPackageShare('nav2_bringup').find('nav2_bringup')
    bringup_launch_file = os.path.join(pkg_nav2_bringup, 'launch', 'bringup_launch.py')

    pkg_slam_toolbox = FindPackageShare('slam_toolbox').find('slam_toolbox')
    slam_launch_file = os.path.join(pkg_slam_toolbox, 'launch', 'online_async_launch.py')

    pkg_share = FindPackageShare('camera_nav').find('camera_nav')
    param_file = os.path.join(pkg_share, 'config', 'costmap_params.yaml')
    rviz_config_file = os.path.join(pkg_share, 'config', 'rviz_config.rviz')

    return launch.LaunchDescription([
        # Launch SLAM Toolbox
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(slam_launch_file),
            launch_arguments={'use_sim_time': 'false'}.items()
        ),
        # Launch Nav2 Bringup
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(bringup_launch_file),
            launch_arguments={
                'params_file': param_file,
                'use_sim_time': 'false'
            }.items()
        ),
        # Launch RViz
        launch.actions.ExecuteProcess(
            cmd=['rviz2', '-d', rviz_config_file],
            output='screen'
        )
    ])
