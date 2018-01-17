/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   December 01, 2017 
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

Option kit_HashMap_new(size_t capacityHint, int compareFn(const void *, const void *), size_t hashFn(const void *)) {
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

void kit_HashMap_delete(struct kit_HashMap *self) {
    if (self) {
        kit_HashMap_clear(self);
        kit_Allocator_free(self);
    }
}

Result kit_HashMap_add(struct kit_HashMap *self, struct kit_Pair *pair) {
    assert(self);
    assert(pair);
    return kit_HashMap_put(self, kit_Pair_getKey(pair), kit_Pair_getValue(pair));
}

Result kit_HashMap_put(struct kit_HashMap *self, const void *key, void *value) {
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

Result kit_HashMap_get(struct kit_HashMap *self, const void *key) {
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

bool kit_HashMap_has(struct kit_HashMap *self, const void *key) {
    assert(self);
    assert(key);
    return Result_isOk(kit_HashMap_get(self, key));
}

Result kit_HashMap_pop(struct kit_HashMap *self, const void *key) {
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

void kit_HashMap_clear(struct kit_HashMap *self) {
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

size_t kit_HashMap_size(struct kit_HashMap *self) {
    assert(self);
    return self->size;
}

bool kit_HashMap_isEmpty(struct kit_HashMap *self) {
    assert(self);
    return 0 == self->size;
}

struct kit_HashMap_Iterator {
    int operationId;
    size_t currentIndex;
    struct kit_HashMap *container;
    struct kit_HashMap_Bucket *last;
    struct kit_HashMap_Bucket *next;
};

Option kit_HashMap_Iterator_new(struct kit_HashMap *container) {
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

void kit_HashMap_Iterator_delete(struct kit_HashMap_Iterator *self) {
    if (self) {
        kit_Allocator_free(self);
    }
}

void kit_HashMap_Iterator_rewind(struct kit_HashMap_Iterator *self) {
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

Result kit_HashMap_Iterator_next(struct kit_HashMap_Iterator *self, struct kit_Pair **ref) {
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

Result kit_HashMap_Iterator_setLast(struct kit_HashMap_Iterator *self, void *value) {
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

bool kit_HashMap_Iterator_isModified(struct kit_HashMap_Iterator *self) {
    assert(self);
    struct kit_HashMap *container = self->container;
    return NULL == container || self->operationId != container->operationId;
}
