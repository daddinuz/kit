/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 21, 2017 
 */

#include <assert.h>
#include <stdlib.h>
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

void kit_invalidate(void **ref, void (*destructor)()) {
    assert(ref);
    assert(destructor);
    destructor(*ref);
    *ref = NULL;
}
