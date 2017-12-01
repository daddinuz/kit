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

Optional(struct kit_Array *) kit_Array_new(size_t capacity) {
    struct kit_Array *self = kit_Allocator_malloc(sizeof(*self));

    if (self) {
        self->raw = kit_Allocator_calloc(capacity, sizeof(self->raw[0]));
        if (self->raw) {
            self->capacity = capacity;
        } else {
            kit_Allocator_free(self);
            self = NULL;
        }
    }

    return Option_new(self);
}

Optional(struct kit_Array *) __kit_Array_from(void *e0, ...) {
    Option self;
    va_list pack;
    va_list packCopy;

    va_start(pack, e0);
    va_copy(packCopy, pack);

    self = kit_Array_new(1 + kit_packSize(packCopy));
    if (Option_isSome(self)) {
        size_t i = 0;
        struct kit_Array *s = Option_unwrap(self);
        for (void *e = e0; e != Ellipsis; e = va_arg(pack, void *)) {
            kit_Array_set(s, e, i);
            i++;
        };
    }

    va_end(packCopy);
    va_end(pack);

    return self;
}

Optional(struct kit_Array *) kit_Array_fromPack(va_list pack) {
    assert(pack);
    Option self;
    va_list packCopy;

    va_copy(packCopy, pack);
    self = kit_Array_new(kit_packSize(packCopy));
    if (Option_isSome(self)) {
        size_t i = 0;
        struct kit_Array *s = Option_unwrap(self);
        for (void *e = va_arg(pack, void *); e != Ellipsis; e = va_arg(pack, void *)) {
            kit_Array_set(s, e, i);
            i++;
        };
    }
    va_end(packCopy);

    return self;
}

void kit_Array_delete(struct kit_Array *self) {
    if (self) {
        kit_Allocator_free(self->raw);
        kit_Allocator_free(self);
    }
}

void kit_Array_clear(struct kit_Array *self) {
    assert(self);
    kit_Allocator_write(self->raw, 0, sizeof(void *) * self->capacity);
}

enum kit_Result kit_Array_set(struct kit_Array *self, void *e, const size_t index) {
    assert(self);
    enum kit_Result result = KIT_RESULT_OK;

    if (index < self->capacity) {
        self->raw[index] = e;
    } else {
        result = KIT_RESULT_OUT_OF_RANGE_ERROR;
    }

    return result;
}

enum kit_Result kit_Array_get(struct kit_Array *self, void **out, const size_t index) {
    assert(self);
    assert(out);
    enum kit_Result result = KIT_RESULT_OK;

    if (index < self->capacity) {
        *out = self->raw[index];
    } else {
        result = KIT_RESULT_OUT_OF_RANGE_ERROR;
    }

    return result;
}

enum kit_Result kit_Array_back(struct kit_Array *self, void **out) {
    assert(self);
    assert(out);
    const size_t size = self->capacity;
    return size > 0 ? kit_Array_get(self, out, size - 1) : KIT_RESULT_OUT_OF_RANGE_ERROR;
}

enum kit_Result kit_Array_front(struct kit_Array *self, void **out) {
    assert(self);
    assert(out);
    return kit_Array_get(self, out, 0);
}

size_t kit_Array_capacity(struct kit_Array *self) {
    assert(self);
    return self->capacity;
}

void **kit_Array_raw(struct kit_Array *self) {
    assert(self);
    return self->raw;
}
