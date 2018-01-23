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
#include <kit/allocator/allocator.h>
#include <kit/allocator/allocator_config.h>

Option __kit_Allocator_malloc(const char *file, const int line, const size_t size) {
    (void) file;
    (void) line;
    assert(file);
    return __kit_Allocator_mallocFn(file, line, size);
}

Option __kit_Allocator_calloc(const char *file, const int line, const size_t numberOfMembers, const size_t memberSize) {
    (void) file;
    (void) line;
    assert(file);
    return __kit_Allocator_callocFn(file, line, numberOfMembers, memberSize);
}

Option __kit_Allocator_ralloc(const char *file, const int line, void *ptr, const size_t newSize) {
    (void) file;
    (void) line;
    assert(file);
    return __kit_Allocator_rallocFn(file, line, ptr, newSize);
}

Option __kit_Allocator_copy(const char *file, const int line, void *dst, const void *src, const size_t size) {
    (void) file;
    (void) line;
    assert(file);
    return __kit_Allocator_copyFn(file, line, dst, src, size);
}

Option __kit_Allocator_move(const char *file, const int line, void *dst, const void *src, size_t size) {
    (void) file;
    (void) line;
    assert(file);
    return __kit_Allocator_moveFn(file, line, dst, src, size);
}

Option __kit_Allocator_set(const char *file, const int line, void *ptr, int value, const size_t size) {
    (void) file;
    (void) line;
    assert(file);
    return __kit_Allocator_setFn(file, line, ptr, value, size);
}

void __kit_Allocator_free(const char *file, const int line, void *ptr) {
    (void) file;
    (void) line;
    assert(file);
    __kit_Allocator_freeFn(file, line, ptr);
}
