#ifndef ROS2_DATA_GRABER_HPP_
#define ROS2_DATA_GRABER_HPP_

#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "geometry_msgs/msg/vector3.hpp"
#include "swing_drone/Var_type.hpp"

class data_graber_ros : public rclcpp::Node
{
public:
    data_graber_ros(imu_data* imu_data_ptr, euler_angles* euler_angles_ptr);
    ~data_graber_ros();

private:
    imu_data* _imu_data;
    euler_angles* _euler_angles_data;
    void imu_topic_callback(const sensor_msgs::msg::Imu::SharedPtr msg);
    void euiler_topic_collback(const geometry_msgs::msg::Vector3::SharedPtr msg);
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_subscription_;
    rclcpp::Subscription<geometry_msgs::msg::Vector3>::SharedPtr euler_subscription_;
};

#endif

