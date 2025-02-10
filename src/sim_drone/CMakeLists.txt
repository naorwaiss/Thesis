cmake_minimum_required(VERSION 3.8)
project(sim_drone)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
add_compile_options(-Wall -Wextra -Wpedantic)
endif()
find_package(ament_cmake REQUIRED)
find_package(gazebo_ros REQUIRED)
# find_package(sensor_msgs REQUIRED)

install(DIRECTORY
launch
config
worlds
meshes
DESTINATION share/${PROJECT_NAME}
)


ament_package()