/// @file

#pragma once

typedef struct Trace {
    const char *const func;
    const char *const file;
    const int line;
} Trace;

#define __TRACE__                                                              \
    ((Trace) { .func = __func__, .file = __FILE__, .line = __LINE__ })
