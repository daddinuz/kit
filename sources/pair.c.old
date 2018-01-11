/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 23, 2017 
 */

#include <assert.h>
#include <kit/allocator/allocator.h>
#include <kit/collections/pair.h>

struct kit_Pair kit_Pair_make(const void *key, void *value) {
    assert(key);
    return (struct kit_Pair) {
            .key=key,
            .value=value
    };
}

MutableOption kit_Pair_new(const void *key, void *value) {
    assert(key);
    struct kit_Pair *self;
    MutableOption selfOption = kit_Allocator_malloc(sizeof(*self));

    if (MutableOption_isSome(selfOption)) {
        self = MutableOption_unwrap(selfOption);
        self->key = key;
        self->value = value;
    }

    return selfOption;
}

void kit_Pair_delete(struct kit_Pair *self) {
    if (self) {
        kit_Allocator_free(self);
    }
}
