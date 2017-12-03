/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 25, 2017 
 */

#include <assert.h>
#include <stdlib.h>
#include <kit/allocator/allocator.h>
#include <kit/collections/doubly_list.h>
#include <kit/collections/singly_list.h>
#include <kit/collections/xor_list.h>
#include <kit/collections/vector.h>
#include <kit/collections/sequence.h>

/*
 * kit_Sequence
 */
enum kit_Sequence_Trait {
    KIT_SEQUENCE_TRAIT_DOUBLY_LIST,
    KIT_SEQUENCE_TRAIT_SINGLY_LIST,
    KIT_SEQUENCE_TRAIT_XOR_LIST,
    KIT_SEQUENCE_TRAIT_VECTOR,
};

typedef void *kit_Sequence_Super;

typedef void (*kit_Sequence_Super_clearFn)(kit_Sequence_Super);
typedef void (*kit_Sequence_Super_deleteFn)(kit_Sequence_Super);
typedef enum kit_Result (*kit_Sequence_Super_insertFn)(kit_Sequence_Super, void *, size_t);
typedef enum kit_Result (*kit_Sequence_Super_pushBackFn)(kit_Sequence_Super, void *);
typedef enum kit_Result (*kit_Sequence_Super_pushFrontFn)(kit_Sequence_Super, void *);
typedef enum kit_Result (*kit_Sequence_Super_popBackFn)(kit_Sequence_Super, void **);
typedef enum kit_Result (*kit_Sequence_Super_popFrontFn)(kit_Sequence_Super, void **);
typedef enum kit_Result (*kit_Sequence_Super_removeFn)(kit_Sequence_Super, void **, size_t);
typedef enum kit_Result (*kit_Sequence_Super_setFn)(kit_Sequence_Super, void *, size_t);
typedef enum kit_Result (*kit_Sequence_Super_getFn)(kit_Sequence_Super, void **, size_t);
typedef enum kit_Result (*kit_Sequence_Super_backFn)(kit_Sequence_Super, void **);
typedef enum kit_Result (*kit_Sequence_Super_frontFn)(kit_Sequence_Super, void **);
typedef size_t (*kit_Sequence_Super_sizeFn)(kit_Sequence_Super);
typedef bool (*kit_Sequence_Super_isEmptyFn)(kit_Sequence_Super);
typedef size_t (*kit_Sequence_Super_capacityFn)(kit_Sequence_Super);
typedef enum kit_Result (*kit_Sequence_Super_reserveFn)(kit_Sequence_Super, size_t);
typedef enum kit_Result (*kit_Sequence_Super_shrinkFn)(kit_Sequence_Super);

struct kit_Sequence {
    enum kit_Sequence_Trait trait;
    kit_Sequence_Super super;
    kit_Sequence_Super_clearFn fnClear;
    kit_Sequence_Super_deleteFn fnDelete;
    kit_Sequence_Super_insertFn fnInsert;
    kit_Sequence_Super_pushBackFn fnPushBack;
    kit_Sequence_Super_pushFrontFn fnPushFront;
    kit_Sequence_Super_popBackFn fnPopBack;
    kit_Sequence_Super_popFrontFn fnPopFront;
    kit_Sequence_Super_removeFn fnRemove;
    kit_Sequence_Super_setFn fnSet;
    kit_Sequence_Super_getFn fnGet;
    kit_Sequence_Super_backFn fnBack;
    kit_Sequence_Super_frontFn fnFront;
    kit_Sequence_Super_sizeFn fnSize;
    kit_Sequence_Super_isEmptyFn fnIsEmpty;
    kit_Sequence_Super_capacityFn fnCapacity;
    kit_Sequence_Super_reserveFn fnReserve;
    kit_Sequence_Super_shrinkFn fnShrink;
};

static enum kit_Result kit_Sequence_Super_reserveNoOp(kit_Sequence_Super p0, size_t p1) {
    (void) p0;
    (void) p1;
    return KIT_RESULT_OK;
}

