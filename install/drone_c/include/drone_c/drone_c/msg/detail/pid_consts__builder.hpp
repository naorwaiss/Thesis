// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from drone_c:msg/PidConsts.idl
// generated code does not contain a copyright notice

#ifndef DRONE_C__MSG__DETAIL__PID_CONSTS__BUILDER_HPP_
#define DRONE_C__MSG__DETAIL__PID_CONSTS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "drone_c/msg/detail/pid_consts__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace drone_c
{

namespace msg
{

namespace builder
{

class Init_PidConsts_rate_yaw
{
public:
  explicit Init_PidConsts_rate_yaw(::drone_c::msg::PidConsts & msg)
  : msg_(msg)
  {}
  ::drone_c::msg::PidConsts rate_yaw(::drone_c::msg::PidConsts::_rate_yaw_type arg)
  {
    msg_.rate_yaw = std::move(arg);
    return std::move(msg_);
  }

private:
  ::drone_c::msg::PidConsts msg_;
};

class Init_PidConsts_stablize_roll
{
public:
  explicit Init_PidConsts_stablize_roll(::drone_c::msg::PidConsts & msg)
  : msg_(msg)
  {}
  Init_PidConsts_rate_yaw stablize_roll(::drone_c::msg::PidConsts::_stablize_roll_type arg)
  {
    msg_.stablize_roll = std::move(arg);
    return Init_PidConsts_rate_yaw(msg_);
  }

private:
  ::drone_c::msg::PidConsts msg_;
};

class Init_PidConsts_stablize_pitch
{
public:
  explicit Init_PidConsts_stablize_pitch(::drone_c::msg::PidConsts & msg)
  : msg_(msg)
  {}
  Init_PidConsts_stablize_roll stablize_pitch(::drone_c::msg::PidConsts::_stablize_pitch_type arg)
  {
    msg_.stablize_pitch = std::move(arg);
    return Init_PidConsts_stablize_roll(msg_);
  }

private:
  ::drone_c::msg::PidConsts msg_;
};

class Init_PidConsts_rate_roll
{
public:
  explicit Init_PidConsts_rate_roll(::drone_c::msg::PidConsts & msg)
  : msg_(msg)
  {}
  Init_PidConsts_stablize_pitch rate_roll(::drone_c::msg::PidConsts::_rate_roll_type arg)
  {
    msg_.rate_roll = std::move(arg);
    return Init_PidConsts_stablize_pitch(msg_);
  }

private:
  ::drone_c::msg::PidConsts msg_;
};

class Init_PidConsts_rate_pitch
{
public:
  Init_PidConsts_rate_pitch()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PidConsts_rate_roll rate_pitch(::drone_c::msg::PidConsts::_rate_pitch_type arg)
  {
    msg_.rate_pitch = std::move(arg);
    return Init_PidConsts_rate_roll(msg_);
  }

private:
  ::drone_c::msg::PidConsts msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::drone_c::msg::PidConsts>()
{
  return drone_c::msg::builder::Init_PidConsts_rate_pitch();
}

}  // namespace drone_c

#endif  // DRONE_C__MSG__DETAIL__PID_CONSTS__BUILDER_HPP_
