// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from ground_bot:msg/RollerData.idl
// generated code does not contain a copyright notice

#ifndef GROUND_BOT__MSG__DETAIL__ROLLER_DATA__STRUCT_HPP_
#define GROUND_BOT__MSG__DETAIL__ROLLER_DATA__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__ground_bot__msg__RollerData __attribute__((deprecated))
#else
# define DEPRECATED__ground_bot__msg__RollerData __declspec(deprecated)
#endif

namespace ground_bot
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct RollerData_
{
  using Type = RollerData_<ContainerAllocator>;

  explicit RollerData_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->tension = 0.0f;
      this->dis_tension = 0.0f;
      this->error = 0.0f;
    }
  }

  explicit RollerData_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->tension = 0.0f;
      this->dis_tension = 0.0f;
      this->error = 0.0f;
    }
  }

  // field types and members
  using _tension_type =
    float;
  _tension_type tension;
  using _dis_tension_type =
    float;
  _dis_tension_type dis_tension;
  using _error_type =
    float;
  _error_type error;

  // setters for named parameter idiom
  Type & set__tension(
    const float & _arg)
  {
    this->tension = _arg;
    return *this;
  }
  Type & set__dis_tension(
    const float & _arg)
  {
    this->dis_tension = _arg;
    return *this;
  }
  Type & set__error(
    const float & _arg)
  {
    this->error = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    ground_bot::msg::RollerData_<ContainerAllocator> *;
  using ConstRawPtr =
    const ground_bot::msg::RollerData_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<ground_bot::msg::RollerData_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<ground_bot::msg::RollerData_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      ground_bot::msg::RollerData_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<ground_bot::msg::RollerData_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      ground_bot::msg::RollerData_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<ground_bot::msg::RollerData_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<ground_bot::msg::RollerData_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<ground_bot::msg::RollerData_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__ground_bot__msg__RollerData
    std::shared_ptr<ground_bot::msg::RollerData_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__ground_bot__msg__RollerData
    std::shared_ptr<ground_bot::msg::RollerData_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RollerData_ & other) const
  {
    if (this->tension != other.tension) {
      return false;
    }
    if (this->dis_tension != other.dis_tension) {
      return false;
    }
    if (this->error != other.error) {
      return false;
    }
    return true;
  }
  bool operator!=(const RollerData_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RollerData_

// alias to use template instance with default allocator
using RollerData =
  ground_bot::msg::RollerData_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace ground_bot

#endif  // GROUND_BOT__MSG__DETAIL__ROLLER_DATA__STRUCT_HPP_
