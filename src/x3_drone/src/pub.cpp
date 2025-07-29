#include "x3_drone/pub.hpp"

pub::pub() : Node("publisher") {
    publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
    message = "Hello, ROS2 World!";
    RCLCPP_INFO(this->get_logger(), "Publisher node initialized");
}

void pub::publish(){
    auto msg = std_msgs::msg::String();
    msg.data = message;
    publisher_->publish(msg);
    RCLCPP_INFO(this->get_logger(), "Published: '%s'", msg.data.c_str());
} 




