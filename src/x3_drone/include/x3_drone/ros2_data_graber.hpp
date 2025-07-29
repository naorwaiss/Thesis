#ifndef ROS2_DATA_GRABER_HPP_
#define ROS2_DATA_GRABER_HPP_

#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "geometry_msgs/msg/vector3.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "x3_drone/Var_type.hpp"

class data_graber_ros : public rclcpp::Node
{
public:
    data_graber_ros(imu_data* imu_data_ptr, euler_angles* euler_angles_ptr, joy_data* joy_data_ptr);
    ~data_graber_ros();
    bool activate_flag = false;

private:
    int heart_beat_timer = 2.0;
    bool imu_received_ = false;
    double imu_last_time_ = 0.0;
    bool euler_received_ = false;
    double euler_last_time_ = 0.0;
    bool joy_received_ = false;
    double joy_last_time_ = 0.0;

    bool data_arrived_validatiom(); 
    imu_data* _imu_data;
    euler_angles* _euler_angles_data;
    joy_data* _joy_data;
    void imu_topic_callback(const sensor_msgs::msg::Imu::SharedPtr msg);
    void euiler_topic_collback(const geometry_msgs::msg::Vector3::SharedPtr msg);
    void joy_topic_callback(const sensor_msgs::msg::Joy::SharedPtr msg);
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_subscription_;
    rclcpp::Subscription<geometry_msgs::msg::Vector3>::SharedPtr euler_subscription_;
    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joy_subscription_;
};




#endif

