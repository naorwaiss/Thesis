# generated from rosidl_generator_py/resource/_idl.py.em
# with input from drone_c:msg/DroneHeader.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

# Member 'mac_adress'
import numpy  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_DroneHeader(type):
    """Metaclass of message 'DroneHeader'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('drone_c')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'drone_c.msg.DroneHeader')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__drone_header
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__drone_header
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__drone_header
            cls._TYPE_SUPPORT = module.type_support_msg__msg__drone_header
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__drone_header

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class DroneHeader(metaclass=Metaclass_DroneHeader):
    """Message class 'DroneHeader'."""

    __slots__ = [
        '_mac_adress',
        '_drone_mode',
        '_drone_filter',
    ]

    _fields_and_field_types = {
        'mac_adress': 'int32[6]',
        'drone_mode': 'int32',
        'drone_filter': 'int32',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('int32'), 6),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        if 'mac_adress' not in kwargs:
            self.mac_adress = numpy.zeros(6, dtype=numpy.int32)
        else:
            self.mac_adress = numpy.array(kwargs.get('mac_adress'), dtype=numpy.int32)
            assert self.mac_adress.shape == (6, )
        self.drone_mode = kwargs.get('drone_mode', int())
        self.drone_filter = kwargs.get('drone_filter', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if all(self.mac_adress != other.mac_adress):
            return False
        if self.drone_mode != other.drone_mode:
            return False
        if self.drone_filter != other.drone_filter:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def mac_adress(self):
        """Message field 'mac_adress'."""
        return self._mac_adress

    @mac_adress.setter
    def mac_adress(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.int32, \
                "The 'mac_adress' numpy.ndarray() must have the dtype of 'numpy.int32'"
            assert value.size == 6, \
                "The 'mac_adress' numpy.ndarray() must have a size of 6"
            self._mac_adress = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 6 and
                 all(isinstance(v, int) for v in value) and
                 all(val >= -2147483648 and val < 2147483648 for val in value)), \
                "The 'mac_adress' field must be a set or sequence with length 6 and each value of type 'int' and each integer in [-2147483648, 2147483647]"
        self._mac_adress = numpy.array(value, dtype=numpy.int32)

    @builtins.property
    def drone_mode(self):
        """Message field 'drone_mode'."""
        return self._drone_mode

    @drone_mode.setter
    def drone_mode(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'drone_mode' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'drone_mode' field must be an integer in [-2147483648, 2147483647]"
        self._drone_mode = value

    @builtins.property
    def drone_filter(self):
        """Message field 'drone_filter'."""
        return self._drone_filter

    @drone_filter.setter
    def drone_filter(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'drone_filter' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'drone_filter' field must be an integer in [-2147483648, 2147483647]"
        self._drone_filter = value
