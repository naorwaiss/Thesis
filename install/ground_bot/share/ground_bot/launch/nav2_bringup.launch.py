import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from nav2_common.launch import RewrittenYaml

def generate_launch_description():
    # Get the launch directory
    pkg_share = get_package_share_directory('ground_bot')
    nav2_params_path = os.path.join(pkg_share, 'config', 'nav2_params.yaml')

    # Create our own temporary YAML files that include substitutions
    param_substitutions = {
        'use_sim_time': 'True'
    }

    configured_params = RewrittenYaml(
        source_file=nav2_params_path,
        root_key='',
        param_rewrites=param_substitutions,
        convert_types=True
    )

    # Declare the launch arguments
    declare_use_sim_time_cmd = DeclareLaunchArgument(
        'use_sim_time',
        default_value='true',
        description='Use simulation (Gazebo) clock if true'
    )

    # Start the nav2_controller node
    start_controller_cmd = Node(
        package='nav2_controller',
        executable='controller_server',
        name='controller_server',
        output='screen',
        parameters=[configured_params],
        use_sim_time=True
    )

    # Start the nav2_planner node
    start_planner_cmd = Node(
        package='nav2_planner',
        executable='planner_server',
        name='planner_server',
        output='screen',
        parameters=[configured_params],
        use_sim_time=True
    )

    # Start the nav2_recoveries node
    start_recoveries_cmd = Node(
        package='nav2_recoveries',
        executable='recoveries_server',
        name='recoveries_server',
        output='screen',
        parameters=[configured_params],
        use_sim_time=True
    )

    # Start the nav2_bt_navigator node
    start_bt_navigator_cmd = Node(
        package='nav2_bt_navigator',
        executable='bt_navigator',
        name='bt_navigator',
        output='screen',
        parameters=[configured_params],
        use_sim_time=True
    )

    # Start the nav2_waypoint_follower node
    start_waypoint_follower_cmd = Node(
        package='nav2_waypoint_follower',
        executable='waypoint_follower',
        name='waypoint_follower',
        output='screen',
        parameters=[configured_params],
        use_sim_time=True
    )

    # Start the nav2_lifecycle_manager node
    start_lifecycle_manager_cmd = Node(
        package='nav2_lifecycle_manager',
        executable='lifecycle_manager',
        name='lifecycle_manager_navigation',
        output='screen',
        parameters=[{'use_sim_time': True},
                   {'autostart': True},
                   {'node_names': ['controller_server',
                                 'planner_server',
                                 'recoveries_server',
                                 'bt_navigator',
                                 'waypoint_follower']}]
    )

    # Create the launch description and populate
    ld = LaunchDescription()

    # Declare the launch options
    ld.add_action(declare_use_sim_time_cmd)

    # Add the nodes to launch
    ld.add_action(start_controller_cmd)
    ld.add_action(start_planner_cmd)
    ld.add_action(start_recoveries_cmd)
    ld.add_action(start_bt_navigator_cmd)
    ld.add_action(start_waypoint_follower_cmd)
    ld.add_action(start_lifecycle_manager_cmd)

    return ld 