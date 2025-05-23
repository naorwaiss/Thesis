set(_AMENT_PACKAGE_NAME "hamma_bot")
set(hamma_bot_VERSION "0.0.1")
set(hamma_bot_MAINTAINER "Naor Weiss <naor-w@apeiro-motion.com>")
set(hamma_bot_BUILD_DEPENDS "rclcpp" "std_msgs" "control_msgs")
set(hamma_bot_BUILDTOOL_DEPENDS "ament_cmake" "rosidl_default_generators")
set(hamma_bot_BUILD_EXPORT_DEPENDS )
set(hamma_bot_BUILDTOOL_EXPORT_DEPENDS )
set(hamma_bot_EXEC_DEPENDS "rclcpp" "std_msgs" "rosidl_default_runtime" "joint_state_publisher" "robot_state_publisher" "ros2_control" "ros2_controllers" "rviz2" "xacro" "robot_localization" "ros_ign_gazebo" "ign_ros2_control" "topic_tools")
set(hamma_bot_TEST_DEPENDS "ament_lint_auto" "ament_lint_common")
set(hamma_bot_GROUP_DEPENDS )
set(hamma_bot_MEMBER_OF_GROUPS "rosidl_interface_packages")
set(hamma_bot_DEPRECATED "")
set(hamma_bot_EXPORT_TAGS)
list(APPEND hamma_bot_EXPORT_TAGS "<build_type>ament_cmake</build_type>")
