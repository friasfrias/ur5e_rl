#ifndef ACTION_MSGS__VISIBILITY_CONTROL_H_
#define ACTION_MSGS__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define ACTION_MSGS_EXPORT __attribute__ ((dllexport))
    #define ACTION_MSGS_IMPORT __attribute__ ((dllimport))
  #else
    #define ACTION_MSGS_EXPORT __declspec(dllexport)
    #define ACTION_MSGS_IMPORT __declspec(dllimport)
  #endif
  #ifdef ACTION_MSGS_BUILDING_LIBRARY
    #define ACTION_MSGS_PUBLIC ACTION_MSGS_EXPORT
  #else
    #define ACTION_MSGS_PUBLIC ACTION_MSGS_IMPORT
  #endif
  #define ACTION_MSGS_PUBLIC_TYPE ACTION_MSGS_PUBLIC
  #define ACTION_MSGS_LOCAL
#else
  #define ACTION_MSGS_EXPORT __attribute__ ((visibility("default")))
  #define ACTION_MSGS_IMPORT
  #if __GNUC__ >= 4
    #define ACTION_MSGS_PUBLIC __attribute__ ((visibility("default")))
    #define ACTION_MSGS_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define ACTION_MSGS_PUBLIC
    #define ACTION_MSGS_LOCAL
  #endif
  #define ACTION_MSGS_PUBLIC_TYPE
#endif
#endif  // ACTION_MSGS__VISIBILITY_CONTROL_H_
// Generated 29-Jun-2025 19:34:38
 