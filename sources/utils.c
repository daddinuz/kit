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

#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <kit/utils.h>

#ifndef NDEBUG

    #include <stdio.h>

#endif

static void *_Ellipsis = NULL;
const void *const Ellipsis = &_Ellipsis;

size_t
kit_packSize(va_list pack) {
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

void
kit_swap(void **const a, void **const b) {
    assert(a);
    assert(b);
    void *tmp = *a;
    *a = *b;
    *b = tmp;
}

void *
kit_move(void **const ref) {
    assert(ref);
    void *data = *ref;
    *ref = NULL;
    return data;
}

int
kit_compareFn(const void *const a, const void *const b) {
    assert(a);
    assert(b);
    return (int) ((intptr_t) b - (intptr_t) a);
}

size_t
kit_hashFn(const void *const key) {
    assert(key);
    return (size_t) ((uintptr_t) key >> 2);
}
