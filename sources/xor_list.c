/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   January 18, 2018
 */

#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <kit/allocator/allocator.h>
#include <kit/collections/xor_list.h>

#define _(x)            ((void) ((x) ? 1 : 0));

struct kit_XorList_Node {
    void *element;
    struct kit_XorList_Node *link;
};

static OptionOf(struct kit_XorList_Node *)
kit_XorList_Node_new(void *element)
__attribute__((__warn_unused_result__));

static struct kit_XorList_Node *
kit_XorList_Node_xor(const struct kit_XorList_Node *p1, const struct kit_XorList_Node *p2)
__attribute__((__warn_unused_result__));

static void *
kit_XorList_Node_delete(struct kit_XorList_Node *self)
__attribute__((__warn_unused_result__, __nonnull__));

struct kit_XorList_Node_Pair {
    struct kit_XorList_Node *prev;
    struct kit_XorList_Node *base;
};

/**
 * @attention
 *  Always check for result status, do never use out without checking!!!
 */
static ResultOf(struct kit_XorList_Node_Pair *, OutOfRangeError)
kit_XorList_Node_Pair_fetch(const struct kit_XorList *list, size_t index, struct kit_XorList_Node_Pair *out)
__attribute__((__warn_unused_result__, __nonnull__));

struct kit_XorList {
    int operationId;
    size_t size;
    struct kit_XorList_Node *front;
    struct kit_XorList_Node *back;
};

OptionOf(struct kit_XorList *)
kit_XorList_new(void) {
    struct kit_XorList *self;
    return kit_Allocator_calloc(1, sizeof(*self));
}

OneOf(Ok, OutOfRangeError, OutOfMemoryError)
kit_XorList_insert(struct kit_XorList *const self, const size_t index, void *const element) {
    assert(self);
    /*
     * A <-> B <-> C
     *   A <-X-> C
     *
     * X = A xor C
     * A = X xor C
     * C = X xor A
     */
    Option newNodeOption;
    struct kit_XorList_Node *newNode = NULL;

    if (index > self->size) {
        return OutOfRangeError;
    }

    newNodeOption = kit_XorList_Node_new(element);
    if (Option_isNone(newNodeOption)) {
        return OutOfMemoryError;
    }
    newNode = Option_unwrap(newNodeOption);

    if (index == 0) {                           /* insert front */
        if (self->front) {                      /* non-empty list */
            newNode->link = self->front;
            self->front->link = kit_XorList_Node_xor(self->front->link, newNode);
            self->front = newNode;
        } else {                                /* empty list */
            self->front = self->back = newNode;
        }
    } else if (index == self->size) {           /* insert back */
        newNode->link = self->back;
        self->back->link = kit_XorList_Node_xor(self->back->link, newNode);
        self->back = newNode;
    } else {                                    /* insert middle */
        /* OutOfRangeError check at the beginning */
        struct kit_XorList_Node_Pair pair = {.prev=NULL, .base=NULL};
        assert(Result_isOk(kit_XorList_Node_Pair_fetch(self, index, &pair)));
        struct kit_XorList_Node *nextNode = pair.base;
        struct kit_XorList_Node *prevNode = pair.prev;
        prevNode->link = kit_XorList_Node_xor(kit_XorList_Node_xor(nextNode, prevNode->link), newNode);
        newNode->link = kit_XorList_Node_xor(prevNode, nextNode);
        nextNode->link = kit_XorList_Node_xor(kit_XorList_Node_xor(prevNode, nextNode->link), newNode);
    }

    self->size += 1;
    self->operationId += 1;
    return Ok;
}

OneOf(Ok, OutOfMemoryError)
kit_XorList_pushBack(struct kit_XorList *const self, void *const element) {
    assert(self);
    return kit_XorList_insert(self, self->size, element);
}

OneOf(Ok, OutOfMemoryError)
kit_XorList_pushFront(struct kit_XorList *const self, void *const element) {
    assert(self);
    return kit_XorList_insert(self, 0, element);
}

ResultOf(void *, OutOfRangeError)
kit_XorList_remove(struct kit_XorList *const self, const size_t index) {
    assert(self);
    struct kit_XorList_Node_Pair pair = {.prev=NULL, .base=NULL};
    Result result = kit_XorList_Node_Pair_fetch(self, index, &pair);

    if (Result_isOk(result)) {
        struct kit_XorList_Node *prev = pair.prev;
        struct kit_XorList_Node *node = pair.base;
        struct kit_XorList_Node *next = kit_XorList_Node_xor(prev, node->link);
        if (prev) {
            prev->link = kit_XorList_Node_xor(kit_XorList_Node_xor(prev->link, node), next);
        } else {
            self->front = next;
        }
        if (next) {
            next->link = kit_XorList_Node_xor(kit_XorList_Node_xor(next->link, node), prev);
        } else {
            self->back = prev;
        }
        self->size -= 1;
        self->operationId += 1;
        return Result_ok(kit_XorList_Node_delete(node));
    } else {
        assert(OutOfRangeError == Result_inspect(result));
        return Result_error(OutOfRangeError);
    }
}

