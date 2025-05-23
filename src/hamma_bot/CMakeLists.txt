cmake_minimum_required(VERSION 3.8)
project(hamma_bot)

# Specify C++ Standard
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find packages
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)  
find_package(geometry_msgs REQUIRED) 
find_package(rosidl_default_generators REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(xacro REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)


# Define message files
set(msg_files
  "msg/Pwm.msg"
  "msg/MotorData.msg"
)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
  DEPENDENCIES std_msgs
)

# === Build C++ executables ===
add_executable(twist_to_twiststamped_node src/twisstump_bridge.cpp)
add_executable(joy_twist_node src/joy_twist.cpp)

ament_target_dependencies(twist_to_twiststamped_node
  rclcpp
  geometry_msgs
)

ament_target_dependencies(joy_twist_node
  rclcpp
  sensor_msgs
  geometry_msgs
)





# === Install binaries ===
install(TARGETS
  twist_to_twiststamped_node
  joy_twist_node
  DESTINATION lib/${PROJECT_NAME}
)

# === Install launch and config files ===
install(
  DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

install(
  DIRECTORY config/
  DESTINATION share/${PROJECT_NAME}/config
)

# === Install URDF files ===
install(
  DIRECTORY urdf/
  DESTINATION share/${PROJECT_NAME}/urdf
)

# === Install world files ===
install(
  DIRECTORY worlds/
  DESTINATION share/${PROJECT_NAME}/worlds
)


# === Install rviz files ===
install(
  DIRECTORY rviz/
  DESTINATION share/${PROJECT_NAME}/rviz
)


# === Install Python scripts ===
install(PROGRAMS
  hamma_bot/hamma_bot_rtcom.py
  DESTINATION lib/${PROJECT_NAME}
)

# === If building for testing ===
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_cppcheck_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

# Export dependencies
ament_export_dependencies(rosidl_default_runtime)

ament_package()
