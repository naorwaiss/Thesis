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
find_package(Eigen3 REQUIRED)

# Include directories
include_directories(include)
include_directories(${EIGEN3_INCLUDE_DIR})

# Create a library for the micros timing functions
add_library(micros_lib src/micros_lib.cpp)

# Create a library for the data grabber
add_library(data_graber_lib src/ros2_data_graber.cpp)
target_link_libraries(data_graber_lib
  rclcpp::rclcpp
  ${geometry_msgs_TARGETS}
  ${sensor_msgs_TARGETS}
  ${std_msgs_TARGETS}
)

# Add executable for flight controller with all dependencies
add_executable(flight_controller src/flight_controller_main.cpp)
target_link_libraries(flight_controller
  micros_lib
  data_graber_lib
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
  micros_lib
  data_graber_lib
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
