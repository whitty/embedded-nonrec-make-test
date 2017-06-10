#pragma once

#include "platform.h"

#ifdef LOG_TO_PRINTF
#include <stdio.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef LOG_TO_PRINTF
#define log_printf(...) printf(__VA_ARGS__)
#else
#define log_printf(...) log_printf_null(__VA_ARGS__)
#endif

/* consume all parameters without warning */
static inline void log_printf_null(...) { }

#define LOG_INFO(...) log_printf(__VA_ARGS__)
#define LOG_WARNING(...) log_printf(__VA_ARGS__)
#define LOG_ERROR(...) log_printf(__VA_ARGS__)
#define LOG_FATAL(...) log_printf(__VA_ARGS__)

#ifndef NDEBUG
#define LOG_DEBUG(...) log_printf(__VA_ARGS__)
#else
#define LOG_DEBUG(...) log_printf_null(__VA_ARGS__)
#endif


#ifdef __cplusplus
}
#endif
