#smart command 

open the container with option to change 
xhost +local:docker

annd -rm to remove all the change when i close the contaianer

docker exec -it <container_name_or_id> bash -> to add another terminal 

xhost +local:docker

docker run -it \
  -v /home/naor/Desktop/naor/study/Thesis/src/swing_drone:/ros_ws/src/swing_drone \
  -e DISPLAY=$DISPLAY \
  -v /tmp/.X11-unix:/tmp/.X11-unix \
  ros2-jazzy-naor /bin/bash






ros2 topic pub /swing_drone/gazebo/command/motor_speed actuator_msgs/msg/Actuators "{velocity: [100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0]}"


ros2 topic pub /swing_drone/gazebo/command/motor_speed actuator_msgs/msg/Actuators "{velocity: [700.0, 700.0, 700.0, 700.0, 700.0, 700.0, 700.0, 700.0]}"


ros2 topic pub /joint_control std_msgs/msg/Bool "data: false"  false-> fix true -> free
