/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 26, 2017 
 */

#include <assert.h>
#include <stdlib.h>
#include <kit/allocator/allocator.h>
#include <kit/collections/doubly_list.h>
#include <kit/collections/singly_list.h>
#include <kit/collections/xor_list.h>
#include <kit/collections/vector.h>
#include <kit/collections/queue.h>

typedef void *kit_Queue_Super;

typedef void (*kit_Queue_Super_Trait_fnDelete)(kit_Queue_Super);
typedef enum kit_Result (*kit_Queue_Super_Trait_fnPush)(kit_Queue_Super, void *);
typedef enum kit_Result (*kit_Queue_Super_Trait_fnPop)(kit_Queue_Super, void **);
typedef enum kit_Result (*kit_Queue_Super_Trait_fnBack)(kit_Queue_Super, void **);
typedef enum kit_Result (*kit_Queue_Super_Trait_fnFront)(kit_Queue_Super, void **);
typedef size_t (*kit_Queue_Super_Trait_fnSize)(kit_Queue_Super);
typedef bool (*kit_Queue_Super_Trait_fnIsEmpty)(kit_Queue_Super);

struct kit_Queue {
    kit_Queue_Super super;
    kit_Queue_Super_Trait_fnDelete mDelete;
    kit_Queue_Super_Trait_fnPush mPush;
    kit_Queue_Super_Trait_fnPop mPop;
    kit_Queue_Super_Trait_fnBack mBack;
    kit_Queue_Super_Trait_fnFront mFront;
    kit_Queue_Super_Trait_fnSize mSize;
    kit_Queue_Super_Trait_fnIsEmpty mIsEmpty;
};

Option kit_Queue_fromDoublyList(void) {
    struct kit_Queue *self;
    Option selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        superOption = kit_DoublyList_new();
        if (Option_isSome(superOption)) {
            self->super = Option_unwrap(superOption);
            self->mDelete = (kit_Queue_Super_Trait_fnDelete) kit_DoublyList_delete;
            self->mPush = (kit_Queue_Super_Trait_fnPush) kit_DoublyList_pushBack;
            self->mPop = (kit_Queue_Super_Trait_fnPop) kit_DoublyList_popFront;
            self->mBack = (kit_Queue_Super_Trait_fnBack) kit_DoublyList_back;
            self->mFront = (kit_Queue_Super_Trait_fnFront) kit_DoublyList_front;
            self->mSize = (kit_Queue_Super_Trait_fnSize) kit_DoublyList_size;
            self->mIsEmpty = (kit_Queue_Super_Trait_fnIsEmpty) kit_DoublyList_isEmpty;
        } else {
            kit_Allocator_free(self);
        }
    }

    return selfOption;
}

Option kit_Queue_fromSinglyList(void) {
    struct kit_Queue *self;
    Option selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        superOption = kit_SinglyList_new();
        if (Option_isSome(superOption)) {
            self->super = Option_unwrap(superOption);
            self->mDelete = (kit_Queue_Super_Trait_fnDelete) kit_SinglyList_delete;
            self->mPush = (kit_Queue_Super_Trait_fnPush) kit_SinglyList_pushBack;
            self->mPop = (kit_Queue_Super_Trait_fnPop) kit_SinglyList_popFront;
            self->mBack = (kit_Queue_Super_Trait_fnBack) kit_SinglyList_back;
            self->mFront = (kit_Queue_Super_Trait_fnFront) kit_SinglyList_front;
            self->mSize = (kit_Queue_Super_Trait_fnSize) kit_SinglyList_size;
            self->mIsEmpty = (kit_Queue_Super_Trait_fnIsEmpty) kit_SinglyList_isEmpty;
        } else {
            kit_Allocator_free(self);
        }
    }

    return selfOption;
}

Option kit_Queue_fromXorList(void) {
    struct kit_Queue *self;
    Option selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        superOption = kit_XorList_new();
        if (Option_isSome(superOption)) {
            self->super = Option_unwrap(superOption);
            self->mDelete = (kit_Queue_Super_Trait_fnDelete) kit_XorList_delete;
            self->mPush = (kit_Queue_Super_Trait_fnPush) kit_XorList_pushBack;
            self->mPop = (kit_Queue_Super_Trait_fnPop) kit_XorList_popFront;
            self->mBack = (kit_Queue_Super_Trait_fnBack) kit_XorList_back;
            self->mFront = (kit_Queue_Super_Trait_fnFront) kit_XorList_front;
            self->mSize = (kit_Queue_Super_Trait_fnSize) kit_XorList_size;
            self->mIsEmpty = (kit_Queue_Super_Trait_fnIsEmpty) kit_XorList_isEmpty;
        } else {
            kit_Allocator_free(self);
        }
    }

    return selfOption;
}

Option kit_Queue_fromVector(void) {
    struct kit_Queue *self;
    Option selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        superOption = kit_Vector_new();
        if (Option_isSome(superOption)) {
            self->super = Option_unwrap(superOption);
            self->mDelete = (kit_Queue_Super_Trait_fnDelete) kit_Vector_delete;
            self->mPush = (kit_Queue_Super_Trait_fnPush) kit_Vector_pushBack;
            self->mPop = (kit_Queue_Super_Trait_fnPop) kit_Vector_popFront;
            self->mBack = (kit_Queue_Super_Trait_fnBack) kit_Vector_back;
            self->mFront = (kit_Queue_Super_Trait_fnFront) kit_Vector_front;
            self->mSize = (kit_Queue_Super_Trait_fnSize) kit_Vector_size;
            self->mIsEmpty = (kit_Queue_Super_Trait_fnIsEmpty) kit_Vector_isEmpty;
        } else {
            kit_Allocator_free(self);
        }
    }

    return selfOption;
}

void kit_Queue_delete(struct kit_Queue *self) {
    if (self) {
        self->mDelete(self->super);
        kit_Allocator_free(self);
    }
}

enum kit_Result kit_Queue_push(struct kit_Queue *self, void *e) {
    assert(self);
    return self->mPush(self->super, e);
}

enum kit_Result kit_Queue_pop(struct kit_Queue *self, void **out) {
    assert(self);
    assert(out);
    return self->mPop(self->super, out);
}

enum kit_Result kit_Queue_back(struct kit_Queue *self, void **out) {
    assert(self);
    assert(out);
    return self->mBack(self->super, out);
}

enum kit_Result kit_Queue_front(struct kit_Queue *self, void **out) {
    assert(self);
    assert(out);
    return self->mFront(self->super, out);
}

size_t kit_Queue_size(struct kit_Queue *self) {
    assert(self);
    return self->mSize(self->super);
}

bool kit_Queue_isEmpty(struct kit_Queue *self) {
    assert(self);
    return self->mIsEmpty(self->super);
}
