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
typedef void *kit_Sequence_Super;

enum kit_Sequence_Super_Trait {
    KIT_SEQUENCE_SUPER_TRAIT_DOUBLY_LIST,
    KIT_SEQUENCE_SUPER_TRAIT_SINGLY_LIST,
    KIT_SEQUENCE_SUPER_TRAIT_XOR_LIST,
    KIT_SEQUENCE_SUPER_TRAIT_VECTOR,
};

typedef void (*kit_Sequence_Super_Trait_fnClear)(kit_Sequence_Super);
typedef void (*kit_Sequence_Super_Trait_fnDelete)(kit_Sequence_Super);
typedef enum kit_Result (*kit_Sequence_Super_Trait_fnInsert)(kit_Sequence_Super, void *, size_t);
typedef enum kit_Result (*kit_Sequence_Super_Trait_fnPushBack)(kit_Sequence_Super, void *);
typedef enum kit_Result (*kit_Sequence_Super_Trait_fnPushFront)(kit_Sequence_Super, void *);
typedef enum kit_Result (*kit_Sequence_Super_Trait_fnPopBack)(kit_Sequence_Super, void **);
typedef enum kit_Result (*kit_Sequence_Super_Trait_fnPopFront)(kit_Sequence_Super, void **);
typedef enum kit_Result (*kit_Sequence_Super_Trait_fnRemove)(kit_Sequence_Super, void **, size_t);
typedef enum kit_Result (*kit_Sequence_Super_Trait_fnSet)(kit_Sequence_Super, void *, size_t);
typedef enum kit_Result (*kit_Sequence_Super_Trait_fnGet)(kit_Sequence_Super, void **, size_t);
typedef enum kit_Result (*kit_Sequence_Super_Trait_fnBack)(kit_Sequence_Super, void **);
typedef enum kit_Result (*kit_Sequence_Super_Trait_fnFront)(kit_Sequence_Super, void **);
typedef size_t (*kit_Sequence_Super_Trait_fnSize)(kit_Sequence_Super);
typedef bool (*kit_Sequence_Super_Trait_fnIsEmpty)(kit_Sequence_Super);
typedef size_t (*kit_Sequence_Super_Trait_fnCapacity)(kit_Sequence_Super);
typedef enum kit_Result (*kit_Sequence_Super_Trait_fnReserve)(kit_Sequence_Super, size_t);
typedef enum kit_Result (*kit_Sequence_Super_Trait_fnShrink)(kit_Sequence_Super);

static enum kit_Result kit_Sequence_Super_Trait_reserveNoOp(kit_Sequence_Super p0, size_t p1) {
    (void) p0;
    (void) p1;
    return KIT_RESULT_OK;
}

static enum kit_Result kit_Sequence_Super_Trait_shrinkNoOp(kit_Sequence_Super p0) {
    (void) p0;
    return KIT_RESULT_OK;
}

struct kit_Sequence {
    kit_Sequence_Super super;
    enum kit_Sequence_Super_Trait superTrait;
    kit_Sequence_Super_Trait_fnClear mClear;
    kit_Sequence_Super_Trait_fnDelete mDelete;
    kit_Sequence_Super_Trait_fnInsert mInsert;
    kit_Sequence_Super_Trait_fnPushBack mPushBack;
    kit_Sequence_Super_Trait_fnPushFront mPushFront;
    kit_Sequence_Super_Trait_fnPopBack mPopBack;
    kit_Sequence_Super_Trait_fnPopFront mPopFront;
    kit_Sequence_Super_Trait_fnRemove mRemove;
    kit_Sequence_Super_Trait_fnSet mSet;
    kit_Sequence_Super_Trait_fnGet mGet;
    kit_Sequence_Super_Trait_fnBack mBack;
    kit_Sequence_Super_Trait_fnFront mFront;
    kit_Sequence_Super_Trait_fnSize mSize;
    kit_Sequence_Super_Trait_fnIsEmpty mIsEmpty;
    kit_Sequence_Super_Trait_fnCapacity mCapacity;
    kit_Sequence_Super_Trait_fnReserve mReserve;
    kit_Sequence_Super_Trait_fnShrink mShrink;
};