static enum kit_Result kit_Sequence_Super_shrinkNoOp(kit_Sequence_Super p0) {
    (void) p0;
    return KIT_RESULT_OK;
}

MutableOption kit_Sequence_fromDoublyList(void) {
    struct kit_Sequence *self;
    MutableOption selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (MutableOption_isSome(selfOption)) {
        self = MutableOption_unwrap(selfOption);
        superOption = kit_DoublyList_new();
        if (MutableOption_isSome(superOption)) {
            self->trait = KIT_SEQUENCE_TRAIT_DOUBLY_LIST;
            self->super = MutableOption_unwrap(superOption);
            self->fnClear = (kit_Sequence_Super_clearFn) kit_DoublyList_clear;
            self->fnDelete = (kit_Sequence_Super_deleteFn) kit_DoublyList_delete;
            self->fnInsert = (kit_Sequence_Super_insertFn) kit_DoublyList_insert;
            self->fnPushBack = (kit_Sequence_Super_pushBackFn) kit_DoublyList_pushBack;
            self->fnPushFront = (kit_Sequence_Super_pushFrontFn) kit_DoublyList_pushFront;
            self->fnPopBack = (kit_Sequence_Super_popBackFn) kit_DoublyList_popBack;
            self->fnPopFront = (kit_Sequence_Super_popFrontFn) kit_DoublyList_popFront;
            self->fnRemove = (kit_Sequence_Super_removeFn) kit_DoublyList_remove;
            self->fnSet = (kit_Sequence_Super_setFn) kit_DoublyList_set;
            self->fnGet = (kit_Sequence_Super_getFn) kit_DoublyList_get;
            self->fnBack = (kit_Sequence_Super_backFn) kit_DoublyList_back;
            self->fnFront = (kit_Sequence_Super_frontFn) kit_DoublyList_front;
            self->fnSize = (kit_Sequence_Super_sizeFn) kit_DoublyList_size;
            self->fnIsEmpty = (kit_Sequence_Super_isEmptyFn) kit_DoublyList_isEmpty;
            /* fake methods - no ops */
            self->fnCapacity = (kit_Sequence_Super_capacityFn) kit_DoublyList_size;
            self->fnReserve = (kit_Sequence_Super_reserveFn) kit_Sequence_Super_reserveNoOp;
            self->fnShrink = (kit_Sequence_Super_shrinkFn) kit_Sequence_Super_shrinkNoOp;
        } else {
            kit_Allocator_free(self);
        }
    }

    return selfOption;
}

MutableOption kit_Sequence_fromSinglyList(void) {
    struct kit_Sequence *self;
    MutableOption selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (MutableOption_isSome(selfOption)) {
        self = MutableOption_unwrap(selfOption);
        superOption = kit_SinglyList_new();
        if (MutableOption_isSome(superOption)) {
            self->trait = KIT_SEQUENCE_TRAIT_SINGLY_LIST;
            self->super = MutableOption_unwrap(superOption);
            self->fnClear = (kit_Sequence_Super_clearFn) kit_SinglyList_clear;
            self->fnDelete = (kit_Sequence_Super_deleteFn) kit_SinglyList_delete;
            self->fnInsert = (kit_Sequence_Super_insertFn) kit_SinglyList_insert;
            self->fnPushBack = (kit_Sequence_Super_pushBackFn) kit_SinglyList_pushBack;
            self->fnPushFront = (kit_Sequence_Super_pushFrontFn) kit_SinglyList_pushFront;
            self->fnPopBack = (kit_Sequence_Super_popBackFn) kit_SinglyList_popBack;
            self->fnPopFront = (kit_Sequence_Super_popFrontFn) kit_SinglyList_popFront;
            self->fnRemove = (kit_Sequence_Super_removeFn) kit_SinglyList_remove;
            self->fnSet = (kit_Sequence_Super_setFn) kit_SinglyList_set;
            self->fnGet = (kit_Sequence_Super_getFn) kit_SinglyList_get;
            self->fnBack = (kit_Sequence_Super_backFn) kit_SinglyList_back;
            self->fnFront = (kit_Sequence_Super_frontFn) kit_SinglyList_front;
            self->fnSize = (kit_Sequence_Super_sizeFn) kit_SinglyList_size;
            self->fnIsEmpty = (kit_Sequence_Super_isEmptyFn) kit_SinglyList_isEmpty;
            /* fake methods - no ops */
            self->fnCapacity = (kit_Sequence_Super_capacityFn) kit_SinglyList_size;
            self->fnReserve = (kit_Sequence_Super_reserveFn) kit_Sequence_Super_reserveNoOp;
            self->fnShrink = (kit_Sequence_Super_shrinkFn) kit_Sequence_Super_shrinkNoOp;
        } else {
            kit_Allocator_free(self);
        }
    }

    return selfOption;
}

