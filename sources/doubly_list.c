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

/*
 * Private
 */
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

static enum kit_Result
kit_DoublyList_Node_fetch(struct kit_DoublyList *list, struct kit_DoublyList_Node **out, size_t index)
__attribute__((__nonnull__));

/*
 * Public
 */
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

enum kit_Result kit_DoublyList_insert(struct kit_DoublyList *self, void *e, const size_t index) {
    assert(self);
    Option nodeOption;
    struct kit_DoublyList_Node *newNode;
    enum kit_Result result = KIT_RESULT_OK;

    if (index == 0) {                           /* insert front */
        nodeOption = kit_DoublyList_Node_new(e);
        if (Option_isSome(nodeOption)) {
            newNode = Option_unwrap(nodeOption);
            if (self->front) {                  /* non-empty list */
                self->front->prev = newNode;
                newNode->next = self->front;
                self->front = newNode;
            } else {                            /* empty list */
                self->front = self->back = newNode;
            }
        } else {
            result = KIT_RESULT_OUT_OF_MEMORY_ERROR;
        }
    } else if (index == self->size) {           /* insert back */
        nodeOption = kit_DoublyList_Node_new(e);
        if (Option_isSome(nodeOption)) {
            newNode = Option_unwrap(nodeOption);
            newNode->prev = self->back;
            self->back->next = newNode;
            self->back = newNode;
        } else {
            result = KIT_RESULT_OUT_OF_MEMORY_ERROR;
        }
    } else {                                    /* insert middle */
        nodeOption = kit_DoublyList_Node_new(e);
        if (Option_isSome(nodeOption)) {
            newNode = Option_unwrap(nodeOption);
            struct kit_DoublyList_Node *nextNode = NULL;
            result = kit_DoublyList_Node_fetch(self, &nextNode, index);
            if (KIT_RESULT_OK == result) {
                assert(nextNode);
                newNode->next = nextNode;
                newNode->prev = nextNode->prev;
                nextNode->prev->next = newNode;
                nextNode->prev = newNode;
            }
        } else {
            result = KIT_RESULT_OUT_OF_MEMORY_ERROR;
        }
    }

    if (KIT_RESULT_OK == result) {
        self->size += 1;
        self->operationId += 1;
    }

    return result;
}

enum kit_Result kit_DoublyList_pushBack(struct kit_DoublyList *self, void *e) {
    assert(self);
    return kit_DoublyList_insert(self, e, self->size);
}

enum kit_Result kit_DoublyList_pushFront(struct kit_DoublyList *self, void *e) {
    assert(self);
    return kit_DoublyList_insert(self, e, 0);
}

enum kit_Result kit_DoublyList_popBack(struct kit_DoublyList *self, void **out) {
    assert(self);
    assert(out);
    const size_t size = self->size;
    return size > 0 ? kit_DoublyList_remove(self, out, size - 1) : KIT_RESULT_OUT_OF_RANGE_ERROR;
}

enum kit_Result kit_DoublyList_popFront(struct kit_DoublyList *self, void **out) {
    assert(self);
    assert(out);
    return kit_DoublyList_remove(self, out, 0);
}

enum kit_Result kit_DoublyList_remove(struct kit_DoublyList *self, void **out, const size_t index) {
    assert(self);
    assert(out);
    struct kit_DoublyList_Node *node = NULL;
    enum kit_Result result = kit_DoublyList_Node_fetch(self, &node, index);

    if (KIT_RESULT_OK == result) {
        assert(node);
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
        *out = kit_DoublyList_Node_delete(node);
    }

    return result;
}

enum kit_Result kit_DoublyList_set(struct kit_DoublyList *self, void *e, const size_t index) {
    assert(self);
    struct kit_DoublyList_Node *node = NULL;
    const enum kit_Result result = kit_DoublyList_Node_fetch(self, &node, index);

    if (KIT_RESULT_OK == result) {
        assert(node);
        node->element = e;
    }

