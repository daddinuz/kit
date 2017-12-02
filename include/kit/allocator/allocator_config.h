/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 21, 2017 
 */

/*
 * kit allocator configuration.
 *
 * Update this file is in order to change at compile time the allocator that kit is going to use.
 * Just define the macros below to what you want to use and include the proper files.
 *
 * IMPORTANT:
 *
 * The macros below are intended for internal use only, DO NOT INCLUDE THIS FILE directly in your code,
 * include the safer version in allocator.h instead.
 */

#ifndef KIT_ALLOCATOR_CONFIG_INCLUDED
#define KIT_ALLOCATOR_CONFIG_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <alligator/alligator.h>

#define __kit_Allocator_mallocFn(file, line, size)                          alligator_malloc(size)
#define __kit_Allocator_callocFn(file, line, numberOfMembers, memberSize)   alligator_calloc(numberOfMembers, memberSize)
#define __kit_Allocator_rallocFn(file, line, ptr, newSize)                  alligator_ralloc(ptr, newSize)
#define __kit_Allocator_copyFn(file, line, dst, src, size)                  alligator_copy(dst, src, size)
#define __kit_Allocator_moveFn(file, line, dst, src, size)                  alligator_move(dst, src, size)
#define __kit_Allocator_setFn(file, line, ptr, value, size)                 alligator_set(ptr, value, size)
#define __kit_Allocator_freeFn(file, line, ptr)                             alligator_free(ptr)

#ifdef __cplusplus
}
#endif

#endif /* KIT_ALLOCATOR_CONFIG_INCLUDED */
