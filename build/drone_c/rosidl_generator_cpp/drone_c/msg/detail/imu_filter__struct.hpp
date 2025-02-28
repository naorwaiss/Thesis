// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from drone_c:msg/ImuFilter.idl
// generated code does not contain a copyright notice

#ifndef DRONE_C__MSG__DETAIL__IMU_FILTER__STRUCT_HPP_
#define DRONE_C__MSG__DETAIL__IMU_FILTER__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__drone_c__msg__ImuFilter __attribute__((deprecated))
#else
# define DEPRECATED__drone_c__msg__ImuFilter __declspec(deprecated)
#endif

namespace drone_c
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ImuFilter_
{
  using Type = ImuFilter_<ContainerAllocator>;

  explicit ImuFilter_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->acc_lpf_x = 0.0f;
      this->acc_lpf_y = 0.0f;
      this->acc_lpf_z = 0.0f;
      this->gyro_hpf_x = 0.0f;
      this->gyro_hpf_y = 0.0f;
      this->gyro_hpf_z = 0.0f;
      this->gyro_lpf_x = 0.0f;
      this->gyro_lpf_y = 0.0f;
      this->gyro_lpf_z = 0.0f;
      this->mag_lpf_x = 0.0f;
      this->mag_lpf_y = 0.0f;
      this->mag_lpf_z = 0.0f;
    }
  }

  explicit ImuFilter_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->acc_lpf_x = 0.0f;
      this->acc_lpf_y = 0.0f;
      this->acc_lpf_z = 0.0f;
      this->gyro_hpf_x = 0.0f;
      this->gyro_hpf_y = 0.0f;
      this->gyro_hpf_z = 0.0f;
      this->gyro_lpf_x = 0.0f;
      this->gyro_lpf_y = 0.0f;
      this->gyro_lpf_z = 0.0f;
      this->mag_lpf_x = 0.0f;
      this->mag_lpf_y = 0.0f;
      this->mag_lpf_z = 0.0f;
    }
  }

  // field types and members
  using _acc_lpf_x_type =
    float;
  _acc_lpf_x_type acc_lpf_x;
  using _acc_lpf_y_type =
    float;
  _acc_lpf_y_type acc_lpf_y;
  using _acc_lpf_z_type =
    float;
  _acc_lpf_z_type acc_lpf_z;
  using _gyro_hpf_x_type =
    float;
  _gyro_hpf_x_type gyro_hpf_x;
  using _gyro_hpf_y_type =
    float;
  _gyro_hpf_y_type gyro_hpf_y;
  using _gyro_hpf_z_type =
    float;
  _gyro_hpf_z_type gyro_hpf_z;
  using _gyro_lpf_x_type =
    float;
  _gyro_lpf_x_type gyro_lpf_x;
  using _gyro_lpf_y_type =
    float;
  _gyro_lpf_y_type gyro_lpf_y;
  using _gyro_lpf_z_type =
    float;
  _gyro_lpf_z_type gyro_lpf_z;
  using _mag_lpf_x_type =
    float;
  _mag_lpf_x_type mag_lpf_x;
  using _mag_lpf_y_type =
    float;
  _mag_lpf_y_type mag_lpf_y;
  using _mag_lpf_z_type =
    float;
  _mag_lpf_z_type mag_lpf_z;

  // setters for named parameter idiom
  Type & set__acc_lpf_x(
    const float & _arg)
  {
    this->acc_lpf_x = _arg;
    return *this;
  }
  Type & set__acc_lpf_y(
    const float & _arg)
  {
    this->acc_lpf_y = _arg;
    return *this;
  }
  Type & set__acc_lpf_z(
    const float & _arg)
  {
    this->acc_lpf_z = _arg;
    return *this;
  }
  Type & set__gyro_hpf_x(
    const float & _arg)
  {
    this->gyro_hpf_x = _arg;
    return *this;
  }
  Type & set__gyro_hpf_y(
    const float & _arg)
  {
    this->gyro_hpf_y = _arg;
    return *this;
  }
  Type & set__gyro_hpf_z(
    const float & _arg)
  {
    this->gyro_hpf_z = _arg;
    return *this;
  }
  Type & set__gyro_lpf_x(
    const float & _arg)
  {
    this->gyro_lpf_x = _arg;
    return *this;
  }
  Type & set__gyro_lpf_y(
    const float & _arg)
  {
    this->gyro_lpf_y = _arg;
    return *this;
  }
  Type & set__gyro_lpf_z(
    const float & _arg)
  {
    this->gyro_lpf_z = _arg;
    return *this;
  }
  Type & set__mag_lpf_x(
    const float & _arg)
  {
    this->mag_lpf_x = _arg;
    return *this;
  }
  Type & set__mag_lpf_y(
    const float & _arg)
  {
    this->mag_lpf_y = _arg;
    return *this;
  }
  Type & set__mag_lpf_z(
    const float & _arg)
  {
    this->mag_lpf_z = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    drone_c::msg::ImuFilter_<ContainerAllocator> *;
  using ConstRawPtr =
    const drone_c::msg::ImuFilter_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<drone_c::msg::ImuFilter_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<drone_c::msg::ImuFilter_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      drone_c::msg::ImuFilter_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<drone_c::msg::ImuFilter_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      drone_c::msg::ImuFilter_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<drone_c::msg::ImuFilter_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<drone_c::msg::ImuFilter_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<drone_c::msg::ImuFilter_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__drone_c__msg__ImuFilter
    std::shared_ptr<drone_c::msg::ImuFilter_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__drone_c__msg__ImuFilter
    std::shared_ptr<drone_c::msg::ImuFilter_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ImuFilter_ & other) const
  {
    if (this->acc_lpf_x != other.acc_lpf_x) {
      return false;
    }
    if (this->acc_lpf_y != other.acc_lpf_y) {
      return false;
    }
    if (this->acc_lpf_z != other.acc_lpf_z) {
      return false;
    }
    if (this->gyro_hpf_x != other.gyro_hpf_x) {
      return false;
    }
    if (this->gyro_hpf_y != other.gyro_hpf_y) {
      return false;
    }
    if (this->gyro_hpf_z != other.gyro_hpf_z) {
      return false;
    }
    if (this->gyro_lpf_x != other.gyro_lpf_x) {
      return false;
    }
    if (this->gyro_lpf_y != other.gyro_lpf_y) {
      return false;
    }
    if (this->gyro_lpf_z != other.gyro_lpf_z) {
      return false;
    }
    if (this->mag_lpf_x != other.mag_lpf_x) {
      return false;
    }
    if (this->mag_lpf_y != other.mag_lpf_y) {
      return false;
    }
    if (this->mag_lpf_z != other.mag_lpf_z) {
      return false;
    }
    return true;
  }
  bool operator!=(const ImuFilter_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ImuFilter_

// alias to use template instance with default allocator
using ImuFilter =
  drone_c::msg::ImuFilter_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace drone_c

#endif  // DRONE_C__MSG__DETAIL__IMU_FILTER__STRUCT_HPP_