MutableOption kit_Sequence_fromXorList(void) {
    struct kit_Sequence *self;
    MutableOption selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (MutableOption_isSome(selfOption)) {
        self = MutableOption_unwrap(selfOption);
        superOption = kit_XorList_new();
        if (MutableOption_isSome(superOption)) {
            self->trait = KIT_SEQUENCE_TRAIT_XOR_LIST;
            self->super = MutableOption_unwrap(superOption);
            self->fnClear = (kit_Sequence_Super_clearFn) kit_XorList_clear;
            self->fnDelete = (kit_Sequence_Super_deleteFn) kit_XorList_delete;
            self->fnInsert = (kit_Sequence_Super_insertFn) kit_XorList_insert;
            self->fnPushBack = (kit_Sequence_Super_pushBackFn) kit_XorList_pushBack;
            self->fnPushFront = (kit_Sequence_Super_pushFrontFn) kit_XorList_pushFront;
            self->fnPopBack = (kit_Sequence_Super_popBackFn) kit_XorList_popBack;
            self->fnPopFront = (kit_Sequence_Super_popFrontFn) kit_XorList_popFront;
            self->fnRemove = (kit_Sequence_Super_removeFn) kit_XorList_remove;
            self->fnSet = (kit_Sequence_Super_setFn) kit_XorList_set;
            self->fnGet = (kit_Sequence_Super_getFn) kit_XorList_get;
            self->fnBack = (kit_Sequence_Super_backFn) kit_XorList_back;
            self->fnFront = (kit_Sequence_Super_frontFn) kit_XorList_front;
            self->fnSize = (kit_Sequence_Super_sizeFn) kit_XorList_size;
            self->fnIsEmpty = (kit_Sequence_Super_isEmptyFn) kit_XorList_isEmpty;
            /* fake methods - no ops */
            self->fnCapacity = (kit_Sequence_Super_capacityFn) kit_XorList_size;
            self->fnReserve = (kit_Sequence_Super_reserveFn) kit_Sequence_Super_reserveNoOp;
            self->fnShrink = (kit_Sequence_Super_shrinkFn) kit_Sequence_Super_shrinkNoOp;
        } else {
            kit_Allocator_free(self);
        }
    }

    return selfOption;
}

