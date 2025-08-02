#include "swing_drone/pub.hpp"

pub::pub() : Node("publisher") {
    dis_rate_publisher_ = this->create_publisher<swing_drone::msg::EulerAngles>("swing_drone/dis_rate", 10);
    actual_rate_publisher_ = this->create_publisher<swing_drone::msg::EulerAngles>("swing_drone/actual_rate", 10);
    pid_publisher_ = this->create_publisher<swing_drone::msg::Pid>("swing_drone/pid_values", 10);
    motor_publisher_ = this->create_publisher<actuator_msgs::msg::Actuators>("/swing_drone/gazebo/command/motor_speed", 10);
    swings_publisher_ = this->create_publisher<std_msgs::msg::Bool>("/joint_control", 10);
    RCLCPP_INFO(this->get_logger(), "Publisher node initialized");
}

void pub::publish_dis_rate(euler_angles des_rate) {
    auto msg = swing_drone::msg::EulerAngles();
    msg.roll = des_rate.roll;
    msg.pitch = des_rate.pitch;
    msg.yaw = des_rate.yaw;
    dis_rate_publisher_->publish(msg);
}

void pub::publish_actual_rate(euler_angles actual_rate) {
    auto msg = swing_drone::msg::EulerAngles();
    msg.roll = actual_rate.roll;
    msg.pitch = actual_rate.pitch;
    msg.yaw = actual_rate.yaw;
    actual_rate_publisher_->publish(msg);
}

void pub::pid_value_publish(PID_out_t pid_out) {
    auto msg = swing_drone::msg::Pid();
    msg.error_roll = pid_out.error.roll;
    msg.error_pitch = pid_out.error.pitch;
    msg.error_yaw = pid_out.error.yaw;
    msg.p_roll = pid_out.P_term.roll;
    msg.p_pitch = pid_out.P_term.pitch;
    msg.p_yaw = pid_out.P_term.yaw;
    msg.i_roll = pid_out.I_term.roll;
    msg.i_pitch = pid_out.I_term.pitch;
    msg.i_yaw = pid_out.I_term.yaw;
    msg.d_roll = pid_out.D_term.roll;
    msg.d_pitch = pid_out.D_term.pitch;
    msg.d_yaw = pid_out.D_term.yaw;
    msg.return_roll = pid_out.PID_return.roll;
    msg.return_pitch = pid_out.PID_return.pitch;
    msg.return_yaw = pid_out.PID_return.yaw;
    pid_publisher_->publish(msg);
}

void pub::publish_swings(bool swings) {
    auto msg = std_msgs::msg::Bool();
    msg.data = swings;
    swings_publisher_->publish(msg);
}

void pub::publish_motor_data(motor_data motor_data_pub) {
    auto msg = actuator_msgs::msg::Actuators();
    msg.velocity.resize(8);
    msg.velocity[0] = motor_data_pub.motor_A;
    msg.velocity[1] = motor_data_pub.motor_B;
    msg.velocity[2] = motor_data_pub.motor_C;
    msg.velocity[3] = motor_data_pub.motor_D;
    msg.velocity[4] = motor_data_pub.motor_E;
    msg.velocity[5] = motor_data_pub.motor_F;
    msg.velocity[6] = motor_data_pub.motor_G;
    msg.velocity[7] = motor_data_pub.motor_H;
    motor_publisher_->publish(msg);
}