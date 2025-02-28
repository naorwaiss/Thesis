// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from drone_c:msg/EulerAngles.idl
// generated code does not contain a copyright notice

#ifndef DRONE_C__MSG__DETAIL__EULER_ANGLES__STRUCT_HPP_
#define DRONE_C__MSG__DETAIL__EULER_ANGLES__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__drone_c__msg__EulerAngles __attribute__((deprecated))
#else
# define DEPRECATED__drone_c__msg__EulerAngles __declspec(deprecated)
#endif

namespace drone_c
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct EulerAngles_
{
  using Type = EulerAngles_<ContainerAllocator>;

  explicit EulerAngles_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pitch = 0.0f;
      this->roll = 0.0f;
      this->yaw = 0.0f;
    }
  }

  explicit EulerAngles_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pitch = 0.0f;
      this->roll = 0.0f;
      this->yaw = 0.0f;
    }
  }

  // field types and members
  using _pitch_type =
    float;
  _pitch_type pitch;
  using _roll_type =
    float;
  _roll_type roll;
  using _yaw_type =
    float;
  _yaw_type yaw;

  // setters for named parameter idiom
  Type & set__pitch(
    const float & _arg)
  {
    this->pitch = _arg;
    return *this;
  }
  Type & set__roll(
    const float & _arg)
  {
    this->roll = _arg;
    return *this;
  }
  Type & set__yaw(
    const float & _arg)
  {
    this->yaw = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    drone_c::msg::EulerAngles_<ContainerAllocator> *;
  using ConstRawPtr =
    const drone_c::msg::EulerAngles_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<drone_c::msg::EulerAngles_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<drone_c::msg::EulerAngles_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      drone_c::msg::EulerAngles_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<drone_c::msg::EulerAngles_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      drone_c::msg::EulerAngles_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<drone_c::msg::EulerAngles_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<drone_c::msg::EulerAngles_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<drone_c::msg::EulerAngles_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__drone_c__msg__EulerAngles
    std::shared_ptr<drone_c::msg::EulerAngles_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__drone_c__msg__EulerAngles
    std::shared_ptr<drone_c::msg::EulerAngles_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const EulerAngles_ & other) const
  {
    if (this->pitch != other.pitch) {
      return false;
    }
    if (this->roll != other.roll) {
      return false;
    }
    if (this->yaw != other.yaw) {
      return false;
    }
    return true;
  }
  bool operator!=(const EulerAngles_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct EulerAngles_

// alias to use template instance with default allocator
using EulerAngles =
  drone_c::msg::EulerAngles_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace drone_c

#endif  // DRONE_C__MSG__DETAIL__EULER_ANGLES__STRUCT_HPP_
