// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from hamma_bot:msg/Pwm.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "hamma_bot/msg/detail/pwm__struct.h"
#include "hamma_bot/msg/detail/pwm__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool hamma_bot__msg__pwm__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[23];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("hamma_bot.msg._pwm.Pwm", full_classname_dest, 22) == 0);
  }
  hamma_bot__msg__Pwm * ros_message = _ros_message;
  {  // pwm_left_motor
    PyObject * field = PyObject_GetAttrString(_pymsg, "pwm_left_motor");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->pwm_left_motor = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // pwm_right_motor
    PyObject * field = PyObject_GetAttrString(_pymsg, "pwm_right_motor");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->pwm_right_motor = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * hamma_bot__msg__pwm__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of Pwm */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("hamma_bot.msg._pwm");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "Pwm");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  hamma_bot__msg__Pwm * ros_message = (hamma_bot__msg__Pwm *)raw_ros_message;
  {  // pwm_left_motor
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->pwm_left_motor);
    {
      int rc = PyObject_SetAttrString(_pymessage, "pwm_left_motor", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // pwm_right_motor
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->pwm_right_motor);
    {
      int rc = PyObject_SetAttrString(_pymessage, "pwm_right_motor", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