MutableOption kit_Sequence_fromVector(size_t capacityHint) {
    struct kit_Sequence *self;
    MutableOption selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (MutableOption_isSome(selfOption)) {
        self = MutableOption_unwrap(selfOption);
        superOption = kit_Vector_from(capacityHint);
        if (MutableOption_isSome(superOption)) {
            self->trait = KIT_SEQUENCE_TRAIT_VECTOR;
            self->super = MutableOption_unwrap(superOption);
            self->fnClear = (kit_Sequence_Super_clearFn) kit_Vector_clear;
            self->fnDelete = (kit_Sequence_Super_deleteFn) kit_Vector_delete;
            self->fnInsert = (kit_Sequence_Super_insertFn) kit_Vector_insert;
            self->fnPushBack = (kit_Sequence_Super_pushBackFn) kit_Vector_pushBack;
            self->fnPushFront = (kit_Sequence_Super_pushFrontFn) kit_Vector_pushFront;
            self->fnPopBack = (kit_Sequence_Super_popBackFn) kit_Vector_popBack;
            self->fnPopFront = (kit_Sequence_Super_popFrontFn) kit_Vector_popFront;
            self->fnRemove = (kit_Sequence_Super_removeFn) kit_Vector_remove;
            self->fnSet = (kit_Sequence_Super_setFn) kit_Vector_set;
            self->fnGet = (kit_Sequence_Super_getFn) kit_Vector_get;
            self->fnBack = (kit_Sequence_Super_backFn) kit_Vector_back;
            self->fnFront = (kit_Sequence_Super_frontFn) kit_Vector_front;
            self->fnSize = (kit_Sequence_Super_sizeFn) kit_Vector_size;
            self->fnIsEmpty = (kit_Sequence_Super_isEmptyFn) kit_Vector_isEmpty;
            self->fnCapacity = (kit_Sequence_Super_capacityFn) kit_Vector_capacity;
            self->fnReserve = (kit_Sequence_Super_reserveFn) kit_Vector_reserve;
            self->fnShrink = (kit_Sequence_Super_shrinkFn) kit_Vector_shrink;
        } else {
            kit_Allocator_free(self);
        }
    }

    return selfOption;
}

void kit_Sequence_clear(struct kit_Sequence *self) {
    assert(self);
    self->fnClear(self->super);
}

void kit_Sequence_delete(struct kit_Sequence *self) {
    if (self) {
        self->fnDelete(self->super);
        kit_Allocator_free(self);
    }
}

enum kit_Result kit_Sequence_insert(struct kit_Sequence *self, void *e, size_t index) {
    assert(self);
    return self->fnInsert(self->super, e, index);
}

enum kit_Result kit_Sequence_pushBack(struct kit_Sequence *self, void *e) {
    assert(self);
    return self->fnPushBack(self->super, e);
}

enum kit_Result kit_Sequence_pushFront(struct kit_Sequence *self, void *e) {
    assert(self);
    return self->fnPushFront(self->super, e);
}

enum kit_Result kit_Sequence_popBack(struct kit_Sequence *self, void **out) {
    assert(self);
    assert(out);
    return self->fnPopBack(self->super, out);
}

enum kit_Result kit_Sequence_popFront(struct kit_Sequence *self, void **out) {
    assert(self);
    assert(out);
    return self->fnPopFront(self->super, out);
}

enum kit_Result kit_Sequence_remove(struct kit_Sequence *self, void **out, size_t index) {
    assert(self);
    assert(out);
    return self->fnRemove(self->super, out, index);
}

enum kit_Result kit_Sequence_set(struct kit_Sequence *self, void *e, size_t index) {
    assert(self);
    return self->fnSet(self->super, e, index);
}

enum kit_Result kit_Sequence_get(struct kit_Sequence *self, void **out, size_t index) {
    assert(self);
    assert(out);
    return self->fnGet(self->super, out, index);
}

enum kit_Result kit_Sequence_back(struct kit_Sequence *self, void **out) {
    assert(self);
    assert(out);
    return self->fnBack(self->super, out);
}

enum kit_Result kit_Sequence_front(struct kit_Sequence *self, void **out) {
    assert(self);
    assert(out);
    return self->fnFront(self->super, out);
}

size_t kit_Sequence_size(struct kit_Sequence *self) {
    assert(self);
    return self->fnSize(self->super);
}

bool kit_Sequence_isEmpty(struct kit_Sequence *self) {
    assert(self);
    return self->fnIsEmpty(self->super);
}

size_t kit_Sequence_capacity(struct kit_Sequence *self) {
    assert(self);
    return self->fnCapacity(self->super);
}

