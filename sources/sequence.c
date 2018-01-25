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

typedef Error (*kit_Sequence_Super_expandFn)(kit_Sequence_Super, size_t);
typedef Error (*kit_Sequence_Super_shrinkFn)(kit_Sequence_Super);
typedef Error (*kit_Sequence_Super_insertFn)(kit_Sequence_Super, size_t, void *);
typedef Error (*kit_Sequence_Super_pushBackFn)(kit_Sequence_Super, void *);
typedef Error (*kit_Sequence_Super_pushFrontFn)(kit_Sequence_Super, void *);
typedef Result (*kit_Sequence_Super_removeFn)(kit_Sequence_Super, size_t);
typedef Result (*kit_Sequence_Super_popBackFn)(kit_Sequence_Super);
typedef Result (*kit_Sequence_Super_popFrontFn)(kit_Sequence_Super);
typedef Result (*kit_Sequence_Super_putFn)(kit_Sequence_Super, size_t, void *);
typedef Result (*kit_Sequence_Super_getFn)(kit_Sequence_Super, size_t);
typedef Result (*kit_Sequence_Super_backFn)(kit_Sequence_Super);
typedef Result (*kit_Sequence_Super_frontFn)(kit_Sequence_Super);
typedef void (*kit_Sequence_Super_clearFn)(kit_Sequence_Super);
typedef size_t (*kit_Sequence_Super_sizeFn)(kit_Sequence_Super);
typedef size_t (*kit_Sequence_Super_capacityFn)(kit_Sequence_Super);
typedef bool (*kit_Sequence_Super_isEmptyFn)(kit_Sequence_Super);
typedef void (*kit_Sequence_Super_deleteFn)(kit_Sequence_Super);

struct kit_Sequence {
    enum kit_Sequence_Trait trait;
    kit_Sequence_Super super;
    kit_Sequence_Super_expandFn fnExpand;
    kit_Sequence_Super_shrinkFn fnShrink;
    kit_Sequence_Super_insertFn fnInsert;
    kit_Sequence_Super_pushBackFn fnPushBack;
    kit_Sequence_Super_pushFrontFn fnPushFront;
    kit_Sequence_Super_removeFn fnRemove;
    kit_Sequence_Super_popBackFn fnPopBack;
    kit_Sequence_Super_popFrontFn fnPopFront;
    kit_Sequence_Super_putFn fnPut;
    kit_Sequence_Super_getFn fnGet;
    kit_Sequence_Super_backFn fnBack;
    kit_Sequence_Super_frontFn fnFront;
    kit_Sequence_Super_clearFn fnClear;
    kit_Sequence_Super_sizeFn fnSize;
    kit_Sequence_Super_capacityFn fnCapacity;
    kit_Sequence_Super_isEmptyFn fnIsEmpty;
    kit_Sequence_Super_deleteFn fnDelete;
};

static Error kit_Sequence_Super_expandNoOp(kit_Sequence_Super p0, size_t p1) {
    (void) p0;
    (void) p1;
    return Ok;
}

static Error kit_Sequence_Super_shrinkNoOp(kit_Sequence_Super p0) {
    (void) p0;
    return Ok;
}


