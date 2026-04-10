#pragma once

#include "defines.h"

//diable by commenting out
#define FASSERTIONS_ENABLED

#ifdef FASSERTIONS_ENABLED
#if _MSC_VER
#include <intrin.h>
#define debugBreak() __debugbreak()
#else
#define debugBreak() __builtin_trap()
#endif

FAPI void report_assertion_failure(const char* expression, const char* message, const char* file, i32 line);

#define FASSERT(expr)\
    {\
        if(expr){\
        }else{\
            report_assertion_failure(#expr, "",__FILE__, __LINE__);\
            debugBreak();\
        }\
    }

#define FASSERT_MSG(expr, message)\
    {\
        if(expr){\
        }else{\
            report_assertion_failure(#expr, message, __FILE__,__LINE__);\
            debugBreak();\
        }\
    }

//check if debug build
#ifdef _DEBUG
#define FASSERT_DEBUG(expr)\
    {\
        if(expr){\
        }else{\
            report_assertion_failure(#expr, "", __FILE__,__LINE__);\
            debugBreak();\
        }\
    }
#else
#define FASSERT_DEBUG(expr) //does nothing at all
#endif


#else
//does nothing at all
#define FASSERT(expr)
#define FASSERT_MSG(expr, message)
#define FASSERT_DEBUG(expr)
#endif