#include "swing_drone/ros2_data_graber.hpp"

data_graber_ros::data_graber_ros(
    imu_data* imu_data_ptr,
    euler_angles* euler_angles_ptr
)
: Node("data_graber_ros")
{
    _imu_data = imu_data_ptr;
    _euler_angles_data = euler_angles_ptr;
    // Initialize the data structures with default values
    _imu_data->accel = Eigen::Vector3d::Zero();
    _imu_data->gyro = Eigen::Vector3d::Zero();
    _euler_angles_data->roll = 0.0f;
    _euler_angles_data->pitch = 0.0f;
    _euler_angles_data->yaw = 0.0f;

    // Create subscription for IMU data
    imu_subscription_ = this->create_subscription<sensor_msgs::msg::Imu>(
        "/imu", 10,
        std::bind(&data_graber_ros::imu_topic_callback, this, std::placeholders::_1)
    );

    // Create subscription for Euler angles data
    euler_subscription_ = this->create_subscription<geometry_msgs::msg::Vector3>(
        "/swing_drone/euler_angles", 10,
        std::bind(&data_graber_ros::euiler_topic_collback, this, std::placeholders::_1)
    );

    RCLCPP_INFO(this->get_logger(), "data_graber_ros node started.");
}

data_graber_ros::~data_graber_ros()
{
    RCLCPP_INFO(this->get_logger(), "data_graber_ros node shutting down.");
    // Explicitly reset subscriptions to ensure clean shutdown
    imu_subscription_.reset();
    euler_subscription_.reset();
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

    RCLCPP_DEBUG(this->get_logger(), "IMU data updated - Accel: [%.2f, %.2f, %.2f], Gyro: [%.2f, %.2f, %.2f]",
                _imu_data->accel(0), _imu_data->accel(1), _imu_data->accel(2),
                _imu_data->gyro(0), _imu_data->gyro(1), _imu_data->gyro(2));
}

void data_graber_ros::euiler_topic_collback(const geometry_msgs::msg::Vector3::SharedPtr msg)
{
    // Extract roll, pitch, yaw from Vector3 (x=roll, y=pitch, z=yaw)
    _euler_angles_data->roll = msg->x;
    _euler_angles_data->pitch = msg->y;
    _euler_angles_data->yaw = msg->z;

    RCLCPP_DEBUG(this->get_logger(), "Euler angles updated - Roll: %.2f, Pitch: %.2f, Yaw: %.2f",
                _euler_angles_data->roll, _euler_angles_data->pitch, _euler_angles_data->yaw);
}

