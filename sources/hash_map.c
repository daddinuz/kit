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

/*
 * TODO:
 *  - heuristic growth and re-hashing
 */

#include <assert.h>
#include <limits.h>
#include <kit/allocator/allocator.h>
#include <kit/collections/hash_map.h>

struct kit_HashMap_Bucket {
    struct kit_HashMap_Bucket *next;
    const void *key;
    void *value;
};

struct kit_HashMap {
    int operationId;
    size_t size;
    size_t capacity;
    size_t (*hashFn)(const void *);
    int (*compareFn)(const void *, const void *);
    struct kit_HashMap_Bucket **buckets;
};

Option
kit_HashMap_new(const size_t capacityHint, int compareFn(const void *, const void *), size_t hashFn(const void *)) {
    assert(compareFn);
    assert(hashFn);

    size_t i;
    Option selfOption;
    struct kit_HashMap *self;
    static size_t primeNumbers[] = {269, 269, 509, 1021, 1021, 2053, 4093, 8191, 16381, 32771, 65521, INT_MAX};

    for (i = 1; primeNumbers[i] < capacityHint; i++);

    selfOption = kit_Allocator_calloc(1, sizeof(*self) + sizeof(self->buckets[0]) * primeNumbers[i - 1]);
    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        self->capacity = primeNumbers[i - 1];
        self->hashFn = hashFn;
        self->compareFn = compareFn;
        self->buckets = (struct kit_HashMap_Bucket **) (self + 1);
    }

    return selfOption;
}

void kit_HashMap_clear(struct kit_HashMap *const self) {
    assert(self);

    if (self->size > 0) {
        struct kit_HashMap_Bucket *current, *next;
        for (size_t i = 0; i < self->capacity; i++) {
            for (current = self->buckets[i]; current; current = next) {
                next = current->next;
                kit_Allocator_free(current);
            }
            self->buckets[i] = NULL;
        }
        self->size = 0;
        self->operationId += 1;
    }
}

Result kit_HashMap_put(struct kit_HashMap *const self, const void *const key, void *const value) {
    assert(self);
    assert(key);

    Option bucketOption;
    struct kit_HashMap_Bucket *bucket;
    const size_t index = self->hashFn(key) % self->capacity;

    for (bucket = self->buckets[index]; bucket; bucket = bucket->next) {
        if (self->compareFn(key, bucket->key) == 0) {
            break;
        }
    }

    bucketOption = Option_new(bucket);
    if (Option_isNone(bucketOption)) {
        bucketOption = kit_Allocator_calloc(1, sizeof(*bucket));
        if (Option_isSome(bucketOption)) {
            bucket = Option_unwrap(bucketOption);
            bucket->key = key;
            bucket->next = self->buckets[index];
            self->buckets[index] = bucket;
            self->size += 1;
        }
    }

    if (Option_isSome(bucketOption)) {
        bucket = Option_unwrap(bucketOption);
        void *previousValue = bucket->value;
        bucket->value = value;
        self->operationId += 1;
        return Result_ok(previousValue);
    }

    return Result_error(OutOfMemoryError);
}

Result kit_HashMap_pop(struct kit_HashMap *const self, const void *const key) {
    assert(self);
    assert(key);

    const size_t index = self->hashFn(key) % self->capacity;
    for (struct kit_HashMap_Bucket **bucketRef = &self->buckets[index]; *bucketRef; bucketRef = &(*bucketRef)->next) {
        if (self->compareFn(key, (*bucketRef)->key) == 0) {
            struct kit_HashMap_Bucket *bucket = *bucketRef;
            void *previousValue = bucket->value;
            *bucketRef = bucket->next;
            kit_Allocator_free(bucket);
            self->size -= 1;
            self->operationId += 1;
            return Result_ok(previousValue);
        }
    }

    return Result_error(OutOfRangeError);
}

Result kit_HashMap_get(const struct kit_HashMap *const self, const void *const key) {
    assert(self);
    assert(key);

    const size_t index = self->hashFn(key) % self->capacity;
    for (struct kit_HashMap_Bucket *bucket = self->buckets[index]; bucket; bucket = bucket->next) {
        if (self->compareFn(key, bucket->key) == 0) {
            return Result_ok(bucket->value);
        }
    }

    return Result_error(OutOfRangeError);
}

