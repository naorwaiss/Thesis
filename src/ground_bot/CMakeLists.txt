cmake_minimum_required(VERSION 3.8)
project(ground_bot)

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


add_executable(joy_twist src/joy_twist.cpp)
ament_target_dependencies(joy_twist rclcpp sensor_msgs geometry_msgs)


# Define message files
set(msg_files
  "msg/Pwm.msg"
  "msg/MotorData.msg"
  "msg/RollerData.msg"
)


rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
  DEPENDENCIES std_msgs
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
  ground_bot/ground_bot_rtcom.py
  DESTINATION lib/${PROJECT_NAME}
)

install(TARGETS
  joy_twist
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
