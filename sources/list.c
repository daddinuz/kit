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
typedef void *kit_List_Super;

enum kit_List_Super_Trait {
    KIT_LIST_SUPER_TRAIT_DOUBLY_LIST,
    KIT_LIST_SUPER_TRAIT_XOR_LIST,
    KIT_LIST_SUPER_TRAIT_VECTOR,
};

typedef void (*kit_List_Super_Trait_fnClear)(kit_List_Super);
typedef void (*kit_List_Super_Trait_fnDelete)(kit_List_Super);
typedef enum kit_Result (*kit_List_Super_Trait_fnInsert)(kit_List_Super, void *, size_t);
typedef enum kit_Result (*kit_List_Super_Trait_fnPushBack)(kit_List_Super, void *);
typedef enum kit_Result (*kit_List_Super_Trait_fnPushFront)(kit_List_Super, void *);
typedef enum kit_Result (*kit_List_Super_Trait_fnPopBack)(kit_List_Super, void **);
typedef enum kit_Result (*kit_List_Super_Trait_fnPopFront)(kit_List_Super, void **);
typedef enum kit_Result (*kit_List_Super_Trait_fnRemove)(kit_List_Super, void **, size_t);
typedef enum kit_Result (*kit_List_Super_Trait_fnSet)(kit_List_Super, void *, size_t);
typedef enum kit_Result (*kit_List_Super_Trait_fnGet)(kit_List_Super, void **, size_t);
typedef enum kit_Result (*kit_List_Super_Trait_fnBack)(kit_List_Super, void **);
typedef enum kit_Result (*kit_List_Super_Trait_fnFront)(kit_List_Super, void **);
typedef size_t (*kit_List_Super_Trait_fnSize)(kit_List_Super);
typedef bool (*kit_List_Super_Trait_fnIsEmpty)(kit_List_Super);

struct kit_List {
    kit_List_Super super;
    enum kit_List_Super_Trait superTrait;
    kit_List_Super_Trait_fnClear mClear;
    kit_List_Super_Trait_fnDelete mDelete;
    kit_List_Super_Trait_fnInsert mInsert;
    kit_List_Super_Trait_fnPushBack mPushBack;
    kit_List_Super_Trait_fnPushFront mPushFront;
    kit_List_Super_Trait_fnPopBack mPopBack;
    kit_List_Super_Trait_fnPopFront mPopFront;
    kit_List_Super_Trait_fnRemove mRemove;
    kit_List_Super_Trait_fnSet mSet;
    kit_List_Super_Trait_fnGet mGet;
    kit_List_Super_Trait_fnBack mBack;
    kit_List_Super_Trait_fnFront mFront;
    kit_List_Super_Trait_fnSize mSize;
    kit_List_Super_Trait_fnIsEmpty mIsEmpty;
};

Optional(struct kit_List *) kit_List_fromDoublyList(void) {
    struct kit_List *self = kit_Allocator_calloc(1, sizeof(*self));

    if (self) {
        Optional(struct kit_DoublyList *) super = kit_DoublyList_new();
        if (Option_isSome(super)) {
            self->super = Option_unwrap(super);
            self->superTrait = KIT_LIST_SUPER_TRAIT_DOUBLY_LIST;
            self->mClear = (kit_List_Super_Trait_fnClear) kit_DoublyList_clear;
            self->mDelete = (kit_List_Super_Trait_fnDelete) kit_DoublyList_delete;
            self->mInsert = (kit_List_Super_Trait_fnInsert) kit_DoublyList_insert;
            self->mPushBack = (kit_List_Super_Trait_fnPushBack) kit_DoublyList_pushBack;
            self->mPushFront = (kit_List_Super_Trait_fnPushFront) kit_DoublyList_pushFront;
            self->mPopBack = (kit_List_Super_Trait_fnPopBack) kit_DoublyList_popBack;
            self->mPopFront = (kit_List_Super_Trait_fnPopFront) kit_DoublyList_popFront;
            self->mRemove = (kit_List_Super_Trait_fnRemove) kit_DoublyList_remove;
            self->mSet = (kit_List_Super_Trait_fnSet) kit_DoublyList_set;
            self->mGet = (kit_List_Super_Trait_fnGet) kit_DoublyList_get;
            self->mBack = (kit_List_Super_Trait_fnBack) kit_DoublyList_back;
            self->mFront = (kit_List_Super_Trait_fnFront) kit_DoublyList_front;
            self->mSize = (kit_List_Super_Trait_fnSize) kit_DoublyList_size;
            self->mIsEmpty = (kit_List_Super_Trait_fnIsEmpty) kit_DoublyList_isEmpty;
        } else {
            kit_Allocator_free(self);
            self = NULL;
        }
    }

    return Option_new(self);
}

