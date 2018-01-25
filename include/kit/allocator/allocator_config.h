/*
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 *
 * Copyright (c) 2018 Davide Di Carlo
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
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
