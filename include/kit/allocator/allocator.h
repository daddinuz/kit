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

#ifndef KIT_ALLOCATOR_INCLUDED
#define KIT_ALLOCATOR_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <option/option.h>
#include <kit/compiler_steroids.h>

extern OptionOf(void *)
__kit_Allocator_malloc(const char *file, int line, size_t size)
__attribute__((__warn_unused_result__, __nonnull__(1)));

extern OptionOf(void *)
__kit_Allocator_calloc(const char *file, int line, size_t numberOfMembers, size_t memberSize)
__attribute__((__warn_unused_result__, __nonnull__(1)));

extern OptionOf(void *)
__kit_Allocator_ralloc(const char *file, int line, void *ptr, size_t newSize)
__attribute__((__warn_unused_result__, __nonnull__(1)));

extern OptionOf(void *)
__kit_Allocator_copy(const char *file, int line, void *dst, const void *src, size_t size)
__attribute__((__nonnull__(1)));

extern OptionOf(void *)
__kit_Allocator_move(const char *file, int line, void *dst, const void *src, size_t size)
__attribute__((__nonnull__(1)));

extern OptionOf(void *)
__kit_Allocator_set(const char *file, int line, void *ptr, int value, size_t size)
__attribute__((__nonnull__(1)));

extern void __kit_Allocator_free(const char *file, int line, void *ptr)
__attribute__((__nonnull__(1)));

#define kit_Allocator_malloc(size)                          __kit_Allocator_malloc(__FILE__, __LINE__, (size))
#define kit_Allocator_calloc(numberOfMembers, memberSize)   __kit_Allocator_calloc(__FILE__, __LINE__, (numberOfMembers), (memberSize))
#define kit_Allocator_ralloc(ptr, newSize)                  __kit_Allocator_ralloc(__FILE__, __LINE__, (ptr), (newSize))
#define kit_Allocator_copy(dst, src, size)                  __kit_Allocator_copy(__FILE__, __LINE__, (dst), (src), (size))
#define kit_Allocator_move(dst, src, size)                  __kit_Allocator_move(__FILE__, __LINE__, (dst), (src), (size))
#define kit_Allocator_set(ptr, value, size)                 __kit_Allocator_set(__FILE__, __LINE__, (ptr), (value), (size))
#define kit_Allocator_free(ptr)                             __kit_Allocator_free(__FILE__, __LINE__, (ptr))

#ifdef __cplusplus
}
#endif

#endif /* KIT_ALLOCATOR_INCLUDED */
