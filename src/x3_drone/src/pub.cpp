#include "x3_drone/pub.hpp"

pub::pub() : Node("publisher") {
    dis_rate_publisher_ = this->create_publisher<x3_drone::msg::EulerAngles>("x3_drone/dis_rate", 10);
    actual_rate_publisher_ = this->create_publisher<x3_drone::msg::EulerAngles>("x3_drone/actual_rate", 10);
    pid_publisher_ = this->create_publisher<x3_drone::msg::Pid>("x3_drone/pid_values", 10);
    motor_publisher_ = this->create_publisher<actuator_msgs::msg::Actuators>("/x3_drone/gazebo/command/motor_speed", 10);
    RCLCPP_INFO(this->get_logger(), "Publisher node initialized");
}

void pub::publish_dis_rate(euler_angles des_rate){
    auto msg = x3_drone::msg::EulerAngles();
    msg.roll = des_rate.roll;
    msg.pitch = des_rate.pitch;
    msg.yaw = des_rate.yaw;
    dis_rate_publisher_->publish(msg);
} 

void pub::publish_actual_rate(euler_angles actual_rate){
    auto msg = x3_drone::msg::EulerAngles();
    msg.roll = actual_rate.roll;
    msg.pitch = actual_rate.pitch;
    msg.yaw = actual_rate.yaw;
    actual_rate_publisher_->publish(msg);
}


void pub::pid_value_publish(PID_out_t pid_out){
    auto msg = x3_drone::msg::Pid();
    msg.error_yaw = pid_out.error.yaw;
    msg.p_pitch = pid_out.P_term.pitch;
    msg.p_roll = pid_out.P_term.roll;
    msg.p_yaw = pid_out.P_term.yaw;
    msg.i_pitch = pid_out.I_term.pitch;
    msg.i_roll = pid_out.I_term.roll;
    msg.i_yaw = pid_out.I_term.yaw;
    msg.d_pitch = pid_out.D_term.pitch;
    msg.d_roll = pid_out.D_term.roll;
    msg.d_yaw = pid_out.D_term.yaw;
    msg.return_roll = pid_out.PID_return.roll;
    msg.return_pitch = pid_out.PID_return.pitch;
    msg.return_yaw = pid_out.PID_return.yaw;
    pid_publisher_->publish(msg);
}

void pub::publish_motor_data(motor_data motor_data){
    auto msg = actuator_msgs::msg::Actuators();
    msg.velocity.resize(4);
    msg.velocity[0] = motor_data.front_right;
    msg.velocity[1] = motor_data.rear_left;
    msg.velocity[2] = motor_data.front_left;
    msg.velocity[3] = motor_data.rear_right;
    
    motor_publisher_->publish(msg);
}