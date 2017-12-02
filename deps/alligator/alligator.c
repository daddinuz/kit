/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   December 02, 2017
 */

#include <alligator/alligator.h>

#ifdef ALLIGATOR_WRAP_STDLIB
#undef malloc
#undef calloc
#undef realloc
#undef memcpy
#undef memmove
#undef memset
#undef free
#endif

#include <stdlib.h>
#include <memory.h>

Option alligator_malloc(const size_t size) {
    return Option_new(malloc(size));
}

Option alligator_calloc(const size_t numberOfMembers, const size_t memberSize) {
    return Option_new(calloc(numberOfMembers, memberSize));
}

Option alligator_ralloc(void *ptr, const size_t newSize) {
    return Option_new(realloc(ptr, newSize));
}

Option alligator_copy(void *dst, const void *src, size_t size) {
    return Option_new(memcpy(dst, src, size));
}

Option alligator_move(void *dst, const void *src, size_t size) {
    return Option_new(memmove(dst, src, size));
}

Option alligator_set(void *ptr, int value, size_t size) {
    return Option_new(memset(ptr, value, size));
}

void alligator_free(void *ptr) {
    free(ptr);
}
