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
#include <kit/collections/stack.h>

typedef void *kit_Stack_Super;

typedef Error (*kit_Stack_Super_pushFn)(kit_Stack_Super, void *);
typedef Result (*kit_Stack_Super_popFn)(kit_Stack_Super);
typedef Result (*kit_Stack_Super_backFn)(kit_Stack_Super);
typedef size_t (*kit_Stack_Super_sizeFn)(kit_Stack_Super);
typedef bool (*kit_Stack_Super_isEmptyFn)(kit_Stack_Super);
typedef void (*kit_Stack_Super_deleteFn)(kit_Stack_Super);

struct kit_Stack {
    kit_Stack_Super super;
    kit_Stack_Super_pushFn fnPush;
    kit_Stack_Super_popFn fnPop;
    kit_Stack_Super_backFn fnBack;
    kit_Stack_Super_sizeFn fnSize;
    kit_Stack_Super_isEmptyFn fnIsEmpty;
    kit_Stack_Super_deleteFn fnDelete;
};

Option kit_Stack_fromDoublyList(void) {
    struct kit_Stack *self;
    Option selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        superOption = kit_DoublyList_new();
        if (Option_isSome(superOption)) {
            self->super = Option_unwrap(superOption);
            self->fnPush = (kit_Stack_Super_pushFn) kit_DoublyList_pushBack;
            self->fnPop = (kit_Stack_Super_popFn) kit_DoublyList_popBack;
            self->fnBack = (kit_Stack_Super_backFn) kit_DoublyList_back;
            self->fnSize = (kit_Stack_Super_sizeFn) kit_DoublyList_size;
            self->fnIsEmpty = (kit_Stack_Super_isEmptyFn) kit_DoublyList_isEmpty;
            self->fnDelete = (kit_Stack_Super_deleteFn) kit_DoublyList_delete;
        } else {
            kit_Allocator_free(self);
            selfOption = None;
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
            self->fnPush = (kit_Stack_Super_pushFn) kit_SinglyList_pushFront;
            self->fnPop = (kit_Stack_Super_popFn) kit_SinglyList_popFront;
            self->fnBack = (kit_Stack_Super_backFn) kit_SinglyList_front;
            self->fnSize = (kit_Stack_Super_sizeFn) kit_SinglyList_size;
            self->fnIsEmpty = (kit_Stack_Super_isEmptyFn) kit_SinglyList_isEmpty;
            self->fnDelete = (kit_Stack_Super_deleteFn) kit_SinglyList_delete;
        } else {
            kit_Allocator_free(self);
            selfOption = None;
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
            self->fnPush = (kit_Stack_Super_pushFn) kit_XorList_pushBack;
            self->fnPop = (kit_Stack_Super_popFn) kit_XorList_popBack;
            self->fnBack = (kit_Stack_Super_backFn) kit_XorList_back;
            self->fnSize = (kit_Stack_Super_sizeFn) kit_XorList_size;
            self->fnIsEmpty = (kit_Stack_Super_isEmptyFn) kit_XorList_isEmpty;
            self->fnDelete = (kit_Stack_Super_deleteFn) kit_XorList_delete;
        } else {
            kit_Allocator_free(self);
            selfOption = None;
        }
    }

    return selfOption;
}

Option kit_Stack_fromVector(size_t capacityHint) {
    struct kit_Stack *self;
    Option selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        superOption = kit_Vector_withCapacity(capacityHint);
        if (Option_isSome(superOption)) {
            self->super = Option_unwrap(superOption);
            self->fnPush = (kit_Stack_Super_pushFn) kit_Vector_pushBack;
            self->fnPop = (kit_Stack_Super_popFn) kit_Vector_popBack;
            self->fnBack = (kit_Stack_Super_backFn) kit_Vector_back;
            self->fnSize = (kit_Stack_Super_sizeFn) kit_Vector_size;
            self->fnIsEmpty = (kit_Stack_Super_isEmptyFn) kit_Vector_isEmpty;
            self->fnDelete = (kit_Stack_Super_deleteFn) kit_Vector_delete;
        } else {
            kit_Allocator_free(self);
            selfOption = None;
        }
    }

    return selfOption;
}

Error kit_Stack_push(struct kit_Stack *const self, void *const element) {
    assert(self);
    return self->fnPush(self->super, element);
}

Result kit_Stack_pop(struct kit_Stack *const self) {
    assert(self);
    return self->fnPop(self->super);
}

Result kit_Stack_back(const struct kit_Stack *const self) {
    assert(self);
    return self->fnBack(self->super);
}

size_t kit_Stack_size(const struct kit_Stack *const self) {
    assert(self);
    return self->fnSize(self->super);
}

bool kit_Stack_isEmpty(const struct kit_Stack *const self) {
    assert(self);
    return self->fnIsEmpty(self->super);
}

void kit_Stack_delete(struct kit_Stack *self) {
    if (self) {
        self->fnDelete(self->super);
        kit_Allocator_free(self);
    }
}
