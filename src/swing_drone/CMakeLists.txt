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

# Find Gazebo packages for the plugin
find_package(gz-sim8 REQUIRED)
find_package(gz-plugin2 REQUIRED)
find_package(gz-transport13 REQUIRED)
find_package(gz-msgs10 REQUIRED)

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

# Create the joint controller plugin
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

# Install executables and libraries
install(TARGETS
  flight_controller
  micros_lib
  data_graber_lib
  DESTINATION lib/${PROJECT_NAME})

# Install the Gazebo plugin in the lib directory
install(TARGETS
  joint_controller_plugin
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
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
  script/joint_controller_test.py
  script/test_joint_movement.py
  DESTINATION lib/${PROJECT_NAME}
)

install(
  DIRECTORY urdf meshes launch rviz2 worlds script
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
