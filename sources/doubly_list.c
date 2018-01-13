/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 23, 2017 
 */

#include <assert.h>
#include <stdlib.h>
#include <kit/allocator/allocator.h>
#include <kit/collections/doubly_list.h>

struct kit_DoublyList_Node {
    void *element;
    struct kit_DoublyList_Node *prev;
    struct kit_DoublyList_Node *next;
};

static Option
kit_DoublyList_Node_new(void *e);

static void *
kit_DoublyList_Node_delete(struct kit_DoublyList_Node *self)
__attribute__((__nonnull__));

static ResultOf(struct kit_DoublyList_Node *, OutOfRangeError)
kit_DoublyList_Node_fetch(struct kit_DoublyList *list, size_t index)
__attribute__((__nonnull__));

struct kit_DoublyList {
    int operationId;
    size_t size;
    struct kit_DoublyList_Node *front;
    struct kit_DoublyList_Node *back;
};

Option kit_DoublyList_new(void) {
    struct kit_DoublyList *self;
    return kit_Allocator_calloc(1, sizeof(*self));
}

void kit_DoublyList_clear(struct kit_DoublyList *self) {
    assert(self);
    struct kit_DoublyList_Node *base = self->front;
    struct kit_DoublyList_Node *next = NULL;

    while (base) {
        next = base->next;
        kit_DoublyList_Node_delete(base);
        base = next;
    }

    self->size = 0;
    self->operationId += 1;
    self->back = self->front = NULL;
}

void kit_DoublyList_delete(struct kit_DoublyList *self) {
    if (self) {
        kit_DoublyList_clear(self);
        kit_Allocator_free(self);
    }
}

Result kit_DoublyList_insert(struct kit_DoublyList *const self, void *const e, const size_t index) {
    assert(self);
    Option newNodeOption;
    struct kit_DoublyList_Node *newNode = NULL;

    if (index > self->size) {
        return Result_error(&OutOfRangeError);
    }

    newNodeOption = kit_DoublyList_Node_new(e);
    if (Option_isNone(newNodeOption)) {
        return Result_error(&OutOfMemoryError);
    }
    newNode = Option_unwrap(newNodeOption);

    if (index == 0) {                           /* insert front */
        if (self->front) {                      /* non-empty list */
            self->front->prev = newNode;
            newNode->next = self->front;
            self->front = newNode;
        } else {                                /* empty list */
            self->front = self->back = newNode;
        }
    } else if (index == self->size) {           /* insert back */
        newNode->prev = self->back;
        self->back->next = newNode;
        self->back = newNode;
    } else {                                    /* insert middle */
        /* OutOfRangeError check at the begging */
        struct kit_DoublyList_Node *nextNode = Result_unwrap(kit_DoublyList_Node_fetch(self, index));
        newNode->next = nextNode;
        newNode->prev = nextNode->prev;
        nextNode->prev->next = newNode;
        nextNode->prev = newNode;
    }

    self->size += 1;
    self->operationId += 1;
    return Result_ok(e);
}

Result kit_DoublyList_pushBack(struct kit_DoublyList *self, void *e) {
    assert(self);
    return kit_DoublyList_insert(self, e, self->size);
}

Result kit_DoublyList_pushFront(struct kit_DoublyList *self, void *e) {
    assert(self);
    return kit_DoublyList_insert(self, e, 0);
}

Result kit_DoublyList_popBack(struct kit_DoublyList *self) {
    assert(self);
    const size_t size = self->size;
    return size > 0 ? kit_DoublyList_remove(self, size - 1) : Result_error(&OutOfRangeError);
}

Result kit_DoublyList_popFront(struct kit_DoublyList *self) {
    assert(self);
    return kit_DoublyList_remove(self, 0);
}

Result kit_DoublyList_remove(struct kit_DoublyList *self, const size_t index) {
    assert(self);
    Result result = kit_DoublyList_Node_fetch(self, index);

    if (Result_isOk(result)) {
        struct kit_DoublyList_Node *node = Result_unwrap(result);
        if (node->prev) {
            node->prev->next = node->next;
        } else {
            self->front = node->next;
        }
        if (node->next) {
            node->next->prev = node->prev;
        } else {
            self->back = node->prev;
        }
        self->size -= 1;
        self->operationId += 1;
        Result_ok(kit_DoublyList_Node_delete(node));
    }

    assert(&OutOfRangeError == Result_inspect(result));
    return result;
}

Result kit_DoublyList_set(struct kit_DoublyList *self, void *e, const size_t index) {
    assert(self);
    Result result = kit_DoublyList_Node_fetch(self, index);

    if (Result_isOk(result)) {
        struct kit_DoublyList_Node *node = Result_unwrap(result);
        void *oldElement = node->element;
        node->element = e;
        Result_ok(oldElement);
    }

    assert(&OutOfRangeError == Result_inspect(result));
    return result;
}

Result kit_DoublyList_get(struct kit_DoublyList *self, const size_t index) {
    assert(self);
    Result result = kit_DoublyList_Node_fetch(self, index);

    if (Result_isOk(result)) {
        struct kit_DoublyList_Node *node = Result_unwrap(result);
        Result_ok(node->element);
    }

    assert(&OutOfRangeError == Result_inspect(result));
    return result;
}

