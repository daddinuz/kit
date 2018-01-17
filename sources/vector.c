/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   January 16, 2018
 */

#include <stdlib.h>
#include <assert.h>
#include <kit/allocator/allocator.h>
#include <kit/collections/vector.h>
#include <kit/collections/vector_config.h>

#ifdef NDEBUG
    #define assertConfigValidity()
#else
static void assertConfigValidity(void) {
    assert(KIT_VECTOR_DEFAULT_CAPACITY > 0UL);
    assert(KIT_VECTOR_LOAD_FACTOR > 1.0F);
}
#endif

static size_t max(size_t a, size_t b) {
    return a > b ? a : b;
}

static size_t nextEven(size_t size) {
    return size + (size % 2);
}

static size_t applyLoadFactor(size_t size) {
    return nextEven(size + (size_t) (size * KIT_VECTOR_LOAD_FACTOR));
}

static size_t calculateNewCapacity(size_t currentCapacity, const size_t targetCapacity) {
    assert(currentCapacity < targetCapacity);
    while (currentCapacity < targetCapacity) {
        currentCapacity = applyLoadFactor(currentCapacity);
    }
    return currentCapacity;
}

struct kit_Vector {
    int operationId;
    size_t size;
    size_t capacity;
    void **raw;
};

OptionOf(struct kit_Vector *)
kit_Vector_new(void) {
    assertConfigValidity();

    return kit_Vector_withCapacity(KIT_VECTOR_DEFAULT_CAPACITY);
}

OptionOf(struct kit_Vector *)
kit_Vector_withCapacity(const size_t capacity) {
    assertConfigValidity();

    struct kit_Vector *self = NULL;
    Option option = kit_Allocator_calloc(1, sizeof(*self));

    if (Option_isSome(option)) {
        const size_t actualCapacity = nextEven(max(capacity, KIT_VECTOR_DEFAULT_CAPACITY));
        const size_t rawSize = sizeof(self->raw[0]) * actualCapacity;

        self = Option_unwrap(option);
        option = kit_Allocator_malloc(rawSize);

        if (Option_isSome(option)) {
            self->raw = Option_unwrap(option);
            self->capacity = actualCapacity;
            return Option_new(self);
        }
    }

    return None;
}

OneOf(Ok, OutOfMemoryError)
kit_Vector_expand(struct kit_Vector *self, const size_t capacity) {
    assertConfigValidity();
    assert(self);

    if (capacity > self->capacity) {
        const size_t newCapacity = calculateNewCapacity(self->capacity, capacity);
        const size_t rawSize = sizeof(self->raw[0]) * newCapacity;
        Option option = kit_Allocator_ralloc(self->raw, rawSize);

        if (Option_isSome(option)) {
            self->raw = Option_unwrap(option);
            self->capacity = newCapacity;
        } else {
            return OutOfMemoryError;
        }
    }

    return Ok;
}

OneOf(Ok, OutOfMemoryError)
kit_Vector_shrink(struct kit_Vector *self) {
    assertConfigValidity();
    assert(self);

    const size_t newCapacity = nextEven(max(self->size, KIT_VECTOR_DEFAULT_CAPACITY));
    const size_t rawSize = sizeof(self->raw[0]) * newCapacity;
    Option option = kit_Allocator_ralloc(self->raw, rawSize);

    if (Option_isSome(option)) {
        self->raw = Option_unwrap(option);
        self->capacity = newCapacity;
    } else {
        return OutOfMemoryError;
    }

    return Ok;
}

OneOf(Ok, OutOfRangeError, OutOfMemoryError)
kit_Vector_insert(struct kit_Vector *self, size_t index, void *element) {
    assertConfigValidity();
    assert(self);

    if (index > self->size) {
        return OutOfRangeError;
    }

    if (Ok != kit_Vector_expand(self, self->size + 1)) {
        return OutOfMemoryError;
    }

    kit_Allocator_move(
            &(self->raw[index + 1]),
            &(self->raw[index]),
            (self->size - index) * sizeof(self->raw[0])
    );
    self->raw[index] = element;
    self->size += 1;
    self->operationId += 1;

    return Ok;
}

