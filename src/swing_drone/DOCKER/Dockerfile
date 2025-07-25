FROM osrf/ros:jazzy-desktop

ENV DEBIAN_FRONTEND=noninteractive
ENV LANG=C.UTF-8
ENV LC_ALL=C.UTF-8

# --- Step 1: Clean up existing ROS sources and install base tools
RUN rm -f /etc/apt/sources.list.d/ros2.list && \
    apt-get update && apt-get install -y \
    curl \
    wget \
    gnupg2 \
    lsb-release \
    software-properties-common

# --- Step 2: Since we're using jazzy base image, ROS is already configured
# Just update and upgrade the system
RUN apt-get update
RUN apt-get upgrade -y


# --- Install gazebo harmonic 

RUN apt-get update
RUN apt-get install -y curl lsb-release gnupg

RUN curl https://packages.osrfoundation.org/gazebo.gpg --output /usr/share/keyrings/pkgs-osrf-archive-keyring.gpg
RUN echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/pkgs-osrf-archive-keyring.gpg] http://packages.osrfoundation.org/gazebo/ubuntu-stable $(lsb_release -cs) main" | tee /etc/apt/sources.list.d/gazebo-stable.list > /dev/null
RUN apt-get update
RUN apt-get install -y gz-harmonic

# Setup ROS environment for all shell sessions
RUN echo "source /opt/ros/jazzy/setup.bash" >> /root/.bashrc

RUN apt install -y ros-jazzy-ros-gz-sim ros-jazzy-ros-gz-bridge ros-jazzy-gz-sim-vendor
RUN apt update
RUN apt install -y ros-jazzy-xacro
RUN apt install -y ros-jazzy-tf-transformations



# --- Entrypoint for GUI
COPY ./entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]
CMD ["bash"]
