#include "swing_drone/ros2_data_graber.hpp"

data_graber_ros::data_graber_ros()
: Node("data_graber_ros")
{
    // Initialize the data structures
    _imu_read.accel = {0.0f, 0.0f, 0.0f};
    _imu_read.gyro = {0.0f, 0.0f, 0.0f};
    _eulier_read.roll = 0.0f;
    _eulier_read.pitch = 0.0f;
    _eulier_read.yaw = 0.0f;

    // Create subscription for IMU data
    imu_subscription_ = this->create_subscription<sensor_msgs::msg::Imu>(
        "/imu", 10,
        std::bind(&data_graber_ros::imu_topic_callback, this, std::placeholders::_1)
    );

    // Create subscription for Euler angles data
    euler_subscription_ = this->create_subscription<std_msgs::msg::Float32MultiArray>(
        "/euler_angles", 10,
        std::bind(&data_graber_ros::euiler_topic_collback, this, std::placeholders::_1)
    );

    RCLCPP_INFO(this->get_logger(), "data_graber_ros node started.");
}

void data_graber_ros::imu_topic_callback(const sensor_msgs::msg::Imu::SharedPtr msg)
{
    // Extract linear acceleration
    _imu_read.accel.x = msg->linear_acceleration.x;
    _imu_read.accel.y = msg->linear_acceleration.y;
    _imu_read.accel.z = msg->linear_acceleration.z;

    // Extract angular velocity
    _imu_read.gyro.x = msg->angular_velocity.x;
    _imu_read.gyro.y = msg->angular_velocity.y;
    _imu_read.gyro.z = msg->angular_velocity.z;

    RCLCPP_DEBUG(this->get_logger(), "IMU data updated - Accel: [%.2f, %.2f, %.2f], Gyro: [%.2f, %.2f, %.2f]",
                _imu_read.accel.x, _imu_read.accel.y, _imu_read.accel.z,
                _imu_read.gyro.x, _imu_read.gyro.y, _imu_read.gyro.z);
}

void data_graber_ros::euiler_topic_collback(const std_msgs::msg::Float32MultiArray::SharedPtr msg)
{
    // Assuming the array contains [roll, pitch, yaw]
    if (msg->data.size() >= 3) {
        _eulier_read.roll = msg->data[0];
        _eulier_read.pitch = msg->data[1];
        _eulier_read.yaw = msg->data[2];

        RCLCPP_DEBUG(this->get_logger(), "Euler angles updated - Roll: %.2f, Pitch: %.2f, Yaw: %.2f",
                    _eulier_read.roll, _eulier_read.pitch, _eulier_read.yaw);
    } else {
        RCLCPP_WARN(this->get_logger(), "Received Euler angle array with insufficient data (size: %zu)", msg->data.size());
    }
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<data_graber_ros>());
    rclcpp::shutdown();
    return 0;
}