ResultOf(void *, OutOfRangeError)
kit_XorList_popBack(struct kit_XorList *const self) {
    assert(self);
    const size_t size = self->size;
    return size > 0 ? kit_XorList_remove(self, size - 1) : Result_error(OutOfRangeError);
}

ResultOf(void *, OutOfRangeError)
kit_XorList_popFront(struct kit_XorList *const self) {
    assert(self);
    return kit_XorList_remove(self, 0);
}

ResultOf(void *, OutOfRangeError)
kit_XorList_put(struct kit_XorList *const self, const size_t index, void *const element) {
    assert(self);
    struct kit_XorList_Node_Pair pair = {.prev=NULL, .base=NULL};
    Result result = kit_XorList_Node_Pair_fetch(self, index, &pair);

    if (Result_isOk(result)) {
        void *replacedElement = pair.base->element;
        pair.base->element = element;
        return Result_ok(replacedElement);
    } else {
        assert(OutOfRangeError == Result_inspect(result));
        return Result_error(OutOfRangeError);
    }
}

ResultOf(void *, OutOfRangeError)
kit_XorList_get(const struct kit_XorList *const self, const size_t index) {
    assert(self);
    struct kit_XorList_Node_Pair pair = {.prev=NULL, .base=NULL};
    Result result = kit_XorList_Node_Pair_fetch(self, index, &pair);

    if (Result_isOk(result)) {
        return Result_ok(pair.base->element);
    } else {
        assert(OutOfRangeError == Result_inspect(result));
        return Result_error(OutOfRangeError);
    }
}

ResultOf(void *, OutOfRangeError)
kit_XorList_back(const struct kit_XorList *const self) {
    assert(self);
    const size_t size = self->size;
    return size > 0 ? kit_XorList_get(self, size - 1) : Result_error(OutOfRangeError);
}

ResultOf(void *, OutOfRangeError)
kit_XorList_front(const struct kit_XorList *const self) {
    assert(self);
    return kit_XorList_get(self, 0);
}

void
kit_XorList_clear(struct kit_XorList *const self) {
    assert(self);

    for (size_t i = self->size; i > 0; i--) {
        _(Result_unwrap(kit_XorList_popFront(self)));
    }

    self->operationId += 1;
}

size_t
kit_XorList_size(const struct kit_XorList *const self) {
    assert(self);
    return self->size;
}

bool
kit_XorList_isEmpty(const struct kit_XorList *const self) {
    assert(self);
    return 0 == self->size;
}

void kit_XorList_delete(struct kit_XorList *self) {
    if (self) {
        kit_XorList_clear(self);
        kit_Allocator_free(self);
    }
}

struct kit_XorList_Iterator {
    int operationId;
    struct kit_XorList *container;
    struct kit_XorList_Node *left;
    struct kit_XorList_Node *middle;
    struct kit_XorList_Node *right;
    struct kit_XorList_Node *last;
    struct kit_XorList_Node *prev;
    struct kit_XorList_Node *next;
};

OptionOf(struct kit_XorList_Iterator *)
kit_XorList_Iterator_new(struct kit_XorList *const container, const enum kit_Bound bound) {
    assert(container);
    assert(KIT_BOUND_BEGIN <= bound && bound <= KIT_BOUND_END);
    struct kit_XorList_Iterator *self;
    Option selfOption = kit_Allocator_calloc(1, sizeof(*self));

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        self->container = container;
        kit_XorList_Iterator_rewind(self, bound);
    }

    return selfOption;
}

OptionOf(struct kit_XorList_Iterator *)
kit_XorList_Iterator_fromBegin(struct kit_XorList *const container) {
    assert(container);
    return kit_XorList_Iterator_new(container, KIT_BOUND_BEGIN);
}

OptionOf(struct kit_XorList_Iterator *)
kit_XorList_Iterator_fromEnd(struct kit_XorList *const container) {
    assert(container);
    return kit_XorList_Iterator_new(container, KIT_BOUND_END);
}

void
kit_XorList_Iterator_rewind(struct kit_XorList_Iterator *const self, const enum kit_Bound bound) {
    assert(self);
    assert(self->container);
    assert(KIT_BOUND_BEGIN <= bound && bound <= KIT_BOUND_END);
    struct kit_XorList *container = self->container;

    self->operationId = container->operationId;
    if (KIT_BOUND_END == bound) {
        self->next = self->last = self->right = NULL;
        self->prev = self->middle = container->back;
        self->left = self->middle ? kit_XorList_Node_xor(self->middle->link, self->right) : NULL;
    } else {
        self->prev = self->last = self->left = NULL;
        self->next = self->middle = container->front;
        self->right = self->middle ? kit_XorList_Node_xor(self->left, self->middle->link) : NULL;
    }
}

