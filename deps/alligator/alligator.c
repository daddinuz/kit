/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   December 02, 2017
 */

#include "alligator.h"

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

MutableOption alligator_malloc(const size_t size) {
    return MutableOption_new(malloc(size));
}

MutableOption alligator_calloc(const size_t numberOfMembers, const size_t memberSize) {
    return MutableOption_new(calloc(numberOfMembers, memberSize));
}

MutableOption alligator_ralloc(void *ptr, const size_t newSize) {
    return MutableOption_new(realloc(ptr, newSize));
}

MutableOption alligator_copy(void *dst, const void *src, size_t size) {
    return MutableOption_new(memcpy(dst, src, size));
}

MutableOption alligator_move(void *dst, const void *src, size_t size) {
    return MutableOption_new(memmove(dst, src, size));
}

MutableOption alligator_set(void *ptr, int value, size_t size) {
    return MutableOption_new(memset(ptr, value, size));
}

void alligator_free(void *ptr) {
    free(ptr);
}
