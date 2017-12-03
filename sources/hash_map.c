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

MutableOption kit_HashMap_new(size_t capacityHint, int compareFn(const void *, const void *), size_t hashFn(const void *)) {
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

enum kit_Result kit_HashMap_get(struct kit_HashMap *self, const void *key, void **out) {
    assert(self);
    assert(key);
    assert(out);
    const size_t index = self->hashFn(key) % self->capacity;
    enum kit_Result result = KIT_RESULT_OUT_OF_RANGE_ERROR;

    for (struct kit_HashMap_Bucket *bucket = self->buckets[index]; bucket; bucket = bucket->next) {
        if (self->compareFn(key, bucket->key) == 0) {
            *out = bucket->value;
            result = KIT_RESULT_OK;
            break;
        }
    }

    return result;
}

bool kit_HashMap_has(struct kit_HashMap *self, const void *key) {
    assert(self);
    assert(key);
    void *unused = NULL;
    return KIT_RESULT_OK == kit_HashMap_get(self, key, &unused);
}

enum kit_Result kit_HashMap_pop(struct kit_HashMap *self, const void *key, void **out) {
    assert(self);
    assert(key);
    assert(out);
    const size_t index = self->hashFn(key) % self->capacity;
    enum kit_Result result = KIT_RESULT_OUT_OF_RANGE_ERROR;

    for (struct kit_HashMap_Bucket **bucketRef = &self->buckets[index]; *bucketRef; bucketRef = &(*bucketRef)->next) {
        if (self->compareFn(key, (*bucketRef)->key) == 0) {
            struct kit_HashMap_Bucket *bucket = *bucketRef;
            *out = bucket->value;
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
