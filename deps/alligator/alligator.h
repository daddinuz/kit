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

#define ALLIGATOR_VERSION   "0.2.1"

#include <stddef.h>
#include <option/option.h>

extern Optional(void *) alligator_malloc(size_t size);
extern Optional(void *) alligator_calloc(size_t numberOfMembers, size_t memberSize);
extern Optional(void *) alligator_ralloc(void *ptr, size_t newSize);
extern Optional(void *) alligator_copy(void *dst, const void *src, size_t size);
extern Optional(void *) alligator_move(void *dst, const void *src, size_t size);
extern Optional(void *) alligator_set(void *ptr, int value, size_t size);
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

#endif /* ALLIGATOR_ALLIGATOR_INCLUDED */
