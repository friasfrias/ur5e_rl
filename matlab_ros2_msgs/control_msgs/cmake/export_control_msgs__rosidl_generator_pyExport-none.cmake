#----------------------------------------------------------------
# Generated CMake target import file for configuration "None".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "control_msgs::control_msgs__rosidl_generator_py" for configuration "None"
set_property(TARGET control_msgs::control_msgs__rosidl_generator_py APPEND PROPERTY IMPORTED_CONFIGURATIONS NONE)
set_target_properties(control_msgs::control_msgs__rosidl_generator_py PROPERTIES
  IMPORTED_LOCATION_NONE "${_IMPORT_PREFIX}/lib/libcontrol_msgs__rosidl_generator_py.so"
  IMPORTED_SONAME_NONE "libcontrol_msgs__rosidl_generator_py.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS control_msgs::control_msgs__rosidl_generator_py )
list(APPEND _IMPORT_CHECK_FILES_FOR_control_msgs::control_msgs__rosidl_generator_py "${_IMPORT_PREFIX}/lib/libcontrol_msgs__rosidl_generator_py.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
