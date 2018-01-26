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
