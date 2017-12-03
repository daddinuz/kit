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
#include <kit/collections/xor_list.h>
#include <kit/collections/vector.h>
#include <kit/collections/list.h>

/*
 * kit_List
 */
enum kit_List_Trait {
    KIT_LIST_TRAIT_DOUBLY_LIST,
    KIT_LIST_TRAIT_XOR_LIST,
    KIT_LIST_TRAIT_VECTOR,
};

typedef void *kit_List_Super;

typedef void (*kit_List_Super_clearFn)(kit_List_Super);
typedef void (*kit_List_Super_deleteFn)(kit_List_Super);
typedef enum kit_Result (*kit_List_Super_insertFn)(kit_List_Super, void *, size_t);
typedef enum kit_Result (*kit_List_Super_pushBackFn)(kit_List_Super, void *);
typedef enum kit_Result (*kit_List_Super_pushFrontFn)(kit_List_Super, void *);
typedef enum kit_Result (*kit_List_Super_popBackFn)(kit_List_Super, void **);
typedef enum kit_Result (*kit_List_Super_popFrontFn)(kit_List_Super, void **);
typedef enum kit_Result (*kit_List_Super_removeFn)(kit_List_Super, void **, size_t);
typedef enum kit_Result (*kit_List_Super_setFn)(kit_List_Super, void *, size_t);
typedef enum kit_Result (*kit_List_Super_getFn)(kit_List_Super, void **, size_t);
typedef enum kit_Result (*kit_List_Super_backFn)(kit_List_Super, void **);
typedef enum kit_Result (*kit_List_Super_frontFn)(kit_List_Super, void **);
typedef size_t (*kit_List_Super_sizeFn)(kit_List_Super);
typedef bool (*kit_List_Super_isEmptyFn)(kit_List_Super);
typedef size_t (*kit_List_Super_capacityFn)(kit_List_Super);
typedef enum kit_Result (*kit_List_Super_reserveFn)(kit_List_Super, size_t);
typedef enum kit_Result (*kit_List_Super_shrinkFn)(kit_List_Super);

struct kit_List {
    enum kit_List_Trait trait;
    kit_List_Super super;
    kit_List_Super_clearFn fnClear;
    kit_List_Super_deleteFn fnDelete;
    kit_List_Super_insertFn fnInsert;
    kit_List_Super_pushBackFn fnPushBack;
    kit_List_Super_pushFrontFn fnPushFront;
    kit_List_Super_popBackFn fnPopBack;
    kit_List_Super_popFrontFn fnPopFront;
    kit_List_Super_removeFn fnRemove;
    kit_List_Super_setFn fnSet;
    kit_List_Super_getFn fnGet;
    kit_List_Super_backFn fnBack;
    kit_List_Super_frontFn fnFront;
    kit_List_Super_sizeFn fnSize;
    kit_List_Super_isEmptyFn fnIsEmpty;
    kit_List_Super_capacityFn fnCapacity;
    kit_List_Super_reserveFn fnReserve;
    kit_List_Super_shrinkFn fnShrink;
};

static enum kit_Result kit_List_Super_reserveNoOp(kit_List_Super p0, size_t p1) {
    (void) p0;
    (void) p1;
    return KIT_RESULT_OK;
}

static enum kit_Result kit_List_Super_shrinkNoOp(kit_List_Super p0) {
    (void) p0;
    return KIT_RESULT_OK;
}

