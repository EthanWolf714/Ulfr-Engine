#include <core/logger.h>
#include <core/asserts.h>



int main(void)
{   
    FFATAL("A TEST MESSAGE: %f", 3.14);
    FERROR("A TEST MESSAGE: %f", 3.14);
    FWARN("A TEST MESSAGE: %f", 3.14);
    FINFO("A TEST MESSAGE: %f", 3.14);
    FDEBUG("A TEST MESSAGE: %f", 3.14);
    FTRACE("A TEST MESSAGE: %f", 3.14);

    FASSERT(1 == 0);
    return 0;
}