/// @file

#pragma once

#include <kit/cta.h>
#include <kit/trace.h>
#include <kit/types.h>
#include <kit/error.h>
#include <kit/memory/layout.h>

extern const Error *const OutOfMemory;
extern const Error *const UnsupportedLayout;

typedef struct AllocResult {
    const union {
        void *const ptr;
        const Error *const error;
    };
    const bool ok;
} AllocResult;

cta(MUST_USE, DENY_NULL(1))
extern AllocResult AllocResult_ok(void *ptr);

cta(MUST_USE, DENY_NULL(1))
extern AllocResult AllocResult_err(const Error *error);

typedef AllocResult (*const AllocateFn)(MemoryLayout layout, Trace trace);

typedef AllocResult (*const ReallocateFn)(void *ptr,
                                          MemoryLayout oldLayout,
                                          MemoryLayout newLayout,
                                          Trace trace);

typedef void (*const DeallocateFn)(void *ptr, MemoryLayout layout, Trace trace);

typedef struct Allocator {
    const AllocateFn allocate;
    const ReallocateFn reallocate;
    const DeallocateFn deallocate;
} Allocator;

cta(MUST_USE, DENY_NULL(1))
extern AllocResult
allocate(const Allocator *allocator, MemoryLayout layout, Trace trace);

#define allocate(allocator, layout)                                            \
    (allocate((allocator), (layout), (__TRACE__)))

cta(MUST_USE, DENY_NULL(1, 2))
extern AllocResult duplicate(const Allocator *allocator,
                             const void *ptr,
                             MemoryLayout layout,
                             Trace trace);

#define duplicate(allocator, ptr, layout)                                      \
    (duplicate((allocator), (ptr), (layout), (__TRACE__)))

cta(MUST_USE, DENY_NULL(1, 2))
extern AllocResult reallocate(const Allocator *allocator,
                              void *ptr,
                              MemoryLayout oldLayout,
                              MemoryLayout newLayout,
                              Trace trace);

#define reallocate(allocator, ptr, oldLayout, newLayout)                       \
    (reallocate((allocator), (ptr), (oldLayout), (newLayout), (__TRACE__)))

cta(DENY_NULL(1, 2))
extern void deallocate(const Allocator *allocator,
                       void *ptr,
                       MemoryLayout layout,
                       Trace trace);

#define deallocate(allocator, ptr, layout)                                     \
    (deallocate((allocator), (ptr), (layout), (__TRACE__)))

/**
 * Helper macro for allocating and initializing a struct.
 */
#define emplace(allocator, type, ...)                                          \
    ((duplicate)((allocator),                                                  \
                 (&((type) { __VA_ARGS__ })),                                  \
                 (layoutof(type)),                                             \
                 (__TRACE__)))