MutableOption kit_List_fromDoublyList(void) {
    struct kit_List *self;
    MutableOption selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (MutableOption_isSome(selfOption)) {
        self = MutableOption_unwrap(selfOption);
        superOption = kit_DoublyList_new();
        if (MutableOption_isSome(superOption)) {
            self->trait = KIT_LIST_TRAIT_DOUBLY_LIST;
            self->super = MutableOption_unwrap(superOption);
            self->fnClear = (kit_List_Super_clearFn) kit_DoublyList_clear;
            self->fnDelete = (kit_List_Super_deleteFn) kit_DoublyList_delete;
            self->fnInsert = (kit_List_Super_insertFn) kit_DoublyList_insert;
            self->fnPushBack = (kit_List_Super_pushBackFn) kit_DoublyList_pushBack;
            self->fnPushFront = (kit_List_Super_pushFrontFn) kit_DoublyList_pushFront;
            self->fnPopBack = (kit_List_Super_popBackFn) kit_DoublyList_popBack;
            self->fnPopFront = (kit_List_Super_popFrontFn) kit_DoublyList_popFront;
            self->fnRemove = (kit_List_Super_removeFn) kit_DoublyList_remove;
            self->fnSet = (kit_List_Super_setFn) kit_DoublyList_set;
            self->fnGet = (kit_List_Super_getFn) kit_DoublyList_get;
            self->fnBack = (kit_List_Super_backFn) kit_DoublyList_back;
            self->fnFront = (kit_List_Super_frontFn) kit_DoublyList_front;
            self->fnSize = (kit_List_Super_sizeFn) kit_DoublyList_size;
            self->fnIsEmpty = (kit_List_Super_isEmptyFn) kit_DoublyList_isEmpty;
            /* fake methods - no ops */
            self->fnCapacity = (kit_List_Super_capacityFn) kit_DoublyList_size;
            self->fnReserve = (kit_List_Super_reserveFn) kit_List_Super_reserveNoOp;
            self->fnShrink = (kit_List_Super_shrinkFn) kit_List_Super_shrinkNoOp;
        } else {
            kit_Allocator_free(self);
        }
    }

    return selfOption;
}

MutableOption kit_List_fromXorList(void) {
    struct kit_List *self;
    MutableOption selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (MutableOption_isSome(selfOption)) {
        self = MutableOption_unwrap(selfOption);
        superOption = kit_XorList_new();
        if (MutableOption_isSome(superOption)) {
            self->trait = KIT_LIST_TRAIT_XOR_LIST;
            self->super = MutableOption_unwrap(superOption);
            self->fnClear = (kit_List_Super_clearFn) kit_XorList_clear;
            self->fnDelete = (kit_List_Super_deleteFn) kit_XorList_delete;
            self->fnInsert = (kit_List_Super_insertFn) kit_XorList_insert;
            self->fnPushBack = (kit_List_Super_pushBackFn) kit_XorList_pushBack;
            self->fnPushFront = (kit_List_Super_pushFrontFn) kit_XorList_pushFront;
            self->fnPopBack = (kit_List_Super_popBackFn) kit_XorList_popBack;
            self->fnPopFront = (kit_List_Super_popFrontFn) kit_XorList_popFront;
            self->fnRemove = (kit_List_Super_removeFn) kit_XorList_remove;
            self->fnSet = (kit_List_Super_setFn) kit_XorList_set;
            self->fnGet = (kit_List_Super_getFn) kit_XorList_get;
            self->fnBack = (kit_List_Super_backFn) kit_XorList_back;
            self->fnFront = (kit_List_Super_frontFn) kit_XorList_front;
            self->fnSize = (kit_List_Super_sizeFn) kit_XorList_size;
            self->fnIsEmpty = (kit_List_Super_isEmptyFn) kit_XorList_isEmpty;
            /* fake methods - no ops */
            self->fnCapacity = (kit_List_Super_capacityFn) kit_XorList_size;
            self->fnReserve = (kit_List_Super_reserveFn) kit_List_Super_reserveNoOp;
            self->fnShrink = (kit_List_Super_shrinkFn) kit_List_Super_shrinkNoOp;
        } else {
            kit_Allocator_free(self);
        }
    }

    return selfOption;
}

