
from pathlib import Path
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, SetEnvironmentVariable, IncludeLaunchDescription
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

    # Use xacro to process the URDF file and load the robot description parameter
    robot_description = ParameterValue(
        Command(["xacro ", LaunchConfiguration("model")]),  # Ensure proper command usage
        value_type=str
    )

    # Node to publish the robot state
    robot_state_publisher = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        parameters=[{"robot_description": robot_description}],
        output="screen"
    )

    # Set the environment variable for Gazebo model path (updated for model directory)
    gazebo_resource_path = SetEnvironmentVariable(
        name="GAZEBO_MODEL_PATH",
        value=str(Path(sim_dir))  # Point to package root
    )

    # Include the Gazebo server launch file with logging level set to debug
    start_gazebo_server_cmd = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            str(Path(gazebo_ros_pkg) / 'launch' / 'gazebo.launch.py')
        ),
        launch_arguments={
            'world': LaunchConfiguration('world'),
            'verbose': 'true',  # Enable verbose logging for Gazebo
            'log_level': 'debug'  # Set the logging level to debug
        }.items()
    )

    # Spawn the robot in Gazebo using the robot_description with debug output
    spawn_robot = Node(
        package="gazebo_ros",
        executable="spawn_entity.py",
        arguments=["-topic", "/robot_description", "-entity", "drone_sim"],
        output="screen",
        additional_env={'GAZEBO_LOG_LEVEL': 'debug'}  # Set logging level for Gazebo
    )

    # Declare the world file argument
    declare_world_cmd = DeclareLaunchArgument(
        name='world',
        default_value=str(Path('/home/naor/Desktop/naor/study/hamama/src/sim_drone/worlds/empty.world')),
        description='Path to the Gazebo world file'
    )

    # Return the complete LaunchDescription
    return LaunchDescription([
        declare_world_cmd,
        model_arg,
        robot_state_publisher,
        gazebo_resource_path,
        start_gazebo_server_cmd,
        spawn_robot
    ])
