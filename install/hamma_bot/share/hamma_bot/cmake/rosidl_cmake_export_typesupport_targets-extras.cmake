# generated from
# rosidl_cmake/cmake/template/rosidl_cmake_export_typesupport_targets.cmake.in

set(_exported_typesupport_targets
  "__rosidl_generator_c:hamma_bot__rosidl_generator_c;__rosidl_typesupport_fastrtps_c:hamma_bot__rosidl_typesupport_fastrtps_c;__rosidl_generator_cpp:hamma_bot__rosidl_generator_cpp;__rosidl_typesupport_fastrtps_cpp:hamma_bot__rosidl_typesupport_fastrtps_cpp;__rosidl_typesupport_introspection_c:hamma_bot__rosidl_typesupport_introspection_c;__rosidl_typesupport_c:hamma_bot__rosidl_typesupport_c;__rosidl_typesupport_introspection_cpp:hamma_bot__rosidl_typesupport_introspection_cpp;__rosidl_typesupport_cpp:hamma_bot__rosidl_typesupport_cpp;__rosidl_generator_py:hamma_bot__rosidl_generator_py")

# populate hamma_bot_TARGETS_<suffix>
if(NOT _exported_typesupport_targets STREQUAL "")
  # loop over typesupport targets
  foreach(_tuple ${_exported_typesupport_targets})
    string(REPLACE ":" ";" _tuple "${_tuple}")
    list(GET _tuple 0 _suffix)
    list(GET _tuple 1 _target)

    set(_target "hamma_bot::${_target}")
    if(NOT TARGET "${_target}")
      # the exported target must exist
      message(WARNING "Package 'hamma_bot' exports the typesupport target '${_target}' which doesn't exist")
    else()
      list(APPEND hamma_bot_TARGETS${_suffix} "${_target}")
    endif()
  endforeach()
endif()
