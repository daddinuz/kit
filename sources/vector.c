/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 23, 2017 
 */

#include <assert.h>
#include <stdlib.h>
#include <kit/allocator/allocator.h>
#include <kit/collections/vector.h>

#define KIT_VECTOR_MINIMUM_SIZE 16

struct kit_Vector {
    int operationId;
    size_t size;
    size_t capacity;
    void **raw;
};

static size_t nextEven(size_t size) {
    return size + (size % 2);
}

static size_t applyLoadFactor(size_t size) {
    return nextEven(size + (size / 2));
}

Optional(struct kit_Vector *) kit_Vector_new(void) {
    return kit_Vector_from(KIT_VECTOR_MINIMUM_SIZE);
}

Optional(struct kit_Vector *) kit_Vector_from(const size_t capacityHint) {
    const size_t capacity = (capacityHint > KIT_VECTOR_MINIMUM_SIZE) ? nextEven(capacityHint) : KIT_VECTOR_MINIMUM_SIZE;
    struct kit_Vector *self = kit_Allocator_calloc(1, sizeof(*self));

    if (self) {
        self->raw = kit_Allocator_malloc(capacity * sizeof(*self->raw));
        if (self->raw) {
            self->capacity = capacity;
        } else {
            kit_Allocator_free(self);
            self = NULL;
        }
    }

    return Option_new(self);
}

void kit_Vector_clear(struct kit_Vector *self) {
    assert(self);
    self->size = 0;
    self->operationId += 1;
}

void kit_Vector_delete(struct kit_Vector *self) {
    if (self) {
        kit_Allocator_free(self->raw);
        kit_Allocator_free(self);
    }
}

enum kit_Result kit_Vector_insert(struct kit_Vector *self, void *e, const size_t index) {
    assert(self);
    enum kit_Result result = KIT_RESULT_OK;

    if (index <= self->size) {
        if (self->size >= self->capacity) {
            const size_t newCapacity = applyLoadFactor(self->size);
            void **newRaw = kit_Allocator_ralloc(self->raw, newCapacity * sizeof(void *));
            if (newRaw) {
                self->raw = newRaw;
                self->capacity = newCapacity;
            } else {
                result = KIT_RESULT_OUT_OF_MEMORY_ERROR;
            }
        }
        if (KIT_RESULT_OK == result) {
            const size_t shift = (self->size - index) * sizeof(void *);
            kit_Allocator_move(&(self->raw[index + 1]), &(self->raw[index]), shift);
            self->raw[index] = e;
            self->size += 1;
            self->operationId += 1;
        }
    } else {
        result = KIT_RESULT_OUT_OF_RANGE_ERROR;
    }

    return result;
}

enum kit_Result kit_Vector_pushBack(struct kit_Vector *self, void *e) {
    assert(self);
    return kit_Vector_insert(self, e, self->size);
}

enum kit_Result kit_Vector_pushFront(struct kit_Vector *self, void *e) {
    assert(self);
    return kit_Vector_insert(self, e, 0);
}

enum kit_Result kit_Vector_popBack(struct kit_Vector *self, void **out) {
    assert(self);
    assert(out);
    const size_t size = self->size;
    return size > 0 ? kit_Vector_remove(self, out, size - 1) : KIT_RESULT_OUT_OF_RANGE_ERROR;
}

enum kit_Result kit_Vector_popFront(struct kit_Vector *self, void **out) {
    assert(self);
    assert(out);
    return kit_Vector_remove(self, out, 0);
}

enum kit_Result kit_Vector_remove(struct kit_Vector *self, void **out, const size_t index) {
    assert(self);
    assert(out);
    enum kit_Result result = KIT_RESULT_OK;

    if (index < self->size) {
        *out = self->raw[index];
        const size_t delta = (self->size - index - 1) * sizeof(void *);
        kit_Allocator_move(&(self->raw[index]), &(self->raw[index + 1]), delta);
        self->size -= 1;
        self->operationId += 1;
    } else {
        result = KIT_RESULT_OUT_OF_RANGE_ERROR;
    }

    return result;
}

enum kit_Result kit_Vector_set(struct kit_Vector *self, void *e, const size_t index) {
    assert(self);
    enum kit_Result result = KIT_RESULT_OK;

    if (index < self->size) {
        self->raw[index] = e;
    } else {
        result = KIT_RESULT_OUT_OF_RANGE_ERROR;
    }

    return result;
}

enum kit_Result kit_Vector_get(struct kit_Vector *self, void **out, const size_t index) {
    assert(self);
    assert(out);
    enum kit_Result result = KIT_RESULT_OK;

    if (index < self->size) {
        *out = self->raw[index];
    } else {
        result = KIT_RESULT_OUT_OF_RANGE_ERROR;
    }

    return result;
}

enum kit_Result kit_Vector_back(struct kit_Vector *self, void **out) {
    assert(self);
    assert(out);
    const size_t size = self->size;
    return size > 0 ? kit_Vector_get(self, out, size - 1) : KIT_RESULT_OUT_OF_RANGE_ERROR;
}

enum kit_Result kit_Vector_front(struct kit_Vector *self, void **out) {
    assert(self);
    assert(out);
    return kit_Vector_get(self, out, 0);
}

size_t kit_Vector_size(struct kit_Vector *self) {
    assert(self);
    return self->size;
}

bool kit_Vector_isEmpty(struct kit_Vector *self) {
    assert(self);
    return 0 == self->size;
}

size_t kit_Vector_capacity(struct kit_Vector *self) {
    assert(self);
    return self->capacity;
}

enum kit_Result kit_Vector_reserve(struct kit_Vector *self, const size_t size) {
    assert(self);
    enum kit_Result result = KIT_RESULT_OK;