MutableOption kit_List_fromVector(size_t capacityHint) {
    struct kit_List *self;
    MutableOption selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (MutableOption_isSome(selfOption)) {
        self = MutableOption_unwrap(selfOption);
        superOption = kit_Vector_from(capacityHint);
        if (MutableOption_isSome(superOption)) {
            self->trait = KIT_LIST_TRAIT_VECTOR;
            self->super = MutableOption_unwrap(superOption);
            self->fnClear = (kit_List_Super_clearFn) kit_Vector_clear;
            self->fnDelete = (kit_List_Super_deleteFn) kit_Vector_delete;
            self->fnInsert = (kit_List_Super_insertFn) kit_Vector_insert;
            self->fnPushBack = (kit_List_Super_pushBackFn) kit_Vector_pushBack;
            self->fnPushFront = (kit_List_Super_pushFrontFn) kit_Vector_pushFront;
            self->fnPopBack = (kit_List_Super_popBackFn) kit_Vector_popBack;
            self->fnPopFront = (kit_List_Super_popFrontFn) kit_Vector_popFront;
            self->fnRemove = (kit_List_Super_removeFn) kit_Vector_remove;
            self->fnSet = (kit_List_Super_setFn) kit_Vector_set;
            self->fnGet = (kit_List_Super_getFn) kit_Vector_get;
            self->fnBack = (kit_List_Super_backFn) kit_Vector_back;
            self->fnFront = (kit_List_Super_frontFn) kit_Vector_front;
            self->fnSize = (kit_List_Super_sizeFn) kit_Vector_size;
            self->fnIsEmpty = (kit_List_Super_isEmptyFn) kit_Vector_isEmpty;
            self->fnCapacity = (kit_List_Super_capacityFn) kit_Vector_capacity;
            self->fnReserve = (kit_List_Super_reserveFn) kit_Vector_reserve;
            self->fnShrink = (kit_List_Super_shrinkFn) kit_Vector_shrink;
        } else {
            kit_Allocator_free(self);
        }
    }

    return selfOption;
}

void kit_List_clear(struct kit_List *self) {
    assert(self);
    self->fnClear(self->super);
}

void kit_List_delete(struct kit_List *self) {
    if (self) {
        self->fnDelete(self->super);
        kit_Allocator_free(self);
    }
}

enum kit_Result kit_List_insert(struct kit_List *self, void *e, size_t index) {
    assert(self);
    return self->fnInsert(self->super, e, index);
}

enum kit_Result kit_List_pushBack(struct kit_List *self, void *e) {
    assert(self);
    return self->fnPushBack(self->super, e);
}

enum kit_Result kit_List_pushFront(struct kit_List *self, void *e) {
    assert(self);
    return self->fnPushFront(self->super, e);
}

enum kit_Result kit_List_popBack(struct kit_List *self, void **out) {
    assert(self);
    assert(out);
    return self->fnPopBack(self->super, out);
}

enum kit_Result kit_List_popFront(struct kit_List *self, void **out) {
    assert(self);
    assert(out);
    return self->fnPopFront(self->super, out);
}

enum kit_Result kit_List_remove(struct kit_List *self, void **out, size_t index) {
    assert(self);
    assert(out);
    return self->fnRemove(self->super, out, index);
}

enum kit_Result kit_List_set(struct kit_List *self, void *e, size_t index) {
    assert(self);
    return self->fnSet(self->super, e, index);
}

enum kit_Result kit_List_get(struct kit_List *self, void **out, size_t index) {
    assert(self);
    assert(out);
    return self->fnGet(self->super, out, index);
}

enum kit_Result kit_List_back(struct kit_List *self, void **out) {
    assert(self);
    assert(out);
    return self->fnBack(self->super, out);
}

enum kit_Result kit_List_front(struct kit_List *self, void **out) {
    assert(self);
    assert(out);
    return self->fnFront(self->super, out);
}

size_t kit_List_size(struct kit_List *self) {
    assert(self);
    return self->fnSize(self->super);
}

bool kit_List_isEmpty(struct kit_List *self) {
    assert(self);
    return self->fnIsEmpty(self->super);
}

size_t kit_List_capacity(struct kit_List *self) {
    assert(self);
    return self->fnCapacity(self->super);
}

enum kit_Result kit_List_reserve(struct kit_List *self, size_t size) {
    assert(self);
    return self->fnReserve(self->super, size);
}

enum kit_Result kit_List_shrink(struct kit_List *self) {
    assert(self);
    return self->fnShrink(self->super);
}

/*
 * kit_List_Iterator
 */
typedef void *kit_List_Iterator_Super;

