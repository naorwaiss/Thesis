// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from ground_bot:msg/RollerData.idl
// generated code does not contain a copyright notice

#ifndef GROUND_BOT__MSG__DETAIL__ROLLER_DATA__BUILDER_HPP_
#define GROUND_BOT__MSG__DETAIL__ROLLER_DATA__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "ground_bot/msg/detail/roller_data__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace ground_bot
{

namespace msg
{

namespace builder
{

class Init_RollerData_error
{
public:
  explicit Init_RollerData_error(::ground_bot::msg::RollerData & msg)
  : msg_(msg)
  {}
  ::ground_bot::msg::RollerData error(::ground_bot::msg::RollerData::_error_type arg)
  {
    msg_.error = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ground_bot::msg::RollerData msg_;
};

class Init_RollerData_dis_tension
{
public:
  explicit Init_RollerData_dis_tension(::ground_bot::msg::RollerData & msg)
  : msg_(msg)
  {}
  Init_RollerData_error dis_tension(::ground_bot::msg::RollerData::_dis_tension_type arg)
  {
    msg_.dis_tension = std::move(arg);
    return Init_RollerData_error(msg_);
  }

private:
  ::ground_bot::msg::RollerData msg_;
};

class Init_RollerData_tension
{
public:
  Init_RollerData_tension()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RollerData_dis_tension tension(::ground_bot::msg::RollerData::_tension_type arg)
  {
    msg_.tension = std::move(arg);
    return Init_RollerData_dis_tension(msg_);
  }

private:
  ::ground_bot::msg::RollerData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::ground_bot::msg::RollerData>()
{
  return ground_bot::msg::builder::Init_RollerData_tension();
}

}  // namespace ground_bot

#endif  // GROUND_BOT__MSG__DETAIL__ROLLER_DATA__BUILDER_HPP_
