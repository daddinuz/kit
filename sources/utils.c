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