typedef void (*kit_List_Iterator_Super_deleteFn)(kit_List_Iterator_Super);
typedef void (*kit_List_Iterator_Super_rewindFn)(kit_List_Iterator_Super, enum kit_Bound);
typedef void (*kit_List_Iterator_Super_rewindToBeginFn)(kit_List_Iterator_Super);
typedef void (*kit_List_Iterator_Super_rewindToEndFn)(kit_List_Iterator_Super);
typedef enum kit_Result (*kit_List_Iterator_Super_nextFn)(kit_List_Iterator_Super, void **);
typedef enum kit_Result (*kit_List_Iterator_Super_previousFn)(kit_List_Iterator_Super, void **);
typedef enum kit_Result (*kit_List_Iterator_Super_setLastFn)(kit_List_Iterator_Super, void *);
typedef bool (*kit_List_Iterator_Super_isModifiedFn)(kit_List_Iterator_Super);

struct kit_List_Iterator {
    kit_List_Iterator_Super super;
    kit_List_Iterator_Super_deleteFn fnDelete;
    kit_List_Iterator_Super_rewindFn fnRewind;
    kit_List_Iterator_Super_rewindToBeginFn fnRewindToBegin;
    kit_List_Iterator_Super_rewindToEndFn fnRewindToEnd;
    kit_List_Iterator_Super_nextFn fnNext;
    kit_List_Iterator_Super_previousFn fnPrevious;
    kit_List_Iterator_Super_setLastFn fnSetLast;
    kit_List_Iterator_Super_isModifiedFn fnIsModified;
};

static MutableOption kit_List_Iterator_fromDoublyList(struct kit_DoublyList *container, enum kit_Bound bound) {
    assert(container);
    struct kit_List_Iterator *self;
    MutableOption selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (MutableOption_isSome(selfOption)) {
        self = MutableOption_unwrap(selfOption);
        superOption = kit_DoublyList_Iterator_new(container, bound);
        if (MutableOption_isSome(superOption)) {
            self->super = MutableOption_unwrap(superOption);
            self->fnDelete = (kit_List_Iterator_Super_deleteFn) kit_DoublyList_Iterator_delete;
            self->fnRewind = (kit_List_Iterator_Super_rewindFn) kit_DoublyList_Iterator_rewind;
            self->fnRewindToBegin = (kit_List_Iterator_Super_rewindToBeginFn) kit_DoublyList_Iterator_rewindToBegin;
            self->fnRewindToEnd = (kit_List_Iterator_Super_rewindToEndFn) kit_DoublyList_Iterator_rewindToEnd;
            self->fnNext = (kit_List_Iterator_Super_nextFn) kit_DoublyList_Iterator_next;
            self->fnPrevious = (kit_List_Iterator_Super_previousFn) kit_DoublyList_Iterator_previous;
            self->fnSetLast = (kit_List_Iterator_Super_setLastFn) kit_DoublyList_Iterator_setLast;
            self->fnIsModified = (kit_List_Iterator_Super_isModifiedFn) kit_DoublyList_Iterator_isModified;
        } else {
            kit_Allocator_free(self);
        }
    }

    return selfOption;
}

static MutableOption kit_List_Iterator_fromXorList(struct kit_XorList *container, enum kit_Bound bound) {
    assert(container);
    struct kit_List_Iterator *self;
    MutableOption selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (MutableOption_isSome(selfOption)) {
        self = MutableOption_unwrap(selfOption);
        superOption = kit_XorList_Iterator_new(container, bound);
        if (MutableOption_isSome(superOption)) {
            self->super = MutableOption_unwrap(superOption);
            self->fnDelete = (kit_List_Iterator_Super_deleteFn) kit_XorList_Iterator_delete;
            self->fnRewind = (kit_List_Iterator_Super_rewindFn) kit_XorList_Iterator_rewind;
            self->fnRewindToBegin = (kit_List_Iterator_Super_rewindToBeginFn) kit_XorList_Iterator_rewindToBegin;
            self->fnRewindToEnd = (kit_List_Iterator_Super_rewindToEndFn) kit_XorList_Iterator_rewindToEnd;
            self->fnNext = (kit_List_Iterator_Super_nextFn) kit_XorList_Iterator_next;
            self->fnPrevious = (kit_List_Iterator_Super_previousFn) kit_XorList_Iterator_previous;
            self->fnSetLast = (kit_List_Iterator_Super_setLastFn) kit_XorList_Iterator_setLast;
            self->fnIsModified = (kit_List_Iterator_Super_isModifiedFn) kit_XorList_Iterator_isModified;
        } else {
            kit_Allocator_free(self);
        }
    }

    return selfOption;
}

