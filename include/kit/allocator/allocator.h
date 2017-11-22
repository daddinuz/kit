/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 21, 2017 
 */

#ifndef KIT_ALLOCATOR_INCLUDED
#define KIT_ALLOCATOR_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

extern void *
__kit_Allocator_malloc(const char *file, int line, size_t size);

extern void *
__kit_Allocator_calloc(const char *file, int line, size_t memberSize, size_t numberOfMembers);

extern void *
__kit_Allocator_ralloc(const char *file, int line, void *ptr, size_t newSize);

extern void *
__kit_Allocator_copy(const char *file, int line, void *dst, const void *src, size_t size);

extern void *
__kit_Allocator_move(const char *file, int line, void *dst, const void *src, size_t size);

extern void *
__kit_Allocator_write(const char *file, int line, void *ptr, int value, size_t size);

extern void
__kit_Allocator_free(const char *file, int line, void *ptr);

#define kit_Allocator_malloc(size)                          \
    __kit_Allocator_malloc(__FILE__, __LINE__, (size))

#define kit_Allocator_calloc(memberSize, numberOfMembers)   \
    __kit_Allocator_calloc(__FILE__, __LINE__, (memberSize), (numberOfMembers))

#define kit_Allocator_ralloc(ptr, newSize)                  \
    __kit_Allocator_ralloc(__FILE__, __LINE__, (ptr), (newSize))

#define kit_Allocator_copy(dst, src, size)                  \
    __kit_Allocator_copy(__FILE__, __LINE__, (dst), (src), (size))

#define kit_Allocator_move(dst, src, size)                  \
    __kit_Allocator_move(__FILE__, __LINE__, (dst), (src), (size))

#define kit_Allocator_write(ptr, value, size)               \
    __kit_Allocator_write(__FILE__, __LINE__, (ptr), (value), (size))

#define kit_Allocator_free(ptr)                             \
    __kit_Allocator_free(__FILE__, __LINE__, (ptr))

#ifdef __cplusplus
}
#endif

#endif /* KIT_ALLOCATOR_INCLUDED */
