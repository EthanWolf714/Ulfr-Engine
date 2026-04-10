#include "logger.h"
#include "asserts.h"

//TODO: Temp
#include <stdio.h>
#include <string.h>
#include <stdarg.h>




b8 initialize_logging(){
    //TODO: creat log file
    return 1;
}

void shutdown_logging(){
    //TODO: cleanup logging/write queued entries
}


void log_output(log_level level, const char* message, ...){
    const char* level_string[6] = {"[FATAL]: ", "[ERROR]:  ","[WARN]:  ","[INFO]:  ","[DEBUG]:  ","[TRACE]:  ",};
   // b8 is_error = level < 2;
    //NOTE: declare this array and 
    //zero out the memory, faster then 
    //dynamic mem alloc using malloc()
    //this is done on the stack
    char out_message[32000]; 
    memset(out_message, 0, sizeof(out_message));

    //takes arugment list, starts using it to perform opertaions on it.
    __builtin_va_list arg_ptr;
    //starts after the message argument
    va_start(arg_ptr, message);
    vsnprintf(out_message, 32000, message, arg_ptr);
    va_end(arg_ptr);


    //output to outmessage, 
    //auto append new line character and log level, then print message
    char out_message2[320000];
    sprintf(out_message2, "%s%s\n", level_string[level], out_message);

    //TODO: platform-sepecfici output.
    printf("%s", out_message2);
}

void report_assertion_failure(const char* expression, const char* message, const char* file, i32 line)
{
    log_output(LOG_LEVEL_FATAL, "Assertion Failure: %s, message: '%s', in file: %s, line: %d\n", expression, message, file, line);
}