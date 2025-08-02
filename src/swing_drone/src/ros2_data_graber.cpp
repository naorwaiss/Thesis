#include "swing_drone/ros2_data_graber.hpp"

data_graber_ros::data_graber_ros(
    imu_data* imu_data_ptr,
    euler_angles* euler_angles_ptr,
    arm_data* arm_data_ptr,
    joy_data* joy_data_ptr
)
: Node("data_graber_ros")
{
    _imu_data = imu_data_ptr;
    _euler_angles_data = euler_angles_ptr;
    _arm_data = arm_data_ptr;
    _joy_data = joy_data_ptr;

    
    imu_subscription_ = this->create_subscription<sensor_msgs::msg::Imu>(
        "/imu", 10,
        std::bind(&data_graber_ros::imu_topic_callback, this, std::placeholders::_1)
    );

    // Create subscription for Euler angles data
    euler_subscription_ = this->create_subscription<geometry_msgs::msg::Vector3>(
        "/swing_drone/euler_angles", 10,
        std::bind(&data_graber_ros::euiler_topic_collback, this, std::placeholders::_1)
    );

    arm_subscription_ = this->create_subscription<sensor_msgs::msg::JointState>(
        "/arm_joint_states", 10,
        std::bind(&data_graber_ros::arm_topic_callback, this, std::placeholders::_1)
    );

    joy_subscription_ = this->create_subscription<sensor_msgs::msg::Joy>(
        "/joy", 10,
        std::bind(&data_graber_ros::joy_topic_callback, this, std::placeholders::_1)
    );

    // Create a timer to periodically check data arrival

    RCLCPP_INFO(this->get_logger(), "data_graber_ros node started.");
}

data_graber_ros::~data_graber_ros()
{
    RCLCPP_INFO(this->get_logger(), "data_graber_ros node shutting down.");
    // Explicitly reset subscriptions to ensure clean shutdown
    imu_subscription_.reset();
    euler_subscription_.reset();
    arm_subscription_.reset();
    joy_subscription_.reset();
}

void data_graber_ros::imu_topic_callback(const sensor_msgs::msg::Imu::SharedPtr msg)
{
    // Extract linear acceleration (using Eigen vector access)
    _imu_data->accel(0) = msg->linear_acceleration.x;
    _imu_data->accel(1) = msg->linear_acceleration.y;
    _imu_data->accel(2) = msg->linear_acceleration.z;

    // Extract angular velocity (using Eigen vector access)
    _imu_data->gyro(0) = msg->angular_velocity.x;
    _imu_data->gyro(1) = msg->angular_velocity.y;
    _imu_data->gyro(2) = msg->angular_velocity.z;

    imu_last_time_ = this->now().seconds();

}

void data_graber_ros::euiler_topic_collback(const geometry_msgs::msg::Vector3::SharedPtr msg)
{
    // Extract roll, pitch, yaw from Vector3 (x=roll, y=pitch, z=yaw)
    _euler_angles_data->roll = msg->x;
    _euler_angles_data->pitch = msg->y;
    _euler_angles_data->yaw = msg->z;

    euler_last_time_ = this->now().seconds();
}

void data_graber_ros::arm_topic_callback(const sensor_msgs::msg::JointState::SharedPtr msg)
{
    // Extract encoder positions and velocities
    for (size_t i = 0; i < 4; ++i)
    {
        _arm_data->encoder_position(i) = msg->position[i];
        _arm_data->encoder_velocity(i) = msg->velocity[i];
    }

    arm_last_time_ = this->now().seconds();
}

void data_graber_ros::joy_topic_callback(const sensor_msgs::msg::Joy::SharedPtr msg)
{
    _joy_data->pitch = msg->axes[1];
    _joy_data->roll = msg->axes[0];
    _joy_data->yaw = msg->axes[3];
    _joy_data->thrust = msg->axes[2];
    _joy_data->aux_1_arm = msg->axes[4];
    _joy_data->mode = msg->axes[5];
    _joy_data->aux_3 = msg->axes[6];
    _joy_data->aux_4 = msg->axes[7];
    joy_last_time_ = this->now().seconds();

    printf("joy_data->roll: %f, joy_data->pitch: %f, joy_data->yaw: %f, joy_data->thrust: %f, joy_data->aux_1_arm: %d, joy_data->mode: %d, joy_data->aux_3: %d, joy_data->aux_4: %d\n", _joy_data->roll, _joy_data->pitch, _joy_data->yaw, _joy_data->thrust, _joy_data->aux_1_arm, _joy_data->mode, _joy_data->aux_3, _joy_data->aux_4);
}

bool data_graber_ros::data_arrived_validatiom() {
    double current_time = this->now().seconds();
    if ((current_time - imu_last_time_ > heart_beat_timer) ||
        (current_time - euler_last_time_ > heart_beat_timer) ||
        (current_time - arm_last_time_ > heart_beat_timer) ||
        (current_time - joy_last_time_ > heart_beat_timer)) {
        activate_flag = false;
        RCLCPP_WARN(this->get_logger(), "One or more topics have not received messages in the last %d seconds.", heart_beat_timer);
    }
    else{
        activate_flag = true;
    }
    return activate_flag;
}