Optional(struct kit_Sequence *) kit_Sequence_fromDoublyList(void) {
    struct kit_Sequence *self = kit_Allocator_calloc(1, sizeof(*self));

    if (self) {
        Optional(struct kit_DoublyList *) super = kit_DoublyList_new();
        if (Option_isSome(super)) {
            self->super = Option_unwrap(super);
            self->superTrait = KIT_SEQUENCE_SUPER_TRAIT_DOUBLY_LIST;
            self->mClear = (kit_Sequence_Super_Trait_fnClear) kit_DoublyList_clear;
            self->mDelete = (kit_Sequence_Super_Trait_fnDelete) kit_DoublyList_delete;
            self->mInsert = (kit_Sequence_Super_Trait_fnInsert) kit_DoublyList_insert;
            self->mPushBack = (kit_Sequence_Super_Trait_fnPushBack) kit_DoublyList_pushBack;
            self->mPushFront = (kit_Sequence_Super_Trait_fnPushFront) kit_DoublyList_pushFront;
            self->mPopBack = (kit_Sequence_Super_Trait_fnPopBack) kit_DoublyList_popBack;
            self->mPopFront = (kit_Sequence_Super_Trait_fnPopFront) kit_DoublyList_popFront;
            self->mRemove = (kit_Sequence_Super_Trait_fnRemove) kit_DoublyList_remove;
            self->mSet = (kit_Sequence_Super_Trait_fnSet) kit_DoublyList_set;
            self->mGet = (kit_Sequence_Super_Trait_fnGet) kit_DoublyList_get;
            self->mBack = (kit_Sequence_Super_Trait_fnBack) kit_DoublyList_back;
            self->mFront = (kit_Sequence_Super_Trait_fnFront) kit_DoublyList_front;
            self->mSize = (kit_Sequence_Super_Trait_fnSize) kit_DoublyList_size;
            self->mIsEmpty = (kit_Sequence_Super_Trait_fnIsEmpty) kit_DoublyList_isEmpty;
            /* fake methods - no ops */
            self->mCapacity = (kit_Sequence_Super_Trait_fnCapacity) kit_DoublyList_size;
            self->mReserve = (kit_Sequence_Super_Trait_fnReserve) kit_Sequence_Super_Trait_reserveNoOp;
            self->mShrink = (kit_Sequence_Super_Trait_fnShrink) kit_Sequence_Super_Trait_shrinkNoOp;
        } else {
            kit_Allocator_free(self);
            self = NULL;
        }
    }

    return Option_new(self);
}

Optional(struct kit_Sequence *) kit_Sequence_fromSinglyList(void) {
    struct kit_Sequence *self = kit_Allocator_calloc(1, sizeof(*self));

    if (self) {
        Optional(struct kit_SinglyList *) super = kit_SinglyList_new();
        if (Option_isSome(super)) {
            self->super = Option_unwrap(super);
            self->superTrait = KIT_SEQUENCE_SUPER_TRAIT_SINGLY_LIST;
            self->mClear = (kit_Sequence_Super_Trait_fnClear) kit_SinglyList_clear;
            self->mDelete = (kit_Sequence_Super_Trait_fnDelete) kit_SinglyList_delete;
            self->mInsert = (kit_Sequence_Super_Trait_fnInsert) kit_SinglyList_insert;
            self->mPushBack = (kit_Sequence_Super_Trait_fnPushBack) kit_SinglyList_pushBack;
            self->mPushFront = (kit_Sequence_Super_Trait_fnPushFront) kit_SinglyList_pushFront;
            self->mPopBack = (kit_Sequence_Super_Trait_fnPopBack) kit_SinglyList_popBack;
            self->mPopFront = (kit_Sequence_Super_Trait_fnPopFront) kit_SinglyList_popFront;
            self->mRemove = (kit_Sequence_Super_Trait_fnRemove) kit_SinglyList_remove;
            self->mSet = (kit_Sequence_Super_Trait_fnSet) kit_SinglyList_set;
            self->mGet = (kit_Sequence_Super_Trait_fnGet) kit_SinglyList_get;
            self->mBack = (kit_Sequence_Super_Trait_fnBack) kit_SinglyList_back;
            self->mFront = (kit_Sequence_Super_Trait_fnFront) kit_SinglyList_front;
            self->mSize = (kit_Sequence_Super_Trait_fnSize) kit_SinglyList_size;
            self->mIsEmpty = (kit_Sequence_Super_Trait_fnIsEmpty) kit_SinglyList_isEmpty;
            /* fake methods - no ops */
            self->mCapacity = (kit_Sequence_Super_Trait_fnCapacity) kit_SinglyList_size;
            self->mReserve = (kit_Sequence_Super_Trait_fnReserve) kit_Sequence_Super_Trait_reserveNoOp;
            self->mShrink = (kit_Sequence_Super_Trait_fnShrink) kit_Sequence_Super_Trait_shrinkNoOp;
        } else {
            kit_Allocator_free(self);
            self = NULL;
        }
    }

    return Option_new(self);
}

