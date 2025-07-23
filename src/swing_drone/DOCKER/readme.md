#smart command 

open the container with option to change 
xhost +local:docker

docker run -it \
  --name ros2-persistent \
  --net=host \
  -e DISPLAY=$DISPLAY \
  -e QT_X11_NO_MITSHM=1 \
  -v /tmp/.X11-unix:/tmp/.X11-unix \
  ros2-humble-base /bin/bash


annd -rm to remove all the change when i close the contaianer

docker exec -it <container_name_or_id> bash -> to add another terminal 



