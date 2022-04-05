/// @file

#pragma once

/**
 * Compile Time Attribute(s), for improved
 * portability between compilers and language revisions.
 */

#if __STDC_VERSION__ > 201710L
    #define cta(...)       [[__VA_ARGS__]]
    #define MUST_USE       nodiscard
    #define DENY_NULL(...) gnu::nonnull(__VA_ARGS__)
#elif defined(__GNUC__) || defined(__clang__)
    #define cta(...)       __attribute__((__VA_ARGS__))
    #define MUST_USE       __warn_unused_result__
    #define DENY_NULL(...) __nonnull__(__VA_ARGS__)
#else
    #define cta(...)
    #define MUST_USE
    #define DENY_NULL(...)
#endif
