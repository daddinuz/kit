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
#include <kit/collections/singly_list.h>

#define _(x)            ((void) ((x) ? 1 : 0));

struct kit_SinglyList_Node {
    void *element;
    struct kit_SinglyList_Node *next;
};

static OptionOf(struct kit_SinglyList_Node *)
kit_SinglyList_Node_new(void *element)
__attribute__((__warn_unused_result__));

static ResultOf(struct kit_SinglyList_Node *, OutOfRangeError)
kit_SinglyList_Node_fetch(const struct kit_SinglyList *list, size_t index)
__attribute__((__warn_unused_result__, __nonnull__));

static void *
kit_SinglyList_Node_delete(struct kit_SinglyList_Node *self)
__attribute__((__warn_unused_result__, __nonnull__));

struct kit_SinglyList {
    int operationId;
    size_t size;
    struct kit_SinglyList_Node *front;
    struct kit_SinglyList_Node *back;
};

OptionOf(struct kit_SinglyList *)
kit_SinglyList_new(void) {
    struct kit_SinglyList *self;
    return kit_Allocator_calloc(1, sizeof(*self));
}

OneOf(Ok, OutOfRangeError, OutOfMemoryError)
kit_SinglyList_insert(struct kit_SinglyList *const self, const size_t index, void *element) {
    assert(self);
    Option newNodeOption;
    struct kit_SinglyList_Node *newNode = NULL;

    if (index > self->size) {
        return OutOfRangeError;
    }

    newNodeOption = kit_SinglyList_Node_new(element);
    if (Option_isNone(newNodeOption)) {
        return OutOfMemoryError;
    }
    newNode = Option_unwrap(newNodeOption);

    if (index == 0) {                           /* insert front */
        if (self->front) {                      /* non-empty list */
            struct kit_SinglyList_Node *oldFront = self->front;
            self->front = newNode;
            self->front->next = oldFront;
        } else {                                /* empty list */
            self->front = self->back = newNode;
        }
    } else if (index == self->size) {           /* insert back */
        self->back->next = newNode;
        self->back = newNode;
    } else {                                    /* insert middle */
        /* OutOfRangeError check at the beginning */
        struct kit_SinglyList_Node *leftNode = Result_unwrap(kit_SinglyList_Node_fetch(self, index - 1));
        struct kit_SinglyList_Node *middleNode = leftNode->next;
        newNode->next = middleNode;
        leftNode->next = newNode;
    }

    self->size += 1;
    self->operationId += 1;
    return Ok;
}

OneOf(Ok, OutOfMemoryError)
kit_SinglyList_pushBack(struct kit_SinglyList *const self, void *const element) {
    assert(self);
    return kit_SinglyList_insert(self, self->size, element);
}

OneOf(Ok, OutOfMemoryError)
kit_SinglyList_pushFront(struct kit_SinglyList *const self, void *const element) {
    assert(self);
    return kit_SinglyList_insert(self, 0, element);
}

ResultOf(void *, OutOfRangeError)
kit_SinglyList_remove(struct kit_SinglyList *const self, const size_t index) {
    assert(self);
    struct kit_SinglyList_Node *leftNode, *middleNode;

    if (index >= self->size) {
        return Result_error(OutOfRangeError);
    }

    if (index > 0) {
        Result result = kit_SinglyList_Node_fetch(self, index - 1);

        leftNode = Result_unwrap(result);
        middleNode = leftNode->next;

        leftNode->next = middleNode->next;
    } else {
        leftNode = NULL;
        middleNode = self->front;

        self->front = middleNode->next;
    }

    if (NULL == middleNode->next) {
        self->back = leftNode;
    }

    self->size -= 1;
    self->operationId += 1;
    return Result_ok(kit_SinglyList_Node_delete(middleNode));
}

ResultOf(void *, OutOfRangeError)
kit_SinglyList_popBack(struct kit_SinglyList *const self) {
    assert(self);
    const size_t size = self->size;
    return size > 0 ? kit_SinglyList_remove(self, size - 1) : Result_error(OutOfRangeError);
}

ResultOf(void *, OutOfRangeError)
kit_SinglyList_popFront(struct kit_SinglyList *const self) {
    assert(self);
    return kit_SinglyList_remove(self, 0);
}

ResultOf(void *, OutOfRangeError)
kit_SinglyList_put(struct kit_SinglyList *const self, const size_t index, void *const element) {
    assert(self);
    Result result = kit_SinglyList_Node_fetch(self, index);

    if (Result_isOk(result)) {
        struct kit_SinglyList_Node *node = Result_unwrap(result);
        void *replacedElement = node->element;
        node->element = element;
        return Result_ok(replacedElement);
    } else {
        assert(OutOfRangeError == Result_inspect(result));
        return Result_error(OutOfRangeError);
    }
}

