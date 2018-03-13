// (C) Copyright 2018 Greg Whiteley
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// call out to terminate the program
// if dump is non-zero dump stack etc if possible
void __attribute__((noreturn))
abort_(unsigned long arg, const char* dump);

#ifdef __cplusplus
}
#endif