Optional(struct kit_Sequence *) kit_Sequence_fromXorList(void) {
    struct kit_Sequence *self = kit_Allocator_calloc(1, sizeof(*self));

    if (self) {
        Optional(struct kit_XorList *) super = kit_XorList_new();
        if (Option_isSome(super)) {
            self->super = Option_unwrap(super);
            self->superTrait = KIT_SEQUENCE_SUPER_TRAIT_XOR_LIST;
            self->mClear = (kit_Sequence_Super_Trait_fnClear) kit_XorList_clear;
            self->mDelete = (kit_Sequence_Super_Trait_fnDelete) kit_XorList_delete;
            self->mInsert = (kit_Sequence_Super_Trait_fnInsert) kit_XorList_insert;
            self->mPushBack = (kit_Sequence_Super_Trait_fnPushBack) kit_XorList_pushBack;
            self->mPushFront = (kit_Sequence_Super_Trait_fnPushFront) kit_XorList_pushFront;
            self->mPopBack = (kit_Sequence_Super_Trait_fnPopBack) kit_XorList_popBack;
            self->mPopFront = (kit_Sequence_Super_Trait_fnPopFront) kit_XorList_popFront;
            self->mRemove = (kit_Sequence_Super_Trait_fnRemove) kit_XorList_remove;
            self->mSet = (kit_Sequence_Super_Trait_fnSet) kit_XorList_set;
            self->mGet = (kit_Sequence_Super_Trait_fnGet) kit_XorList_get;
            self->mBack = (kit_Sequence_Super_Trait_fnBack) kit_XorList_back;
            self->mFront = (kit_Sequence_Super_Trait_fnFront) kit_XorList_front;
            self->mSize = (kit_Sequence_Super_Trait_fnSize) kit_XorList_size;
            self->mIsEmpty = (kit_Sequence_Super_Trait_fnIsEmpty) kit_XorList_isEmpty;
            /* fake methods - no ops */
            self->mCapacity = (kit_Sequence_Super_Trait_fnCapacity) kit_XorList_size;
            self->mReserve = (kit_Sequence_Super_Trait_fnReserve) kit_Sequence_Super_Trait_reserveNoOp;
            self->mShrink = (kit_Sequence_Super_Trait_fnShrink) kit_Sequence_Super_Trait_shrinkNoOp;
        } else {
            kit_Allocator_free(self);
            self = NULL;
        }
    }

    return Option_new(self);
}

