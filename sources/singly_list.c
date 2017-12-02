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

/*
 * Private
 */
struct kit_SinglyList_Node {
    void *element;
    struct kit_SinglyList_Node *next;
};

static Option
kit_SinglyList_Node_new(void *e);

static void *
kit_SinglyList_Node_delete(struct kit_SinglyList_Node *self)
__attribute__((__nonnull__));

struct kit_SinglyList_Node_Pair {
    struct kit_SinglyList_Node *prev;
    struct kit_SinglyList_Node *base;
};

static enum kit_Result
kit_SinglyList_Node_Pair_fetch(struct kit_SinglyList *list, struct kit_SinglyList_Node_Pair *out, size_t index)
__attribute__((__nonnull__));

/*
 * Public
 */
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
    struct kit_SinglyList_Node_Pair pair = {.prev=NULL, .base=self->front};

    while (pair.base) {
        pair.prev = pair.base;
        pair.base = pair.base->next;
        kit_SinglyList_Node_delete(pair.prev);
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

enum kit_Result kit_SinglyList_insert(struct kit_SinglyList *self, void *e, const size_t index) {
    assert(self);
    Option optionNode;
    struct kit_SinglyList_Node *newNode;
    enum kit_Result result = KIT_RESULT_OK;

    if (index == 0) {                           /* insert front */
        optionNode = kit_SinglyList_Node_new(e);
        if (Option_isSome(optionNode)) {
            newNode = Option_unwrap(optionNode);
            if (self->front) {                  /* non-empty list */
                struct kit_SinglyList_Node *oldFront = self->front;
                self->front = newNode;
                self->front->next = oldFront;
            } else {                            /* empty list */
                self->front = self->back = newNode;
            }
        } else {
            result = KIT_RESULT_OUT_OF_MEMORY_ERROR;
        }
    } else if (index == self->size) {           /* insert back */
        optionNode = kit_SinglyList_Node_new(e);
        if (Option_isSome(optionNode)) {
            newNode = Option_unwrap(optionNode);
            if (self->back) {                   /* non-empty list */
                self->back->next = newNode;
                self->back = newNode;
            } else {                            /* empty list */
                self->front = self->back = newNode;
            }
        } else {
            result = KIT_RESULT_OUT_OF_MEMORY_ERROR;
        }
    } else {                                    /* insert middle */
        struct kit_SinglyList_Node_Pair pair = {.prev=NULL, .base=NULL};
        result = kit_SinglyList_Node_Pair_fetch(self, &pair, index);  /* may return: KIT_RESULT_OUT_OF_RANGE */
        if (KIT_RESULT_OK == result) {
            optionNode = kit_SinglyList_Node_new(e);
            if (Option_isSome(optionNode)) {
                newNode = Option_unwrap(optionNode);
                newNode->next = pair.base;
                pair.prev->next = newNode;
            } else {
                result = KIT_RESULT_OUT_OF_MEMORY_ERROR;
            }
        }
    }

    if (KIT_RESULT_OK == result) {
        self->size += 1;
        self->operationId += 1;
    };

    return result;
}

enum kit_Result kit_SinglyList_pushBack(struct kit_SinglyList *self, void *e) {
    assert(self);
    return kit_SinglyList_insert(self, e, self->size);
}

enum kit_Result kit_SinglyList_pushFront(struct kit_SinglyList *self, void *e) {
    assert(self);
    return kit_SinglyList_insert(self, e, 0);
}

enum kit_Result kit_SinglyList_popBack(struct kit_SinglyList *self, void **out) {
    assert(self);
    assert(out);
    const size_t size = self->size;
    return size > 0 ? kit_SinglyList_remove(self, out, size - 1) : KIT_RESULT_OUT_OF_RANGE_ERROR;
}

enum kit_Result kit_SinglyList_popFront(struct kit_SinglyList *self, void **out) {
    assert(self);
    assert(out);
    return kit_SinglyList_remove(self, out, 0);
}

enum kit_Result kit_SinglyList_remove(struct kit_SinglyList *self, void **out, const size_t index) {
    assert(self);
    assert(out);
    struct kit_SinglyList_Node_Pair pair = {.prev=NULL, .base=NULL};
    enum kit_Result result = kit_SinglyList_Node_Pair_fetch(self, &pair, index);

    if (KIT_RESULT_OK == result) {
        if (pair.prev) {
            pair.prev->next = pair.base->next;
        } else {
            self->front = pair.base->next;
        }
        if (NULL == pair.base->next) {
            self->back = pair.prev;
        }
        self->size -= 1;
        self->operationId += 1;
        *out = kit_SinglyList_Node_delete(pair.base);
    }

    return result;
}

enum kit_Result kit_SinglyList_set(struct kit_SinglyList *self, void *e, const size_t index) {
    assert(self);
    struct kit_SinglyList_Node_Pair pair = {.prev=NULL, .base=NULL};
    const enum kit_Result result = kit_SinglyList_Node_Pair_fetch(self, &pair, index);

    if (KIT_RESULT_OK == result) {
        pair.base->element = e;
    }

    return result;
}

enum kit_Result kit_SinglyList_get(struct kit_SinglyList *self, void **out, const size_t index) {
    assert(self);
    assert(out);
    struct kit_SinglyList_Node_Pair pair = {.prev=NULL, .base=NULL};
    const enum kit_Result result = kit_SinglyList_Node_Pair_fetch(self, &pair, index);

    if (KIT_RESULT_OK == result) {
        *out = pair.base->element;
    }

    return result;
}

enum kit_Result kit_SinglyList_back(struct kit_SinglyList *self, void **out) {
    assert(self);
    assert(out);
    const size_t size = self->size;
    return size > 0 ? kit_SinglyList_get(self, out, size - 1) : KIT_RESULT_OUT_OF_RANGE_ERROR;
}

enum kit_Result kit_SinglyList_front(struct kit_SinglyList *self, void **out) {
    assert(self);
    assert(out);
    return kit_SinglyList_get(self, out, 0);
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

enum kit_Result kit_SinglyList_Iterator_next(struct kit_SinglyList_Iterator *self, void **out) {
    assert(self);
    assert(out);
    enum kit_Result result;

    if (kit_SinglyList_Iterator_isModified(self)) {
        result = KIT_RESULT_CONCURRENT_MODIFICATION_ERROR;
    } else if (self->next) {
        *out = self->next->element;
        self->last = self->next;
        self->next = self->next->next;
        result = KIT_RESULT_OK;
    } else {
        result = KIT_RESULT_OUT_OF_RANGE_ERROR;
    }

    return result;
}

enum kit_Result kit_SinglyList_Iterator_setLast(struct kit_SinglyList_Iterator *self, void *e) {
    assert(self);
    enum kit_Result result = KIT_RESULT_OK;

    if (kit_SinglyList_Iterator_isModified(self)) {
        result = KIT_RESULT_CONCURRENT_MODIFICATION_ERROR;
    } else if (self->last) {
        self->last->element = e;
    } else {
        result = KIT_RESULT_ILLEGAL_STATE_ERROR;
    }

    return result;
}

bool kit_SinglyList_Iterator_isModified(struct kit_SinglyList_Iterator *self) {
    assert(self);
    struct kit_SinglyList *container = self->container;
    return NULL == container || self->operationId != container->operationId;
}

/*
 * Private implementations
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

enum kit_Result
kit_SinglyList_Node_Pair_fetch(struct kit_SinglyList *list, struct kit_SinglyList_Node_Pair *out, const size_t index) {
    assert(list);
    assert(out);
    enum kit_Result result = KIT_RESULT_OK;

    if (index < list->size) {
        out->prev = NULL;
        out->base = list->front;
        for (size_t i = 0; i < index; i += 1) {
            out->prev = out->base;
            out->base = out->base->next;
        }
    } else {
        result = KIT_RESULT_OUT_OF_RANGE_ERROR;
    }

    return result;
}
