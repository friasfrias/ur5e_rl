#ifndef TRAJECTORY_MSGS__VISIBILITY_CONTROL_H_
#define TRAJECTORY_MSGS__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define TRAJECTORY_MSGS_EXPORT __attribute__ ((dllexport))
    #define TRAJECTORY_MSGS_IMPORT __attribute__ ((dllimport))
  #else
    #define TRAJECTORY_MSGS_EXPORT __declspec(dllexport)
    #define TRAJECTORY_MSGS_IMPORT __declspec(dllimport)
  #endif
  #ifdef TRAJECTORY_MSGS_BUILDING_LIBRARY
    #define TRAJECTORY_MSGS_PUBLIC TRAJECTORY_MSGS_EXPORT
  #else
    #define TRAJECTORY_MSGS_PUBLIC TRAJECTORY_MSGS_IMPORT
  #endif
  #define TRAJECTORY_MSGS_PUBLIC_TYPE TRAJECTORY_MSGS_PUBLIC
  #define TRAJECTORY_MSGS_LOCAL
#else
  #define TRAJECTORY_MSGS_EXPORT __attribute__ ((visibility("default")))
  #define TRAJECTORY_MSGS_IMPORT
  #if __GNUC__ >= 4
    #define TRAJECTORY_MSGS_PUBLIC __attribute__ ((visibility("default")))
    #define TRAJECTORY_MSGS_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define TRAJECTORY_MSGS_PUBLIC
    #define TRAJECTORY_MSGS_LOCAL
  #endif
  #define TRAJECTORY_MSGS_PUBLIC_TYPE
#endif
#endif  // TRAJECTORY_MSGS__VISIBILITY_CONTROL_H_
// Generated 29-Jun-2025 19:34:43
 