// (C) Copyright 2018 Greg Whiteley

#include "abort.h"

void abort_(unsigned long arg, const char* dump)
{
    if (dump)
    {
        //doDump(dump, arg);
    }
    asm("mov r0, %0;"
        : : "r"(arg) : "r0");
    for(;;)
        asm("bkpt #0;");
}

void abort(void)
{
    abort_(0, "abort() called");
}
