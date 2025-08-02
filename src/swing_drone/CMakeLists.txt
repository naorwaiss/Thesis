

cmake_minimum_required(VERSION 3.8)
project(swing_drone)

# =============================================================================
# COMPILER SETTINGS
# =============================================================================
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# =============================================================================
# PACKAGE DEPENDENCIES
# =============================================================================
# Core ROS2 packages
find_package(ament_cmake REQUIRED)
find_package(rclpy REQUIRED)
find_package(rclcpp REQUIRED)

# Message packages
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(actuator_msgs REQUIRED)

# Other dependencies
find_package(Eigen3 REQUIRED)

# Message generation support
find_package(rosidl_default_generators REQUIRED)

# =============================================================================
# CUSTOM MESSAGE GENERATION
# =============================================================================
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/EulerAngles.msg"
  "msg/Pid.msg"
  DEPENDENCIES std_msgs geometry_msgs
)

# =============================================================================
# GAZEBO PLUGIN (DISTRO-SPECIFIC)
# =============================================================================

if("$ENV{ROS_DISTRO}" STREQUAL "jazzy")
  message(STATUS "Building for ROS2 Jazzy")
  
  # Find Gazebo packages
  find_package(gz-sim8 REQUIRED)
  find_package(gz-plugin2 REQUIRED)
  find_package(gz-transport13 REQUIRED)
  find_package(gz-msgs10 REQUIRED)

  # Create joint controller plugin
  add_library(joint_controller_plugin SHARED src/joint_controller_plugin.cpp)
  target_link_libraries(joint_controller_plugin
    rclcpp::rclcpp
    ${sensor_msgs_TARGETS}
    ${std_msgs_TARGETS}
    gz-sim8::gz-sim8
    gz-plugin2::gz-plugin2
    gz-transport13::gz-transport13
    gz-msgs10::gz-msgs10
  )

  # Install Gazebo plugin
  install(TARGETS joint_controller_plugin
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
  )
else()
  message(STATUS "Building for ROS2 ${ROS_DISTRO} - skipping Gazebo plugin")
endif()

# =============================================================================
# INCLUDE DIRECTORIES
# =============================================================================
include_directories(include)
include_directories(${EIGEN3_INCLUDE_DIR})

# =============================================================================
# UTILITY LIBRARIES
# =============================================================================
# Timing utilities
add_library(micros_lib src/micros_lib.cpp)

# =============================================================================
# CORE LIBRARIES
# =============================================================================
set(COMMON_DEPENDENCIES
  rclcpp::rclcpp
  ${sensor_msgs_TARGETS}
  ${std_msgs_TARGETS}
  ${actuator_msgs_TARGETS}
)

# Data grabber library
add_library(data_graber_lib src/ros2_data_graber.cpp)
target_link_libraries(data_graber_lib ${COMMON_DEPENDENCIES})

# Rate mode controller library
add_library(simple_rate_mode_lib src/simple_rate_mode.cpp)
target_link_libraries(simple_rate_mode_lib ${COMMON_DEPENDENCIES})

# Publisher library
add_library(pub_lib src/pub.cpp)
target_link_libraries(pub_lib ${COMMON_DEPENDENCIES})

# Standard operations library
add_library(std_operation_lib src/std_operation.cpp)
target_link_libraries(std_operation_lib ${COMMON_DEPENDENCIES})

# =============================================================================
# MESSAGE TYPE SUPPORT
# =============================================================================
rosidl_get_typesupport_target(cpp_typesupport_target ${PROJECT_NAME} rosidl_typesupport_cpp)

# Link custom message support to all libraries
set(CORE_LIBRARIES
  data_graber_lib
  simple_rate_mode_lib
  pub_lib
  std_operation_lib
)

foreach(lib ${CORE_LIBRARIES})
  target_link_libraries(${lib} ${cpp_typesupport_target})
  add_dependencies(${lib} ${PROJECT_NAME})
endforeach()

# =============================================================================
# MAIN EXECUTABLE
# =============================================================================
add_executable(flight_controller src/flight_controller_main.cpp)

target_link_libraries(flight_controller
  # Internal libraries
  micros_lib
  ${CORE_LIBRARIES}
  
  # ROS2 dependencies
  rclcpp::rclcpp
  ${geometry_msgs_TARGETS}
  ${sensor_msgs_TARGETS}
  ${std_msgs_TARGETS}
  ${actuator_msgs_TARGETS}
  ${cpp_typesupport_target}
)

# Ensure message generation before executable compilation
add_dependencies(flight_controller ${PROJECT_NAME})

# =============================================================================
# INSTALLATION
# =============================================================================
# Install headers
install(DIRECTORY include/
  DESTINATION include/
)

# Install shared libraries to standard lib/ directory for proper linking
install(TARGETS
  micros_lib
  ${CORE_LIBRARIES}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

# Install executables to package-specific directory
install(TARGETS
  flight_controller
  DESTINATION lib/${PROJECT_NAME}
)

# Install Python scripts
install(PROGRAMS
  script/quart_euler.py
  DESTINATION lib/${PROJECT_NAME}
)

# Install package resources
install(DIRECTORY
  urdf
  meshes
  launch
  rviz2
  worlds
  script
  DESTINATION share/${PROJECT_NAME}
)

# =============================================================================
# TESTING
# =============================================================================
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

# =============================================================================
# PACKAGE FINALIZATION
# =============================================================================
ament_package()
