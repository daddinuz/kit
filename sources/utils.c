/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 21, 2017 
 */

#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <kit/utils.h>

#ifndef NDEBUG

#   include <stdio.h>

#endif

static void *_Ellipsis = NULL;
const void *const Ellipsis = &_Ellipsis;

size_t kit_packSize(va_list pack) {
    assert(pack);

    size_t size = 0;
    while (Ellipsis != va_arg(pack, void *)) {
        size++;
#ifndef NDEBUG
        if (0 == size % 128) {
            fprintf(stderr, "WARNING\n  At: %s:%d:\n  Reached %zu iterations\n", __FILE__, __LINE__, size);
        }
        if (size >= 1024) {
            fprintf(stderr, "ERROR\n  At: %s:%d:\n  Too many iterations\n", __FILE__, __LINE__);
            abort();
        }
#endif
    }

    return size;
}

void kit_swap(void **a, void **b) {
    assert(a);
    assert(b);
    void *tmp = *a;
    *a = *b;
    *b = tmp;
}

void *kit_move(void **ref) {
    assert(ref);
    void *data = *ref;
    *ref = NULL;
    return data;
}

int kit_compareFn(const void *a, const void *b) {
    assert(a);
    assert(b);
    return (int) ((intptr_t) b - (intptr_t) a);
}

size_t kit_hashFn(const void *key) {
    assert(key);
    return (size_t) ((uintptr_t) key >> 2);
}
