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
#include <kit/collections/stack.h>

typedef void *kit_Stack_Super;

typedef void (*kit_Stack_Super_Trait_fnDelete)(kit_Stack_Super);
typedef enum kit_Result (*kit_Stack_Super_Trait_fnPush)(kit_Stack_Super, void *);
typedef enum kit_Result (*kit_Stack_Super_Trait_fnPop)(kit_Stack_Super, void **);
typedef enum kit_Result (*kit_Stack_Super_Trait_fnBack)(kit_Stack_Super, void **);
typedef size_t (*kit_Stack_Super_Trait_fnSize)(kit_Stack_Super);
typedef bool (*kit_Stack_Super_Trait_fnIsEmpty)(kit_Stack_Super);

struct kit_Stack {
    kit_Stack_Super super;
    kit_Stack_Super_Trait_fnDelete mDelete;
    kit_Stack_Super_Trait_fnPush mPush;
    kit_Stack_Super_Trait_fnPop mPop;
    kit_Stack_Super_Trait_fnBack mBack;
    kit_Stack_Super_Trait_fnSize mSize;
    kit_Stack_Super_Trait_fnIsEmpty mIsEmpty;
};

Option kit_Stack_fromDoublyList(void) {
    struct kit_Stack *self;
    Option selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        superOption = kit_DoublyList_new();
        if (Option_isSome(superOption)) {
            self->super = Option_unwrap(superOption);
            self->mDelete = (kit_Stack_Super_Trait_fnDelete) kit_DoublyList_delete;
            self->mPush = (kit_Stack_Super_Trait_fnPush) kit_DoublyList_pushBack;
            self->mPop = (kit_Stack_Super_Trait_fnPop) kit_DoublyList_popBack;
            self->mBack = (kit_Stack_Super_Trait_fnBack) kit_DoublyList_back;
            self->mSize = (kit_Stack_Super_Trait_fnSize) kit_DoublyList_size;
            self->mIsEmpty = (kit_Stack_Super_Trait_fnIsEmpty) kit_DoublyList_isEmpty;
        } else {
            kit_Allocator_free(self);
        }
    }

    return selfOption;
}

Option kit_Stack_fromSinglyList(void) {
    struct kit_Stack *self;
    Option selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        superOption = kit_SinglyList_new();
        if (Option_isSome(superOption)) {
            self->super = Option_unwrap(superOption);
            self->mDelete = (kit_Stack_Super_Trait_fnDelete) kit_SinglyList_delete;
            self->mPush = (kit_Stack_Super_Trait_fnPush) kit_SinglyList_pushFront;
            self->mPop = (kit_Stack_Super_Trait_fnPop) kit_SinglyList_popFront;
            self->mBack = (kit_Stack_Super_Trait_fnBack) kit_SinglyList_front;
            self->mSize = (kit_Stack_Super_Trait_fnSize) kit_SinglyList_size;
            self->mIsEmpty = (kit_Stack_Super_Trait_fnIsEmpty) kit_SinglyList_isEmpty;
        } else {
            kit_Allocator_free(self);
        }
    }

    return selfOption;
}

Option kit_Stack_fromXorList(void) {
    struct kit_Stack *self;
    Option selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        superOption = kit_XorList_new();
        if (Option_isSome(superOption)) {
            self->super = Option_unwrap(superOption);
            self->mDelete = (kit_Stack_Super_Trait_fnDelete) kit_XorList_delete;
            self->mPush = (kit_Stack_Super_Trait_fnPush) kit_XorList_pushBack;
            self->mPop = (kit_Stack_Super_Trait_fnPop) kit_XorList_popBack;
            self->mBack = (kit_Stack_Super_Trait_fnBack) kit_XorList_back;
            self->mSize = (kit_Stack_Super_Trait_fnSize) kit_XorList_size;
            self->mIsEmpty = (kit_Stack_Super_Trait_fnIsEmpty) kit_XorList_isEmpty;
        } else {
            kit_Allocator_free(self);
        }
    }

    return selfOption;
}

Option kit_Stack_fromVector(void) {
    struct kit_Stack *self;
    Option selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        superOption = kit_Vector_new();
        if (Option_isSome(superOption)) {
            self->super = Option_unwrap(superOption);
            self->mDelete = (kit_Stack_Super_Trait_fnDelete) kit_Vector_delete;
            self->mPush = (kit_Stack_Super_Trait_fnPush) kit_Vector_pushBack;
            self->mPop = (kit_Stack_Super_Trait_fnPop) kit_Vector_popBack;
            self->mBack = (kit_Stack_Super_Trait_fnBack) kit_Vector_back;
            self->mSize = (kit_Stack_Super_Trait_fnSize) kit_Vector_size;
            self->mIsEmpty = (kit_Stack_Super_Trait_fnIsEmpty) kit_Vector_isEmpty;
        } else {
            kit_Allocator_free(self);
        }
    }

    return selfOption;
}

void kit_Stack_delete(struct kit_Stack *self) {
    if (self) {
        self->mDelete(self->super);
        kit_Allocator_free(self);
    }
}

enum kit_Result kit_Stack_push(struct kit_Stack *self, void *e) {
    assert(self);
    return self->mPush(self->super, e);
}

enum kit_Result kit_Stack_pop(struct kit_Stack *self, void **out) {
    assert(self);
    assert(out);
    return self->mPop(self->super, out);
}

enum kit_Result kit_Stack_back(struct kit_Stack *self, void **out) {
    assert(self);
    assert(out);
    return self->mBack(self->super, out);
}

size_t kit_Stack_size(struct kit_Stack *self) {
    assert(self);
    return self->mSize(self->super);
}

bool kit_Stack_isEmpty(struct kit_Stack *self) {
    assert(self);
    return self->mIsEmpty(self->super);
}
