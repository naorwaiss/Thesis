// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from ground_bot:msg/MotorData.idl
// generated code does not contain a copyright notice

#ifndef GROUND_BOT__MSG__DETAIL__MOTOR_DATA__BUILDER_HPP_
#define GROUND_BOT__MSG__DETAIL__MOTOR_DATA__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "ground_bot/msg/detail/motor_data__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace ground_bot
{

namespace msg
{

namespace builder
{

class Init_MotorData_right_motor
{
public:
  explicit Init_MotorData_right_motor(::ground_bot::msg::MotorData & msg)
  : msg_(msg)
  {}
  ::ground_bot::msg::MotorData right_motor(::ground_bot::msg::MotorData::_right_motor_type arg)
  {
    msg_.right_motor = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ground_bot::msg::MotorData msg_;
};

class Init_MotorData_left_motor
{
public:
  Init_MotorData_left_motor()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MotorData_right_motor left_motor(::ground_bot::msg::MotorData::_left_motor_type arg)
  {
    msg_.left_motor = std::move(arg);
    return Init_MotorData_right_motor(msg_);
  }

private:
  ::ground_bot::msg::MotorData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::ground_bot::msg::MotorData>()
{
  return ground_bot::msg::builder::Init_MotorData_left_motor();
}

}  // namespace ground_bot

#endif  // GROUND_BOT__MSG__DETAIL__MOTOR_DATA__BUILDER_HPP_
