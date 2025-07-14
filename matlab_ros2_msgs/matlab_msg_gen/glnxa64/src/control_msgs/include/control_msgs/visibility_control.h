#ifndef CONTROL_MSGS__VISIBILITY_CONTROL_H_
#define CONTROL_MSGS__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define CONTROL_MSGS_EXPORT __attribute__ ((dllexport))
    #define CONTROL_MSGS_IMPORT __attribute__ ((dllimport))
  #else
    #define CONTROL_MSGS_EXPORT __declspec(dllexport)
    #define CONTROL_MSGS_IMPORT __declspec(dllimport)
  #endif
  #ifdef CONTROL_MSGS_BUILDING_LIBRARY
    #define CONTROL_MSGS_PUBLIC CONTROL_MSGS_EXPORT
  #else
    #define CONTROL_MSGS_PUBLIC CONTROL_MSGS_IMPORT
  #endif
  #define CONTROL_MSGS_PUBLIC_TYPE CONTROL_MSGS_PUBLIC
  #define CONTROL_MSGS_LOCAL
#else
  #define CONTROL_MSGS_EXPORT __attribute__ ((visibility("default")))
  #define CONTROL_MSGS_IMPORT
  #if __GNUC__ >= 4
    #define CONTROL_MSGS_PUBLIC __attribute__ ((visibility("default")))
    #define CONTROL_MSGS_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define CONTROL_MSGS_PUBLIC
    #define CONTROL_MSGS_LOCAL
  #endif
  #define CONTROL_MSGS_PUBLIC_TYPE
#endif
#endif  // CONTROL_MSGS__VISIBILITY_CONTROL_H_
// Generated 29-Jun-2025 19:34:41
 