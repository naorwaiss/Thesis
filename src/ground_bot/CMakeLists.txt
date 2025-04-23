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
find_package(rosidl_default_generators REQUIRED)
find_package(ament_cmake_python REQUIRED) # Add this for Python support

# Define message files
set(msg_files
  "msg/Pwm.msg"
  "msg/MotorData.msg"
)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
  DEPENDENCIES std_msgs
)

install(
  DIRECTORY launch
  DESTINATION share/ground_bot/launch
)
install(
  DIRECTORY config
  DESTINATION share/ground_bot/config
)
# Install URDF files
install(
  DIRECTORY urdf/
  DESTINATION share/${PROJECT_NAME}/urdf
)



# install(
#   DIRECTORY ground_bot
#   DESTINATION lib/${PROJECT_NAME}
#   USE_SOURCE_PERMISSIONS
# )


# Install Python modules
# ament_python_install_package(${PROJECT_NAME})

# Install Python scripts (if any are executable scripts)
install(PROGRAMS
  ground_bot/ground_bot_rtcom.py  # Add your Python script here
  DESTINATION lib/${PROJECT_NAME}
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
