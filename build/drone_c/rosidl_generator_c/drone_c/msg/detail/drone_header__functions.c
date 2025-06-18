// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from drone_c:msg/DroneHeader.idl
// generated code does not contain a copyright notice
#include "drone_c/msg/detail/drone_header__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
drone_c__msg__DroneHeader__init(drone_c__msg__DroneHeader * msg)
{
  if (!msg) {
    return false;
  }
  // mac_adress
  // drone_mode
  // drone_filter
  return true;
}

void
drone_c__msg__DroneHeader__fini(drone_c__msg__DroneHeader * msg)
{
  if (!msg) {
    return;
  }
  // mac_adress
  // drone_mode
  // drone_filter
}

bool
drone_c__msg__DroneHeader__are_equal(const drone_c__msg__DroneHeader * lhs, const drone_c__msg__DroneHeader * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // mac_adress
  for (size_t i = 0; i < 6; ++i) {
    if (lhs->mac_adress[i] != rhs->mac_adress[i]) {
      return false;
    }
  }
  // drone_mode
  if (lhs->drone_mode != rhs->drone_mode) {
    return false;
  }
  // drone_filter
  if (lhs->drone_filter != rhs->drone_filter) {
    return false;
  }
  return true;
}

bool
drone_c__msg__DroneHeader__copy(
  const drone_c__msg__DroneHeader * input,
  drone_c__msg__DroneHeader * output)
{
  if (!input || !output) {
    return false;
  }
  // mac_adress
  for (size_t i = 0; i < 6; ++i) {
    output->mac_adress[i] = input->mac_adress[i];
  }
  // drone_mode
  output->drone_mode = input->drone_mode;
  // drone_filter
  output->drone_filter = input->drone_filter;
  return true;
}

drone_c__msg__DroneHeader *
drone_c__msg__DroneHeader__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  drone_c__msg__DroneHeader * msg = (drone_c__msg__DroneHeader *)allocator.allocate(sizeof(drone_c__msg__DroneHeader), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(drone_c__msg__DroneHeader));
  bool success = drone_c__msg__DroneHeader__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
drone_c__msg__DroneHeader__destroy(drone_c__msg__DroneHeader * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    drone_c__msg__DroneHeader__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
drone_c__msg__DroneHeader__Sequence__init(drone_c__msg__DroneHeader__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  drone_c__msg__DroneHeader * data = NULL;

  if (size) {
    data = (drone_c__msg__DroneHeader *)allocator.zero_allocate(size, sizeof(drone_c__msg__DroneHeader), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = drone_c__msg__DroneHeader__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        drone_c__msg__DroneHeader__fini(&data[i - 1]);
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
drone_c__msg__DroneHeader__Sequence__fini(drone_c__msg__DroneHeader__Sequence * array)
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
      drone_c__msg__DroneHeader__fini(&array->data[i]);
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

drone_c__msg__DroneHeader__Sequence *
drone_c__msg__DroneHeader__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  drone_c__msg__DroneHeader__Sequence * array = (drone_c__msg__DroneHeader__Sequence *)allocator.allocate(sizeof(drone_c__msg__DroneHeader__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = drone_c__msg__DroneHeader__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
drone_c__msg__DroneHeader__Sequence__destroy(drone_c__msg__DroneHeader__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    drone_c__msg__DroneHeader__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
drone_c__msg__DroneHeader__Sequence__are_equal(const drone_c__msg__DroneHeader__Sequence * lhs, const drone_c__msg__DroneHeader__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!drone_c__msg__DroneHeader__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
drone_c__msg__DroneHeader__Sequence__copy(
  const drone_c__msg__DroneHeader__Sequence * input,
  drone_c__msg__DroneHeader__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(drone_c__msg__DroneHeader);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    drone_c__msg__DroneHeader * data =
      (drone_c__msg__DroneHeader *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!drone_c__msg__DroneHeader__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          drone_c__msg__DroneHeader__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!drone_c__msg__DroneHeader__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
