/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 22, 2017 
 */

#include <assert.h>
#include <kit/allocator/allocator.h>
#include <kit/collections/array.h>

struct kit_Array {
    size_t capacity;
    void **raw;
};

Option kit_Array_new(size_t capacity) {
    struct kit_Array *self;
    const size_t elementsSize = sizeof(self->raw[0]) * capacity;
    Option selfOption = kit_Allocator_malloc(sizeof(*self) + elementsSize);

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        self->capacity = capacity;
        self->raw = (void **) (self + 1);
        kit_Allocator_set(self->raw, 0, elementsSize);
    }

    return selfOption;
}

Option __kit_Array_from(void *e0, ...) {
    Option selfOption;
    va_list pack;
    va_list packCopy;

    va_start(pack, e0);
    va_copy(packCopy, pack);
    selfOption = kit_Array_new(1 + kit_packSize(packCopy));
    if (Option_isSome(selfOption)) {
        size_t i = 0;
        struct kit_Array *self = Option_unwrap(selfOption);
        for (void *e = e0; e != Ellipsis; e = va_arg(pack, void *)) {
            kit_Array_set(self, e, i);
            i++;
        };
    }
    va_end(packCopy);
    va_end(pack);

    return selfOption;
}

Option kit_Array_fromPack(va_list pack) {
    assert(pack);
    Option selfOption;
    va_list packCopy;

    va_copy(packCopy, pack);
    selfOption = kit_Array_new(kit_packSize(packCopy));
    if (Option_isSome(selfOption)) {
        size_t i = 0;
        struct kit_Array *self = Option_unwrap(selfOption);
        for (void *e = va_arg(pack, void *); e != Ellipsis; e = va_arg(pack, void *)) {
            kit_Array_set(self, e, i);
            i++;
        };
    }
    va_end(packCopy);

    return selfOption;
}

void kit_Array_delete(struct kit_Array *self) {
    if (self) {
        kit_Allocator_free(self);
    }
}

void kit_Array_clear(struct kit_Array *self) {
    assert(self);
    kit_Allocator_set(self->raw, 0, sizeof(void *) * self->capacity);
}

Result kit_Array_set(struct kit_Array *self, void *element, const size_t index) {
    assert(self);

    if (index < self->capacity) {
        void *oldElement = self->raw[index];
        self->raw[index] = element;
        return Result_ok(oldElement);
    }

    return Result_error(&OutOfRangeError);
}

Result kit_Array_get(struct kit_Array *self, const size_t index) {
    assert(self);

    if (index < self->capacity) {
        return Result_ok(self->raw[index]);
    }

    return Result_error(&OutOfRangeError);
}

Result kit_Array_back(struct kit_Array *self) {
    assert(self);
    const size_t capacity = self->capacity;
    return capacity > 0 ? kit_Array_get(self, capacity - 1) : Result_error(&OutOfRangeError);
}

Result kit_Array_front(struct kit_Array *self) {
    assert(self);
    return kit_Array_get(self, 0);
}

size_t kit_Array_capacity(struct kit_Array *self) {
    assert(self);
    return self->capacity;
}

void **kit_Array_raw(struct kit_Array *self) {
    assert(self);
    return self->raw;
}
