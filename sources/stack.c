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

typedef void (*kit_Stack_Super_deleteFn)(kit_Stack_Super);
typedef enum kit_Result (*kit_Stack_Super_pushFn)(kit_Stack_Super, void *);
typedef enum kit_Result (*kit_Stack_Super_popFn)(kit_Stack_Super, void **);
typedef enum kit_Result (*kit_Stack_Super_backFn)(kit_Stack_Super, void **);
typedef size_t (*kit_Stack_Super_sizeFn)(kit_Stack_Super);
typedef bool (*kit_Stack_Super_isEmptyFn)(kit_Stack_Super);

struct kit_Stack {
    kit_Stack_Super super;
    kit_Stack_Super_deleteFn fnDelete;
    kit_Stack_Super_pushFn fnPush;
    kit_Stack_Super_popFn fnPop;
    kit_Stack_Super_backFn fnBack;
    kit_Stack_Super_sizeFn fnSize;
    kit_Stack_Super_isEmptyFn fnIsEmpty;
};

Option kit_Stack_fromDoublyList(void) {
    struct kit_Stack *self;
    Option selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        superOption = kit_DoublyList_new();
        if (Option_isSome(superOption)) {
            self->super = Option_unwrap(superOption);
            self->fnDelete = (kit_Stack_Super_deleteFn) kit_DoublyList_delete;
            self->fnPush = (kit_Stack_Super_pushFn) kit_DoublyList_pushBack;
            self->fnPop = (kit_Stack_Super_popFn) kit_DoublyList_popBack;
            self->fnBack = (kit_Stack_Super_backFn) kit_DoublyList_back;
            self->fnSize = (kit_Stack_Super_sizeFn) kit_DoublyList_size;
            self->fnIsEmpty = (kit_Stack_Super_isEmptyFn) kit_DoublyList_isEmpty;
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
            self->fnDelete = (kit_Stack_Super_deleteFn) kit_SinglyList_delete;
            self->fnPush = (kit_Stack_Super_pushFn) kit_SinglyList_pushFront;
            self->fnPop = (kit_Stack_Super_popFn) kit_SinglyList_popFront;
            self->fnBack = (kit_Stack_Super_backFn) kit_SinglyList_front;
            self->fnSize = (kit_Stack_Super_sizeFn) kit_SinglyList_size;
            self->fnIsEmpty = (kit_Stack_Super_isEmptyFn) kit_SinglyList_isEmpty;
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
            self->fnDelete = (kit_Stack_Super_deleteFn) kit_XorList_delete;
            self->fnPush = (kit_Stack_Super_pushFn) kit_XorList_pushBack;
            self->fnPop = (kit_Stack_Super_popFn) kit_XorList_popBack;
            self->fnBack = (kit_Stack_Super_backFn) kit_XorList_back;
            self->fnSize = (kit_Stack_Super_sizeFn) kit_XorList_size;
            self->fnIsEmpty = (kit_Stack_Super_isEmptyFn) kit_XorList_isEmpty;
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
            self->fnDelete = (kit_Stack_Super_deleteFn) kit_Vector_delete;
            self->fnPush = (kit_Stack_Super_pushFn) kit_Vector_pushBack;
            self->fnPop = (kit_Stack_Super_popFn) kit_Vector_popBack;
            self->fnBack = (kit_Stack_Super_backFn) kit_Vector_back;
            self->fnSize = (kit_Stack_Super_sizeFn) kit_Vector_size;
            self->fnIsEmpty = (kit_Stack_Super_isEmptyFn) kit_Vector_isEmpty;
        } else {
            kit_Allocator_free(self);
        }
    }

    return selfOption;
}

void kit_Stack_delete(struct kit_Stack *self) {
    if (self) {
        self->fnDelete(self->super);
        kit_Allocator_free(self);
    }
}

enum kit_Result kit_Stack_push(struct kit_Stack *self, void *e) {
    assert(self);
    return self->fnPush(self->super, e);
}

enum kit_Result kit_Stack_pop(struct kit_Stack *self, void **out) {
    assert(self);
    assert(out);
    return self->fnPop(self->super, out);
}

enum kit_Result kit_Stack_back(struct kit_Stack *self, void **out) {
    assert(self);
    assert(out);
    return self->fnBack(self->super, out);
}

size_t kit_Stack_size(struct kit_Stack *self) {
    assert(self);
    return self->fnSize(self->super);
}

bool kit_Stack_isEmpty(struct kit_Stack *self) {
    assert(self);
    return self->fnIsEmpty(self->super);
}