Optional(struct kit_List *) kit_List_fromXorList(void) {
    struct kit_List *self = kit_Allocator_calloc(1, sizeof(*self));

    if (self) {
        Optional(struct kit_XorList *) super = kit_XorList_new();
        if (Option_isSome(super)) {
            self->super = Option_unwrap(super);
            self->superTrait = KIT_LIST_SUPER_TRAIT_XOR_LIST;
            self->mClear = (kit_List_Super_Trait_fnClear) kit_XorList_clear;
            self->mDelete = (kit_List_Super_Trait_fnDelete) kit_XorList_delete;
            self->mInsert = (kit_List_Super_Trait_fnInsert) kit_XorList_insert;
            self->mPushBack = (kit_List_Super_Trait_fnPushBack) kit_XorList_pushBack;
            self->mPushFront = (kit_List_Super_Trait_fnPushFront) kit_XorList_pushFront;
            self->mPopBack = (kit_List_Super_Trait_fnPopBack) kit_XorList_popBack;
            self->mPopFront = (kit_List_Super_Trait_fnPopFront) kit_XorList_popFront;
            self->mRemove = (kit_List_Super_Trait_fnRemove) kit_XorList_remove;
            self->mSet = (kit_List_Super_Trait_fnSet) kit_XorList_set;
            self->mGet = (kit_List_Super_Trait_fnGet) kit_XorList_get;
            self->mBack = (kit_List_Super_Trait_fnBack) kit_XorList_back;
            self->mFront = (kit_List_Super_Trait_fnFront) kit_XorList_front;
            self->mSize = (kit_List_Super_Trait_fnSize) kit_XorList_size;
            self->mIsEmpty = (kit_List_Super_Trait_fnIsEmpty) kit_XorList_isEmpty;
        } else {
            kit_Allocator_free(self);
            self = NULL;
        }
    }

    return Option_new(self);
}

Optional(struct kit_List *) kit_List_fromVector(size_t capacityHint) {
    struct kit_List *self = kit_Allocator_calloc(1, sizeof(*self));

    if (self) {
        Optional(struct kit_Vector *) super = kit_Vector_from(capacityHint);
        if (Option_isSome(super)) {
            self->super = Option_unwrap(super);
            self->superTrait = KIT_LIST_SUPER_TRAIT_VECTOR;
            self->mClear = (kit_List_Super_Trait_fnClear) kit_Vector_clear;
            self->mDelete = (kit_List_Super_Trait_fnDelete) kit_Vector_delete;
            self->mInsert = (kit_List_Super_Trait_fnInsert) kit_Vector_insert;
            self->mPushBack = (kit_List_Super_Trait_fnPushBack) kit_Vector_pushBack;
            self->mPushFront = (kit_List_Super_Trait_fnPushFront) kit_Vector_pushFront;
            self->mPopBack = (kit_List_Super_Trait_fnPopBack) kit_Vector_popBack;
            self->mPopFront = (kit_List_Super_Trait_fnPopFront) kit_Vector_popFront;
            self->mRemove = (kit_List_Super_Trait_fnRemove) kit_Vector_remove;
            self->mSet = (kit_List_Super_Trait_fnSet) kit_Vector_set;
            self->mGet = (kit_List_Super_Trait_fnGet) kit_Vector_get;
            self->mBack = (kit_List_Super_Trait_fnBack) kit_Vector_back;
            self->mFront = (kit_List_Super_Trait_fnFront) kit_Vector_front;
            self->mSize = (kit_List_Super_Trait_fnSize) kit_Vector_size;
            self->mIsEmpty = (kit_List_Super_Trait_fnIsEmpty) kit_Vector_isEmpty;
        } else {
            kit_Allocator_free(self);
            self = NULL;
        }
    }

    return Option_new(self);
}