Result kit_DoublyList_back(struct kit_DoublyList *self) {
    assert(self);
    const size_t size = self->size;
    return size > 0 ? kit_DoublyList_get(self, size - 1) : Result_error(&OutOfRangeError);
}

Result kit_DoublyList_front(struct kit_DoublyList *self) {
    assert(self);
    return kit_DoublyList_get(self, 0);
}

size_t kit_DoublyList_size(struct kit_DoublyList *self) {
    assert(self);
    return self->size;
}

bool kit_DoublyList_isEmpty(struct kit_DoublyList *self) {
    assert(self);
    return 0 == self->size;
}

struct kit_DoublyList_Iterator {
    int operationId;
    struct kit_DoublyList *container;
    struct kit_DoublyList_Node *last;
    struct kit_DoublyList_Node *prev;
    struct kit_DoublyList_Node *next;
};

Option kit_DoublyList_Iterator_new(struct kit_DoublyList *container, enum kit_Bound bound) {
    assert(container);
    assert(KIT_BOUND_BEGIN <= bound && bound <= KIT_BOUND_END);
    struct kit_DoublyList_Iterator *self;
    Option selfOption = kit_Allocator_calloc(1, sizeof(*self));

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        self->container = container;
        kit_DoublyList_Iterator_rewind(self, bound);
    }

    return selfOption;
}

Option kit_DoublyList_Iterator_fromBegin(struct kit_DoublyList *container) {
    assert(container);
    return kit_DoublyList_Iterator_new(container, KIT_BOUND_BEGIN);
}

Option kit_DoublyList_Iterator_fromEnd(struct kit_DoublyList *container) {
    assert(container);
    return kit_DoublyList_Iterator_new(container, KIT_BOUND_END);
}

void kit_DoublyList_Iterator_rewind(struct kit_DoublyList_Iterator *self, enum kit_Bound bound) {
    assert(self);
    assert(self->container);
    assert(KIT_BOUND_BEGIN <= bound && bound <= KIT_BOUND_END);
    struct kit_DoublyList *container = self->container;

    self->operationId = container->operationId;
    self->last = NULL;
    if (KIT_BOUND_END == bound) {
        self->next = NULL;
        self->prev = container->back;
    } else {
        self->next = container->front;
        self->prev = NULL;
    }
}

void kit_DoublyList_Iterator_rewindToBegin(struct kit_DoublyList_Iterator *self) {
    assert(self);
    kit_DoublyList_Iterator_rewind(self, KIT_BOUND_BEGIN);
}

void kit_DoublyList_Iterator_rewindToEnd(struct kit_DoublyList_Iterator *self) {
    assert(self);
    kit_DoublyList_Iterator_rewind(self, KIT_BOUND_END);
}

void kit_DoublyList_Iterator_delete(struct kit_DoublyList_Iterator *self) {
    kit_Allocator_free(self);
}

Result kit_DoublyList_Iterator_next(struct kit_DoublyList_Iterator *self) {
    assert(self);

    if (kit_DoublyList_Iterator_isModified(self)) {
        return Result_error(&ConcurrentModificationError);
    } else if (self->next) {
        void *nextElement = self->next->element;
        self->last = self->prev = self->next;
        self->next = self->next->next;
        return Result_ok(nextElement);
    } else {
        return Result_error(&OutOfRangeError);
    }
}

Result kit_DoublyList_Iterator_previous(struct kit_DoublyList_Iterator *self) {
    assert(self);

    if (kit_DoublyList_Iterator_isModified(self)) {
        return Result_error(&ConcurrentModificationError);
    } else if (self->prev) {
        void *previousElement = self->prev->element;
        self->last = self->next = self->prev;
        self->prev = self->prev->prev;
        return Result_ok(previousElement);
    } else {
        return Result_error(&OutOfRangeError);
    }
}

Result kit_DoublyList_Iterator_setLast(struct kit_DoublyList_Iterator *self, void *e) {
    assert(self);

    if (kit_DoublyList_Iterator_isModified(self)) {
        return Result_error(&ConcurrentModificationError);
    } else if (self->last) {
        void *lastElement = self->last->element;
        self->last->element = e;
        return Result_ok(lastElement);
    } else {
        return Result_error(&IllegalStateError);
    }
}

bool kit_DoublyList_Iterator_isModified(struct kit_DoublyList_Iterator *self) {
    assert(self);
    struct kit_DoublyList *container = self->container;
    return NULL == container || self->operationId != container->operationId;
}

/*
 * Internals
 */
Option kit_DoublyList_Node_new(void *e) {
    struct kit_DoublyList_Node *self;
    Option selfOption = kit_Allocator_calloc(1, sizeof(*self));

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        self->element = e;
    }

    return selfOption;
}

void *kit_DoublyList_Node_delete(struct kit_DoublyList_Node *self) {
    assert(self);
    void *e = self->element;
    kit_Allocator_free(self);
    return e;
}

Result kit_DoublyList_Node_fetch(struct kit_DoublyList *list, const size_t index) {
    assert(list);
    struct kit_DoublyList_Node *node;

    if (index >= list->size) {
        return Result_error(&OutOfRangeError);
    }

    if (index < list->size / 2) {
        node = list->front;
        for (size_t i = 0; i < index; i++) {
            node = node->next;
        }
    } else {
        node = list->back;
        for (size_t i = list->size - 1; i > index; i--) {
            node = node->prev;
        }
    }

    return Result_ok(node);
}
