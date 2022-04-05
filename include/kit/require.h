/// @file

#pragma once

#include <kit/pp.h>
#include <kit/trace.h>
#include <kit/types.h>

typedef struct RequireArgs {
    const char *const message;
    const Trace trace;
} RequireArgs;

extern void require(bool condition, const RequireArgs args);

#define require(condition)                                                     \
    ((require)((condition), ((RequireArgs) {                                   \
                   .message = "requirement: " STRINGIZE_DEFER(condition)       \
                   " not met", .trace = __TRACE__                              \
               })))

#define require_with(condition, ...)                                           \
    ((require)((condition), ((RequireArgs) {                                   \
                   .message = "requirement: " STRINGIZE_DEFER(condition)       \
                   " not met", .trace = __TRACE__, __VA_ARGS__                 \
               })))
