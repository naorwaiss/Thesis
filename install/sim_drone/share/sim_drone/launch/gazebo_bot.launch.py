
# from pathlib import Path
# from launch import LaunchDescription
# from launch.actions import DeclareLaunchArgument, SetEnvironmentVariable, IncludeLaunchDescription
# from launch_ros.actions import Node
# from ament_index_python.packages import get_package_share_directory
# from launch.substitutions import Command, LaunchConfiguration
# from launch.launch_description_sources import PythonLaunchDescriptionSource
# from launch_ros.parameter_descriptions import ParameterValue
# from launch.event_handlers import OnProcessStart


# def generate_launch_description():
#     # Define package directories
#     sim_dir = get_package_share_directory("sim_drone")
#     gazebo_ros_pkg = get_package_share_directory('gazebo_ros')

#     # Declare the model argument to specify the path to the URDF file
#     model_arg = DeclareLaunchArgument(
#         name="model",
#         default_value=str(Path(sim_dir) / "config" / "main.urdf.xacro"),
#         description="Absolute path to robot URDF file"
#     )

#     controller_config = Path(sim_dir) / "config" / "controller_config.yaml"

#     # Use xacro to process the URDF file and load the robot description parameter
#     robot_description = ParameterValue(
#         Command(["xacro ", LaunchConfiguration("model")]),  # Ensure proper command usage
#         value_type=str
#     )

#     # Node to publish the robot state
#     robot_state_publisher = Node(
#         package="robot_state_publisher",
#         executable="robot_state_publisher",
#         parameters=[{"robot_description": robot_description}],
#         output="screen"
#     )

#     # Set the environment variable for Gazebo model path (updated for model directory)
#     gazebo_resource_path = SetEnvironmentVariable(
#         name="GAZEBO_MODEL_PATH",
#         value=str(Path(sim_dir))  # Point to package root
#     )

#     # Include the Gazebo server launch file with logging level set to debug
#     start_gazebo_server_cmd = IncludeLaunchDescription(
#         PythonLaunchDescriptionSource(
#             str(Path(gazebo_ros_pkg) / 'launch' / 'gazebo.launch.py')
#         ),
#         launch_arguments={
#             'world': LaunchConfiguration('world'),
#             'verbose': 'true',  # Enable verbose logging for Gazebo
#             'log_level': 'debug'  # Set the logging level to debug
#         }.items()
#     )

#     # Spawn the robot in Gazebo using the robot_description with debug output
#     spawn_robot = Node(
#         package="gazebo_ros",
#         executable="spawn_entity.py",
#         arguments=["-topic", "/robot_description", "-entity", "drone_sim"],
#         output="screen",
#         additional_env={'GAZEBO_LOG_LEVEL': 'debug'}  # Set logging level for Gazebo
#     )

#     controller_manager = Node(
#         package="controller_manager",
#         executable="ros2_control_node",
#         parameters=[
#             {"robot_description": robot_description},
#             controller_config
#         ],
#         output="screen",
#     )

#     delay_controllers_after_spawn = RegisterEventHandler(
#         event_handler=OnProcessStart(
#             target_action=spawn_robot,
#             on_start=[
#                 Node(
#                     package="controller_manager",
#                     executable="spawner",
#                     arguments=["joint_state_broadcaster"],
#                     output="screen",
#                 ),
#                 Node(
#                     package="controller_manager",
#                     executable="spawner",
#                     arguments=["propeller_controllers"],
#                     output="screen",
#                 ),
#                 Node(
#                     package="controller_manager",
#                     executable="spawner",
#                     arguments=["imu_broadcaster"],
#                     output="screen",
#                 )
#             ]
#         )
#     )


#     # Declare the world file argument
#     declare_world_cmd = DeclareLaunchArgument(
#         name='world',
#         default_value=str(Path('/home/naor/Desktop/naor/study/hamama/src/sim_drone/worlds/empty.world')),
#         description='Path to the Gazebo world file'
#     )

#     # Return the complete LaunchDescription
#     return LaunchDescription([
#         declare_world_cmd,
#         model_arg,
#         robot_state_publisher,
#         gazebo_resource_path,
#         start_gazebo_server_cmd,
#         spawn_robot,
#         controller_manager,
#         delay_controllers_after_spawn
#     ])











from pathlib import Path
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, SetEnvironmentVariable, IncludeLaunchDescription
from launch.event_handlers import OnProcessStart
from launch.events import matches_action
from launch.actions import RegisterEventHandler
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
from launch.substitutions import Command, LaunchConfiguration
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.parameter_descriptions import ParameterValue

def generate_launch_description():
    # Define package directories
    sim_dir = get_package_share_directory("sim_drone")
    gazebo_ros_pkg = get_package_share_directory('gazebo_ros')

    # Declare the model argument to specify the path to the URDF file
    model_arg = DeclareLaunchArgument(
        name="model",
        default_value=str(Path(sim_dir) / "config" / "main.urdf.xacro"),
        description="Absolute path to robot URDF file"
    )

    # Controller configuration
    controller_config = Path(sim_dir) / "config" / "controller_config.yaml"

    # Use xacro to process the URDF file and load the robot description parameter
    robot_description = ParameterValue(
        Command(["xacro ", LaunchConfiguration("model")]),
        value_type=str
    )

    # Node to publish the robot state
    robot_state_publisher = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        parameters=[{"robot_description": robot_description}],
        output="screen"
    )

    # Set the environment variable for Gazebo model path
    gazebo_resource_path = SetEnvironmentVariable(
        name="GAZEBO_MODEL_PATH",
        value=str(Path(sim_dir))
    )

    # Include the Gazebo server launch file
    start_gazebo_server_cmd = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            str(Path(gazebo_ros_pkg) / 'launch' / 'gazebo.launch.py')
        ),
        launch_arguments={
            'world': LaunchConfiguration('world'),
            'verbose': 'true',
            'log_level': 'debug'
        }.items()
    )

    # Spawn the robot in Gazebo
    spawn_robot = Node(
        package="gazebo_ros",
        executable="spawn_entity.py",
        arguments=["-topic", "/robot_description", "-entity", "drone_sim"],
        output="screen"
    )

    # Controller Manager Node
    controller_manager = Node(
        package="controller_manager",
        executable="ros2_control_node",
        parameters=[
            {"robot_description": robot_description},
            str(controller_config)
        ],
        output="both",
        emulate_tty=True,
        prefix=['xterm -e gdb -ex run --args']  # or prefix=['gdbserver localhost:3000']


    )

    # Define controller spawner nodes
    joint_state_broadcaster_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["joint_state_broadcaster"],
        output="screen"
    )

    propeller_controller_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["propeller_controllers"],
        output="screen"
    )

    imu_broadcaster_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["imu_broadcaster"],
        output="screen"
    )

    # Delay controller spawning until after robot is spawned
    delay_controller_spawners = RegisterEventHandler(
        event_handler=OnProcessStart(
            target_action=spawn_robot,
            on_start=[
                joint_state_broadcaster_spawner,
                propeller_controller_spawner,
                imu_broadcaster_spawner
            ]
        )
    )

    # Declare the world file argument
    declare_world_cmd = DeclareLaunchArgument(
        name='world',
        default_value=str(Path(sim_dir) / 'worlds' / 'empty.world'),
        description='Path to the Gazebo world file'
    )

    # Return the complete LaunchDescription
    return LaunchDescription([
        declare_world_cmd,
        model_arg,
        robot_state_publisher,
        gazebo_resource_path,
        start_gazebo_server_cmd,
        spawn_robot,
        controller_manager,
        delay_controller_spawners
    ])