#ifndef ROS2_DATA_GRABER_HPP_
#define ROS2_DATA_GRABER_HPP_

#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "std_msgs/msg/float32_multi_array.hpp"

struct vector3{
    float x;
    float y;
    float z;
};

struct imu_data{
    vector3 accel;
    vector3 gyro;
};

struct euler_angles{
    float roll;
    float pitch;
    float yaw;
};

class data_graber_ros : public rclcpp::Node
{
public:
    data_graber_ros();
    imu_data _imu_read;
    euler_angles _eulier_read; 

private:
    void imu_topic_callback(const sensor_msgs::msg::Imu::SharedPtr msg);
    void euiler_topic_collback(const std_msgs::msg::Float32MultiArray::SharedPtr msg);
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_subscription_;
    rclcpp::Subscription<std_msgs::msg::Float32MultiArray>::SharedPtr euler_subscription_;
};

#endif  // ROS2_DATA_GRABER_HPP_

