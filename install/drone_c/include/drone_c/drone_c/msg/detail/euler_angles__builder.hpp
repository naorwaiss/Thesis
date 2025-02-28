// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from drone_c:msg/EulerAngles.idl
// generated code does not contain a copyright notice

#ifndef DRONE_C__MSG__DETAIL__EULER_ANGLES__BUILDER_HPP_
#define DRONE_C__MSG__DETAIL__EULER_ANGLES__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "drone_c/msg/detail/euler_angles__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace drone_c
{

namespace msg
{

namespace builder
{

class Init_EulerAngles_yaw
{
public:
  explicit Init_EulerAngles_yaw(::drone_c::msg::EulerAngles & msg)
  : msg_(msg)
  {}
  ::drone_c::msg::EulerAngles yaw(::drone_c::msg::EulerAngles::_yaw_type arg)
  {
    msg_.yaw = std::move(arg);
    return std::move(msg_);
  }

private:
  ::drone_c::msg::EulerAngles msg_;
};

class Init_EulerAngles_roll
{
public:
  explicit Init_EulerAngles_roll(::drone_c::msg::EulerAngles & msg)
  : msg_(msg)
  {}
  Init_EulerAngles_yaw roll(::drone_c::msg::EulerAngles::_roll_type arg)
  {
    msg_.roll = std::move(arg);
    return Init_EulerAngles_yaw(msg_);
  }

private:
  ::drone_c::msg::EulerAngles msg_;
};

class Init_EulerAngles_pitch
{
public:
  Init_EulerAngles_pitch()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_EulerAngles_roll pitch(::drone_c::msg::EulerAngles::_pitch_type arg)
  {
    msg_.pitch = std::move(arg);
    return Init_EulerAngles_roll(msg_);
  }

private:
  ::drone_c::msg::EulerAngles msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::drone_c::msg::EulerAngles>()
{
  return drone_c::msg::builder::Init_EulerAngles_pitch();
}

}  // namespace drone_c

#endif  // DRONE_C__MSG__DETAIL__EULER_ANGLES__BUILDER_HPP_
