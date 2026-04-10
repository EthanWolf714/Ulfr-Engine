#pragma once
#include "defines.h"

//enabling log level
//fatal and error always active
#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1

//Disable debug and trace logging for release builds

#if FRELEASE == 1
#define LOG_DEBUG_ENABLED 0
#define LOG_TRACE_ENABLED 0
#endif

typedef enum log_level{
    LOG_LEVEL_FATAL = 0,
    LOG_LEVEL_ERROR = 1, 
    LOG_LEVEL_WARN = 2,
    LOG_LEVEL_INFO = 3,
    //not included in release
    LOG_LEVEL_DEBUG = 4,
    LOG_LEVEL_TRACE = 5
} log_level;

b8 initialize_logging();
void shutdown_logging();

//where all logging output funnels through
FAPI void log_output(log_level level, const char* message, ...);

//variadic arguments in preprocessor
//logs fatal level messages
#define FFATAL(message, ...) log_output(LOG_LEVEL_FATAL, message, ##__VA_ARGS__)
#ifndef FERROR
//logs error level messages
#define FERROR(message, ...) log_output(LOG_LEVEL_ERROR, message, ##__VA_ARGS__)
#endif

#if LOG_WARN_ENABLED == 1
//logs warning level messages
#define FWARN(message, ...) log_output(LOG_LEVEL_WARN, message, ##__VA_ARGS__)
#else
//does nothing when warn is diabled
#define FWARN(message,...)
#endif

#if LOG_INFO_ENABLED == 1
//logs infor level messages
#define FINFO(message, ...) log_output(LOG_LEVEL_INFO, message, ##__VA_ARGS__)
#else
//does nothing when info is diabled
#define FINFO(message,...)
#endif

#if LOG_DEBUG_ENABLED == 1
//logs debug level messages
#define FDEBUG(message, ...) log_output(LOG_LEVEL_DEBUG, message, ##__VA_ARGS__)
#else
//does nothing when debug is diabled
#define FDEBUG(message,...)
#endif


#if LOG_TRACE_ENABLED == 1
//logs trace level messages
#define FTRACE(message, ...) log_output(LOG_LEVEL_TRACE, message, ##__VA_ARGS__)
#else
//does nothing when trace is diabled
#define FTRACE(message,...)
#endif
