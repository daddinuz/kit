/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   December 01, 2017 
 */

#include <assert.h>
#include <stdlib.h>
#include <kit/allocator/allocator.h>
#include <kit/collections/map.h>
#include <kit/collections/hash_map.h>

enum kit_Map_Trait {
    KIT_MAP_TRAIT_HASH_MAP
};

typedef void *kit_Map_Super;

typedef void (*kit_Map_Super_deleteFn)(kit_Map_Super);
typedef enum kit_Result (*kit_Map_Super_putFn)(kit_Map_Super, const void *, void *);
typedef enum kit_Result (*kit_Map_Super_getFn)(kit_Map_Super, const void *, void **);
typedef bool (*kit_Map_Super_hasFn)(kit_Map_Super, const void *);
typedef enum kit_Result (*kit_Map_Super_popFn)(kit_Map_Super, const void *, void **);
typedef void (*kit_Map_Super_clearFn)(kit_Map_Super);
typedef size_t (*kit_Map_Super_sizeFn)(kit_Map_Super);
typedef bool (*kit_Map_Super_isEmptyFn)(kit_Map_Super);

struct kit_Map {
    enum kit_Map_Trait trait;
    kit_Map_Super super;
    kit_Map_Super_deleteFn fnDelete;
    kit_Map_Super_putFn fnPut;
    kit_Map_Super_getFn fnGet;
    kit_Map_Super_hasFn fnHas;
    kit_Map_Super_popFn fnPop;
    kit_Map_Super_clearFn fnClear;
    kit_Map_Super_sizeFn fnSize;
    kit_Map_Super_isEmptyFn fnIsEmpty;
};

MutableOption
kit_Map_fromHashMap(size_t capacityHint, int compareFn(const void *, const void *), size_t hashFn(const void *)) {
    struct kit_Map *self;
    MutableOption selfOption = kit_Allocator_malloc(sizeof(*self)), superOption;

    if (MutableOption_isSome(selfOption)) {
        self = MutableOption_unwrap(selfOption);
        superOption = kit_HashMap_new(capacityHint, compareFn, hashFn);
        if (MutableOption_isSome(superOption)) {
            self->trait = KIT_MAP_TRAIT_HASH_MAP;
            self->super = MutableOption_unwrap(superOption);
            self->fnDelete = (kit_Map_Super_deleteFn) kit_HashMap_delete;
            self->fnPut = (kit_Map_Super_putFn) kit_HashMap_put;
            self->fnGet = (kit_Map_Super_getFn) kit_HashMap_get;
            self->fnHas = (kit_Map_Super_hasFn) kit_HashMap_has;
            self->fnPop = (kit_Map_Super_popFn) kit_HashMap_pop;
            self->fnClear = (kit_Map_Super_clearFn) kit_HashMap_clear;
            self->fnSize = (kit_Map_Super_sizeFn) kit_HashMap_size;
            self->fnIsEmpty = (kit_Map_Super_isEmptyFn) kit_HashMap_isEmpty;
        } else {
            kit_Allocator_free(self);
        }
    }

    return selfOption;
}

void kit_Map_delete(struct kit_Map *self) {
    if (self) {
        self->fnDelete(self->super);
        kit_Allocator_free(self);
    }
}

enum kit_Result kit_Map_put(struct kit_Map *self, const void *key, void *value) {
    assert(self);
    assert(key);
    return self->fnPut(self->super, key, value);
}

enum kit_Result kit_Map_get(struct kit_Map *self, const void *key, void **out) {
    assert(self);
    assert(key);
    assert(out);
    return self->fnGet(self->super, key, out);
}

bool kit_Map_has(struct kit_Map *self, const void *key) {
    assert(self);
    assert(key);
    return self->fnHas(self->super, key);
}

enum kit_Result kit_Map_pop(struct kit_Map *self, const void *key, void **out) {
    assert(self);
    assert(key);
    assert(out);
    return self->fnPop(self->super, key, out);
}

void kit_Map_clear(struct kit_Map *self) {
    assert(self);
    self->fnClear(self->super);
}

size_t kit_Map_size(struct kit_Map *self) {
    assert(self);
    return self->fnSize(self->super);
}

bool kit_Map_isEmpty(struct kit_Map *self) {
    assert(self);
    return self->fnIsEmpty(self->super);
}
