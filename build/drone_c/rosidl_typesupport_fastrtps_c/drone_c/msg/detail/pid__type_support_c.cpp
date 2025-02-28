// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from drone_c:msg/Pid.idl
// generated code does not contain a copyright notice
#include "drone_c/msg/detail/pid__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "drone_c/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "drone_c/msg/detail/pid__struct.h"
#include "drone_c/msg/detail/pid__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif


// forward declare type support functions


using _Pid__ros_msg_type = drone_c__msg__Pid;

static bool _Pid__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _Pid__ros_msg_type * ros_message = static_cast<const _Pid__ros_msg_type *>(untyped_ros_message);
  // Field name: p_pitch
  {
    cdr << ros_message->p_pitch;
  }

  // Field name: p_roll
  {
    cdr << ros_message->p_roll;
  }

  // Field name: p_yaw
  {
    cdr << ros_message->p_yaw;
  }

  // Field name: i_pitch
  {
    cdr << ros_message->i_pitch;
  }

  // Field name: i_roll
  {
    cdr << ros_message->i_roll;
  }

  // Field name: i_yaw
  {
    cdr << ros_message->i_yaw;
  }

  // Field name: d_pitch
  {
    cdr << ros_message->d_pitch;
  }

  // Field name: d_roll
  {
    cdr << ros_message->d_roll;
  }

  // Field name: d_yaw
  {
    cdr << ros_message->d_yaw;
  }

  // Field name: sum_pitch
  {
    cdr << ros_message->sum_pitch;
  }

  // Field name: sum_roll
  {
    cdr << ros_message->sum_roll;
  }

  // Field name: sum_yaw
  {
    cdr << ros_message->sum_yaw;
  }

  return true;
}

static bool _Pid__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _Pid__ros_msg_type * ros_message = static_cast<_Pid__ros_msg_type *>(untyped_ros_message);
  // Field name: p_pitch
  {
    cdr >> ros_message->p_pitch;
  }

  // Field name: p_roll
  {
    cdr >> ros_message->p_roll;
  }

  // Field name: p_yaw
  {
    cdr >> ros_message->p_yaw;
  }

  // Field name: i_pitch
  {
    cdr >> ros_message->i_pitch;
  }

  // Field name: i_roll
  {
    cdr >> ros_message->i_roll;
  }

  // Field name: i_yaw
  {
    cdr >> ros_message->i_yaw;
  }

  // Field name: d_pitch
  {
    cdr >> ros_message->d_pitch;
  }

  // Field name: d_roll
  {
    cdr >> ros_message->d_roll;
  }

  // Field name: d_yaw
  {
    cdr >> ros_message->d_yaw;
  }

  // Field name: sum_pitch
  {
    cdr >> ros_message->sum_pitch;
  }

  // Field name: sum_roll
  {
    cdr >> ros_message->sum_roll;
  }

  // Field name: sum_yaw
  {
    cdr >> ros_message->sum_yaw;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_drone_c
size_t get_serialized_size_drone_c__msg__Pid(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _Pid__ros_msg_type * ros_message = static_cast<const _Pid__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name p_pitch
  {
    size_t item_size = sizeof(ros_message->p_pitch);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name p_roll
  {
    size_t item_size = sizeof(ros_message->p_roll);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name p_yaw
  {
    size_t item_size = sizeof(ros_message->p_yaw);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name i_pitch
  {
    size_t item_size = sizeof(ros_message->i_pitch);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name i_roll
  {
    size_t item_size = sizeof(ros_message->i_roll);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name i_yaw
  {
    size_t item_size = sizeof(ros_message->i_yaw);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name d_pitch
  {
    size_t item_size = sizeof(ros_message->d_pitch);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name d_roll
  {
    size_t item_size = sizeof(ros_message->d_roll);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name d_yaw
  {
    size_t item_size = sizeof(ros_message->d_yaw);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name sum_pitch
  {
    size_t item_size = sizeof(ros_message->sum_pitch);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name sum_roll
  {
    size_t item_size = sizeof(ros_message->sum_roll);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name sum_yaw
  {
    size_t item_size = sizeof(ros_message->sum_yaw);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _Pid__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_drone_c__msg__Pid(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_drone_c
size_t max_serialized_size_drone_c__msg__Pid(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // member: p_pitch
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: p_roll
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: p_yaw
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: i_pitch
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: i_roll
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: i_yaw
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: d_pitch
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: d_roll
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: d_yaw
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: sum_pitch
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: sum_roll
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: sum_yaw
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = drone_c__msg__Pid;
    is_plain =
      (
      offsetof(DataType, sum_yaw) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _Pid__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_drone_c__msg__Pid(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_Pid = {
  "drone_c::msg",
  "Pid",
  _Pid__cdr_serialize,
  _Pid__cdr_deserialize,
  _Pid__get_serialized_size,
  _Pid__max_serialized_size
};

static rosidl_message_type_support_t _Pid__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_Pid,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, drone_c, msg, Pid)() {
  return &_Pid__type_support;
}

#if defined(__cplusplus)
}
#endif
