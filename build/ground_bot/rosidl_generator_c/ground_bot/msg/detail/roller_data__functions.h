// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from ground_bot:msg/RollerData.idl
// generated code does not contain a copyright notice

#ifndef GROUND_BOT__MSG__DETAIL__ROLLER_DATA__FUNCTIONS_H_
#define GROUND_BOT__MSG__DETAIL__ROLLER_DATA__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "ground_bot/msg/rosidl_generator_c__visibility_control.h"

#include "ground_bot/msg/detail/roller_data__struct.h"

/// Initialize msg/RollerData message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * ground_bot__msg__RollerData
 * )) before or use
 * ground_bot__msg__RollerData__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_ground_bot
bool
ground_bot__msg__RollerData__init(ground_bot__msg__RollerData * msg);

/// Finalize msg/RollerData message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ground_bot
void
ground_bot__msg__RollerData__fini(ground_bot__msg__RollerData * msg);

/// Create msg/RollerData message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * ground_bot__msg__RollerData__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ground_bot
ground_bot__msg__RollerData *
ground_bot__msg__RollerData__create();

/// Destroy msg/RollerData message.
/**
 * It calls
 * ground_bot__msg__RollerData__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ground_bot
void
ground_bot__msg__RollerData__destroy(ground_bot__msg__RollerData * msg);

/// Check for msg/RollerData message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_ground_bot
bool
ground_bot__msg__RollerData__are_equal(const ground_bot__msg__RollerData * lhs, const ground_bot__msg__RollerData * rhs);

/// Copy a msg/RollerData message.
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
ROSIDL_GENERATOR_C_PUBLIC_ground_bot
bool
ground_bot__msg__RollerData__copy(
  const ground_bot__msg__RollerData * input,
  ground_bot__msg__RollerData * output);

/// Initialize array of msg/RollerData messages.
/**
 * It allocates the memory for the number of elements and calls
 * ground_bot__msg__RollerData__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_ground_bot
bool
ground_bot__msg__RollerData__Sequence__init(ground_bot__msg__RollerData__Sequence * array, size_t size);

/// Finalize array of msg/RollerData messages.
/**
 * It calls
 * ground_bot__msg__RollerData__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ground_bot
void
ground_bot__msg__RollerData__Sequence__fini(ground_bot__msg__RollerData__Sequence * array);

/// Create array of msg/RollerData messages.
/**
 * It allocates the memory for the array and calls
 * ground_bot__msg__RollerData__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ground_bot
ground_bot__msg__RollerData__Sequence *
ground_bot__msg__RollerData__Sequence__create(size_t size);

/// Destroy array of msg/RollerData messages.
/**
 * It calls
 * ground_bot__msg__RollerData__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ground_bot
void
ground_bot__msg__RollerData__Sequence__destroy(ground_bot__msg__RollerData__Sequence * array);

/// Check for msg/RollerData message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_ground_bot
bool
ground_bot__msg__RollerData__Sequence__are_equal(const ground_bot__msg__RollerData__Sequence * lhs, const ground_bot__msg__RollerData__Sequence * rhs);

/// Copy an array of msg/RollerData messages.
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
ROSIDL_GENERATOR_C_PUBLIC_ground_bot
bool
ground_bot__msg__RollerData__Sequence__copy(
  const ground_bot__msg__RollerData__Sequence * input,
  ground_bot__msg__RollerData__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // GROUND_BOT__MSG__DETAIL__ROLLER_DATA__FUNCTIONS_H_
