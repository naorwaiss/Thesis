// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from drone_c:msg/Pid.idl
// generated code does not contain a copyright notice

#ifndef DRONE_C__MSG__DETAIL__PID__BUILDER_HPP_
#define DRONE_C__MSG__DETAIL__PID__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "drone_c/msg/detail/pid__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace drone_c
{

namespace msg
{

namespace builder
{

class Init_Pid_sum_yaw
{
public:
  explicit Init_Pid_sum_yaw(::drone_c::msg::Pid & msg)
  : msg_(msg)
  {}
  ::drone_c::msg::Pid sum_yaw(::drone_c::msg::Pid::_sum_yaw_type arg)
  {
    msg_.sum_yaw = std::move(arg);
    return std::move(msg_);
  }

private:
  ::drone_c::msg::Pid msg_;
};

class Init_Pid_sum_roll
{
public:
  explicit Init_Pid_sum_roll(::drone_c::msg::Pid & msg)
  : msg_(msg)
  {}
  Init_Pid_sum_yaw sum_roll(::drone_c::msg::Pid::_sum_roll_type arg)
  {
    msg_.sum_roll = std::move(arg);
    return Init_Pid_sum_yaw(msg_);
  }

private:
  ::drone_c::msg::Pid msg_;
};

class Init_Pid_sum_pitch
{
public:
  explicit Init_Pid_sum_pitch(::drone_c::msg::Pid & msg)
  : msg_(msg)
  {}
  Init_Pid_sum_roll sum_pitch(::drone_c::msg::Pid::_sum_pitch_type arg)
  {
    msg_.sum_pitch = std::move(arg);
    return Init_Pid_sum_roll(msg_);
  }

private:
  ::drone_c::msg::Pid msg_;
};

class Init_Pid_d_yaw
{
public:
  explicit Init_Pid_d_yaw(::drone_c::msg::Pid & msg)
  : msg_(msg)
  {}
  Init_Pid_sum_pitch d_yaw(::drone_c::msg::Pid::_d_yaw_type arg)
  {
    msg_.d_yaw = std::move(arg);
    return Init_Pid_sum_pitch(msg_);
  }

private:
  ::drone_c::msg::Pid msg_;
};

class Init_Pid_d_roll
{
public:
  explicit Init_Pid_d_roll(::drone_c::msg::Pid & msg)
  : msg_(msg)
  {}
  Init_Pid_d_yaw d_roll(::drone_c::msg::Pid::_d_roll_type arg)
  {
    msg_.d_roll = std::move(arg);
    return Init_Pid_d_yaw(msg_);
  }

private:
  ::drone_c::msg::Pid msg_;
};

class Init_Pid_d_pitch
{
public:
  explicit Init_Pid_d_pitch(::drone_c::msg::Pid & msg)
  : msg_(msg)
  {}
  Init_Pid_d_roll d_pitch(::drone_c::msg::Pid::_d_pitch_type arg)
  {
    msg_.d_pitch = std::move(arg);
    return Init_Pid_d_roll(msg_);
  }

private:
  ::drone_c::msg::Pid msg_;
};

class Init_Pid_i_yaw
{
public:
  explicit Init_Pid_i_yaw(::drone_c::msg::Pid & msg)
  : msg_(msg)
  {}
  Init_Pid_d_pitch i_yaw(::drone_c::msg::Pid::_i_yaw_type arg)
  {
    msg_.i_yaw = std::move(arg);
    return Init_Pid_d_pitch(msg_);
  }

private:
  ::drone_c::msg::Pid msg_;
};

class Init_Pid_i_roll
{
public:
  explicit Init_Pid_i_roll(::drone_c::msg::Pid & msg)
  : msg_(msg)
  {}
  Init_Pid_i_yaw i_roll(::drone_c::msg::Pid::_i_roll_type arg)
  {
    msg_.i_roll = std::move(arg);
    return Init_Pid_i_yaw(msg_);
  }

private:
  ::drone_c::msg::Pid msg_;
};

class Init_Pid_i_pitch
{
public:
  explicit Init_Pid_i_pitch(::drone_c::msg::Pid & msg)
  : msg_(msg)
  {}
  Init_Pid_i_roll i_pitch(::drone_c::msg::Pid::_i_pitch_type arg)
  {
    msg_.i_pitch = std::move(arg);
    return Init_Pid_i_roll(msg_);
  }

private:
  ::drone_c::msg::Pid msg_;
};

class Init_Pid_p_yaw
{
public:
  explicit Init_Pid_p_yaw(::drone_c::msg::Pid & msg)
  : msg_(msg)
  {}
  Init_Pid_i_pitch p_yaw(::drone_c::msg::Pid::_p_yaw_type arg)
  {
    msg_.p_yaw = std::move(arg);
    return Init_Pid_i_pitch(msg_);
  }

private:
  ::drone_c::msg::Pid msg_;
};

class Init_Pid_p_roll
{
public:
  explicit Init_Pid_p_roll(::drone_c::msg::Pid & msg)
  : msg_(msg)
  {}
  Init_Pid_p_yaw p_roll(::drone_c::msg::Pid::_p_roll_type arg)
  {
    msg_.p_roll = std::move(arg);
    return Init_Pid_p_yaw(msg_);
  }

private:
  ::drone_c::msg::Pid msg_;
};

class Init_Pid_p_pitch
{
public:
  Init_Pid_p_pitch()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Pid_p_roll p_pitch(::drone_c::msg::Pid::_p_pitch_type arg)
  {
    msg_.p_pitch = std::move(arg);
    return Init_Pid_p_roll(msg_);
  }

private:
  ::drone_c::msg::Pid msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::drone_c::msg::Pid>()
{
  return drone_c::msg::builder::Init_Pid_p_pitch();
}

}  // namespace drone_c

#endif  // DRONE_C__MSG__DETAIL__PID__BUILDER_HPP_