void kit_List_clear(struct kit_List *self) {
    assert(self);
    self->mClear(self->super);
}

void kit_List_delete(struct kit_List *self) {
    if (self) {
        self->mDelete(self->super);
        kit_Allocator_free(self);
    }
}

enum kit_Result kit_List_insert(struct kit_List *self, void *e, size_t index) {
    assert(self);
    return self->mInsert(self->super, e, index);
}

enum kit_Result kit_List_pushBack(struct kit_List *self, void *e) {
    assert(self);
    return self->mPushBack(self->super, e);
}

enum kit_Result kit_List_pushFront(struct kit_List *self, void *e) {
    assert(self);
    return self->mPushFront(self->super, e);
}

enum kit_Result kit_List_popBack(struct kit_List *self, void **out) {
    assert(self);
    assert(out);
    return self->mPopBack(self->super, out);
}

enum kit_Result kit_List_popFront(struct kit_List *self, void **out) {
    assert(self);
    assert(out);
    return self->mPopFront(self->super, out);
}

enum kit_Result kit_List_remove(struct kit_List *self, void **out, size_t index) {
    assert(self);
    assert(out);
    return self->mRemove(self->super, out, index);
}

enum kit_Result kit_List_set(struct kit_List *self, void *e, size_t index) {
    assert(self);
    return self->mSet(self->super, e, index);
}

enum kit_Result kit_List_get(struct kit_List *self, void **out, size_t index) {
    assert(self);
    assert(out);
    return self->mGet(self->super, out, index);
}

enum kit_Result kit_List_back(struct kit_List *self, void **out) {
    assert(self);
    assert(out);
    return self->mBack(self->super, out);
}

enum kit_Result kit_List_front(struct kit_List *self, void **out) {
    assert(self);
    assert(out);
    return self->mFront(self->super, out);
}

size_t kit_List_size(struct kit_List *self) {
    assert(self);
    return self->mSize(self->super);
}

bool kit_List_isEmpty(struct kit_List *self) {
    assert(self);
    return self->mIsEmpty(self->super);
}

/*
 * kit_List_Iterator
 */
typedef void *kit_List_Iterator_Super;

typedef void (*kit_List_Iterator_Super_Trait_fnDelete)(kit_List_Iterator_Super);
typedef void (*kit_List_Iterator_Super_Trait_fnRewind)(kit_List_Iterator_Super, enum kit_Bound);
typedef void (*kit_List_Iterator_Super_Trait_fnRewindToBegin)(kit_List_Iterator_Super);
typedef void (*kit_List_Iterator_Super_Trait_fnRewindToEnd)(kit_List_Iterator_Super);
typedef enum kit_Result (*kit_List_Iterator_Super_Trait_fnNext)(kit_List_Iterator_Super, void **);
typedef enum kit_Result (*kit_List_Iterator_Super_Trait_fnPrevious)(kit_List_Iterator_Super, void **);
typedef enum kit_Result (*kit_List_Iterator_Super_Trait_fnSetLast)(kit_List_Iterator_Super, void *);
typedef bool (*kit_List_Iterator_Super_Trait_fnIsModified)(kit_List_Iterator_Super);

