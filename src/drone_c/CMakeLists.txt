cmake_minimum_required(VERSION 3.8)
project(drone_c)

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
find_package(rosidl_default_generators REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

# Define message files
set(msg_files
  "msg/Pid.msg"
  "msg/EulerAngles.msg"
  "msg/Motors.msg"
  "msg/ImuFilter.msg"
  "msg/PidConsts.msg"
  "msg/DroneHeader.msg"
)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
  DEPENDENCIES std_msgs sensor_msgs geometry_msgs
)

# Install the rtcom Python package
install(DIRECTORY
  src/rtcom
  DESTINATION lib/${PROJECT_NAME}
  PATTERN "*.py"
  PATTERN "__pycache__" EXCLUDE
)

# Install Python scripts
install(PROGRAMS
  src/rtcom_teensy_ros.py
  DESTINATION lib/${PROJECT_NAME}
)

# Install launch files
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)


install(DIRECTORY
  plotjuggler
  DESTINATION share/${PROJECT_NAME}
)


# If building for testing
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_cppcheck_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

# Export dependencies
ament_export_dependencies(rosidl_default_runtime)

ament_package()