Optional(struct kit_Sequence *) kit_Sequence_fromVector(size_t capacityHint) {
    struct kit_Sequence *self = kit_Allocator_calloc(1, sizeof(*self));

    if (self) {
        Optional(struct kit_Vector *) super = kit_Vector_from(capacityHint);
        if (Option_isSome(super)) {
            self->super = Option_unwrap(super);
            self->superTrait = KIT_SEQUENCE_SUPER_TRAIT_VECTOR;
            self->mClear = (kit_Sequence_Super_Trait_fnClear) kit_Vector_clear;
            self->mDelete = (kit_Sequence_Super_Trait_fnDelete) kit_Vector_delete;
            self->mInsert = (kit_Sequence_Super_Trait_fnInsert) kit_Vector_insert;
            self->mPushBack = (kit_Sequence_Super_Trait_fnPushBack) kit_Vector_pushBack;
            self->mPushFront = (kit_Sequence_Super_Trait_fnPushFront) kit_Vector_pushFront;
            self->mPopBack = (kit_Sequence_Super_Trait_fnPopBack) kit_Vector_popBack;
            self->mPopFront = (kit_Sequence_Super_Trait_fnPopFront) kit_Vector_popFront;
            self->mRemove = (kit_Sequence_Super_Trait_fnRemove) kit_Vector_remove;
            self->mSet = (kit_Sequence_Super_Trait_fnSet) kit_Vector_set;
            self->mGet = (kit_Sequence_Super_Trait_fnGet) kit_Vector_get;
            self->mBack = (kit_Sequence_Super_Trait_fnBack) kit_Vector_back;
            self->mFront = (kit_Sequence_Super_Trait_fnFront) kit_Vector_front;
            self->mSize = (kit_Sequence_Super_Trait_fnSize) kit_Vector_size;
            self->mIsEmpty = (kit_Sequence_Super_Trait_fnIsEmpty) kit_Vector_isEmpty;
            self->mCapacity = (kit_Sequence_Super_Trait_fnCapacity) kit_Vector_capacity;
            self->mReserve = (kit_Sequence_Super_Trait_fnReserve) kit_Vector_reserve;
            self->mShrink = (kit_Sequence_Super_Trait_fnShrink) kit_Vector_shrink;
        } else {
            kit_Allocator_free(self);
            self = NULL;
        }
    }

    return Option_new(self);
}

void kit_Sequence_clear(struct kit_Sequence *self) {
    assert(self);
    self->mClear(self->super);
}

void kit_Sequence_delete(struct kit_Sequence *self) {
    if (self) {
        self->mDelete(self->super);
        kit_Allocator_free(self);
    }
}

enum kit_Result kit_Sequence_insert(struct kit_Sequence *self, void *e, size_t index) {
    assert(self);
    return self->mInsert(self->super, e, index);
}

enum kit_Result kit_Sequence_pushBack(struct kit_Sequence *self, void *e) {
    assert(self);
    return self->mPushBack(self->super, e);
}

enum kit_Result kit_Sequence_pushFront(struct kit_Sequence *self, void *e) {
    assert(self);
    return self->mPushFront(self->super, e);
}

enum kit_Result kit_Sequence_popBack(struct kit_Sequence *self, void **out) {
    assert(self);
    assert(out);
    return self->mPopBack(self->super, out);
}

enum kit_Result kit_Sequence_popFront(struct kit_Sequence *self, void **out) {
    assert(self);
    assert(out);
    return self->mPopFront(self->super, out);
}

enum kit_Result kit_Sequence_remove(struct kit_Sequence *self, void **out, size_t index) {
    assert(self);
    assert(out);
    return self->mRemove(self->super, out, index);
}

enum kit_Result kit_Sequence_set(struct kit_Sequence *self, void *e, size_t index) {
    assert(self);
    return self->mSet(self->super, e, index);
}

enum kit_Result kit_Sequence_get(struct kit_Sequence *self, void **out, size_t index) {
    assert(self);
    assert(out);
    return self->mGet(self->super, out, index);
}

enum kit_Result kit_Sequence_back(struct kit_Sequence *self, void **out) {
    assert(self);
    assert(out);
    return self->mBack(self->super, out);
}

enum kit_Result kit_Sequence_front(struct kit_Sequence *self, void **out) {
    assert(self);
    assert(out);
    return self->mFront(self->super, out);
}

size_t kit_Sequence_size(struct kit_Sequence *self) {
    assert(self);
    return self->mSize(self->super);
}

bool kit_Sequence_isEmpty(struct kit_Sequence *self) {
    assert(self);
    return self->mIsEmpty(self->super);
}

size_t kit_Sequence_capacity(struct kit_Sequence *self) {
    assert(self);
    return self->mCapacity(self->super);
}

