// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from drone_c:msg/Motors.idl
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
#include "drone_c/msg/detail/motors__struct.h"
#include "drone_c/msg/detail/motors__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool drone_c__msg__motors__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[27];
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
    assert(strncmp("drone_c.msg._motors.Motors", full_classname_dest, 26) == 0);
  }
  drone_c__msg__Motors * ros_message = _ros_message;
  {  // front_right
    PyObject * field = PyObject_GetAttrString(_pymsg, "front_right");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->front_right = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // back_right
    PyObject * field = PyObject_GetAttrString(_pymsg, "back_right");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->back_right = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // front_left
    PyObject * field = PyObject_GetAttrString(_pymsg, "front_left");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->front_left = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // back_left
    PyObject * field = PyObject_GetAttrString(_pymsg, "back_left");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->back_left = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * drone_c__msg__motors__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of Motors */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("drone_c.msg._motors");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "Motors");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  drone_c__msg__Motors * ros_message = (drone_c__msg__Motors *)raw_ros_message;
  {  // front_right
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->front_right);
    {
      int rc = PyObject_SetAttrString(_pymessage, "front_right", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // back_right
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->back_right);
    {
      int rc = PyObject_SetAttrString(_pymessage, "back_right", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // front_left
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->front_left);
    {
      int rc = PyObject_SetAttrString(_pymessage, "front_left", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // back_left
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->back_left);
    {
      int rc = PyObject_SetAttrString(_pymessage, "back_left", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