Option kit_Sequence_fromDoublyList(void) {
    struct kit_Sequence *self;
    Option selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        superOption = kit_DoublyList_new();
        if (Option_isSome(superOption)) {
            self->trait = KIT_SEQUENCE_TRAIT_DOUBLY_LIST;
            self->super = Option_unwrap(superOption);
            self->fnExpand = (kit_Sequence_Super_expandFn) kit_Sequence_Super_expandNoOp;
            self->fnShrink = (kit_Sequence_Super_shrinkFn) kit_Sequence_Super_shrinkNoOp;
            self->fnInsert = (kit_Sequence_Super_insertFn) kit_DoublyList_insert;
            self->fnPushBack = (kit_Sequence_Super_pushBackFn) kit_DoublyList_pushBack;
            self->fnPushFront = (kit_Sequence_Super_pushFrontFn) kit_DoublyList_pushFront;
            self->fnRemove = (kit_Sequence_Super_removeFn) kit_DoublyList_remove;
            self->fnPopBack = (kit_Sequence_Super_popBackFn) kit_DoublyList_popBack;
            self->fnPopFront = (kit_Sequence_Super_popFrontFn) kit_DoublyList_popFront;
            self->fnPut = (kit_Sequence_Super_putFn) kit_DoublyList_put;
            self->fnGet = (kit_Sequence_Super_getFn) kit_DoublyList_get;
            self->fnBack = (kit_Sequence_Super_backFn) kit_DoublyList_back;
            self->fnFront = (kit_Sequence_Super_frontFn) kit_DoublyList_front;
            self->fnClear = (kit_Sequence_Super_clearFn) kit_DoublyList_clear;
            self->fnSize = (kit_Sequence_Super_sizeFn) kit_DoublyList_size;
            self->fnIsEmpty = (kit_Sequence_Super_isEmptyFn) kit_DoublyList_isEmpty;
            self->fnCapacity = (kit_Sequence_Super_capacityFn) kit_DoublyList_size;
            self->fnDelete = (kit_Sequence_Super_deleteFn) kit_DoublyList_delete;
        } else {
            kit_Allocator_free(self);
            selfOption = None;
        }
    }

    return selfOption;
}

Option kit_Sequence_fromSinglyList(void) {
    struct kit_Sequence *self;
    Option selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        superOption = kit_SinglyList_new();
        if (Option_isSome(superOption)) {
            self->trait = KIT_SEQUENCE_TRAIT_SINGLY_LIST;
            self->super = Option_unwrap(superOption);
            self->fnExpand = (kit_Sequence_Super_expandFn) kit_Sequence_Super_expandNoOp;
            self->fnShrink = (kit_Sequence_Super_shrinkFn) kit_Sequence_Super_shrinkNoOp;
            self->fnInsert = (kit_Sequence_Super_insertFn) kit_SinglyList_insert;
            self->fnPushBack = (kit_Sequence_Super_pushBackFn) kit_SinglyList_pushBack;
            self->fnPushFront = (kit_Sequence_Super_pushFrontFn) kit_SinglyList_pushFront;
            self->fnRemove = (kit_Sequence_Super_removeFn) kit_SinglyList_remove;
            self->fnPopBack = (kit_Sequence_Super_popBackFn) kit_SinglyList_popBack;
            self->fnPopFront = (kit_Sequence_Super_popFrontFn) kit_SinglyList_popFront;
            self->fnPut = (kit_Sequence_Super_putFn) kit_SinglyList_put;
            self->fnGet = (kit_Sequence_Super_getFn) kit_SinglyList_get;
            self->fnBack = (kit_Sequence_Super_backFn) kit_SinglyList_back;
            self->fnFront = (kit_Sequence_Super_frontFn) kit_SinglyList_front;
            self->fnClear = (kit_Sequence_Super_clearFn) kit_SinglyList_clear;
            self->fnSize = (kit_Sequence_Super_sizeFn) kit_SinglyList_size;
            self->fnIsEmpty = (kit_Sequence_Super_isEmptyFn) kit_SinglyList_isEmpty;
            self->fnCapacity = (kit_Sequence_Super_capacityFn) kit_SinglyList_size;
            self->fnDelete = (kit_Sequence_Super_deleteFn) kit_SinglyList_delete;
        } else {
            kit_Allocator_free(self);
            selfOption = None;
        }
    }

    return selfOption;
}

