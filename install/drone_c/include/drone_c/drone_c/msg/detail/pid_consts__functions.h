// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from drone_c:msg/PidConsts.idl
// generated code does not contain a copyright notice

#ifndef DRONE_C__MSG__DETAIL__PID_CONSTS__FUNCTIONS_H_
#define DRONE_C__MSG__DETAIL__PID_CONSTS__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "drone_c/msg/rosidl_generator_c__visibility_control.h"

#include "drone_c/msg/detail/pid_consts__struct.h"

/// Initialize msg/PidConsts message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * drone_c__msg__PidConsts
 * )) before or use
 * drone_c__msg__PidConsts__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_drone_c
bool
drone_c__msg__PidConsts__init(drone_c__msg__PidConsts * msg);

/// Finalize msg/PidConsts message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_drone_c
void
drone_c__msg__PidConsts__fini(drone_c__msg__PidConsts * msg);

/// Create msg/PidConsts message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * drone_c__msg__PidConsts__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_drone_c
drone_c__msg__PidConsts *
drone_c__msg__PidConsts__create();

/// Destroy msg/PidConsts message.
/**
 * It calls
 * drone_c__msg__PidConsts__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_drone_c
void
drone_c__msg__PidConsts__destroy(drone_c__msg__PidConsts * msg);

/// Check for msg/PidConsts message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_drone_c
bool
drone_c__msg__PidConsts__are_equal(const drone_c__msg__PidConsts * lhs, const drone_c__msg__PidConsts * rhs);

/// Copy a msg/PidConsts message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_drone_c
bool
drone_c__msg__PidConsts__copy(
  const drone_c__msg__PidConsts * input,
  drone_c__msg__PidConsts * output);

/// Initialize array of msg/PidConsts messages.
/**
 * It allocates the memory for the number of elements and calls
 * drone_c__msg__PidConsts__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_drone_c
bool
drone_c__msg__PidConsts__Sequence__init(drone_c__msg__PidConsts__Sequence * array, size_t size);

/// Finalize array of msg/PidConsts messages.
/**
 * It calls
 * drone_c__msg__PidConsts__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_drone_c
void
drone_c__msg__PidConsts__Sequence__fini(drone_c__msg__PidConsts__Sequence * array);

/// Create array of msg/PidConsts messages.
/**
 * It allocates the memory for the array and calls
 * drone_c__msg__PidConsts__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_drone_c
drone_c__msg__PidConsts__Sequence *
drone_c__msg__PidConsts__Sequence__create(size_t size);

/// Destroy array of msg/PidConsts messages.
/**
 * It calls
 * drone_c__msg__PidConsts__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_drone_c
void
drone_c__msg__PidConsts__Sequence__destroy(drone_c__msg__PidConsts__Sequence * array);

/// Check for msg/PidConsts message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_drone_c
bool
drone_c__msg__PidConsts__Sequence__are_equal(const drone_c__msg__PidConsts__Sequence * lhs, const drone_c__msg__PidConsts__Sequence * rhs);

/// Copy an array of msg/PidConsts messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_drone_c
bool
drone_c__msg__PidConsts__Sequence__copy(
  const drone_c__msg__PidConsts__Sequence * input,
  drone_c__msg__PidConsts__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // DRONE_C__MSG__DETAIL__PID_CONSTS__FUNCTIONS_H_
