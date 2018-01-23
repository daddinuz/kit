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
#include <kit/collections/doubly_list.h>
#include <kit/collections/singly_list.h>
#include <kit/collections/xor_list.h>
#include <kit/collections/vector.h>
#include <kit/collections/queue.h>

typedef void *kit_Queue_Super;

typedef Error (*kit_Queue_Super_pushFn)(kit_Queue_Super, void *);
typedef Result (*kit_Queue_Super_popFn)(kit_Queue_Super);
typedef Result (*kit_Queue_Super_backFn)(kit_Queue_Super);
typedef Result (*kit_Queue_Super_frontFn)(kit_Queue_Super);
typedef size_t (*kit_Queue_Super_sizeFn)(kit_Queue_Super);
typedef bool (*kit_Queue_Super_isEmptyFn)(kit_Queue_Super);
typedef void (*kit_Queue_Super_deleteFn)(kit_Queue_Super);

struct kit_Queue {
    kit_Queue_Super super;
    kit_Queue_Super_pushFn fnPush;
    kit_Queue_Super_popFn fnPop;
    kit_Queue_Super_backFn fnBack;
    kit_Queue_Super_frontFn fnFront;
    kit_Queue_Super_sizeFn fnSize;
    kit_Queue_Super_isEmptyFn fnIsEmpty;
    kit_Queue_Super_deleteFn fnDelete;
};

Option kit_Queue_fromDoublyList(void) {
    struct kit_Queue *self;
    Option selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        superOption = kit_DoublyList_new();
        if (Option_isSome(superOption)) {
            self->super = Option_unwrap(superOption);
            self->fnPush = (kit_Queue_Super_pushFn) kit_DoublyList_pushBack;
            self->fnPop = (kit_Queue_Super_popFn) kit_DoublyList_popFront;
            self->fnBack = (kit_Queue_Super_backFn) kit_DoublyList_back;
            self->fnFront = (kit_Queue_Super_frontFn) kit_DoublyList_front;
            self->fnSize = (kit_Queue_Super_sizeFn) kit_DoublyList_size;
            self->fnIsEmpty = (kit_Queue_Super_isEmptyFn) kit_DoublyList_isEmpty;
            self->fnDelete = (kit_Queue_Super_deleteFn) kit_DoublyList_delete;
        } else {
            kit_Allocator_free(self);
            selfOption = None;
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
            self->fnPush = (kit_Queue_Super_pushFn) kit_SinglyList_pushBack;
            self->fnPop = (kit_Queue_Super_popFn) kit_SinglyList_popFront;
            self->fnBack = (kit_Queue_Super_backFn) kit_SinglyList_back;
            self->fnFront = (kit_Queue_Super_frontFn) kit_SinglyList_front;
            self->fnSize = (kit_Queue_Super_sizeFn) kit_SinglyList_size;
            self->fnIsEmpty = (kit_Queue_Super_isEmptyFn) kit_SinglyList_isEmpty;
            self->fnDelete = (kit_Queue_Super_deleteFn) kit_SinglyList_delete;
        } else {
            kit_Allocator_free(self);
            selfOption = None;
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
            self->fnPush = (kit_Queue_Super_pushFn) kit_XorList_pushBack;
            self->fnPop = (kit_Queue_Super_popFn) kit_XorList_popFront;
            self->fnBack = (kit_Queue_Super_backFn) kit_XorList_back;
            self->fnFront = (kit_Queue_Super_frontFn) kit_XorList_front;
            self->fnSize = (kit_Queue_Super_sizeFn) kit_XorList_size;
            self->fnIsEmpty = (kit_Queue_Super_isEmptyFn) kit_XorList_isEmpty;
            self->fnDelete = (kit_Queue_Super_deleteFn) kit_XorList_delete;
        } else {
            kit_Allocator_free(self);
            selfOption = None;
        }
    }

    return selfOption;
}

Option kit_Queue_fromVector(size_t capacityHint) {
    struct kit_Queue *self;
    Option selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        superOption = kit_Vector_withCapacity(capacityHint);
        if (Option_isSome(superOption)) {
            self->super = Option_unwrap(superOption);
            self->fnPush = (kit_Queue_Super_pushFn) kit_Vector_pushBack;
            self->fnPop = (kit_Queue_Super_popFn) kit_Vector_popFront;
            self->fnBack = (kit_Queue_Super_backFn) kit_Vector_back;
            self->fnFront = (kit_Queue_Super_frontFn) kit_Vector_front;
            self->fnSize = (kit_Queue_Super_sizeFn) kit_Vector_size;
            self->fnIsEmpty = (kit_Queue_Super_isEmptyFn) kit_Vector_isEmpty;
            self->fnDelete = (kit_Queue_Super_deleteFn) kit_Vector_delete;
        } else {
            kit_Allocator_free(self);
            selfOption = None;
        }
    }

    return selfOption;
}

Error kit_Queue_push(struct kit_Queue *const self, void *const element) {
    assert(self);
    return self->fnPush(self->super, element);
}

Result kit_Queue_pop(struct kit_Queue *const self) {
    assert(self);
    return self->fnPop(self->super);
}

Result kit_Queue_back(const struct kit_Queue *const self) {
    assert(self);
    return self->fnBack(self->super);
}

Result kit_Queue_front(const struct kit_Queue *const self) {
    assert(self);
    return self->fnFront(self->super);
}

size_t kit_Queue_size(const struct kit_Queue *const self) {
    assert(self);
    return self->fnSize(self->super);
}

bool kit_Queue_isEmpty(const struct kit_Queue *const self) {
    assert(self);
    return self->fnIsEmpty(self->super);
}

void kit_Queue_delete(struct kit_Queue *self) {
    if (self) {
        self->fnDelete(self->super);
        kit_Allocator_free(self);
    }
}