OneOf(Ok, OutOfMemoryError)
kit_Vector_pushBack(struct kit_Vector *self, void *element) {
    assertConfigValidity();
    assert(self);

    return kit_Vector_insert(self, self->size, element);
}

OneOf(Ok, OutOfMemoryError)
kit_Vector_pushFront(struct kit_Vector *self, void *element) {
    assertConfigValidity();
    assert(self);

    return kit_Vector_insert(self, 0, element);
}

ResultOf(void *, OutOfRangeError)
kit_Vector_remove(struct kit_Vector *self, size_t index) {
    assertConfigValidity();
    assert(self);

    if (index >= self->size) {
        return Result_error(OutOfRangeError);
    }

    void *removedElement = self->raw[index];
    kit_Allocator_move(
            &(self->raw[index]),
            &(self->raw[index + 1]),
            (self->size - index - 1) * sizeof(self->raw[0])
    );
    self->size -= 1;
    self->operationId += 1;
    return Result_ok(removedElement);
}

ResultOf(void *, OutOfRangeError)
kit_Vector_popBack(struct kit_Vector *self) {
    assertConfigValidity();
    assert(self);

    const size_t size = self->size;
    return size > 0 ? kit_Vector_remove(self, size - 1) : Result_error(OutOfRangeError);
}

ResultOf(void *, OutOfRangeError)
kit_Vector_popFront(struct kit_Vector *self) {
    assertConfigValidity();
    assert(self);

    return kit_Vector_remove(self, 0);
}

ResultOf(void *, OutOfRangeError)
kit_Vector_put(struct kit_Vector *self, size_t index, void *element) {
    assertConfigValidity();
    assert(self);

    if (index >= self->size) {
        return Result_error(OutOfRangeError);
    }

    void *oldElement = self->raw[index];
    self->raw[index] = element;
    return Result_ok(oldElement);
}

ResultOf(void *, OutOfRangeError)
kit_Vector_get(const struct kit_Vector *self, size_t index) {
    assertConfigValidity();
    assert(self);

    return (index < self->size) ? Result_ok(self->raw[index]) : Result_error(OutOfRangeError);
}

ResultOf(void *, OutOfRangeError)
kit_Vector_back(const struct kit_Vector *self) {
    assertConfigValidity();
    assert(self);

    const size_t size = self->size;
    return size > 0 ? kit_Vector_get(self, size - 1) : Result_error(OutOfRangeError);
}

ResultOf(void *, OutOfRangeError)
kit_Vector_front(const struct kit_Vector *self) {
    assertConfigValidity();
    assert(self);

    return kit_Vector_get(self, 0);
}

void
kit_Vector_clear(struct kit_Vector *self) {
    assertConfigValidity();
    assert(self);

    self->size = 0;
    self->operationId += 1;
}

size_t
kit_Vector_size(const struct kit_Vector *self) {
    assertConfigValidity();
    assert(self);

    return self->size;
}

size_t
kit_Vector_capacity(const struct kit_Vector *self) {
    assertConfigValidity();
    assert(self);

    return self->capacity;
}

bool
kit_Vector_isEmpty(const struct kit_Vector *self) {
    assertConfigValidity();
    assert(self);

    return 0 == self->size;
}

void **
kit_Vector_raw(const struct kit_Vector *self) {
    assertConfigValidity();
    assert(self);

    return self->raw;
}

void
kit_Vector_delete(struct kit_Vector *self) {
    assertConfigValidity();

    if (self) {
        kit_Allocator_free(self->raw);
        kit_Allocator_free(self);
    }
}

struct kit_Vector_Iterator {
    int operationId;
    struct kit_Vector *container;
    size_t lastIndex;
    size_t prevIndex;
    size_t nextIndex;
};