    return result;
}

enum kit_Result kit_DoublyList_get(struct kit_DoublyList *self, void **out, const size_t index) {
    assert(self);
    assert(out);
    struct kit_DoublyList_Node *node = NULL;
    const enum kit_Result result = kit_DoublyList_Node_fetch(self, &node, index);

    if (KIT_RESULT_OK == result) {
        assert(node);
        *out = node->element;
    }

    return result;
}

enum kit_Result kit_DoublyList_back(struct kit_DoublyList *self, void **out) {
    assert(self);
    assert(out);
    const size_t size = self->size;
    return size > 0 ? kit_DoublyList_get(self, out, size - 1) : KIT_RESULT_OUT_OF_RANGE_ERROR;
}

enum kit_Result kit_DoublyList_front(struct kit_DoublyList *self, void **out) {
    assert(self);
    assert(out);
    return kit_DoublyList_get(self, out, 0);
}

size_t kit_DoublyList_size(struct kit_DoublyList *self) {
    assert(self);
    return self->size;
}

bool kit_DoublyList_isEmpty(struct kit_DoublyList *self) {
    assert(self);
    return 0 == self->size;
}

/**
 * kit_DoublyList_Iterator_T
 */
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

enum kit_Result kit_DoublyList_Iterator_next(struct kit_DoublyList_Iterator *self, void **out) {
    assert(self);
    assert(out);
    enum kit_Result result;

    if (kit_DoublyList_Iterator_isModified(self)) {
        result = KIT_RESULT_CONCURRENT_MODIFICATION_ERROR;
    } else if (self->next) {
        *out = self->next->element;
        self->last = self->prev = self->next;
        self->next = self->next->next;
        result = KIT_RESULT_OK;
    } else {
        result = KIT_RESULT_OUT_OF_RANGE_ERROR;
    }

    return result;
}

enum kit_Result kit_DoublyList_Iterator_previous(struct kit_DoublyList_Iterator *self, void **out) {
    assert(self);
    assert(out);
    enum kit_Result result;

    if (kit_DoublyList_Iterator_isModified(self)) {
        result = KIT_RESULT_CONCURRENT_MODIFICATION_ERROR;
    } else if (self->prev) {
        *out = self->prev->element;
        self->last = self->next = self->prev;
        self->prev = self->prev->prev;
        result = KIT_RESULT_OK;
    } else {
        result = KIT_RESULT_OUT_OF_RANGE_ERROR;
    }

    return result;
}

enum kit_Result kit_DoublyList_Iterator_setLast(struct kit_DoublyList_Iterator *self, void *e) {
    assert(self);
    enum kit_Result result = KIT_RESULT_OK;

    if (kit_DoublyList_Iterator_isModified(self)) {
        result = KIT_RESULT_CONCURRENT_MODIFICATION_ERROR;
    } else if (self->last) {
        self->last->element = e;
    } else {
        result = KIT_RESULT_ILLEGAL_STATE_ERROR;
    }

    return result;
}

bool kit_DoublyList_Iterator_isModified(struct kit_DoublyList_Iterator *self) {
    assert(self);
    struct kit_DoublyList *container = self->container;
    return NULL == container || self->operationId != container->operationId;
}

/*
 * Private implementations
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

enum kit_Result
kit_DoublyList_Node_fetch(struct kit_DoublyList *list, struct kit_DoublyList_Node **out, const size_t index) {
    assert(list);
    assert(out);
    enum kit_Result result = KIT_RESULT_OK;

    if (index < list->size) {
        if (index < list->size / 2) {
            *out = list->front;
            for (size_t i = 0; i < index; i++) {
                *out = (*out)->next;
            }
        } else {
            *out = list->back;
            for (size_t i = list->size - 1; i > index; i--) {
                *out = (*out)->prev;
            }
        }
    } else {
        result = KIT_RESULT_OUT_OF_RANGE_ERROR;
    }

    return result;
}