Option kit_Sequence_fromXorList(void) {
    struct kit_Sequence *self;
    Option selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        superOption = kit_XorList_new();
        if (Option_isSome(superOption)) {
            self->trait = KIT_SEQUENCE_TRAIT_XOR_LIST;
            self->super = Option_unwrap(superOption);
            self->fnExpand = (kit_Sequence_Super_expandFn) kit_Sequence_Super_expandNoOp;
            self->fnShrink = (kit_Sequence_Super_shrinkFn) kit_Sequence_Super_shrinkNoOp;
            self->fnInsert = (kit_Sequence_Super_insertFn) kit_XorList_insert;
            self->fnPushBack = (kit_Sequence_Super_pushBackFn) kit_XorList_pushBack;
            self->fnPushFront = (kit_Sequence_Super_pushFrontFn) kit_XorList_pushFront;
            self->fnRemove = (kit_Sequence_Super_removeFn) kit_XorList_remove;
            self->fnPopBack = (kit_Sequence_Super_popBackFn) kit_XorList_popBack;
            self->fnPopFront = (kit_Sequence_Super_popFrontFn) kit_XorList_popFront;
            self->fnPut = (kit_Sequence_Super_putFn) kit_XorList_put;
            self->fnGet = (kit_Sequence_Super_getFn) kit_XorList_get;
            self->fnBack = (kit_Sequence_Super_backFn) kit_XorList_back;
            self->fnFront = (kit_Sequence_Super_frontFn) kit_XorList_front;
            self->fnClear = (kit_Sequence_Super_clearFn) kit_XorList_clear;
            self->fnSize = (kit_Sequence_Super_sizeFn) kit_XorList_size;
            self->fnIsEmpty = (kit_Sequence_Super_isEmptyFn) kit_XorList_isEmpty;
            self->fnCapacity = (kit_Sequence_Super_capacityFn) kit_XorList_size;
            self->fnDelete = (kit_Sequence_Super_deleteFn) kit_XorList_delete;
        } else {
            kit_Allocator_free(self);
            selfOption = None;
        }
    }

    return selfOption;
}

Option kit_Sequence_fromVector(size_t capacity) {
    struct kit_Sequence *self;
    Option selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        superOption = kit_Vector_withCapacity(capacity);
        if (Option_isSome(superOption)) {
            self->trait = KIT_SEQUENCE_TRAIT_VECTOR;
            self->super = Option_unwrap(superOption);
            self->fnExpand = (kit_Sequence_Super_expandFn) kit_Vector_expand;
            self->fnShrink = (kit_Sequence_Super_shrinkFn) kit_Vector_shrink;
            self->fnInsert = (kit_Sequence_Super_insertFn) kit_Vector_insert;
            self->fnPushBack = (kit_Sequence_Super_pushBackFn) kit_Vector_pushBack;
            self->fnPushFront = (kit_Sequence_Super_pushFrontFn) kit_Vector_pushFront;
            self->fnRemove = (kit_Sequence_Super_removeFn) kit_Vector_remove;
            self->fnPopBack = (kit_Sequence_Super_popBackFn) kit_Vector_popBack;
            self->fnPopFront = (kit_Sequence_Super_popFrontFn) kit_Vector_popFront;
            self->fnPut = (kit_Sequence_Super_putFn) kit_Vector_put;
            self->fnGet = (kit_Sequence_Super_getFn) kit_Vector_get;
            self->fnBack = (kit_Sequence_Super_backFn) kit_Vector_back;
            self->fnFront = (kit_Sequence_Super_frontFn) kit_Vector_front;
            self->fnClear = (kit_Sequence_Super_clearFn) kit_Vector_clear;
            self->fnSize = (kit_Sequence_Super_sizeFn) kit_Vector_size;
            self->fnIsEmpty = (kit_Sequence_Super_isEmptyFn) kit_Vector_isEmpty;
            self->fnCapacity = (kit_Sequence_Super_capacityFn) kit_Vector_capacity;
            self->fnDelete = (kit_Sequence_Super_deleteFn) kit_Vector_delete;
        } else {
            kit_Allocator_free(self);
            selfOption = None;
        }
    }

    return selfOption;
}

Error kit_Sequence_expand(struct kit_Sequence *const self, const size_t capacity) {
    assert(self);
    return self->fnExpand(self->super, capacity);
}

Error kit_Sequence_shrink(struct kit_Sequence *const self) {
    assert(self);
    return self->fnShrink(self->super);
}

Error kit_Sequence_insert(struct kit_Sequence *const self, const size_t index, void *const element) {
    assert(self);
    return self->fnInsert(self->super, index, element);
}

Error kit_Sequence_pushBack(struct kit_Sequence *const self, void *const element) {
    assert(self);
    return self->fnPushBack(self->super, element);
}

Error kit_Sequence_pushFront(struct kit_Sequence *const self, void *const element) {
    assert(self);
    return self->fnPushFront(self->super, element);
}

