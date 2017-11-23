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

Optional(struct kit_Pair *) kit_Pair_new(void *first, void *second) {
    struct kit_Pair *self = kit_Allocator_malloc(sizeof(*self));

    if (self) {
        self->first = first;
        self->second = second;
    }

    return Option_new(self);
}

void kit_Pair_delete(struct kit_Pair *self) {
    kit_Allocator_free(self);
}

void *kit_Pair_first(struct kit_Pair *self) {
    assert(self);
    return self->first;
}

void *kit_Pair_second(struct kit_Pair *self) {
    assert(self);
    return self->second;
}
