#ifndef PUB_HPP
#define PUB_HPP

#include "Var_type.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/bool.hpp"
#include "swing_drone/msg/euler_angles.hpp"
#include "swing_drone/msg/pid.hpp"
#include "actuator_msgs/msg/actuators.hpp"

class pub : public rclcpp::Node {
   public:
    pub();
    void publish_dis_rate(euler_angles des_rate);
    void publish_actual_rate(euler_angles actual_rate);
    void pid_value_publish(PID_out_t pid_out);
    void publish_motor_data(motor_data motor_data_pub);
    void publish_swings(bool swings);
    
   private:
    rclcpp::Publisher<swing_drone::msg::EulerAngles>::SharedPtr dis_rate_publisher_;
    rclcpp::Publisher<swing_drone::msg::EulerAngles>::SharedPtr actual_rate_publisher_;
    rclcpp::Publisher<swing_drone::msg::Pid>::SharedPtr pid_publisher_;
    rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr swings_publisher_;
    rclcpp::Publisher<actuator_msgs::msg::Actuators>::SharedPtr motor_publisher_;
};
#endif
