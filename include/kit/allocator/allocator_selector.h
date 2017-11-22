/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 21, 2017 
 */

/*
 * kit allocator selection.
 *
 * Update this file is in order to change at compile time the allocator that kit is going to use.
 * Just define the macros below to what you want to use and include the proper files.
 * By default kit will use the libc standard allocator.
 *
 *
 * IMPORTANT:
 *
 * The macros below are intended for internal use only, DO NOT INCLUDE THIS FILE directly in your code,
 * include the safer version in allocator.h instead.
 */

#ifndef KIT_ALLOCATOR_SELECTOR_INCLUDED
#define KIT_ALLOCATOR_SELECTOR_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <memory.h>

#define __kit_Allocator_mallocFn(file, line, size)                           \
    malloc(size)

#define __kit_Allocator_callocFn(file, line, memberSize, numberOfMembers)    \
    calloc(memberSize, numberOfMembers)

#define __kit_Allocator_rallocFn(file, line, ptr, newSize)                   \
    realloc(ptr, newSize)

#define __kit_Allocator_copyFn(file, line, dst, src, size)                   \
    memcpy(dst, src, size)

#define __kit_Allocator_moveFn(file, line, dst, src, size)                   \
    memmove(dst, src, size)

#define __kit_Allocator_writeFn(file, line, ptr, value, size)                \
    memset(ptr, value, size)

#define __kit_Allocator_freeFn(file, line, ptr)                              \
    free(ptr)

#ifdef __cplusplus
}
#endif

#endif /* KIT_ALLOCATOR_SELECTOR_INCLUDED */
