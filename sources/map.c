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

#include <assert.h>
#include <stdlib.h>
#include <kit/allocator/allocator.h>
#include <kit/collections/map.h>
#include <kit/collections/hash_map.h>

/*
 * kit_Map
 */
enum kit_Map_Trait {
    KIT_MAP_TRAIT_HASH_MAP
};

typedef void *kit_Map_Super;

typedef void (*kit_Map_Super_clearFn)(kit_Map_Super);
typedef Result (*kit_Map_Super_putFn)(kit_Map_Super, const void *, void *);
typedef Result (*kit_Map_Super_popFn)(kit_Map_Super, const void *);
typedef Result (*kit_Map_Super_getFn)(kit_Map_Super, const void *);
typedef bool (*kit_Map_Super_hasFn)(kit_Map_Super, const void *);
typedef size_t (*kit_Map_Super_sizeFn)(kit_Map_Super);
typedef bool (*kit_Map_Super_isEmptyFn)(kit_Map_Super);
typedef void (*kit_Map_Super_deleteFn)(kit_Map_Super);

struct kit_Map {
    enum kit_Map_Trait trait;
    kit_Map_Super super;
    kit_Map_Super_clearFn fnClear;
    kit_Map_Super_putFn fnPut;
    kit_Map_Super_popFn fnPop;
    kit_Map_Super_getFn fnGet;
    kit_Map_Super_hasFn fnHas;
    kit_Map_Super_sizeFn fnSize;
    kit_Map_Super_isEmptyFn fnIsEmpty;
    kit_Map_Super_deleteFn fnDelete;
};

Option
kit_Map_fromHashMap(const size_t capacityHint, int compareFn(const void *, const void *), size_t hashFn(const void *)) {
    assert(compareFn);
    assert(hashFn);
    struct kit_Map *self;
    Option selfOption = kit_Allocator_malloc(sizeof(*self)), superOption;

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        superOption = kit_HashMap_new(capacityHint, compareFn, hashFn);
        if (Option_isSome(superOption)) {
            self->trait = KIT_MAP_TRAIT_HASH_MAP;
            self->super = Option_unwrap(superOption);
            self->fnClear = (kit_Map_Super_clearFn) kit_HashMap_clear;
            self->fnPut = (kit_Map_Super_putFn) kit_HashMap_put;
            self->fnPop = (kit_Map_Super_popFn) kit_HashMap_pop;
            self->fnGet = (kit_Map_Super_getFn) kit_HashMap_get;
            self->fnHas = (kit_Map_Super_hasFn) kit_HashMap_has;
            self->fnSize = (kit_Map_Super_sizeFn) kit_HashMap_size;
            self->fnIsEmpty = (kit_Map_Super_isEmptyFn) kit_HashMap_isEmpty;
            self->fnDelete = (kit_Map_Super_deleteFn) kit_HashMap_delete;
        } else {
            kit_Allocator_free(self);
            selfOption = None;
        }
    }

    return selfOption;
}

void kit_Map_delete(struct kit_Map *const self) {
    if (self) {
        self->fnDelete(self->super);
        kit_Allocator_free(self);
    }
}

void kit_Map_clear(struct kit_Map *const self) {
    assert(self);
    self->fnClear(self->super);
}

Result kit_Map_put(struct kit_Map *const self, const void *const key, void *const value) {
    assert(self);
    assert(key);
    return self->fnPut(self->super, key, value);
}

Result kit_Map_pop(struct kit_Map *const self, const void *const key) {
    assert(self);
    assert(key);
    return self->fnPop(self->super, key);
}

Result kit_Map_get(const struct kit_Map *const self, const void *const key) {
    assert(self);
    assert(key);
    return self->fnGet(self->super, key);
}

bool kit_Map_has(const struct kit_Map *const self, const void *const key) {
    assert(self);
    assert(key);
    return self->fnHas(self->super, key);
}

size_t kit_Map_size(const struct kit_Map *const self) {
    assert(self);
    return self->fnSize(self->super);
}

bool kit_Map_isEmpty(const struct kit_Map *const self) {
    assert(self);
    return self->fnIsEmpty(self->super);
}

/*
 * kit_Map_Iterator
 */
typedef void *kit_Map_Iterator_Super;

typedef void (*kit_Map_Iterator_Super_rewindFn)(kit_Map_Iterator_Super);
typedef Result (*kit_Map_Iterator_Super_nextFn)(kit_Map_Iterator_Super, struct kit_Pair **);
typedef Result (*kit_Map_Iterator_Super_setLastFn)(kit_Map_Iterator_Super, void *);
typedef bool (*kit_Map_Iterator_Super_isModifiedFn)(kit_Map_Iterator_Super);
typedef void (*kit_Map_Iterator_Super_deleteFn)(kit_Map_Iterator_Super);

struct kit_Map_Iterator {
    kit_Map_Iterator_Super super;
    kit_Map_Iterator_Super_rewindFn fnRewind;
    kit_Map_Iterator_Super_nextFn fnNext;
    kit_Map_Iterator_Super_setLastFn fnSetLast;
    kit_Map_Iterator_Super_isModifiedFn fnIsModified;
    kit_Map_Iterator_Super_deleteFn fnDelete;
};

static Option kit_Map_Iterator_fromHashMap(struct kit_HashMap *const container) {
    assert(container);
    struct kit_Map_Iterator *self;
    Option selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        superOption = kit_HashMap_Iterator_new(container);
        if (Option_isSome(superOption)) {
            self->super = Option_unwrap(superOption);
            self->fnRewind = (kit_Map_Iterator_Super_rewindFn) kit_HashMap_Iterator_rewind;
            self->fnNext = (kit_Map_Iterator_Super_nextFn) kit_HashMap_Iterator_next;
            self->fnSetLast = (kit_Map_Iterator_Super_setLastFn) kit_HashMap_Iterator_setLast;
            self->fnIsModified = (kit_Map_Iterator_Super_isModifiedFn) kit_HashMap_Iterator_isModified;
            self->fnDelete = (kit_Map_Iterator_Super_deleteFn) kit_HashMap_Iterator_delete;
        } else {
            kit_Allocator_free(self);
            selfOption = None;
        }
    }

    return selfOption;

}

Option kit_Map_Iterator_new(struct kit_Map *const container) {
    assert(container);
    switch (container->trait) {
        case KIT_MAP_TRAIT_HASH_MAP: {
            return kit_Map_Iterator_fromHashMap(container->super);
        }
        default: {
            assert(false);
            abort();
        }
    }
}

void kit_Map_Iterator_rewind(struct kit_Map_Iterator *const self) {
    assert(self);
    self->fnRewind(self->super);
}

Result kit_Map_Iterator_next(struct kit_Map_Iterator *const self, struct kit_Pair **const ref) {
    assert(self);
    return self->fnNext(self->super, ref);
}

Result kit_Map_Iterator_setLast(struct kit_Map_Iterator *const self, void *const value) {
    assert(self);
    return self->fnSetLast(self->super, value);
}

bool kit_Map_Iterator_isModified(const struct kit_Map_Iterator *const self) {
    assert(self);
    return self->fnIsModified(self->super);
}

void kit_Map_Iterator_delete(struct kit_Map_Iterator *self) {
    if (self) {
        self->fnDelete(self->super);
        kit_Allocator_free(self);
    }
}
