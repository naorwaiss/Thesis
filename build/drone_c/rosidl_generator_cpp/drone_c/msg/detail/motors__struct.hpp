// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from drone_c:msg/Motors.idl
// generated code does not contain a copyright notice

#ifndef DRONE_C__MSG__DETAIL__MOTORS__STRUCT_HPP_
#define DRONE_C__MSG__DETAIL__MOTORS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__drone_c__msg__Motors __attribute__((deprecated))
#else
# define DEPRECATED__drone_c__msg__Motors __declspec(deprecated)
#endif

namespace drone_c
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Motors_
{
  using Type = Motors_<ContainerAllocator>;

  explicit Motors_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->front_right = 0.0f;
      this->back_right = 0.0f;
      this->front_left = 0.0f;
      this->back_left = 0.0f;
    }
  }

  explicit Motors_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->front_right = 0.0f;
      this->back_right = 0.0f;
      this->front_left = 0.0f;
      this->back_left = 0.0f;
    }
  }

  // field types and members
  using _front_right_type =
    float;
  _front_right_type front_right;
  using _back_right_type =
    float;
  _back_right_type back_right;
  using _front_left_type =
    float;
  _front_left_type front_left;
  using _back_left_type =
    float;
  _back_left_type back_left;

  // setters for named parameter idiom
  Type & set__front_right(
    const float & _arg)
  {
    this->front_right = _arg;
    return *this;
  }
  Type & set__back_right(
    const float & _arg)
  {
    this->back_right = _arg;
    return *this;
  }
  Type & set__front_left(
    const float & _arg)
  {
    this->front_left = _arg;
    return *this;
  }
  Type & set__back_left(
    const float & _arg)
  {
    this->back_left = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    drone_c::msg::Motors_<ContainerAllocator> *;
  using ConstRawPtr =
    const drone_c::msg::Motors_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<drone_c::msg::Motors_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<drone_c::msg::Motors_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      drone_c::msg::Motors_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<drone_c::msg::Motors_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      drone_c::msg::Motors_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<drone_c::msg::Motors_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<drone_c::msg::Motors_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<drone_c::msg::Motors_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__drone_c__msg__Motors
    std::shared_ptr<drone_c::msg::Motors_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__drone_c__msg__Motors
    std::shared_ptr<drone_c::msg::Motors_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Motors_ & other) const
  {
    if (this->front_right != other.front_right) {
      return false;
    }
    if (this->back_right != other.back_right) {
      return false;
    }
    if (this->front_left != other.front_left) {
      return false;
    }
    if (this->back_left != other.back_left) {
      return false;
    }
    return true;
  }
  bool operator!=(const Motors_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Motors_

// alias to use template instance with default allocator
using Motors =
  drone_c::msg::Motors_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace drone_c

#endif  // DRONE_C__MSG__DETAIL__MOTORS__STRUCT_HPP_