ResultOf(void *, OutOfRangeError)
kit_SinglyList_get(const struct kit_SinglyList *const self, const size_t index) {
    assert(self);
    Result result = kit_SinglyList_Node_fetch(self, index);

    if (Result_isOk(result)) {
        struct kit_SinglyList_Node *node = Result_unwrap(result);
        return Result_ok(node->element);
    } else {
        assert(OutOfRangeError == Result_inspect(result));
        return Result_error(OutOfRangeError);
    }
}

ResultOf(void *, OutOfRangeError)
kit_SinglyList_back(const struct kit_SinglyList *const self) {
    assert(self);
    const size_t size = self->size;
    return size > 0 ? kit_SinglyList_get(self, size - 1) : Result_error(OutOfRangeError);
}

ResultOf(void *, OutOfRangeError)
kit_SinglyList_front(const struct kit_SinglyList *const self) {
    assert(self);
    return kit_SinglyList_get(self, 0);
}

void
kit_SinglyList_clear(struct kit_SinglyList *const self) {
    assert(self);

    for (size_t i = self->size; i > 0; i--) {
        _(Result_unwrap(kit_SinglyList_popFront(self)));
    }

    self->operationId += 1;
}

size_t
kit_SinglyList_size(const struct kit_SinglyList *const self) {
    assert(self);
    return self->size;
}

bool
kit_SinglyList_isEmpty(const struct kit_SinglyList *const self) {
    assert(self);
    return 0 == self->size;
}

void kit_SinglyList_delete(struct kit_SinglyList *self) {
    if (self) {
        kit_SinglyList_clear(self);
        kit_Allocator_free(self);
    }
}

struct kit_SinglyList_Iterator {
    int operationId;
    struct kit_SinglyList *container;
    struct kit_SinglyList_Node *last;
    struct kit_SinglyList_Node *next;
};

OptionOf(struct kit_SinglyList_Iterator *)
kit_SinglyList_Iterator_fromBegin(struct kit_SinglyList *const container) {
    assert(container);
    struct kit_SinglyList_Iterator *self;
    Option selfOption = kit_Allocator_calloc(1, sizeof(*self));

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        self->container = container;
        kit_SinglyList_Iterator_rewindToBegin(self);
    }

    return selfOption;
}

void
kit_SinglyList_Iterator_rewindToBegin(struct kit_SinglyList_Iterator *const self) {
    assert(self);
    assert(self->container);
    struct kit_SinglyList *container = self->container;

    self->operationId = container->operationId;
    self->last = NULL;
    self->next = container->front;
}

ResultOf(void *, OutOfRangeError, ConcurrentModificationError)
kit_SinglyList_Iterator_next(struct kit_SinglyList_Iterator *const self) {
    assert(self);

    if (kit_SinglyList_Iterator_isModified(self)) {
        return Result_error(ConcurrentModificationError);
    } else if (self->next) {
        void *nextElement = self->next->element;
        self->last = self->next;
        self->next = self->next->next;
        return Result_ok(nextElement);
    } else {
        return Result_error(OutOfRangeError);
    }
}

ResultOf(void *, IllegalStateError, ConcurrentModificationError)
kit_SinglyList_Iterator_setLast(struct kit_SinglyList_Iterator *const self, void *const element) {
    assert(self);

    if (kit_SinglyList_Iterator_isModified(self)) {
        return Result_error(ConcurrentModificationError);
    } else if (self->last) {
        void *replacedElement = self->last->element;
        self->last->element = element;
        return Result_ok(replacedElement);
    } else {
        return Result_error(IllegalStateError);
    }
}

bool
kit_SinglyList_Iterator_isModified(const struct kit_SinglyList_Iterator *const self) {
    assert(self);
    struct kit_SinglyList *container = self->container;
    return NULL == container || self->operationId != container->operationId;
}

void kit_SinglyList_Iterator_delete(struct kit_SinglyList_Iterator *self) {
    if (self) {
        kit_Allocator_free(self);
    }
}

/*
 * Internals
 */
OptionOf(struct kit_SinglyList_Node *)
kit_SinglyList_Node_new(void *element) {
    struct kit_SinglyList_Node *self;
    Option selfOption = kit_Allocator_calloc(1, sizeof(*self));

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        self->element = element;
    }

    return selfOption;
}

ResultOf(struct kit_SinglyList_Node *, OutOfRangeError)
kit_SinglyList_Node_fetch(const struct kit_SinglyList *const list, const size_t index) {
    assert(list);

    if (index < list->size) {
        struct kit_SinglyList_Node *node = list->front;
        for (size_t i = 0; i < index; i += 1) {
            node = node->next;
        }
        return Result_ok(node);
    } else {
        return Result_error(OutOfRangeError);
    }
}

void *
kit_SinglyList_Node_delete(struct kit_SinglyList_Node *self) {
    assert(self);
    void *e = self->element;
    kit_Allocator_free(self);
    return e;
}
