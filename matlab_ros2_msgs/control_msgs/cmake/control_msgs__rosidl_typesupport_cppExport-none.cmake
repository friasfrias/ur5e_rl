#----------------------------------------------------------------
# Generated CMake target import file for configuration "None".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "control_msgs::control_msgs__rosidl_typesupport_cpp" for configuration "None"
set_property(TARGET control_msgs::control_msgs__rosidl_typesupport_cpp APPEND PROPERTY IMPORTED_CONFIGURATIONS NONE)
set_target_properties(control_msgs::control_msgs__rosidl_typesupport_cpp PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_NONE "rosidl_runtime_c::rosidl_runtime_c;rosidl_typesupport_cpp::rosidl_typesupport_cpp;rosidl_typesupport_c::rosidl_typesupport_c"
  IMPORTED_LOCATION_NONE "${_IMPORT_PREFIX}/lib/libcontrol_msgs__rosidl_typesupport_cpp.so"
  IMPORTED_SONAME_NONE "libcontrol_msgs__rosidl_typesupport_cpp.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS control_msgs::control_msgs__rosidl_typesupport_cpp )
list(APPEND _IMPORT_CHECK_FILES_FOR_control_msgs::control_msgs__rosidl_typesupport_cpp "${_IMPORT_PREFIX}/lib/libcontrol_msgs__rosidl_typesupport_cpp.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
