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

MutableOption
kit_HashMap_new(size_t capacityHint, int compareFn(const void *, const void *), size_t hashFn(const void *)) {
    assert(compareFn);
    assert(hashFn);
    size_t i;
    MutableOption selfOption;
    struct kit_HashMap *self;
    static size_t primeNumbers[] = {269, 269, 509, 1021, 1021, 2053, 4093, 8191, 16381, 32771, 65521, INT_MAX};

    for (i = 1; primeNumbers[i] < capacityHint; i++);

    selfOption = kit_Allocator_calloc(1, sizeof(*self) + sizeof(self->buckets[0]) * primeNumbers[i - 1]);
    if (MutableOption_isSome(selfOption)) {
        self = MutableOption_unwrap(selfOption);
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

enum kit_Result kit_HashMap_put(struct kit_HashMap *self, const void *key, void *value) {
    assert(self);
    assert(key);
    MutableOption bucketMutableOption;
    struct kit_HashMap_Bucket *bucket;
    enum kit_Result result = KIT_RESULT_OK;
    const size_t index = self->hashFn(key) % self->capacity;

    for (bucket = self->buckets[index]; bucket; bucket = bucket->next) {
        if (self->compareFn(key, bucket->key) == 0) {
            break;
        }
    }

    bucketMutableOption = MutableOption_new(bucket);
    if (MutableOption_isNone(bucketMutableOption)) {
        bucketMutableOption = kit_Allocator_calloc(1, sizeof(*bucket));
        if (MutableOption_isSome(bucketMutableOption)) {
            bucket = MutableOption_unwrap(bucketMutableOption);
            bucket->key = key;
            bucket->next = self->buckets[index];
            self->buckets[index] = bucket;
            self->size += 1;
        }
    }

    if (MutableOption_isSome(bucketMutableOption)) {
        bucket = MutableOption_unwrap(bucketMutableOption);
        bucket->value = value;
        self->operationId += 1;
    } else {
        result = KIT_RESULT_OUT_OF_MEMORY_ERROR;
    }

    return result;
}

enum kit_Result kit_HashMap_add(struct kit_HashMap *self, struct kit_Pair pair) {
    assert(self);
    assert(pair.key);
    return kit_HashMap_put(self, pair.key, pair.value);
}

enum kit_Result kit_HashMap_get(struct kit_HashMap *self, const void *key, struct kit_Pair *out) {
    assert(self);
    assert(key);
    assert(out);
    const size_t index = self->hashFn(key) % self->capacity;
    enum kit_Result result = KIT_RESULT_OUT_OF_RANGE_ERROR;

    for (struct kit_HashMap_Bucket *bucket = self->buckets[index]; bucket; bucket = bucket->next) {
        if (self->compareFn(key, bucket->key) == 0) {
            (*out).key = bucket->key;
            (*out).value = bucket->value;
            result = KIT_RESULT_OK;
            break;
        }
    }

    return result;
}

bool kit_HashMap_has(struct kit_HashMap *self, const void *key) {
    assert(self);
    assert(key);
    struct kit_Pair pair;
    return KIT_RESULT_OK == kit_HashMap_get(self, key, &pair);
}

enum kit_Result kit_HashMap_pop(struct kit_HashMap *self, const void *key, struct kit_Pair *out) {
    assert(self);
    assert(key);
    assert(out);
    const size_t index = self->hashFn(key) % self->capacity;
    enum kit_Result result = KIT_RESULT_OUT_OF_RANGE_ERROR;

    for (struct kit_HashMap_Bucket **bucketRef = &self->buckets[index]; *bucketRef; bucketRef = &(*bucketRef)->next) {
        if (self->compareFn(key, (*bucketRef)->key) == 0) {
            struct kit_HashMap_Bucket *bucket = *bucketRef;
            (*out).key = bucket->key;
            (*out).value = bucket->value;
            *bucketRef = bucket->next;
            kit_Allocator_free(bucket);
            self->size -= 1;
            self->operationId += 1;
            result = KIT_RESULT_OK;
            break;
        }
    }

    return result;
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

MutableOption kit_HashMap_Iterator_new(struct kit_HashMap *container) {
    assert(container);
    struct kit_HashMap_Iterator *self;
    MutableOption selfOption = kit_Allocator_calloc(1, sizeof(*self));

    if (MutableOption_isSome(selfOption)) {
        self = MutableOption_unwrap(selfOption);
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
    const size_t CAPACITY = container->capacity;
    size_t currentIndex = 0;

    if (container->size > 0) {
        while (currentIndex < CAPACITY && NULL == buckets[currentIndex]) {
            currentIndex += 1;
        }
    }

    self->operationId = container->operationId;
    self->currentIndex = currentIndex;
    self->last = NULL;
    self->next = buckets[currentIndex];
}

enum kit_Result kit_HashMap_Iterator_next(struct kit_HashMap_Iterator *self, struct kit_Pair *out) {
    assert(self);
    assert(out);

    if (kit_HashMap_Iterator_isModified(self)) {
        return KIT_RESULT_CONCURRENT_MODIFICATION_ERROR;
    }

    struct kit_HashMap_Bucket *currentBucket = self->next;
    if (currentBucket) {
        (*out).key = currentBucket->key;
        (*out).value = currentBucket->value;
        self->last = currentBucket;

        if (currentBucket->next) {
            self->next = currentBucket->next;
            return KIT_RESULT_OK;
        }

        size_t currentIndex = self->currentIndex + 1;
        const size_t CAPACITY = self->container->capacity;

        if (self->currentIndex < CAPACITY) {
            struct kit_HashMap_Bucket **buckets = self->container->buckets;

            while (currentIndex < CAPACITY) {
                if (buckets[currentIndex]) {
                    self->next = buckets[currentIndex];
                    self->currentIndex = currentIndex;
                    return KIT_RESULT_OK;
                }
                currentIndex += 1;
            }

            self->next = NULL;
            self->currentIndex = 0;
            return KIT_RESULT_OK;
        }
    }

    self->next = NULL;
    self->currentIndex = 0;
    return KIT_RESULT_OUT_OF_RANGE_ERROR;
}

enum kit_Result kit_HashMap_Iterator_setLast(struct kit_HashMap_Iterator *self, void *value) {
    assert(self);
    enum kit_Result result = KIT_RESULT_OK;

    if (kit_HashMap_Iterator_isModified(self)) {
        result = KIT_RESULT_CONCURRENT_MODIFICATION_ERROR;
    } else if (self->last) {
        self->last->value = value;
    } else {
        result = KIT_RESULT_ILLEGAL_STATE_ERROR;
    }

    return result;
}

bool kit_HashMap_Iterator_isModified(struct kit_HashMap_Iterator *self) {
    assert(self);
    struct kit_HashMap *container = self->container;
    return NULL == container || self->operationId != container->operationId;
}
