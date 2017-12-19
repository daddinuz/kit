/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   December 02, 2017 
 */

#ifndef ALLIGATOR_ALLIGATOR_INCLUDED
#define ALLIGATOR_ALLIGATOR_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#define ALLIGATOR_VERSION           "0.3.2"
#define ALLIGATOR_VERSION_MAJOR     0
#define ALLIGATOR_VERSION_MINOR     3
#define ALLIGATOR_VERSION_PATCH     2

#include <stddef.h>
#include <option/option.h>

#if !(OPTION_VERSION_MAJOR == 0 && OPTION_VERSION_MINOR == 3 && OPTION_VERSION_PATCH == 0)
#error "Alligator requires option version 0.3.0"
#endif

extern MutableOptional(void *) alligator_malloc(size_t size);
extern MutableOptional(void *) alligator_calloc(size_t numberOfMembers, size_t memberSize);
extern MutableOptional(void *) alligator_ralloc(void *ptr, size_t newSize);
extern MutableOptional(void *) alligator_copy(void *dst, const void *src, size_t size);
extern MutableOptional(void *) alligator_move(void *dst, const void *src, size_t size);
extern MutableOptional(void *) alligator_set(void *ptr, int value, size_t size);
extern void alligator_free(void *ptr);

#ifdef ALLIGATOR_WRAP_STDLIB
#undef malloc
#undef calloc
#undef realloc
#undef memcpy
#undef memmove
#undef memset
#undef free

#define malloc(size)                        MutableOption_unwrap(alligator_malloc(size))
#define calloc(numberOfMembers, memberSize) MutableOption_unwrap(alligator_calloc(numberOfMembers, memberSize))
#define realloc(ptr, newSize)               MutableOption_unwrap(alligator_ralloc(ptr, newSize))
#define memcpy(dst, src, size)              MutableOption_unwrap(alligator_copy((dst), (src), (size)))
#define memmove(dst, src, size)             MutableOption_unwrap(alligator_move((dst), (src), (size)))
#define memset(ptr, value, size)            MutableOption_unwrap(alligator_set((ptr), (value), (size)))
#define free(ptr)                           alligator_free(ptr)
#endif

#ifdef __cplusplus
}
#endif

#endif /* ALLIGATOR_ALLIGATOR_INCLUDED */
