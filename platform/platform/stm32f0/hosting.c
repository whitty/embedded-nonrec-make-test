// (C) Copyright 2018 Greg Whiteley

#include "abort.h"
#include <stdlib.h>

void exit(int status)
{
    abort_(status, 0);
}

void _exit(int status)
{
    abort_(status, 0);
}

int __attribute__((noreturn)) atexit(void (*function)(void))
{
    abort_((unsigned long)function, "atexit() called");
}