enum kit_Result kit_Sequence_reserve(struct kit_Sequence *self, size_t size) {
    assert(self);
    return self->mReserve(self->super, size);
}

enum kit_Result kit_Sequence_shrink(struct kit_Sequence *self) {
    assert(self);
    return self->mShrink(self->super);
}

/*
 * kit_Sequence_Iterator
 */
typedef void *kit_Sequence_Iterator_Super;

typedef void (*kit_Sequence_Iterator_Super_Trait_fnDelete)(kit_Sequence_Iterator_Super);
typedef void (*kit_Sequence_Iterator_Super_Trait_fnRewind)(kit_Sequence_Iterator_Super);
typedef enum kit_Result (*kit_Sequence_Iterator_Super_Trait_fnNext)(kit_Sequence_Iterator_Super, void **);
typedef enum kit_Result (*kit_Sequence_Iterator_Super_Trait_fnSetLast)(kit_Sequence_Iterator_Super, void *);
typedef bool (*kit_Sequence_Iterator_Super_Trait_fnIsModified)(kit_Sequence_Iterator_Super);

struct kit_Sequence_Iterator {
    kit_Sequence_Iterator_Super super;
    kit_Sequence_Iterator_Super_Trait_fnDelete mDelete;
    kit_Sequence_Iterator_Super_Trait_fnRewind mRewind;
    kit_Sequence_Iterator_Super_Trait_fnNext mNext;
    kit_Sequence_Iterator_Super_Trait_fnSetLast mSetLast;
    kit_Sequence_Iterator_Super_Trait_fnIsModified mIsModified;
};

static Optional(struct kit_Sequence_Iterator *) kit_Sequence_Iterator_fromDoublyList(struct kit_DoublyList *container) {
    assert(container);
    struct kit_Sequence_Iterator *self = kit_Allocator_calloc(1, sizeof(*self));

    if (self) {
        Optional(struct kit_DoublyList_Iterator *) super = kit_DoublyList_Iterator_fromBegin(container);
        if (Option_isSome(super)) {
            self->super = Option_unwrap(super);
            self->mDelete = (kit_Sequence_Iterator_Super_Trait_fnDelete) kit_DoublyList_Iterator_delete;
            self->mRewind = (kit_Sequence_Iterator_Super_Trait_fnRewind) kit_DoublyList_Iterator_rewindToBegin;
            self->mNext = (kit_Sequence_Iterator_Super_Trait_fnNext) kit_DoublyList_Iterator_next;
            self->mSetLast = (kit_Sequence_Iterator_Super_Trait_fnSetLast) kit_DoublyList_Iterator_setLast;
            self->mIsModified = (kit_Sequence_Iterator_Super_Trait_fnIsModified) kit_DoublyList_Iterator_isModified;
        } else {
            kit_Allocator_free(self);
            self = NULL;
        }
    }

    return Option_new(self);
}

static Optional(struct kit_Sequence_Iterator *) kit_Sequence_Iterator_fromSinglyList(struct kit_SinglyList *container) {
    assert(container);
    struct kit_Sequence_Iterator *self = kit_Allocator_calloc(1, sizeof(*self));

    if (self) {
        Optional(struct kit_SinglyList_Iterator *) super = kit_SinglyList_Iterator_fromBegin(container);
        if (Option_isSome(super)) {
            self->super = Option_unwrap(super);
            self->mDelete = (kit_Sequence_Iterator_Super_Trait_fnDelete) kit_SinglyList_Iterator_delete;
            self->mRewind = (kit_Sequence_Iterator_Super_Trait_fnRewind) kit_SinglyList_Iterator_rewindToBegin;
            self->mNext = (kit_Sequence_Iterator_Super_Trait_fnNext) kit_SinglyList_Iterator_next;
            self->mSetLast = (kit_Sequence_Iterator_Super_Trait_fnSetLast) kit_SinglyList_Iterator_setLast;
            self->mIsModified = (kit_Sequence_Iterator_Super_Trait_fnIsModified) kit_SinglyList_Iterator_isModified;
        } else {
            kit_Allocator_free(self);
            self = NULL;
        }
    }

    return Option_new(self);
}