void
kit_XorList_Iterator_rewindToBegin(struct kit_XorList_Iterator *const self) {
    assert(self);
    kit_XorList_Iterator_rewind(self, KIT_BOUND_BEGIN);
}

void
kit_XorList_Iterator_rewindToEnd(struct kit_XorList_Iterator *const self) {
    assert(self);
    kit_XorList_Iterator_rewind(self, KIT_BOUND_END);
}

ResultOf(void *, OutOfRangeError, ConcurrentModificationError)
kit_XorList_Iterator_next(struct kit_XorList_Iterator *const self) {
    assert(self);

    if (kit_XorList_Iterator_isModified(self)) {
        return Result_error(ConcurrentModificationError);
    } else if (self->next) {
        void *nextElement = self->next->element;
        self->last = self->prev = self->next;
        if (self->right) {
            self->left = self->middle;
            self->middle = self->right;
            self->right = (self->middle) ? kit_XorList_Node_xor(self->left, self->middle->link) : NULL;
            self->next = self->middle;
        } else {
            self->next = NULL;
        }
        return Result_ok(nextElement);
    } else {
        return Result_error(OutOfRangeError);
    }
}

ResultOf(void *, OutOfRangeError, ConcurrentModificationError)
kit_XorList_Iterator_previous(struct kit_XorList_Iterator *const self) {
    assert(self);

    if (kit_XorList_Iterator_isModified(self)) {
        return Result_error(ConcurrentModificationError);
    } else if (self->prev) {
        void *previousElement = self->prev->element;
        self->last = self->next = self->prev;
        if (self->left) {
            self->right = self->middle;
            self->middle = self->left;
            self->left = (self->middle) ? kit_XorList_Node_xor(self->middle->link, self->right) : NULL;
            self->prev = self->middle;
        } else {
            self->prev = NULL;
        }
        return Result_ok(previousElement);
    } else {
        return Result_error(OutOfRangeError);
    }
}

ResultOf(void *, IllegalStateError, ConcurrentModificationError)
kit_XorList_Iterator_setLast(struct kit_XorList_Iterator *const self, void *const element) {
    assert(self);

    if (kit_XorList_Iterator_isModified(self)) {
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
kit_XorList_Iterator_isModified(const struct kit_XorList_Iterator *const self) {
    assert(self);
    struct kit_XorList *container = self->container;
    return NULL == container || self->operationId != container->operationId;
}

void
kit_XorList_Iterator_delete(struct kit_XorList_Iterator *self) {
    if (self) {
        kit_Allocator_free(self);
    }
}

/*
 * Internals
 */
OptionOf(struct kit_XorList_Node *)
kit_XorList_Node_new(void *const element) {
    struct kit_XorList_Node *self;
    Option selfOption = kit_Allocator_calloc(1, sizeof(*self));

    if (Option_isSome(selfOption)) {
        self = Option_unwrap(selfOption);
        self->element = element;
    }

    return selfOption;
}

struct kit_XorList_Node *
kit_XorList_Node_xor(const struct kit_XorList_Node *const p1, const struct kit_XorList_Node *const p2) {
    return ((struct kit_XorList_Node *) ((intptr_t) p1 ^ (intptr_t) p2));
}

void *
kit_XorList_Node_delete(struct kit_XorList_Node *self) {
    assert(self);
    void *e = self->element;
    kit_Allocator_free(self);
    return e;
}

ResultOf(struct kit_XorList_Node_Pair *, OutOfRangeError)
kit_XorList_Node_Pair_fetch(
        const struct kit_XorList *const list, const size_t index, struct kit_XorList_Node_Pair *out
) {
    assert(list);

    if (index >= list->size) {
        return Result_error(OutOfRangeError);
    }

    const bool isFrontCloser = index < list->size / 2;
    struct kit_XorList_Node *tmp = NULL, *previousNode = NULL, *node = NULL;

    if (isFrontCloser) {
        node = list->front;
        for (size_t i = 0; i < index; i++) {
            tmp = node;
            node = kit_XorList_Node_xor(previousNode, node->link);
            previousNode = tmp;
        }
    } else {
        node = list->back;
        for (size_t i = list->size - 1; i > index; i--) {
            tmp = node;
            node = kit_XorList_Node_xor(previousNode, node->link);
            previousNode = tmp;
        }
    }

    out->prev = isFrontCloser ? previousNode : kit_XorList_Node_xor(node->link, previousNode);
    out->base = node;
    return Result_ok(out);
}
