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

struct kit_Pair {
    void *first;
    void *second;
};

Option kit_Pair_new(void *first, void *second) {
    struct kit_Pair *self;
    Option selfOption = kit_Allocator_malloc(sizeof(*self));

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        self->first = first;
        self->second = second;
    }

    return selfOption;
}

void kit_Pair_delete(struct kit_Pair *self) {
    if (self) {
        kit_Allocator_free(self);
    }
}

void *kit_Pair_first(struct kit_Pair *self) {
    assert(self);
    return self->first;
}

void *kit_Pair_second(struct kit_Pair *self) {
    assert(self);
    return self->second;
}
