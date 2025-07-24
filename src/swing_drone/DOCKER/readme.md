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
  ros2-jazzy /bin/bash



gz topic -t /swing_drone/gazebo/command/motor_speed --msgtype gz.msgs.Actuators -p 'velocity:[700, 700, 700, 700 , 700 , 700 , 700 , 700]'