struct kit_List_Iterator {
    kit_List_Iterator_Super super;
    kit_List_Iterator_Super_Trait_fnDelete mDelete;
    kit_List_Iterator_Super_Trait_fnRewind mRewind;
    kit_List_Iterator_Super_Trait_fnRewindToBegin mRewindToBegin;
    kit_List_Iterator_Super_Trait_fnRewindToEnd mRewindToEnd;
    kit_List_Iterator_Super_Trait_fnNext mNext;
    kit_List_Iterator_Super_Trait_fnPrevious mPrevious;
    kit_List_Iterator_Super_Trait_fnSetLast mSetLast;
    kit_List_Iterator_Super_Trait_fnIsModified mIsModified;
};

static Optional(struct kit_List_Iterator *)
kit_List_Iterator_fromDoublyList(struct kit_DoublyList *container, enum kit_Bound bound) {
    assert(container);
    struct kit_List_Iterator *self = kit_Allocator_calloc(1, sizeof(*self));

    if (self) {
        Optional(struct kit_DoublyList_Iterator *) super = kit_DoublyList_Iterator_new(container, bound);
        if (Option_isSome(super)) {
            self->super = Option_unwrap(super);
            self->mDelete = (kit_List_Iterator_Super_Trait_fnDelete) kit_DoublyList_Iterator_delete;
            self->mRewind = (kit_List_Iterator_Super_Trait_fnRewind) kit_DoublyList_Iterator_rewind;
            self->mRewindToBegin = (kit_List_Iterator_Super_Trait_fnRewindToBegin) kit_DoublyList_Iterator_rewindToBegin;
            self->mRewindToEnd = (kit_List_Iterator_Super_Trait_fnRewindToEnd) kit_DoublyList_Iterator_rewindToEnd;
            self->mNext = (kit_List_Iterator_Super_Trait_fnNext) kit_DoublyList_Iterator_next;
            self->mPrevious = (kit_List_Iterator_Super_Trait_fnPrevious) kit_DoublyList_Iterator_previous;
            self->mSetLast = (kit_List_Iterator_Super_Trait_fnSetLast) kit_DoublyList_Iterator_setLast;
            self->mIsModified = (kit_List_Iterator_Super_Trait_fnIsModified) kit_DoublyList_Iterator_isModified;
        } else {
            kit_Allocator_free(self);
            self = NULL;
        }
    }

    return Option_new(self);
}

static Optional(struct kit_List_Iterator *)
kit_List_Iterator_fromXorList(struct kit_XorList *container, enum kit_Bound bound) {
    assert(container);
    struct kit_List_Iterator *self = kit_Allocator_calloc(1, sizeof(*self));

    if (self) {
        Optional(struct kit_XorList_Iterator *) super = kit_XorList_Iterator_new(container, bound);
        if (Option_isSome(super)) {
            self->super = Option_unwrap(super);
            self->mDelete = (kit_List_Iterator_Super_Trait_fnDelete) kit_XorList_Iterator_delete;
            self->mRewind = (kit_List_Iterator_Super_Trait_fnRewind) kit_XorList_Iterator_rewind;
            self->mRewindToBegin = (kit_List_Iterator_Super_Trait_fnRewindToBegin) kit_XorList_Iterator_rewindToBegin;
            self->mRewindToEnd = (kit_List_Iterator_Super_Trait_fnRewindToEnd) kit_XorList_Iterator_rewindToEnd;
            self->mNext = (kit_List_Iterator_Super_Trait_fnNext) kit_XorList_Iterator_next;
            self->mPrevious = (kit_List_Iterator_Super_Trait_fnPrevious) kit_XorList_Iterator_previous;
            self->mSetLast = (kit_List_Iterator_Super_Trait_fnSetLast) kit_XorList_Iterator_setLast;
            self->mIsModified = (kit_List_Iterator_Super_Trait_fnIsModified) kit_XorList_Iterator_isModified;
        } else {
            kit_Allocator_free(self);
            self = NULL;
        }
    }

    return Option_new(self);
}

