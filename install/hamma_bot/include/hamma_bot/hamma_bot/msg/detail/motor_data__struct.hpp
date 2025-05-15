// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from hamma_bot:msg/MotorData.idl
// generated code does not contain a copyright notice

#ifndef HAMMA_BOT__MSG__DETAIL__MOTOR_DATA__STRUCT_HPP_
#define HAMMA_BOT__MSG__DETAIL__MOTOR_DATA__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__hamma_bot__msg__MotorData __attribute__((deprecated))
#else
# define DEPRECATED__hamma_bot__msg__MotorData __declspec(deprecated)
#endif

namespace hamma_bot
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MotorData_
{
  using Type = MotorData_<ContainerAllocator>;

  explicit MotorData_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->left_motor = 0.0f;
      this->right_motor = 0.0f;
    }
  }

  explicit MotorData_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->left_motor = 0.0f;
      this->right_motor = 0.0f;
    }
  }

  // field types and members
  using _left_motor_type =
    float;
  _left_motor_type left_motor;
  using _right_motor_type =
    float;
  _right_motor_type right_motor;

  // setters for named parameter idiom
  Type & set__left_motor(
    const float & _arg)
  {
    this->left_motor = _arg;
    return *this;
  }
  Type & set__right_motor(
    const float & _arg)
  {
    this->right_motor = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    hamma_bot::msg::MotorData_<ContainerAllocator> *;
  using ConstRawPtr =
    const hamma_bot::msg::MotorData_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<hamma_bot::msg::MotorData_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<hamma_bot::msg::MotorData_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      hamma_bot::msg::MotorData_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<hamma_bot::msg::MotorData_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      hamma_bot::msg::MotorData_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<hamma_bot::msg::MotorData_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<hamma_bot::msg::MotorData_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<hamma_bot::msg::MotorData_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__hamma_bot__msg__MotorData
    std::shared_ptr<hamma_bot::msg::MotorData_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__hamma_bot__msg__MotorData
    std::shared_ptr<hamma_bot::msg::MotorData_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MotorData_ & other) const
  {
    if (this->left_motor != other.left_motor) {
      return false;
    }
    if (this->right_motor != other.right_motor) {
      return false;
    }
    return true;
  }
  bool operator!=(const MotorData_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MotorData_

// alias to use template instance with default allocator
using MotorData =
  hamma_bot::msg::MotorData_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace hamma_bot

#endif  // HAMMA_BOT__MSG__DETAIL__MOTOR_DATA__STRUCT_HPP_