    if (size > self->capacity) {
        const size_t newCapacity = nextEven(size);
        void **newRaw = kit_Allocator_ralloc(self->raw, newCapacity * sizeof(void *));
        if (newRaw) {
            self->raw = newRaw;
            self->capacity = newCapacity;
        } else {
            result = KIT_RESULT_OUT_OF_MEMORY_ERROR;
        }
    }

    return result;
}

enum kit_Result kit_Vector_shrink(struct kit_Vector *self) {
    assert(self);
    enum kit_Result result = KIT_RESULT_OK;
    const size_t newCapacity = (self->size > KIT_VECTOR_MINIMUM_SIZE) ? nextEven(self->size) : KIT_VECTOR_MINIMUM_SIZE;
    void **newRaw = kit_Allocator_ralloc(self->raw, newCapacity * sizeof(void *));

    if (newRaw) {
        self->raw = newRaw;
        self->capacity = newCapacity;
    } else {
        result = KIT_RESULT_OUT_OF_MEMORY_ERROR;
    }

    return result;
}

void **kit_Vector_raw(struct kit_Vector *self) {
    assert(self);
    return self->raw;
}

/**
 * kit_Vector_Iterator_T
 */
struct kit_Vector_Iterator {
    int operationId;
    struct kit_Vector *container;
    size_t lastIndex;
    size_t prevIndex;
    size_t nextIndex;
};

Optional(struct kit_Vector_Iterator *) kit_Vector_Iterator_new(struct kit_Vector *container, enum kit_Bound bound) {
    assert(container);
    assert(KIT_BOUND_BEGIN <= bound && bound <= KIT_BOUND_END);
    struct kit_Vector_Iterator *self = kit_Allocator_calloc(1, sizeof(*self));

    if (self) {
        self->container = container;
        kit_Vector_Iterator_rewind(self, bound);
    }

    return Option_new(self);
}

Optional(struct kit_Vector_Iterator *) kit_Vector_Iterator_fromBegin(struct kit_Vector *container) {
    assert(container);
    return kit_Vector_Iterator_new(container, KIT_BOUND_BEGIN);
}

Optional(struct kit_Vector_Iterator *) kit_Vector_Iterator_fromEnd(struct kit_Vector *container) {
    assert(container);
    return kit_Vector_Iterator_new(container, KIT_BOUND_END);
}

void kit_Vector_Iterator_rewind(struct kit_Vector_Iterator *self, enum kit_Bound bound) {
    assert(self);
    assert(KIT_BOUND_BEGIN <= bound && bound <= KIT_BOUND_END);
    struct kit_Vector *container = self->container;

    self->operationId = container->operationId;
    self->container = container;
    if (KIT_BOUND_END == bound) {
        self->lastIndex = self->nextIndex = container->size + 1;
        self->prevIndex = container->size;
    } else {
        self->lastIndex = self->prevIndex = 0;
        self->nextIndex = 1;
    }
}

void kit_Vector_Iterator_rewindToBegin(struct kit_Vector_Iterator *self) {
    assert(self);
    kit_Vector_Iterator_rewind(self, KIT_BOUND_BEGIN);
}

void kit_Vector_Iterator_rewindToEnd(struct kit_Vector_Iterator *self) {
    assert(self);
    kit_Vector_Iterator_rewind(self, KIT_BOUND_END);
}

void kit_Vector_Iterator_delete(struct kit_Vector_Iterator *self) {
    kit_Allocator_free(self);
}

enum kit_Result kit_Vector_Iterator_next(struct kit_Vector_Iterator *self, void **out) {
    assert(self);
    assert(out);
    enum kit_Result result;

    if (kit_Vector_Iterator_isModified(self)) {
        result = KIT_RESULT_CONCURRENT_MODIFICATION_ERROR;
    } else if (0 < self->nextIndex && self->nextIndex <= self->container->size) {
        *out = self->container->raw[self->nextIndex - 1];
        self->lastIndex = self->prevIndex = self->nextIndex;
        self->nextIndex += 1;
        result = KIT_RESULT_OK;
    } else {
        result = KIT_RESULT_OUT_OF_RANGE_ERROR;
    }

    return result;
}

enum kit_Result kit_Vector_Iterator_previous(struct kit_Vector_Iterator *self, void **out) {
    assert(self);
    assert(out);
    enum kit_Result result;

    if (kit_Vector_Iterator_isModified(self)) {
        result = KIT_RESULT_CONCURRENT_MODIFICATION_ERROR;
    } else if (0 < self->prevIndex && self->prevIndex <= self->container->size) {
        *out = self->container->raw[self->prevIndex - 1];
        self->lastIndex = self->nextIndex = self->prevIndex;
        self->prevIndex -= 1;
        result = KIT_RESULT_OK;
    } else {
        result = KIT_RESULT_OUT_OF_RANGE_ERROR;
    }

    return result;
}

enum kit_Result kit_Vector_Iterator_setLast(struct kit_Vector_Iterator *self, void *e) {
    assert(self);
    enum kit_Result result = KIT_RESULT_OK;

    if (kit_Vector_Iterator_isModified(self)) {
        result = KIT_RESULT_CONCURRENT_MODIFICATION_ERROR;
    } else if (0 < self->lastIndex && self->lastIndex <= self->container->size) {
        self->container->raw[self->lastIndex - 1] = e;
    } else {
        result = KIT_RESULT_ILLEGAL_STATE_ERROR;
    }

    return result;
}

bool kit_Vector_Iterator_isModified(struct kit_Vector_Iterator *self) {
    assert(self);
    struct kit_Vector *container = self->container;
    return NULL == container || self->operationId != container->operationId;
}
