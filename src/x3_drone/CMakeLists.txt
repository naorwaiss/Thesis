cmake_minimum_required(VERSION 3.8)
project(x3_drone)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(ros_gz_sim REQUIRED)
find_package(ros_gz_bridge REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(actuator_msgs REQUIRED)

# Include directories
include_directories(include)

add_executable(flight_controller src/flight_controller_main.cpp src/ros2_data_graber.cpp src/micros_lib.cpp src/pub.cpp src/rate_mode.cpp)
ament_target_dependencies(flight_controller rclcpp std_msgs sensor_msgs geometry_msgs tf2 tf2_ros tf2_geometry_msgs actuator_msgs)
target_link_libraries(flight_controller Eigen3::Eigen)

# Generate interfaces
set(msg_files
  "msg/EulerAngles.msg"
  "msg/Pid.msg"
)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
  DEPENDENCIES std_msgs
)

# Make sure the executable depends on the generated messages
rosidl_get_typesupport_target(cpp_typesupport_target ${PROJECT_NAME} "rosidl_typesupport_cpp")
target_link_libraries(flight_controller "${cpp_typesupport_target}")

# Install targets
install(TARGETS
  flight_controller
  DESTINATION lib/${PROJECT_NAME}
)


install(
  DIRECTORY meshes launch worlds script
  DESTINATION share/${PROJECT_NAME}
)


install(FILES
  model.sdf
  model.config
  DESTINATION share/${PROJECT_NAME}/
)

install(PROGRAMS
  script/quart_euilr.py
  DESTINATION lib/${PROJECT_NAME}
)


# Install any additional directories
install(DIRECTORY thumbnails/
  DESTINATION share/${PROJECT_NAME}/thumbnails/
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