Result kit_Sequence_remove(struct kit_Sequence *const self, const size_t index) {
    assert(self);
    return self->fnRemove(self->super, index);
}

Result kit_Sequence_popBack(struct kit_Sequence *const self) {
    assert(self);
    return self->fnPopBack(self->super);
}

Result kit_Sequence_popFront(struct kit_Sequence *const self) {
    assert(self);
    return self->fnPopFront(self->super);
}

Result kit_Sequence_put(struct kit_Sequence *const self, const size_t index, void *const element) {
    assert(self);
    return self->fnPut(self->super, index, element);
}

Result kit_Sequence_get(const struct kit_Sequence *const self, const size_t index) {
    assert(self);
    return self->fnGet(self->super, index);
}

Result kit_Sequence_back(const struct kit_Sequence *const self) {
    assert(self);
    return self->fnBack(self->super);
}

Result kit_Sequence_front(const struct kit_Sequence *const self) {
    assert(self);
    return self->fnFront(self->super);
}

void kit_Sequence_clear(struct kit_Sequence *const self) {
    assert(self);
    self->fnClear(self->super);
}

size_t kit_Sequence_size(const struct kit_Sequence *const self) {
    assert(self);
    return self->fnSize(self->super);
}

bool kit_Sequence_isEmpty(const struct kit_Sequence *const self) {
    assert(self);
    return self->fnIsEmpty(self->super);
}

size_t kit_Sequence_capacity(const struct kit_Sequence *const self) {
    assert(self);
    return self->fnCapacity(self->super);
}

void kit_Sequence_delete(struct kit_Sequence *self) {
    if (self) {
        self->fnDelete(self->super);
        kit_Allocator_free(self);
    }
}

/*
 * kit_Sequence_Iterator
 */
typedef void *kit_Sequence_Iterator_Super;

typedef void (*kit_Sequence_Iterator_Super_rewindToBeginFn)(kit_Sequence_Iterator_Super);
typedef Result (*kit_Sequence_Iterator_Super_nextFn)(kit_Sequence_Iterator_Super);
typedef Result (*kit_Sequence_Iterator_Super_setLastFn)(kit_Sequence_Iterator_Super, void *);
typedef bool (*kit_Sequence_Iterator_Super_isModifiedFn)(kit_Sequence_Iterator_Super);
typedef void (*kit_Sequence_Iterator_Super_deleteFn)(kit_Sequence_Iterator_Super);

struct kit_Sequence_Iterator {
    kit_Sequence_Iterator_Super super;
    kit_Sequence_Iterator_Super_rewindToBeginFn fnRewindToBegin;
    kit_Sequence_Iterator_Super_nextFn fnNext;
    kit_Sequence_Iterator_Super_setLastFn fnSetLast;
    kit_Sequence_Iterator_Super_isModifiedFn fnIsModified;
    kit_Sequence_Iterator_Super_deleteFn fnDelete;
};

static Option kit_Sequence_Iterator_fromDoublyList(struct kit_DoublyList *const container) {
    assert(container);
    struct kit_Sequence_Iterator *self;
    Option selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        superOption = kit_DoublyList_Iterator_fromBegin(container);
        if (Option_isSome(superOption)) {
            self->super = Option_unwrap(superOption);
            self->fnRewindToBegin = (kit_Sequence_Iterator_Super_rewindToBeginFn) kit_DoublyList_Iterator_rewindToBegin;
            self->fnNext = (kit_Sequence_Iterator_Super_nextFn) kit_DoublyList_Iterator_next;
            self->fnSetLast = (kit_Sequence_Iterator_Super_setLastFn) kit_DoublyList_Iterator_setLast;
            self->fnIsModified = (kit_Sequence_Iterator_Super_isModifiedFn) kit_DoublyList_Iterator_isModified;
            self->fnDelete = (kit_Sequence_Iterator_Super_deleteFn) kit_DoublyList_Iterator_delete;
        } else {
            kit_Allocator_free(self);
            selfOption = None;
        }
    }

    return selfOption;
}