static Optional(struct kit_Sequence_Iterator *) kit_Sequence_Iterator_fromXorList(struct kit_XorList *container) {
    assert(container);
    struct kit_Sequence_Iterator *self = kit_Allocator_calloc(1, sizeof(*self));

    if (self) {
        Optional(struct kit_XorList_Iterator *) super = kit_XorList_Iterator_fromBegin(container);
        if (Option_isSome(super)) {
            self->super = Option_unwrap(super);
            self->mDelete = (kit_Sequence_Iterator_Super_Trait_fnDelete) kit_XorList_Iterator_delete;
            self->mRewind = (kit_Sequence_Iterator_Super_Trait_fnRewind) kit_XorList_Iterator_rewindToBegin;
            self->mNext = (kit_Sequence_Iterator_Super_Trait_fnNext) kit_XorList_Iterator_next;
            self->mSetLast = (kit_Sequence_Iterator_Super_Trait_fnSetLast) kit_XorList_Iterator_setLast;
            self->mIsModified = (kit_Sequence_Iterator_Super_Trait_fnIsModified) kit_XorList_Iterator_isModified;
        } else {
            kit_Allocator_free(self);
            self = NULL;
        }
    }

    return Option_new(self);
}

static Optional(struct kit_Sequence_Iterator *) kit_Sequence_Iterator_fromVector(struct kit_Vector *container) {
    assert(container);
    struct kit_Sequence_Iterator *self = kit_Allocator_calloc(1, sizeof(*self));

    if (self) {
        Optional(struct kit_Vector_Iterator *) super = kit_Vector_Iterator_fromBegin(container);
        if (Option_isSome(super)) {
            self->super = Option_unwrap(super);
            self->mDelete = (kit_Sequence_Iterator_Super_Trait_fnDelete) kit_Vector_Iterator_delete;
            self->mRewind = (kit_Sequence_Iterator_Super_Trait_fnRewind) kit_Vector_Iterator_rewindToBegin;
            self->mNext = (kit_Sequence_Iterator_Super_Trait_fnNext) kit_Vector_Iterator_next;
            self->mSetLast = (kit_Sequence_Iterator_Super_Trait_fnSetLast) kit_Vector_Iterator_setLast;
            self->mIsModified = (kit_Sequence_Iterator_Super_Trait_fnIsModified) kit_Vector_Iterator_isModified;
        } else {
            kit_Allocator_free(self);
            self = NULL;
        }
    }

    return Option_new(self);
}

Optional(struct kit_Sequence_Iterator *) kit_Sequence_Iterator_new(struct kit_Sequence *container) {
    assert(container);
    switch (container->superTrait) {
        case KIT_SEQUENCE_SUPER_TRAIT_DOUBLY_LIST: {
            return kit_Sequence_Iterator_fromDoublyList(container->super);
        }
        case KIT_SEQUENCE_SUPER_TRAIT_SINGLY_LIST: {
            return kit_Sequence_Iterator_fromSinglyList(container->super);
        }
        case KIT_SEQUENCE_SUPER_TRAIT_XOR_LIST: {
            return kit_Sequence_Iterator_fromXorList(container->super);
        }
        case KIT_SEQUENCE_SUPER_TRAIT_VECTOR: {
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
    self->mRewind(self->super);
}

void kit_Sequence_Iterator_delete(struct kit_Sequence_Iterator *self) {
    if (self) {
        self->mDelete(self->super);
        kit_Allocator_free(self);
    }
}

enum kit_Result kit_Sequence_Iterator_next(struct kit_Sequence_Iterator *self, void **out) {
    assert(self);
    assert(out);
    return self->mNext(self->super, out);
}

enum kit_Result kit_Sequence_Iterator_setLast(struct kit_Sequence_Iterator *self, void *e) {
    assert(self);
    return self->mSetLast(self->super, e);
}

bool kit_Sequence_Iterator_isModified(struct kit_Sequence_Iterator *self) {
    assert(self);
    return self->mIsModified(self->super);
}
