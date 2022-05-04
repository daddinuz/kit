/// @file

#pragma once

#include <kit/cta.h>
#include <kit/trace.h>
#include <kit/types.h>
#include <kit/error.h>
#include <kit/alloc/result.h>

typedef AllocResult (*const Allocator)(void *ptr, usize size, Trace trace);

cta(MUST_USE, DENY_NULL(1))
extern AllocResult allocate(const Allocator allocator, usize size, Trace trace);

#define allocate(allocator, size) (allocate((allocator), (size), (__TRACE__)))

cta(MUST_USE, DENY_NULL(1, 2))
extern AllocResult
duplicate(const Allocator allocator, const void *ptr, usize size, Trace trace);

#define duplicate(allocator, ptr, size)                                        \
    (duplicate((allocator), (ptr), (size), (__TRACE__)))

cta(MUST_USE, DENY_NULL(1, 2))
extern AllocResult
reallocate(const Allocator allocator, void *ptr, usize size, Trace trace);

#define reallocate(allocator, ptr, size)                                       \
    (reallocate((allocator), (ptr), (size), (__TRACE__)))

cta(DENY_NULL(1, 2))
extern void deallocate(const Allocator allocator, void *ptr, Trace trace);

#define deallocate(allocator, ptr) (deallocate((allocator), (ptr), (__TRACE__)))

/**
 * Helper macro for allocating and initializing a struct.
 */
#define emplace(allocator, type, ...)                                          \
    ((duplicate)((allocator),                                                  \
                 (&((type) { __VA_ARGS__ })),                                  \
                 (sizeof(type)),                                               \
                 (__TRACE__)))
