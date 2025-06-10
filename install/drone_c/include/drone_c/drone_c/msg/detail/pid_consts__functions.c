// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from drone_c:msg/PidConsts.idl
// generated code does not contain a copyright notice
#include "drone_c/msg/detail/pid_consts__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
drone_c__msg__PidConsts__init(drone_c__msg__PidConsts * msg)
{
  if (!msg) {
    return false;
  }
  // rate_pitch
  // rate_roll
  // stablize_pitch
  // stablize_roll
  // rate_yaw
  return true;
}

void
drone_c__msg__PidConsts__fini(drone_c__msg__PidConsts * msg)
{
  if (!msg) {
    return;
  }
  // rate_pitch
  // rate_roll
  // stablize_pitch
  // stablize_roll
  // rate_yaw
}

bool
drone_c__msg__PidConsts__are_equal(const drone_c__msg__PidConsts * lhs, const drone_c__msg__PidConsts * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // rate_pitch
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->rate_pitch[i] != rhs->rate_pitch[i]) {
      return false;
    }
  }
  // rate_roll
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->rate_roll[i] != rhs->rate_roll[i]) {
      return false;
    }
  }
  // stablize_pitch
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->stablize_pitch[i] != rhs->stablize_pitch[i]) {
      return false;
    }
  }
  // stablize_roll
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->stablize_roll[i] != rhs->stablize_roll[i]) {
      return false;
    }
  }
  // rate_yaw
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->rate_yaw[i] != rhs->rate_yaw[i]) {
      return false;
    }
  }
  return true;
}

bool
drone_c__msg__PidConsts__copy(
  const drone_c__msg__PidConsts * input,
  drone_c__msg__PidConsts * output)
{
  if (!input || !output) {
    return false;
  }
  // rate_pitch
  for (size_t i = 0; i < 3; ++i) {
    output->rate_pitch[i] = input->rate_pitch[i];
  }
  // rate_roll
  for (size_t i = 0; i < 3; ++i) {
    output->rate_roll[i] = input->rate_roll[i];
  }
  // stablize_pitch
  for (size_t i = 0; i < 3; ++i) {
    output->stablize_pitch[i] = input->stablize_pitch[i];
  }
  // stablize_roll
  for (size_t i = 0; i < 3; ++i) {
    output->stablize_roll[i] = input->stablize_roll[i];
  }
  // rate_yaw
  for (size_t i = 0; i < 3; ++i) {
    output->rate_yaw[i] = input->rate_yaw[i];
  }
  return true;
}

drone_c__msg__PidConsts *
drone_c__msg__PidConsts__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  drone_c__msg__PidConsts * msg = (drone_c__msg__PidConsts *)allocator.allocate(sizeof(drone_c__msg__PidConsts), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(drone_c__msg__PidConsts));
  bool success = drone_c__msg__PidConsts__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
drone_c__msg__PidConsts__destroy(drone_c__msg__PidConsts * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    drone_c__msg__PidConsts__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
drone_c__msg__PidConsts__Sequence__init(drone_c__msg__PidConsts__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  drone_c__msg__PidConsts * data = NULL;

  if (size) {
    data = (drone_c__msg__PidConsts *)allocator.zero_allocate(size, sizeof(drone_c__msg__PidConsts), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = drone_c__msg__PidConsts__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        drone_c__msg__PidConsts__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
drone_c__msg__PidConsts__Sequence__fini(drone_c__msg__PidConsts__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      drone_c__msg__PidConsts__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

drone_c__msg__PidConsts__Sequence *
drone_c__msg__PidConsts__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  drone_c__msg__PidConsts__Sequence * array = (drone_c__msg__PidConsts__Sequence *)allocator.allocate(sizeof(drone_c__msg__PidConsts__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = drone_c__msg__PidConsts__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
drone_c__msg__PidConsts__Sequence__destroy(drone_c__msg__PidConsts__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    drone_c__msg__PidConsts__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
drone_c__msg__PidConsts__Sequence__are_equal(const drone_c__msg__PidConsts__Sequence * lhs, const drone_c__msg__PidConsts__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!drone_c__msg__PidConsts__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
drone_c__msg__PidConsts__Sequence__copy(
  const drone_c__msg__PidConsts__Sequence * input,
  drone_c__msg__PidConsts__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(drone_c__msg__PidConsts);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    drone_c__msg__PidConsts * data =
      (drone_c__msg__PidConsts *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!drone_c__msg__PidConsts__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          drone_c__msg__PidConsts__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!drone_c__msg__PidConsts__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
