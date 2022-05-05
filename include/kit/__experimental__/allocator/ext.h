/// @file

/**
 * Known issues:
 * - double indirection overhead (AllocatorExt is passed by ref)
 * - portability issues due to platform specific support for over-aligned types
 */

#pragma once

#include <kit/cta.h>
#include <kit/trace.h>
#include <kit/types.h>
#include <kit/error.h>
#include <kit/alloc/result.h>
#include <kit/memory/layout.h>

typedef AllocResult (*const Allocate)(MemoryLayout layout, Trace trace);

typedef AllocResult (*const Reallocate)(void *ptr,
                                        MemoryLayout oldLayout,
                                        MemoryLayout newLayout,
                                        Trace trace);

typedef void (*const Deallocate)(void *ptr, MemoryLayout layout, Trace trace);

typedef struct AllocatorExt {
    const Allocate allocate;
    const Reallocate reallocate;
    const Deallocate deallocate;
} AllocatorExt;

cta(MUST_USE, DENY_NULL(1))
extern AllocResult
xallocate(const AllocatorExt *allocator, MemoryLayout layout, Trace trace);

#define xallocate(allocator, layout)                                           \
    (xallocate((allocator), (layout), (__TRACE__)))

cta(MUST_USE, DENY_NULL(1, 2))
extern AllocResult xduplicate(const AllocatorExt *allocator,
                              const void *ptr,
                              MemoryLayout layout,
                              Trace trace);

#define xduplicate(allocator, ptr, layout)                                     \
    (xduplicate((allocator), (ptr), (layout), (__TRACE__)))

cta(MUST_USE, DENY_NULL(1, 2))
extern AllocResult xreallocate(const AllocatorExt *allocator,
                               void *ptr,
                               MemoryLayout oldLayout,
                               MemoryLayout newLayout,
                               Trace trace);

#define xreallocate(allocator, ptr, oldLayout, newLayout)                      \
    (xreallocate((allocator), (ptr), (oldLayout), (newLayout), (__TRACE__)))

cta(DENY_NULL(1, 2))
extern void xdeallocate(const AllocatorExt *allocator,
                        void *ptr,
                        MemoryLayout layout,
                        Trace trace);

#define xdeallocate(allocator, ptr, layout)                                    \
    (xdeallocate((allocator), (ptr), (layout), (__TRACE__)))

/**
 * Helper macro for allocating and initializing a struct.
 */
#define xemplace(allocator, type, ...)                                         \
    ((xduplicate)((allocator),                                                 \
                  (&((type) { __VA_ARGS__ })),                                 \
                  (layoutof(type)),                                            \
                  (__TRACE__)))
