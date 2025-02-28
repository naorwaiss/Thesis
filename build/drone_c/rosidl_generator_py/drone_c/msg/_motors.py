# generated from rosidl_generator_py/resource/_idl.py.em
# with input from drone_c:msg/Motors.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Motors(type):
    """Metaclass of message 'Motors'."""

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
                'drone_c.msg.Motors')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__motors
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__motors
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__motors
            cls._TYPE_SUPPORT = module.type_support_msg__msg__motors
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__motors

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Motors(metaclass=Metaclass_Motors):
    """Message class 'Motors'."""

    __slots__ = [
        '_front_right',
        '_back_right',
        '_front_left',
        '_back_left',
    ]

    _fields_and_field_types = {
        'front_right': 'float',
        'back_right': 'float',
        'front_left': 'float',
        'back_left': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.front_right = kwargs.get('front_right', float())
        self.back_right = kwargs.get('back_right', float())
        self.front_left = kwargs.get('front_left', float())
        self.back_left = kwargs.get('back_left', float())

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
        if self.front_right != other.front_right:
            return False
        if self.back_right != other.back_right:
            return False
        if self.front_left != other.front_left:
            return False
        if self.back_left != other.back_left:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def front_right(self):
        """Message field 'front_right'."""
        return self._front_right

    @front_right.setter
    def front_right(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'front_right' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'front_right' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._front_right = value

    @builtins.property
    def back_right(self):
        """Message field 'back_right'."""
        return self._back_right

    @back_right.setter
    def back_right(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'back_right' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'back_right' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._back_right = value

    @builtins.property
    def front_left(self):
        """Message field 'front_left'."""
        return self._front_left

    @front_left.setter
    def front_left(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'front_left' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'front_left' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._front_left = value

    @builtins.property
    def back_left(self):
        """Message field 'back_left'."""
        return self._back_left

    @back_left.setter
    def back_left(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'back_left' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'back_left' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._back_left = value