static Optional(struct kit_List_Iterator *)
kit_List_Iterator_fromVector(struct kit_Vector *container, enum kit_Bound bound) {
    assert(container);
    struct kit_List_Iterator *self = kit_Allocator_calloc(1, sizeof(*self));

    if (self) {
        Optional(struct kit_Vector_Iterator *) super = kit_Vector_Iterator_new(container, bound);
        if (Option_isSome(super)) {
            self->super = Option_unwrap(super);
            self->mDelete = (kit_List_Iterator_Super_Trait_fnDelete) kit_Vector_Iterator_delete;
            self->mRewind = (kit_List_Iterator_Super_Trait_fnRewind) kit_Vector_Iterator_rewind;
            self->mRewindToBegin = (kit_List_Iterator_Super_Trait_fnRewindToBegin) kit_Vector_Iterator_rewindToBegin;
            self->mRewindToEnd = (kit_List_Iterator_Super_Trait_fnRewindToEnd) kit_Vector_Iterator_rewindToEnd;
            self->mNext = (kit_List_Iterator_Super_Trait_fnNext) kit_Vector_Iterator_next;
            self->mPrevious = (kit_List_Iterator_Super_Trait_fnPrevious) kit_Vector_Iterator_previous;
            self->mSetLast = (kit_List_Iterator_Super_Trait_fnSetLast) kit_Vector_Iterator_setLast;
            self->mIsModified = (kit_List_Iterator_Super_Trait_fnIsModified) kit_Vector_Iterator_isModified;
        } else {
            kit_Allocator_free(self);
            self = NULL;
        }
    }

    return Option_new(self);
}

Optional(struct kit_List_Iterator *)
kit_List_Iterator_new(struct kit_List *container, enum kit_Bound bound) {
    assert(container);
    switch (container->superTrait) {
        case KIT_LIST_SUPER_TRAIT_DOUBLY_LIST: {
            return kit_List_Iterator_fromDoublyList(container->super, bound);
        }
        case KIT_LIST_SUPER_TRAIT_XOR_LIST: {
            return kit_List_Iterator_fromXorList(container->super, bound);
        }
        case KIT_LIST_SUPER_TRAIT_VECTOR: {
            return kit_List_Iterator_fromVector(container->super, bound);
        }
        default: {
            assert(false);
            abort();
        }
    }
}

Optional(struct kit_List_Iterator *)
kit_List_Iterator_fromBegin(struct kit_List *container) {
    assert(container);
    return kit_List_Iterator_new(container, KIT_BOUND_BEGIN);
}

Optional(struct kit_List_Iterator *)
kit_List_Iterator_fromEnd(struct kit_List *container) {
    assert(container);
    return kit_List_Iterator_new(container, KIT_BOUND_END);
}

void kit_List_Iterator_rewind(struct kit_List_Iterator *self, enum kit_Bound bound) {
    assert(self);
    self->mRewind(self->super, bound);
}

void kit_List_Iterator_rewindToBegin(struct kit_List_Iterator *self) {
    assert(self);
    self->mRewindToBegin(self->super);
}

void kit_List_Iterator_rewindToEnd(struct kit_List_Iterator *self) {
    assert(self);
    self->mRewindToEnd(self->super);
}

void kit_List_Iterator_delete(struct kit_List_Iterator *self) {
    if (self) {
        self->mDelete(self->super);
        kit_Allocator_free(self);
    }
}

enum kit_Result kit_List_Iterator_next(struct kit_List_Iterator *self, void **out) {
    assert(self);
    assert(out);
    return self->mNext(self->super, out);
}

enum kit_Result kit_List_Iterator_previous(struct kit_List_Iterator *self, void **out) {
    assert(self);
    assert(out);
    return self->mPrevious(self->super, out);
}

enum kit_Result kit_List_Iterator_setLast(struct kit_List_Iterator *self, void *e) {
    assert(self);
    return self->mSetLast(self->super, e);
}

bool kit_List_Iterator_isModified(struct kit_List_Iterator *self) {
    assert(self);
    return self->mIsModified(self->super);
}