enum kit_Result kit_Sequence_reserve(struct kit_Sequence *self, size_t size) {
    assert(self);
    return self->fnReserve(self->super, size);
}

enum kit_Result kit_Sequence_shrink(struct kit_Sequence *self) {
    assert(self);
    return self->fnShrink(self->super);
}

/*
 * kit_Sequence_Iterator
 */
typedef void *kit_Sequence_Iterator_Super;

typedef void (*kit_Sequence_Iterator_Super_deleteFn)(kit_Sequence_Iterator_Super);
typedef void (*kit_Sequence_Iterator_Super_rewindFn)(kit_Sequence_Iterator_Super);
typedef enum kit_Result (*kit_Sequence_Iterator_Super_nextFn)(kit_Sequence_Iterator_Super, void **);
typedef enum kit_Result (*kit_Sequence_Iterator_Super_setLastFn)(kit_Sequence_Iterator_Super, void *);
typedef bool (*kit_Sequence_Iterator_Super_isModifiedFn)(kit_Sequence_Iterator_Super);

struct kit_Sequence_Iterator {
    kit_Sequence_Iterator_Super super;
    kit_Sequence_Iterator_Super_deleteFn fnDelete;
    kit_Sequence_Iterator_Super_rewindFn fnRewind;
    kit_Sequence_Iterator_Super_nextFn fnNext;
    kit_Sequence_Iterator_Super_setLastFn fnSetLast;
    kit_Sequence_Iterator_Super_isModifiedFn fnIsModified;
};

static MutableOption kit_Sequence_Iterator_fromDoublyList(struct kit_DoublyList *container) {
    assert(container);
    struct kit_Sequence_Iterator *self;
    MutableOption selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (MutableOption_isSome(selfOption)) {
        self = MutableOption_unwrap(selfOption);
        superOption = kit_DoublyList_Iterator_fromBegin(container);
        if (MutableOption_isSome(superOption)) {
            self->super = MutableOption_unwrap(superOption);
            self->fnDelete = (kit_Sequence_Iterator_Super_deleteFn) kit_DoublyList_Iterator_delete;
            self->fnRewind = (kit_Sequence_Iterator_Super_rewindFn) kit_DoublyList_Iterator_rewindToBegin;
            self->fnNext = (kit_Sequence_Iterator_Super_nextFn) kit_DoublyList_Iterator_next;
            self->fnSetLast = (kit_Sequence_Iterator_Super_setLastFn) kit_DoublyList_Iterator_setLast;
            self->fnIsModified = (kit_Sequence_Iterator_Super_isModifiedFn) kit_DoublyList_Iterator_isModified;
        } else {
            kit_Allocator_free(self);
        }
    }

    return selfOption;
}

static MutableOption kit_Sequence_Iterator_fromSinglyList(struct kit_SinglyList *container) {
    assert(container);
    struct kit_Sequence_Iterator *self;
    MutableOption selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (MutableOption_isSome(selfOption)) {
        self = MutableOption_unwrap(selfOption);
        superOption = kit_SinglyList_Iterator_fromBegin(container);
        if (MutableOption_isSome(superOption)) {
            self->super = MutableOption_unwrap(superOption);
            self->fnDelete = (kit_Sequence_Iterator_Super_deleteFn) kit_SinglyList_Iterator_delete;
            self->fnRewind = (kit_Sequence_Iterator_Super_rewindFn) kit_SinglyList_Iterator_rewindToBegin;
            self->fnNext = (kit_Sequence_Iterator_Super_nextFn) kit_SinglyList_Iterator_next;
            self->fnSetLast = (kit_Sequence_Iterator_Super_setLastFn) kit_SinglyList_Iterator_setLast;
            self->fnIsModified = (kit_Sequence_Iterator_Super_isModifiedFn) kit_SinglyList_Iterator_isModified;
        } else {
            kit_Allocator_free(self);
        }
    }

    return selfOption;
}

