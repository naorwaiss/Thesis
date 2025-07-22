cmake_minimum_required(VERSION 3.8)
project(swing_drone)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find required packages
find_package(ament_cmake REQUIRED)
find_package(rclpy REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(ignition-gazebo6 REQUIRED)
find_package(ignition-plugin1 REQUIRED)
find_package(ignition-common4 REQUIRED)

# Include directories
include_directories(include)

# Build the joint wrench plugin
add_library(joint_wrench_plugin SHARED
  src/joint_wrench_plugin.cpp
)

ament_target_dependencies(joint_wrench_plugin
  rclcpp
  geometry_msgs
)

target_link_libraries(joint_wrench_plugin
  ${ignition-gazebo6_LIBRARIES}
  ${ignition-plugin1_LIBRARIES}
  ${ignition-common4_LIBRARIES}
)

target_include_directories(joint_wrench_plugin PUBLIC
  ${ignition-gazebo6_INCLUDE_DIRS}
  ${ignition-plugin1_INCLUDE_DIRS}
  ${ignition-common4_INCLUDE_DIRS}
)

# Install the plugin library
install(TARGETS joint_wrench_plugin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

# Install headers
install(DIRECTORY include/
  DESTINATION include/
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

# Install Python scripts
install(PROGRAMS
  script/quart_euilr.py
  DESTINATION lib/${PROJECT_NAME}
)

install(
  DIRECTORY urdf meshes launch rviz2 worlds config script
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