OptionOf(struct kit_Vector_Iterator *)
kit_Vector_Iterator_new(struct kit_Vector *container, enum kit_Bound bound) {
    assertConfigValidity();
    assert(container);
    assert(KIT_BOUND_BEGIN <= bound && bound <= KIT_BOUND_END);

    struct kit_Vector_Iterator *self;
    Option option = kit_Allocator_calloc(1, sizeof(*self));

    if (Option_isSome(option)) {
        self = Option_unwrap(option);
        self->container = container;
        kit_Vector_Iterator_rewind(self, bound);
        return Option_new(self);
    }

    return None;
}

OptionOf(struct kit_Vector_Iterator *)
kit_Vector_Iterator_fromBegin(struct kit_Vector *container) {
    assertConfigValidity();
    assert(container);

    return kit_Vector_Iterator_new(container, KIT_BOUND_BEGIN);
}

OptionOf(struct kit_Vector_Iterator *)
kit_Vector_Iterator_fromEnd(struct kit_Vector *container) {
    assertConfigValidity();
    assert(container);

    return kit_Vector_Iterator_new(container, KIT_BOUND_END);
}

void
kit_Vector_Iterator_rewind(struct kit_Vector_Iterator *self, enum kit_Bound bound) {
    assertConfigValidity();
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

void
kit_Vector_Iterator_rewindToBegin(struct kit_Vector_Iterator *self) {
    assertConfigValidity();
    assert(self);

    kit_Vector_Iterator_rewind(self, KIT_BOUND_BEGIN);
}

void
kit_Vector_Iterator_rewindToEnd(struct kit_Vector_Iterator *self) {
    assertConfigValidity();
    assert(self);

    kit_Vector_Iterator_rewind(self, KIT_BOUND_END);
}

ResultOf(void *, OutOfRangeError, ConcurrentModificationError)
kit_Vector_Iterator_next(struct kit_Vector_Iterator *self) {
    assertConfigValidity();
    assert(self);

    if (kit_Vector_Iterator_isModified(self)) {
        return Result_error(ConcurrentModificationError);
    } else if (0 < self->nextIndex && self->nextIndex <= self->container->size) {
        void *nextElement = self->container->raw[self->nextIndex - 1];
        self->lastIndex = self->prevIndex = self->nextIndex;
        self->nextIndex += 1;
        return Result_ok(nextElement);
    } else {
        return Result_error(OutOfRangeError);
    }
}

ResultOf(void *, OutOfRangeError, ConcurrentModificationError)
kit_Vector_Iterator_previous(struct kit_Vector_Iterator *self) {
    assertConfigValidity();
    assert(self);

    if (kit_Vector_Iterator_isModified(self)) {
        return Result_error(ConcurrentModificationError);
    } else if (0 < self->prevIndex && self->prevIndex <= self->container->size) {
        void *previousElement = self->container->raw[self->prevIndex - 1];
        self->lastIndex = self->nextIndex = self->prevIndex;
        self->prevIndex -= 1;
        return Result_ok(previousElement);
    } else {
        return Result_error(OutOfRangeError);
    }
}

ResultOf(void *, IllegalStateError, ConcurrentModificationError)
kit_Vector_Iterator_setLast(struct kit_Vector_Iterator *self, void *element) {
    assertConfigValidity();
    assert(self);

    if (kit_Vector_Iterator_isModified(self)) {
        return Result_error(ConcurrentModificationError);
    } else if (0 < self->lastIndex && self->lastIndex <= self->container->size) {
        void *lastElement = self->container->raw[self->lastIndex - 1];
        self->container->raw[self->lastIndex - 1] = element;
        return Result_ok(lastElement);
    } else {
        return Result_error(IllegalStateError);
    };
}

bool
kit_Vector_Iterator_isModified(struct kit_Vector_Iterator *self) {
    assertConfigValidity();
    assert(self);

    struct kit_Vector *container = self->container;
    return NULL == container || self->operationId != container->operationId;
}

void
kit_Vector_Iterator_delete(struct kit_Vector_Iterator *self) {
    assertConfigValidity();

    if (self) {
        kit_Allocator_free(self);
    }
}