bool kit_HashMap_has(const struct kit_HashMap *const self, const void *const key) {
    assert(self);
    assert(key);
    return Result_isOk(kit_HashMap_get(self, key));
}

size_t kit_HashMap_size(const struct kit_HashMap *const self) {
    assert(self);
    return self->size;
}

bool kit_HashMap_isEmpty(const struct kit_HashMap *const self) {
    assert(self);
    return 0 == self->size;
}

void kit_HashMap_delete(struct kit_HashMap *self) {
    if (self) {
        kit_HashMap_clear(self);
        kit_Allocator_free(self);
    }
}

struct kit_HashMap_Iterator {
    int operationId;
    size_t currentIndex;
    struct kit_HashMap *container;
    struct kit_HashMap_Bucket *last;
    struct kit_HashMap_Bucket *next;
};

Option kit_HashMap_Iterator_new(struct kit_HashMap *const container) {
    assert(container);

    struct kit_HashMap_Iterator *self;
    Option selfOption = kit_Allocator_calloc(1, sizeof(*self));

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        self->container = container;
        kit_HashMap_Iterator_rewind(self);
    }

    return selfOption;
}

void kit_HashMap_Iterator_rewind(struct kit_HashMap_Iterator *const self) {
    assert(self);
    assert(self->container);

    const struct kit_HashMap *container = self->container;
    struct kit_HashMap_Bucket **buckets = container->buckets;
    size_t currentIndex = 0;
    const size_t capacity = container->capacity;

    if (container->size > 0) {
        while (currentIndex < capacity && NULL == buckets[currentIndex]) {
            currentIndex += 1;
        }
    }

    self->operationId = container->operationId;
    self->currentIndex = currentIndex;
    self->last = NULL;
    self->next = buckets[currentIndex];
}

Result kit_HashMap_Iterator_next(struct kit_HashMap_Iterator *const self, struct kit_Pair **const ref) {
    assert(self);
    assert(ref);

    if (kit_HashMap_Iterator_isModified(self)) {
        return Result_error(ConcurrentModificationError);
    }

    struct kit_HashMap_Bucket *currentBucket = self->next;
    if (currentBucket) {
        struct kit_Pair *out = *ref;
        kit_Pair_setKey(out, currentBucket->key);
        kit_Pair_setValue(out, currentBucket->value);

        self->last = currentBucket;

        if (currentBucket->next) {
            self->next = currentBucket->next;

            *ref = NULL;
            return Result_ok(out);
        }

        size_t currentIndex = self->currentIndex + 1;
        const size_t capacity = self->container->capacity;

        if (self->currentIndex < capacity) {
            struct kit_HashMap_Bucket **buckets = self->container->buckets;

            while (currentIndex < capacity) {
                if (buckets[currentIndex]) {
                    self->next = buckets[currentIndex];
                    self->currentIndex = currentIndex;

                    *ref = NULL;
                    return Result_ok(out);
                }
                currentIndex += 1;
            }

            self->next = NULL;
            self->currentIndex = 0;

            *ref = NULL;
            return Result_ok(out);
        }
    }

    self->next = NULL;
    self->currentIndex = 0;
    // FIXME at this point *ref should not be modified
    return Result_error(OutOfRangeError);
}

Result kit_HashMap_Iterator_setLast(struct kit_HashMap_Iterator *const self, void *const value) {
    assert(self);

    if (kit_HashMap_Iterator_isModified(self)) {
        return Result_error(ConcurrentModificationError);
    } else if (self->last) {
        void *previousValue = self->last->value;
        self->last->value = value;
        return Result_ok(previousValue);
    } else {
        return Result_error(IllegalStateError);
    }
}

bool kit_HashMap_Iterator_isModified(const struct kit_HashMap_Iterator *const self) {
    assert(self);
    struct kit_HashMap *container = self->container;
    return NULL == container || self->operationId != container->operationId;
}

void kit_HashMap_Iterator_delete(struct kit_HashMap_Iterator *self) {
    if (self) {
        kit_Allocator_free(self);
    }
}
