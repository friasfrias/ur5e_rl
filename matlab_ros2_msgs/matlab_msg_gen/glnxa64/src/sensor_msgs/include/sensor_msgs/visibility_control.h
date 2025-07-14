#ifndef SENSOR_MSGS__VISIBILITY_CONTROL_H_
#define SENSOR_MSGS__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define SENSOR_MSGS_EXPORT __attribute__ ((dllexport))
    #define SENSOR_MSGS_IMPORT __attribute__ ((dllimport))
  #else
    #define SENSOR_MSGS_EXPORT __declspec(dllexport)
    #define SENSOR_MSGS_IMPORT __declspec(dllimport)
  #endif
  #ifdef SENSOR_MSGS_BUILDING_LIBRARY
    #define SENSOR_MSGS_PUBLIC SENSOR_MSGS_EXPORT
  #else
    #define SENSOR_MSGS_PUBLIC SENSOR_MSGS_IMPORT
  #endif
  #define SENSOR_MSGS_PUBLIC_TYPE SENSOR_MSGS_PUBLIC
  #define SENSOR_MSGS_LOCAL
#else
  #define SENSOR_MSGS_EXPORT __attribute__ ((visibility("default")))
  #define SENSOR_MSGS_IMPORT
  #if __GNUC__ >= 4
    #define SENSOR_MSGS_PUBLIC __attribute__ ((visibility("default")))
    #define SENSOR_MSGS_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define SENSOR_MSGS_PUBLIC
    #define SENSOR_MSGS_LOCAL
  #endif
  #define SENSOR_MSGS_PUBLIC_TYPE
#endif
#endif  // SENSOR_MSGS__VISIBILITY_CONTROL_H_
// Generated 29-Jun-2025 19:34:42
 