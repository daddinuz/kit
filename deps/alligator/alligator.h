/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   January 10, 2018
 */

#ifndef ALLIGATOR_INCLUDED
#define ALLIGATOR_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#define ALLIGATOR_VERSION           "0.11.2"
#define ALLIGATOR_VERSION_MAJOR     0
#define ALLIGATOR_VERSION_MINOR     11
#define ALLIGATOR_VERSION_PATCH     2

#include <stddef.h>
#include <option/option.h>

#if !(OPTION_VERSION_MAJOR == 0 && OPTION_VERSION_MINOR == 11 && OPTION_VERSION_PATCH == 2)
#error "Alligator requires option version 0.11.2"
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
