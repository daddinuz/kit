/// @file

/**
 * This module provides an abstraction layer over memory allocation
 * and helpers functions/macros for better usability.
 */

#pragma once

#include <kit/cta.h>
#include <kit/trace.h>
#include <kit/types.h>
#include <kit/error.h>
#include <kit/alloc/result.h>

/**
 * Allocator is intended to be a customizable general-purpose interface
 * for memory allocation.
 *
 * Users are not expected to use directly the allocator instance but the helpers
 * functions/macros provided in this module.
 *
 * Implementations must follow the following semantic:
 * - ptr == NULL && size  > 0: Allocate size bytes of storage suitably aligned
 *                             for any object type with fundamental alignment.
 *                             If such storage is zero-initialized or not
 *                             is implementation-defined.
 * - ptr != NULL && size  > 0: Reallocate the given storage previously allocated
 *                             by this allocator
 *                             and not yet deallocated. Otherwise, the results
 *                             are undefined. The reallocation strategy is
 *                             implementation-defined.
 *                             On success the given storage is invalidated and
 *                             must not be accessed anymore, the newly returned
 *                             storage must be used instead.
 * - ptr != NULL && size == 0: Deallocate the given storage previously allocated
 *                             by this allocator and not yet deallocated.
 *                             Otherwise, the results are undefined.
 *                             On success neither the given storage nor the
 *                             newly returned one must be dereferenced.
 * - ptr == NULL && size == 0: Implementation-defined, either an error or a
 *                             valid storage is returned, such storage
 *                             must not be dereferenced.
 *
 * Under no circumstances a compliant implementation is allowed to return
 * a null ptr or error.
 *
 * Known limitations:
 * - for better portability it's not possible to specify custom alignments.
 */
typedef AllocResult (*const Allocator)(void *ptr, usize size, Trace trace);

/**
 * On debug builds:
 * - null-allocator is a checked runtime error.
 * - zero-size is a checked runtime error.
 */
cta(MUST_USE, DENY_NULL(1))
extern AllocResult allocate(const Allocator allocator, usize size, Trace trace);

/**
 * On debug builds:
 * - null-allocator is a checked runtime error.
 * - zero-size is a checked runtime error.
 */
#define allocate(allocator, size) (allocate((allocator), (size), (__TRACE__)))

/**
 * On debug builds:
 * - null-allocator is a checked runtime error.
 * - null-ptr is a checked runtime error.
 * - zero-size is a checked runtime error.
 */
cta(MUST_USE, DENY_NULL(1, 2))
extern AllocResult
duplicate(const Allocator allocator, const void *ptr, usize size, Trace trace);

/**
 * On debug builds:
 * - null-allocator is a checked runtime error.
 * - null-ptr is a checked runtime error.
 * - zero-size is a checked runtime error.
 */
#define duplicate(allocator, ptr, size)                                        \
    (duplicate((allocator), (ptr), (size), (__TRACE__)))

/**
 * On debug builds:
 * - null-allocator is a checked runtime error.
 * - null-ptr is a checked runtime error.
 * - zero-size is a checked runtime error.
 */
cta(MUST_USE, DENY_NULL(1, 2))
extern AllocResult
reallocate(const Allocator allocator, void *ptr, usize size, Trace trace);

/**
 * On debug builds:
 * - null-allocator is a checked runtime error.
 * - null-ptr is a checked runtime error.
 * - zero-size is a checked runtime error.
 */
#define reallocate(allocator, ptr, size)                                       \
    (reallocate((allocator), (ptr), (size), (__TRACE__)))

/**
 * On debug builds:
 * - null-allocator is a checked runtime error.
 * - null-ptr is a checked runtime error.
 */
cta(DENY_NULL(1, 2))
extern void deallocate(const Allocator allocator, void *ptr, Trace trace);

/**
 * On debug builds:
 * - null-allocator is a checked runtime error.
 * - null-ptr is a checked runtime error.
 */
#define deallocate(allocator, ptr) (deallocate((allocator), (ptr), (__TRACE__)))

/**
 * Helper macro for allocating and initializing a struct.
 */
#define emplace(allocator, type, ...)                                          \
    ((duplicate)((allocator),                                                  \
                 (&((type) { __VA_ARGS__ })),                                  \
                 (sizeof(type)),                                               \
                 (__TRACE__)))