static MutableOption kit_List_Iterator_fromVector(struct kit_Vector *container, enum kit_Bound bound) {
    assert(container);
    struct kit_List_Iterator *self;
    MutableOption selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (MutableOption_isSome(selfOption)) {
        self = MutableOption_unwrap(selfOption);
        superOption = kit_Vector_Iterator_new(container, bound);
        if (MutableOption_isSome(superOption)) {
            self->super = MutableOption_unwrap(superOption);
            self->fnDelete = (kit_List_Iterator_Super_deleteFn) kit_Vector_Iterator_delete;
            self->fnRewind = (kit_List_Iterator_Super_rewindFn) kit_Vector_Iterator_rewind;
            self->fnRewindToBegin = (kit_List_Iterator_Super_rewindToBeginFn) kit_Vector_Iterator_rewindToBegin;
            self->fnRewindToEnd = (kit_List_Iterator_Super_rewindToEndFn) kit_Vector_Iterator_rewindToEnd;
            self->fnNext = (kit_List_Iterator_Super_nextFn) kit_Vector_Iterator_next;
            self->fnPrevious = (kit_List_Iterator_Super_previousFn) kit_Vector_Iterator_previous;
            self->fnSetLast = (kit_List_Iterator_Super_setLastFn) kit_Vector_Iterator_setLast;
            self->fnIsModified = (kit_List_Iterator_Super_isModifiedFn) kit_Vector_Iterator_isModified;
        } else {
            kit_Allocator_free(self);
        }
    }

    return selfOption;
}

MutableOption kit_List_Iterator_new(struct kit_List *container, enum kit_Bound bound) {
    assert(container);
    switch (container->trait) {
        case KIT_LIST_TRAIT_DOUBLY_LIST: {
            return kit_List_Iterator_fromDoublyList(container->super, bound);
        }
        case KIT_LIST_TRAIT_XOR_LIST: {
            return kit_List_Iterator_fromXorList(container->super, bound);
        }
        case KIT_LIST_TRAIT_VECTOR: {
            return kit_List_Iterator_fromVector(container->super, bound);
        }
        default: {
            assert(false);
            abort();
        }
    }
}

MutableOption kit_List_Iterator_fromBegin(struct kit_List *container) {
    assert(container);
    return kit_List_Iterator_new(container, KIT_BOUND_BEGIN);
}

MutableOption kit_List_Iterator_fromEnd(struct kit_List *container) {
    assert(container);
    return kit_List_Iterator_new(container, KIT_BOUND_END);
}

void kit_List_Iterator_rewind(struct kit_List_Iterator *self, enum kit_Bound bound) {
    assert(self);
    self->fnRewind(self->super, bound);
}

void kit_List_Iterator_rewindToBegin(struct kit_List_Iterator *self) {
    assert(self);
    self->fnRewindToBegin(self->super);
}

void kit_List_Iterator_rewindToEnd(struct kit_List_Iterator *self) {
    assert(self);
    self->fnRewindToEnd(self->super);
}

void kit_List_Iterator_delete(struct kit_List_Iterator *self) {
    if (self) {
        self->fnDelete(self->super);
        kit_Allocator_free(self);
    }
}

enum kit_Result kit_List_Iterator_next(struct kit_List_Iterator *self, void **out) {
    assert(self);
    assert(out);
    return self->fnNext(self->super, out);
}

enum kit_Result kit_List_Iterator_previous(struct kit_List_Iterator *self, void **out) {
    assert(self);
    assert(out);
    return self->fnPrevious(self->super, out);
}

enum kit_Result kit_List_Iterator_setLast(struct kit_List_Iterator *self, void *e) {
    assert(self);
    return self->fnSetLast(self->super, e);
}

bool kit_List_Iterator_isModified(struct kit_List_Iterator *self) {
    assert(self);
    return self->fnIsModified(self->super);
}
