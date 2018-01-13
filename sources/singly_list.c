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
#include <kit/collections/singly_list.h>

struct kit_SinglyList_Node {
    void *element;
    struct kit_SinglyList_Node *next;
};

static OptionOf(struct kit_SinglyList_Node *)
kit_SinglyList_Node_new(void *e);

static void *
kit_SinglyList_Node_delete(struct kit_SinglyList_Node *self)
__attribute__((__nonnull__));

static ResultOf(struct kit_SinglyList_Node *, OutOfRangeError)
kit_SinglyList_Node_fetch(struct kit_SinglyList *list, size_t index)
__attribute__((__nonnull__));

struct kit_SinglyList {
    int operationId;
    size_t size;
    struct kit_SinglyList_Node *front;
    struct kit_SinglyList_Node *back;
};

Option kit_SinglyList_new(void) {
    struct kit_SinglyList *self;
    return kit_Allocator_calloc(1, sizeof(*self));
}

void kit_SinglyList_clear(struct kit_SinglyList *self) {
    assert(self);
    struct kit_SinglyList_Node *leftNode = NULL, *middleNode = self->front;

    while (middleNode) {
        leftNode = middleNode;
        middleNode = middleNode->next;
        kit_SinglyList_Node_delete(leftNode);
    }

    self->size = 0;
    self->back = NULL;
    self->front = NULL;
    self->operationId += 1;
}

void kit_SinglyList_delete(struct kit_SinglyList *self) {
    if (self) {
        kit_SinglyList_clear(self);
        kit_Allocator_free(self);
    }
}

Result kit_SinglyList_insert(struct kit_SinglyList *self, void *e, const size_t index) {
    assert(self);
    Option newNodeOption;
    struct kit_SinglyList_Node *newNode = NULL;

    if (index > self->size) {
        return Result_error(&OutOfRangeError);
    }

    newNodeOption = kit_SinglyList_Node_new(e);
    if (Option_isNone(newNodeOption)) {
        return Result_error(&OutOfMemoryError);
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
    return Result_ok(newNode);
}

Result kit_SinglyList_pushBack(struct kit_SinglyList *self, void *e) {
    assert(self);
    return kit_SinglyList_insert(self, e, self->size);
}

Result kit_SinglyList_pushFront(struct kit_SinglyList *self, void *e) {
    assert(self);
    return kit_SinglyList_insert(self, e, 0);
}

Result kit_SinglyList_popBack(struct kit_SinglyList *self) {
    assert(self);
    const size_t size = self->size;
    return size > 0 ? kit_SinglyList_remove(self, size - 1) : Result_error(&OutOfRangeError);
}

Result kit_SinglyList_popFront(struct kit_SinglyList *self) {
    assert(self);
    return kit_SinglyList_remove(self, 0);
}

Result kit_SinglyList_remove(struct kit_SinglyList *self, const size_t index) {
    assert(self);
    struct kit_SinglyList_Node *leftNode, *middleNode;

    if (index >= self->size) {
        return Result_error(&OutOfRangeError);
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

Result kit_SinglyList_set(struct kit_SinglyList *self, void *e, const size_t index) {
    assert(self);
    Result result = kit_SinglyList_Node_fetch(self, index);

    if (Result_isOk(result)) {
        struct kit_SinglyList_Node *node = Result_unwrap(result);
        void *oldElement = node->element;
        node->element = e;
        return Result_ok(oldElement);
    }

    assert(&OutOfRangeError == Result_inspect(result));
    return result;
}

Result kit_SinglyList_get(struct kit_SinglyList *self, const size_t index) {
    assert(self);
    Result result = kit_SinglyList_Node_fetch(self, index);

    if (Result_isOk(result)) {
        struct kit_SinglyList_Node *node = Result_unwrap(result);
        Result_ok(node->element);
    }

    assert(&OutOfRangeError == Result_inspect(result));
    return result;
}

Result kit_SinglyList_back(struct kit_SinglyList *self) {
    assert(self);
    const size_t size = self->size;
    return size > 0 ? kit_SinglyList_get(self, size - 1) : Result_error(&OutOfRangeError);
}

Result kit_SinglyList_front(struct kit_SinglyList *self) {
    assert(self);
    return kit_SinglyList_get(self, 0);
}

size_t kit_SinglyList_size(struct kit_SinglyList *self) {
    assert(self);
    return self->size;
}

bool kit_SinglyList_isEmpty(struct kit_SinglyList *self) {
    assert(self);
    return 0 == self->size;
}

struct kit_SinglyList_Iterator {
    int operationId;
    struct kit_SinglyList *container;
    struct kit_SinglyList_Node *last;
    struct kit_SinglyList_Node *next;
};

Option kit_SinglyList_Iterator_fromBegin(struct kit_SinglyList *container) {
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

void kit_SinglyList_Iterator_rewindToBegin(struct kit_SinglyList_Iterator *self) {
    assert(self);
    assert(self->container);
    struct kit_SinglyList *container = self->container;

    self->operationId = container->operationId;
    self->last = NULL;
    self->next = container->front;
}

void kit_SinglyList_Iterator_delete(struct kit_SinglyList_Iterator *self) {
    kit_Allocator_free(self);
}

Result kit_SinglyList_Iterator_next(struct kit_SinglyList_Iterator *self) {
    assert(self);

    if (kit_SinglyList_Iterator_isModified(self)) {
        return Result_error(&ConcurrentModificationError);
    } else if (self->next) {
        void *nextElement = self->next->element;
        self->last = self->next;
        self->next = self->next->next;
        return Result_ok(nextElement);
    } else {
        return Result_error(&OutOfRangeError);
    }
}

Result kit_SinglyList_Iterator_setLast(struct kit_SinglyList_Iterator *self, void *e) {
    assert(self);

    if (kit_SinglyList_Iterator_isModified(self)) {
        return Result_error(&ConcurrentModificationError);
    } else if (self->last) {
        void *lastElement = self->last->element;
        self->last->element = e;
        return Result_ok(lastElement);
    } else {
        return Result_error(&IllegalStateError);
    }
}

bool kit_SinglyList_Iterator_isModified(struct kit_SinglyList_Iterator *self) {
    assert(self);
    struct kit_SinglyList *container = self->container;
    return NULL == container || self->operationId != container->operationId;
}

/*
 * Internals
 */
Option kit_SinglyList_Node_new(void *e) {
    struct kit_SinglyList_Node *self;
    Option selfOption = kit_Allocator_calloc(1, sizeof(*self));

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        self->element = e;
    }

    return selfOption;
}

void *kit_SinglyList_Node_delete(struct kit_SinglyList_Node *self) {
    assert(self);
    void *e = self->element;
    kit_Allocator_free(self);
    return e;
}

Result kit_SinglyList_Node_fetch(struct kit_SinglyList *list, const size_t index) {
    assert(list);

    if (index < list->size) {
        struct kit_SinglyList_Node *node = list->front;
        for (size_t i = 0; i < index; i += 1) {
            node = node->next;
        }
        return Result_ok(node);
    } else {
        return Result_error(&OutOfRangeError);
    }
}
