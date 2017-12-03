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

typedef void (*kit_Queue_Super_deleteFn)(kit_Queue_Super);
typedef enum kit_Result (*kit_Queue_Super_pushFn)(kit_Queue_Super, void *);
typedef enum kit_Result (*kit_Queue_Super_popFn)(kit_Queue_Super, void **);
typedef enum kit_Result (*kit_Queue_Super_backFn)(kit_Queue_Super, void **);
typedef enum kit_Result (*kit_Queue_Super_FrontFn)(kit_Queue_Super, void **);
typedef size_t (*kit_Queue_Super_sizeFn)(kit_Queue_Super);
typedef bool (*kit_Queue_Super_isEmptyFn)(kit_Queue_Super);

struct kit_Queue {
    kit_Queue_Super super;
    kit_Queue_Super_deleteFn fnDelete;
    kit_Queue_Super_pushFn fnPush;
    kit_Queue_Super_popFn fnPop;
    kit_Queue_Super_backFn fnBack;
    kit_Queue_Super_FrontFn fnFront;
    kit_Queue_Super_sizeFn fnSize;
    kit_Queue_Super_isEmptyFn fnIsEmpty;
};

MutableOption kit_Queue_fromDoublyList(void) {
    struct kit_Queue *self;
    MutableOption selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (MutableOption_isSome(selfOption)) {
        self = MutableOption_unwrap(selfOption);
        superOption = kit_DoublyList_new();
        if (MutableOption_isSome(superOption)) {
            self->super = MutableOption_unwrap(superOption);
            self->fnDelete = (kit_Queue_Super_deleteFn) kit_DoublyList_delete;
            self->fnPush = (kit_Queue_Super_pushFn) kit_DoublyList_pushBack;
            self->fnPop = (kit_Queue_Super_popFn) kit_DoublyList_popFront;
            self->fnBack = (kit_Queue_Super_backFn) kit_DoublyList_back;
            self->fnFront = (kit_Queue_Super_FrontFn) kit_DoublyList_front;
            self->fnSize = (kit_Queue_Super_sizeFn) kit_DoublyList_size;
            self->fnIsEmpty = (kit_Queue_Super_isEmptyFn) kit_DoublyList_isEmpty;
        } else {
            kit_Allocator_free(self);
        }
    }

    return selfOption;
}

MutableOption kit_Queue_fromSinglyList(void) {
    struct kit_Queue *self;
    MutableOption selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (MutableOption_isSome(selfOption)) {
        self = MutableOption_unwrap(selfOption);
        superOption = kit_SinglyList_new();
        if (MutableOption_isSome(superOption)) {
            self->super = MutableOption_unwrap(superOption);
            self->fnDelete = (kit_Queue_Super_deleteFn) kit_SinglyList_delete;
            self->fnPush = (kit_Queue_Super_pushFn) kit_SinglyList_pushBack;
            self->fnPop = (kit_Queue_Super_popFn) kit_SinglyList_popFront;
            self->fnBack = (kit_Queue_Super_backFn) kit_SinglyList_back;
            self->fnFront = (kit_Queue_Super_FrontFn) kit_SinglyList_front;
            self->fnSize = (kit_Queue_Super_sizeFn) kit_SinglyList_size;
            self->fnIsEmpty = (kit_Queue_Super_isEmptyFn) kit_SinglyList_isEmpty;
        } else {
            kit_Allocator_free(self);
        }
    }

    return selfOption;
}

MutableOption kit_Queue_fromXorList(void) {
    struct kit_Queue *self;
    MutableOption selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (MutableOption_isSome(selfOption)) {
        self = MutableOption_unwrap(selfOption);
        superOption = kit_XorList_new();
        if (MutableOption_isSome(superOption)) {
            self->super = MutableOption_unwrap(superOption);
            self->fnDelete = (kit_Queue_Super_deleteFn) kit_XorList_delete;
            self->fnPush = (kit_Queue_Super_pushFn) kit_XorList_pushBack;
            self->fnPop = (kit_Queue_Super_popFn) kit_XorList_popFront;
            self->fnBack = (kit_Queue_Super_backFn) kit_XorList_back;
            self->fnFront = (kit_Queue_Super_FrontFn) kit_XorList_front;
            self->fnSize = (kit_Queue_Super_sizeFn) kit_XorList_size;
            self->fnIsEmpty = (kit_Queue_Super_isEmptyFn) kit_XorList_isEmpty;
        } else {
            kit_Allocator_free(self);
        }
    }

    return selfOption;
}

MutableOption kit_Queue_fromVector(void) {
    struct kit_Queue *self;
    MutableOption selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (MutableOption_isSome(selfOption)) {
        self = MutableOption_unwrap(selfOption);
        superOption = kit_Vector_new();
        if (MutableOption_isSome(superOption)) {
            self->super = MutableOption_unwrap(superOption);
            self->fnDelete = (kit_Queue_Super_deleteFn) kit_Vector_delete;
            self->fnPush = (kit_Queue_Super_pushFn) kit_Vector_pushBack;
            self->fnPop = (kit_Queue_Super_popFn) kit_Vector_popFront;
            self->fnBack = (kit_Queue_Super_backFn) kit_Vector_back;
            self->fnFront = (kit_Queue_Super_FrontFn) kit_Vector_front;
            self->fnSize = (kit_Queue_Super_sizeFn) kit_Vector_size;
            self->fnIsEmpty = (kit_Queue_Super_isEmptyFn) kit_Vector_isEmpty;
        } else {
            kit_Allocator_free(self);
        }
    }

    return selfOption;
}

void kit_Queue_delete(struct kit_Queue *self) {
    if (self) {
        self->fnDelete(self->super);
        kit_Allocator_free(self);
    }
}

enum kit_Result kit_Queue_push(struct kit_Queue *self, void *e) {
    assert(self);
    return self->fnPush(self->super, e);
}

enum kit_Result kit_Queue_pop(struct kit_Queue *self, void **out) {
    assert(self);
    assert(out);
    return self->fnPop(self->super, out);
}

enum kit_Result kit_Queue_back(struct kit_Queue *self, void **out) {
    assert(self);
    assert(out);
    return self->fnBack(self->super, out);
}

enum kit_Result kit_Queue_front(struct kit_Queue *self, void **out) {
    assert(self);
    assert(out);
    return self->fnFront(self->super, out);
}

size_t kit_Queue_size(struct kit_Queue *self) {
    assert(self);
    return self->fnSize(self->super);
}

bool kit_Queue_isEmpty(struct kit_Queue *self) {
    assert(self);
    return self->fnIsEmpty(self->super);
}
