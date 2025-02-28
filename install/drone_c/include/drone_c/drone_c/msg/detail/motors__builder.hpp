// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from drone_c:msg/Motors.idl
// generated code does not contain a copyright notice

#ifndef DRONE_C__MSG__DETAIL__MOTORS__BUILDER_HPP_
#define DRONE_C__MSG__DETAIL__MOTORS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "drone_c/msg/detail/motors__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace drone_c
{

namespace msg
{

namespace builder
{

class Init_Motors_back_left
{
public:
  explicit Init_Motors_back_left(::drone_c::msg::Motors & msg)
  : msg_(msg)
  {}
  ::drone_c::msg::Motors back_left(::drone_c::msg::Motors::_back_left_type arg)
  {
    msg_.back_left = std::move(arg);
    return std::move(msg_);
  }

private:
  ::drone_c::msg::Motors msg_;
};

class Init_Motors_front_left
{
public:
  explicit Init_Motors_front_left(::drone_c::msg::Motors & msg)
  : msg_(msg)
  {}
  Init_Motors_back_left front_left(::drone_c::msg::Motors::_front_left_type arg)
  {
    msg_.front_left = std::move(arg);
    return Init_Motors_back_left(msg_);
  }

private:
  ::drone_c::msg::Motors msg_;
};

class Init_Motors_back_right
{
public:
  explicit Init_Motors_back_right(::drone_c::msg::Motors & msg)
  : msg_(msg)
  {}
  Init_Motors_front_left back_right(::drone_c::msg::Motors::_back_right_type arg)
  {
    msg_.back_right = std::move(arg);
    return Init_Motors_front_left(msg_);
  }

private:
  ::drone_c::msg::Motors msg_;
};

class Init_Motors_front_right
{
public:
  Init_Motors_front_right()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Motors_back_right front_right(::drone_c::msg::Motors::_front_right_type arg)
  {
    msg_.front_right = std::move(arg);
    return Init_Motors_back_right(msg_);
  }

private:
  ::drone_c::msg::Motors msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::drone_c::msg::Motors>()
{
  return drone_c::msg::builder::Init_Motors_front_right();
}

}  // namespace drone_c

#endif  // DRONE_C__MSG__DETAIL__MOTORS__BUILDER_HPP_
