/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   January 16, 2018
 */

#include <assert.h>
#include <kit/allocator/allocator.h>
#include <kit/collections/array.h>

struct kit_Array {
    size_t capacity;
    void **raw;
};

ResultOf(struct kit_Array *, OutOfMemoryError)
kit_Array_new(size_t capacity) {
    struct kit_Array *self = NULL;
    const size_t rawSize = sizeof(self->raw[0]) * capacity;
    Option option = kit_Allocator_malloc(sizeof(*self) + rawSize);

    if (Option_isSome(option)) {
        self = Option_unwrap(option);
        self->capacity = capacity;
        self->raw = (void **) (self + 1);
        kit_Allocator_set(self->raw, 0, rawSize);
        return Result_ok(self);
    }

    return Result_error(&OutOfMemoryError);
}

ResultOf(struct kit_Array *, OutOfMemoryError)
__kit_Array_from(void *e0, ...) {
    Result result;
    va_list pack, packCopy;
    struct kit_Array *self = NULL;

    va_start(pack, e0);
    va_copy(packCopy, pack);

    result = kit_Array_new(1 + kit_packSize(packCopy));
    if (Result_isOk(result)) {
        size_t i = 0;
        self = Result_unwrap(result);
        for (void *e = e0; e != Ellipsis; e = va_arg(pack, void *)) {
            kit_Array_put(self, i, e);
            i++;
        };
    }

    va_end(packCopy);
    va_end(pack);

    assert((Result_isOk(result) && self) || (&OutOfMemoryError == Result_inspect(result) && NULL == self));
    return Result_isOk(result) ? Result_ok(self) : Result_error(&OutOfMemoryError);
}

ResultOf(struct kit_Array *, OutOfMemoryError)
kit_Array_fromPack(va_list pack) {
    assert(pack);

    Result result;
    va_list packCopy;
    struct kit_Array *self = NULL;

    va_copy(packCopy, pack);

    result = kit_Array_new(kit_packSize(packCopy));
    if (Result_isOk(result)) {
        size_t i = 0;
        self = Result_unwrap(result);
        for (void *e = va_arg(pack, void *); e != Ellipsis; e = va_arg(pack, void *)) {
            kit_Array_put(self, i, e);
            i++;
        };
    }

    va_end(packCopy);

    assert((Result_isOk(result) && self) || (&OutOfMemoryError == Result_inspect(result) && NULL == self));
    return Result_isOk(result) ? Result_ok(self) : Result_error(&OutOfMemoryError);
}

ResultOf(void *, OutOfRangeError)
kit_Array_put(struct kit_Array *self, const size_t index, void *element) {
    assert(self);
    if (index < self->capacity) {
        void *oldElement = self->raw[index];
        self->raw[index] = element;
        return Result_ok(oldElement);
    }
    return Result_error(&OutOfRangeError);
}

ResultOf(void *, OutOfRangeError)
kit_Array_get(const struct kit_Array *self, const size_t index) {
    assert(self);
    if (index < self->capacity) {
        return Result_ok(self->raw[index]);
    }
    return Result_error(&OutOfRangeError);
}

ResultOf(void *, OutOfRangeError)
kit_Array_back(const struct kit_Array *self) {
    assert(self);
    const size_t capacity = self->capacity;
    return capacity > 0 ? kit_Array_get(self, capacity - 1) : Result_error(&OutOfRangeError);
}

ResultOf(void *, OutOfRangeError)
kit_Array_front(const struct kit_Array *self) {
    assert(self);
    return kit_Array_get(self, 0);
}

void
kit_Array_clear(struct kit_Array *self) {
    assert(self);
    kit_Allocator_set(self->raw, 0, sizeof(void *) * self->capacity);
}

size_t
kit_Array_capacity(const struct kit_Array *self) {
    assert(self);
    return self->capacity;
}

void **
kit_Array_raw(const struct kit_Array *self) {
    assert(self);
    return self->raw;
}

void
kit_Array_delete(struct kit_Array *self) {
    if (self) {
        kit_Allocator_free(self);
    }
}
