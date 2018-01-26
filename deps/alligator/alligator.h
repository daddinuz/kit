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

#ifndef ALLIGATOR_INCLUDED
#define ALLIGATOR_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#define ALLIGATOR_VERSION           "0.11.3"
#define ALLIGATOR_VERSION_MAJOR     0
#define ALLIGATOR_VERSION_MINOR     11
#define ALLIGATOR_VERSION_PATCH     3

#include <stddef.h>
#include <option/option.h>

#if !(OPTION_VERSION_MAJOR == 0 && OPTION_VERSION_MINOR == 11 && OPTION_VERSION_PATCH == 3)
#error "Alligator requires option version 0.11.3"
#endif

extern OptionOf(void *) alligator_malloc(size_t size);
extern OptionOf(void *) alligator_calloc(size_t numberOfMembers, size_t memberSize);
extern OptionOf(void *) alligator_ralloc(void *ptr, size_t newSize);
extern OptionOf(void *) alligator_copy(void *dst, const void *src, size_t size);
extern OptionOf(void *) alligator_move(void *dst, const void *src, size_t size);
extern OptionOf(void *) alligator_set(void *ptr, int value, size_t size);
extern void alligator_free(void *ptr);

#ifdef ALLIGATOR_WRAP_STDLIB
#undef malloc
#undef calloc
#undef realloc
#undef memcpy
#undef memmove
#undef memset
#undef free

#define malloc(size)                        Option_unwrap(alligator_malloc(size))
#define calloc(numberOfMembers, memberSize) Option_unwrap(alligator_calloc(numberOfMembers, memberSize))
#define realloc(ptr, newSize)               Option_unwrap(alligator_ralloc(ptr, newSize))
#define memcpy(dst, src, size)              Option_unwrap(alligator_copy((dst), (src), (size)))
#define memmove(dst, src, size)             Option_unwrap(alligator_move((dst), (src), (size)))
#define memset(ptr, value, size)            Option_unwrap(alligator_set((ptr), (value), (size)))
#define free(ptr)                           alligator_free(ptr)
#endif

#ifdef __cplusplus
}
#endif

#endif /* ALLIGATOR_INCLUDED */