static Option kit_Sequence_Iterator_fromSinglyList(struct kit_SinglyList *const container) {
    assert(container);
    struct kit_Sequence_Iterator *self;
    Option selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        superOption = kit_SinglyList_Iterator_fromBegin(container);
        if (Option_isSome(superOption)) {
            self->super = Option_unwrap(superOption);
            self->fnRewindToBegin = (kit_Sequence_Iterator_Super_rewindToBeginFn) kit_SinglyList_Iterator_rewindToBegin;
            self->fnNext = (kit_Sequence_Iterator_Super_nextFn) kit_SinglyList_Iterator_next;
            self->fnSetLast = (kit_Sequence_Iterator_Super_setLastFn) kit_SinglyList_Iterator_setLast;
            self->fnIsModified = (kit_Sequence_Iterator_Super_isModifiedFn) kit_SinglyList_Iterator_isModified;
            self->fnDelete = (kit_Sequence_Iterator_Super_deleteFn) kit_SinglyList_Iterator_delete;
        } else {
            kit_Allocator_free(self);
            selfOption = None;
        }
    }

    return selfOption;
}

static Option kit_Sequence_Iterator_fromXorList(struct kit_XorList *const container) {
    assert(container);
    struct kit_Sequence_Iterator *self;
    Option selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        superOption = kit_XorList_Iterator_fromBegin(container);
        if (Option_isSome(superOption)) {
            self->super = Option_unwrap(superOption);
            self->fnRewindToBegin = (kit_Sequence_Iterator_Super_rewindToBeginFn) kit_XorList_Iterator_rewindToBegin;
            self->fnNext = (kit_Sequence_Iterator_Super_nextFn) kit_XorList_Iterator_next;
            self->fnSetLast = (kit_Sequence_Iterator_Super_setLastFn) kit_XorList_Iterator_setLast;
            self->fnIsModified = (kit_Sequence_Iterator_Super_isModifiedFn) kit_XorList_Iterator_isModified;
            self->fnDelete = (kit_Sequence_Iterator_Super_deleteFn) kit_XorList_Iterator_delete;
        } else {
            kit_Allocator_free(self);
            selfOption = None;
        }
    }

    return selfOption;
}

static Option kit_Sequence_Iterator_fromVector(struct kit_Vector *const container) {
    assert(container);
    struct kit_Sequence_Iterator *self;
    Option selfOption = kit_Allocator_calloc(1, sizeof(*self)), superOption;

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        superOption = kit_Vector_Iterator_fromBegin(container);
        if (Option_isSome(superOption)) {
            self->super = Option_unwrap(superOption);
            self->fnRewindToBegin = (kit_Sequence_Iterator_Super_rewindToBeginFn) kit_Vector_Iterator_rewindToBegin;
            self->fnNext = (kit_Sequence_Iterator_Super_nextFn) kit_Vector_Iterator_next;
            self->fnSetLast = (kit_Sequence_Iterator_Super_setLastFn) kit_Vector_Iterator_setLast;
            self->fnIsModified = (kit_Sequence_Iterator_Super_isModifiedFn) kit_Vector_Iterator_isModified;
            self->fnDelete = (kit_Sequence_Iterator_Super_deleteFn) kit_Vector_Iterator_delete;
        } else {
            kit_Allocator_free(self);
            selfOption = None;
        }
    }

    return selfOption;
}

Option kit_Sequence_Iterator_fromBegin(struct kit_Sequence *const container) {
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

void kit_Sequence_Iterator_rewindToBegin(struct kit_Sequence_Iterator *const self) {
    assert(self);
    self->fnRewindToBegin(self->super);
}

Result kit_Sequence_Iterator_next(struct kit_Sequence_Iterator *const self) {
    assert(self);
    return self->fnNext(self->super);
}

Result kit_Sequence_Iterator_setLast(struct kit_Sequence_Iterator *const self, void *const element) {
    assert(self);
    return self->fnSetLast(self->super, element);
}

bool kit_Sequence_Iterator_isModified(const struct kit_Sequence_Iterator *const self) {
    assert(self);
    return self->fnIsModified(self->super);
}

void kit_Sequence_Iterator_delete(struct kit_Sequence_Iterator *const self) {
    if (self) {
        self->fnDelete(self->super);
        kit_Allocator_free(self);
    }
}
