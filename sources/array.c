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
#include <kit/collections/array.h>

#define _(x)            ((void) ((x) ? 1 : 0));

struct kit_Array {
    size_t capacity;
    void **raw;
};

OptionOf(struct kit_Array *)
kit_Array_new(const size_t capacity) {
    struct kit_Array *self = NULL;
    const size_t rawSize = sizeof(self->raw[0]) * capacity;
    Option option = kit_Allocator_malloc(sizeof(*self) + rawSize);

    if (Option_isSome(option)) {
        self = Option_unwrap(option);
        self->capacity = capacity;
        self->raw = (void **) (self + 1);
        kit_Allocator_set(self->raw, 0, rawSize);
        return Option_new(self);
    }

    return None;
}

OptionOf(struct kit_Array *)
__kit_Array_from(void *e0, ...) {
    Option option;
    va_list pack, packCopy;
    struct kit_Array *self = NULL;

    va_start(pack, e0);
    va_copy(packCopy, pack);

    option = kit_Array_new(1 + kit_packSize(packCopy));
    if (Option_isSome(option)) {
        size_t i = 0;
        self = Option_unwrap(option);
        for (void *e = e0; e != Ellipsis; e = va_arg(pack, void *)) {
            _(Result_unwrap(kit_Array_put(self, i, e)));
            i++;
        };
    }

    va_end(packCopy);
    va_end(pack);

    return option;
}

OptionOf(struct kit_Array *)
kit_Array_fromPack(va_list pack) {
    Option option;
    va_list packCopy;
    struct kit_Array *self = NULL;

    va_copy(packCopy, pack);

    option = kit_Array_new(kit_packSize(packCopy));
    if (Option_isSome(option)) {
        size_t i = 0;
        self = Option_unwrap(option);
        for (void *e = va_arg(pack, void *); e != Ellipsis; e = va_arg(pack, void *)) {
            _(Result_unwrap(kit_Array_put(self, i, e)));
            i++;
        };
    }

    va_end(packCopy);

    return option;
}

ResultOf(void *, OutOfRangeError)
kit_Array_put(struct kit_Array *const self, const size_t index, void *const element) {
    assert(self);
    if (index < self->capacity) {
        void *replacedElement = self->raw[index];
        self->raw[index] = element;
        return Result_ok(replacedElement);
    }
    return Result_error(OutOfRangeError);
}

ResultOf(void *, OutOfRangeError)
kit_Array_get(const struct kit_Array *const self, const size_t index) {
    assert(self);
    if (index < self->capacity) {
        return Result_ok(self->raw[index]);
    }
    return Result_error(OutOfRangeError);
}

ResultOf(void *, OutOfRangeError)
kit_Array_back(const struct kit_Array *const self) {
    assert(self);
    const size_t capacity = self->capacity;
    return capacity > 0 ? kit_Array_get(self, capacity - 1) : Result_error(OutOfRangeError);
}

ResultOf(void *, OutOfRangeError)
kit_Array_front(const struct kit_Array *const self) {
    assert(self);
    return kit_Array_get(self, 0);
}

void
kit_Array_clear(struct kit_Array *const self) {
    assert(self);
    kit_Allocator_set(self->raw, 0, sizeof(void *) * self->capacity);
}

size_t
kit_Array_capacity(const struct kit_Array *const self) {
    assert(self);
    return self->capacity;
}

void **
kit_Array_raw(const struct kit_Array *const self) {
    assert(self);
    return self->raw;
}

void
kit_Array_delete(struct kit_Array *self) {
    if (self) {
        kit_Allocator_free(self);
    }
}
