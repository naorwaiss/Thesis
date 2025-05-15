// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from hamma_bot:msg/Pwm.idl
// generated code does not contain a copyright notice

#ifndef HAMMA_BOT__MSG__DETAIL__PWM__BUILDER_HPP_
#define HAMMA_BOT__MSG__DETAIL__PWM__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "hamma_bot/msg/detail/pwm__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace hamma_bot
{

namespace msg
{

namespace builder
{

class Init_Pwm_pwm_right_motor
{
public:
  explicit Init_Pwm_pwm_right_motor(::hamma_bot::msg::Pwm & msg)
  : msg_(msg)
  {}
  ::hamma_bot::msg::Pwm pwm_right_motor(::hamma_bot::msg::Pwm::_pwm_right_motor_type arg)
  {
    msg_.pwm_right_motor = std::move(arg);
    return std::move(msg_);
  }

private:
  ::hamma_bot::msg::Pwm msg_;
};

class Init_Pwm_pwm_left_motor
{
public:
  Init_Pwm_pwm_left_motor()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Pwm_pwm_right_motor pwm_left_motor(::hamma_bot::msg::Pwm::_pwm_left_motor_type arg)
  {
    msg_.pwm_left_motor = std::move(arg);
    return Init_Pwm_pwm_right_motor(msg_);
  }

private:
  ::hamma_bot::msg::Pwm msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::hamma_bot::msg::Pwm>()
{
  return hamma_bot::msg::builder::Init_Pwm_pwm_left_motor();
}

}  // namespace hamma_bot

#endif  // HAMMA_BOT__MSG__DETAIL__PWM__BUILDER_HPP_
