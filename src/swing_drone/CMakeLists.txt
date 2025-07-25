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
find_package(std_msgs REQUIRED)

# Include directories
include_directories(include)

# Add executable for flight controller
add_executable(flight_controller src/flight_controller_main.cpp)

# Add executable for imu graber with ROS2 dependencies
add_executable(imu_graber src/ros2_data_graber.cpp)
target_link_libraries(imu_graber
  rclcpp::rclcpp
  ${geometry_msgs_TARGETS}
  ${sensor_msgs_TARGETS}
  ${std_msgs_TARGETS}
)

# Install headers
install(DIRECTORY include/
  DESTINATION include/
)

# Install executables
install(TARGETS
  flight_controller
  imu_graber
  DESTINATION lib/${PROJECT_NAME})

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
