/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   January 16, 2018
 */

#include <assert.h>
#include <kit/allocator/allocator.h>
#include <kit/collections/pair.h>

struct kit_Pair {
    const void *key;
    void *value;
};

OptionOf(struct kit_Pair *)
kit_Pair_new(const void *const key, void *const value) {
    assert(key);
    struct kit_Pair *self;
    Option selfOption = kit_Allocator_malloc(sizeof(*self));

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        self->key = key;
        self->value = value;
    }

    return selfOption;
}

const void *
kit_Pair_getKey(struct kit_Pair *const self) {
    assert(self);
    return self->key;
}

void *
kit_Pair_getValue(struct kit_Pair *const self) {
    assert(self);
    return self->value;
}

void
kit_Pair_setKey(struct kit_Pair *const self, const void *const key) {
    assert(self);
    assert(key);
    self->key = key;
}

void
kit_Pair_setValue(struct kit_Pair *const self, void *const value) {
    assert(self);
    self->value = value;
}

void
kit_Pair_delete(struct kit_Pair *self) {
    if (self) {
        kit_Allocator_free(self);
    }
}
