/// @file

#pragma once

/**
 * Quick and dirty logging utility when everything seems to be going wrong.
 */

#include <stdio.h>
#include <kit/pp.h>

#if 0
// Multiple threads could intersperse the output.
    #define dbg(...)                                                           \
        do {                                                                   \
            fprintf(stderr, "[%s@%s:%d] ", __func__, __FILE__, __LINE__);      \
            fprintf(stderr, __VA_ARGS__);                                      \
            fputc('\n', stderr);                                               \
        } while (0)
#endif

#ifdef NDEBUG
    #define dbg(...) ((void)0)
#else
    #define dbg(...)                                                           \
        ((void)fprintf(stderr,                                                 \
                       "[%s@%s:%d] " VA_HEAD(__VA_ARGS__) "\n%c",              \
                       __func__,                                               \
                       __FILE__,                                               \
                       __LINE__,                                               \
                       VA_TAIL(__VA_ARGS__)))
#endif