static MutableOption kit_Sequence_Iterator_fromXorList(struct kit_XorList *container) {
    assert(container);
    struct kit_Sequence_Iterator *self;
    MutableOption selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (MutableOption_isSome(selfOption)) {
        self = MutableOption_unwrap(selfOption);
        superOption = kit_XorList_Iterator_fromBegin(container);
        if (MutableOption_isSome(superOption)) {
            self->super = MutableOption_unwrap(superOption);
            self->fnDelete = (kit_Sequence_Iterator_Super_deleteFn) kit_XorList_Iterator_delete;
            self->fnRewind = (kit_Sequence_Iterator_Super_rewindFn) kit_XorList_Iterator_rewindToBegin;
            self->fnNext = (kit_Sequence_Iterator_Super_nextFn) kit_XorList_Iterator_next;
            self->fnSetLast = (kit_Sequence_Iterator_Super_setLastFn) kit_XorList_Iterator_setLast;
            self->fnIsModified = (kit_Sequence_Iterator_Super_isModifiedFn) kit_XorList_Iterator_isModified;
        } else {
            kit_Allocator_free(self);
        }
    }

    return selfOption;
}

static MutableOption kit_Sequence_Iterator_fromVector(struct kit_Vector *container) {
    assert(container);
    struct kit_Sequence_Iterator *self;
    MutableOption selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (MutableOption_isSome(selfOption)) {
        self = MutableOption_unwrap(selfOption);
        superOption = kit_Vector_Iterator_fromBegin(container);
        if (MutableOption_isSome(superOption)) {
            self->super = MutableOption_unwrap(superOption);
            self->fnDelete = (kit_Sequence_Iterator_Super_deleteFn) kit_Vector_Iterator_delete;
            self->fnRewind = (kit_Sequence_Iterator_Super_rewindFn) kit_Vector_Iterator_rewindToBegin;
            self->fnNext = (kit_Sequence_Iterator_Super_nextFn) kit_Vector_Iterator_next;
            self->fnSetLast = (kit_Sequence_Iterator_Super_setLastFn) kit_Vector_Iterator_setLast;
            self->fnIsModified = (kit_Sequence_Iterator_Super_isModifiedFn) kit_Vector_Iterator_isModified;
        } else {
            kit_Allocator_free(self);
        }
    }

    return selfOption;
}

MutableOption kit_Sequence_Iterator_new(struct kit_Sequence *container) {
    assert(container);
    switch (container->trait) {
        case KIT_SEQUENCE_TRAIT_DOUBLY_LIST: {
            return kit_Sequence_Iterator_fromDoublyList(container->super);
        }
        case KIT_SEQUENCE_TRAIT_SINGLY_LIST: {
            return kit_Sequence_Iterator_fromSinglyList(container->super);
        }
        case KIT_SEQUENCE_TRAIT_XOR_LIST: {
            return kit_Sequence_Iterator_fromXorList(container->super);
        }
        case KIT_SEQUENCE_TRAIT_VECTOR: {
            return kit_Sequence_Iterator_fromVector(container->super);
        }
        default: {
            assert(false);
            abort();
        }
    }
}

void kit_Sequence_Iterator_rewind(struct kit_Sequence_Iterator *self) {
    assert(self);
    self->fnRewind(self->super);
}

void kit_Sequence_Iterator_delete(struct kit_Sequence_Iterator *self) {
    if (self) {
        self->fnDelete(self->super);
        kit_Allocator_free(self);
    }
}

enum kit_Result kit_Sequence_Iterator_next(struct kit_Sequence_Iterator *self, void **out) {
    assert(self);
    assert(out);
    return self->fnNext(self->super, out);
}

enum kit_Result kit_Sequence_Iterator_setLast(struct kit_Sequence_Iterator *self, void *e) {
    assert(self);
    return self->fnSetLast(self->super, e);
}

bool kit_Sequence_Iterator_isModified(struct kit_Sequence_Iterator *self) {
    assert(self);
    return self->fnIsModified(self->super);
}
