// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from drone_c:msg/Pid.idl
// generated code does not contain a copyright notice
#include "drone_c/msg/detail/pid__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
drone_c__msg__Pid__init(drone_c__msg__Pid * msg)
{
  if (!msg) {
    return false;
  }
  // error_pitch
  // error_roll
  // error_yaw
  // p_pitch
  // p_roll
  // p_yaw
  // i_pitch
  // i_roll
  // i_yaw
  // d_pitch
  // d_roll
  // d_yaw
  // sum_pitch
  // sum_roll
  // sum_yaw
  return true;
}

void
drone_c__msg__Pid__fini(drone_c__msg__Pid * msg)
{
  if (!msg) {
    return;
  }
  // error_pitch
  // error_roll
  // error_yaw
  // p_pitch
  // p_roll
  // p_yaw
  // i_pitch
  // i_roll
  // i_yaw
  // d_pitch
  // d_roll
  // d_yaw
  // sum_pitch
  // sum_roll
  // sum_yaw
}

bool
drone_c__msg__Pid__are_equal(const drone_c__msg__Pid * lhs, const drone_c__msg__Pid * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // error_pitch
  if (lhs->error_pitch != rhs->error_pitch) {
    return false;
  }
  // error_roll
  if (lhs->error_roll != rhs->error_roll) {
    return false;
  }
  // error_yaw
  if (lhs->error_yaw != rhs->error_yaw) {
    return false;
  }
  // p_pitch
  if (lhs->p_pitch != rhs->p_pitch) {
    return false;
  }
  // p_roll
  if (lhs->p_roll != rhs->p_roll) {
    return false;
  }
  // p_yaw
  if (lhs->p_yaw != rhs->p_yaw) {
    return false;
  }
  // i_pitch
  if (lhs->i_pitch != rhs->i_pitch) {
    return false;
  }
  // i_roll
  if (lhs->i_roll != rhs->i_roll) {
    return false;
  }
  // i_yaw
  if (lhs->i_yaw != rhs->i_yaw) {
    return false;
  }
  // d_pitch
  if (lhs->d_pitch != rhs->d_pitch) {
    return false;
  }
  // d_roll
  if (lhs->d_roll != rhs->d_roll) {
    return false;
  }
  // d_yaw
  if (lhs->d_yaw != rhs->d_yaw) {
    return false;
  }
  // sum_pitch
  if (lhs->sum_pitch != rhs->sum_pitch) {
    return false;
  }
  // sum_roll
  if (lhs->sum_roll != rhs->sum_roll) {
    return false;
  }
  // sum_yaw
  if (lhs->sum_yaw != rhs->sum_yaw) {
    return false;
  }
  return true;
}

bool
drone_c__msg__Pid__copy(
  const drone_c__msg__Pid * input,
  drone_c__msg__Pid * output)
{
  if (!input || !output) {
    return false;
  }
  // error_pitch
  output->error_pitch = input->error_pitch;
  // error_roll
  output->error_roll = input->error_roll;
  // error_yaw
  output->error_yaw = input->error_yaw;
  // p_pitch
  output->p_pitch = input->p_pitch;
  // p_roll
  output->p_roll = input->p_roll;
  // p_yaw
  output->p_yaw = input->p_yaw;
  // i_pitch
  output->i_pitch = input->i_pitch;
  // i_roll
  output->i_roll = input->i_roll;
  // i_yaw
  output->i_yaw = input->i_yaw;
  // d_pitch
  output->d_pitch = input->d_pitch;
  // d_roll
  output->d_roll = input->d_roll;
  // d_yaw
  output->d_yaw = input->d_yaw;
  // sum_pitch
  output->sum_pitch = input->sum_pitch;
  // sum_roll
  output->sum_roll = input->sum_roll;
  // sum_yaw
  output->sum_yaw = input->sum_yaw;
  return true;
}

drone_c__msg__Pid *
drone_c__msg__Pid__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  drone_c__msg__Pid * msg = (drone_c__msg__Pid *)allocator.allocate(sizeof(drone_c__msg__Pid), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(drone_c__msg__Pid));
  bool success = drone_c__msg__Pid__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
drone_c__msg__Pid__destroy(drone_c__msg__Pid * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    drone_c__msg__Pid__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
drone_c__msg__Pid__Sequence__init(drone_c__msg__Pid__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  drone_c__msg__Pid * data = NULL;

  if (size) {
    data = (drone_c__msg__Pid *)allocator.zero_allocate(size, sizeof(drone_c__msg__Pid), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = drone_c__msg__Pid__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        drone_c__msg__Pid__fini(&data[i - 1]);
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
drone_c__msg__Pid__Sequence__fini(drone_c__msg__Pid__Sequence * array)
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
      drone_c__msg__Pid__fini(&array->data[i]);
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

drone_c__msg__Pid__Sequence *
drone_c__msg__Pid__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  drone_c__msg__Pid__Sequence * array = (drone_c__msg__Pid__Sequence *)allocator.allocate(sizeof(drone_c__msg__Pid__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = drone_c__msg__Pid__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
drone_c__msg__Pid__Sequence__destroy(drone_c__msg__Pid__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    drone_c__msg__Pid__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
drone_c__msg__Pid__Sequence__are_equal(const drone_c__msg__Pid__Sequence * lhs, const drone_c__msg__Pid__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!drone_c__msg__Pid__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
drone_c__msg__Pid__Sequence__copy(
  const drone_c__msg__Pid__Sequence * input,
  drone_c__msg__Pid__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(drone_c__msg__Pid);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    drone_c__msg__Pid * data =
      (drone_c__msg__Pid *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!drone_c__msg__Pid__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          drone_c__msg__Pid__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!drone_c__msg__Pid__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
