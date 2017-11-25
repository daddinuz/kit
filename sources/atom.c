/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 22, 2017 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <kit/allocator/allocator.h>
#include <kit/collections/atom.h>

/*
 * Private
 */
#define KIT_ATOM_NODE_TABLE_SIZE    (2039)

struct kit_Atom_Node {
    size_t hash;
    size_t length;
    struct kit_Atom_Node *next;
    char *atom;
};

static Optional(struct kit_Atom_Node *)
kit_Atom_table_put(const char *s, size_t length, size_t hash) __attribute__((__nonnull__));

static Optional(struct kit_Atom_Node *)
kit_Atom_table_fetch(const char *s, size_t length, size_t hash) __attribute__((__nonnull__));

static void
kit_Atom_table_clear(void);

static void
kit_Atom_assertValidInstance(kit_Atom atom);

static size_t
kit_Atom_hash(const char *s, size_t length)  __attribute__((__nonnull__));

static bool clearCallbackRegistered = false;
static struct kit_Atom_Node *atomsTable[KIT_ATOM_NODE_TABLE_SIZE] = {0};

/*
 * Public
 */
Optional(kit_Atom) kit_Atom_put(const char *const s, const size_t length) {
    assert(s);
    Optional(struct kit_Atom_Node *) _ = kit_Atom_table_put(s, length, kit_Atom_hash(s, length));

    if (Option_isSome(_)) {
        struct kit_Atom_Node *node = Option_unwrap(_);
        return Option_new(node->atom);
    } else {
        return Option_None;
    }
}

Optional(kit_Atom) kit_Atom_fromLiteral(const char *const s) {
    assert(s);
    return kit_Atom_put(s, strlen(s));
}

Optional(kit_Atom) kit_Atom_fromInteger(long long n) {
    char buffer[32] = {0};
    const size_t bufferSize = sizeof(buffer) / sizeof(buffer[0]);
    const int length = snprintf(buffer, bufferSize, "%lld", n);
    assert(0 < length && length < (int) bufferSize);
    return kit_Atom_put(buffer, (size_t) length);
}

Optional(kit_Atom) kit_Atom_fromFloating(long double n) {
    char buffer[32] = {0};
    const size_t bufferSize = sizeof(buffer) / sizeof(buffer[0]);
    const int length = snprintf(buffer, bufferSize, "%Lf", n);
    assert(0 < length && length < (int) bufferSize);
    return kit_Atom_put(buffer, (size_t) length);
}

size_t kit_Atom_length(kit_Atom atom) {
    assert(atom);
    kit_Atom_assertValidInstance(atom);
    struct kit_Atom_Node *node = ((struct kit_Atom_Node *) atom) - 1;
    return node->length;
}

/*
 * Private implementations
 */

Optional(struct kit_Atom_Node *) kit_Atom_table_put(const char *const s, const size_t length, const size_t hash) {
    assert(s);
    Optional(struct kit_Atom_Node *) result = kit_Atom_table_fetch(s, length, hash);

    if (Option_isNone(result)) {
        const size_t index = hash % KIT_ATOM_NODE_TABLE_SIZE;
        struct kit_Atom_Node *node = kit_Allocator_malloc(sizeof(*node) + length + 1);
        if (node) {
            /* construct node */
            node->hash = hash;
            node->length = length;
            node->atom = (char *) (node + 1);
            kit_Allocator_copy((void *) node->atom, s, length);
            node->atom[length] = '\0';
            /* add to table */
            node->next = atomsTable[index];
            atomsTable[index] = node;
        }
        result = Option_new(node);
    }

    if (!clearCallbackRegistered) {
        atexit(kit_Atom_table_clear);
        clearCallbackRegistered = true;
    }

    return result;
}

Optional(struct kit_Atom_Node *) kit_Atom_table_fetch(const char *const s, const size_t length, const size_t hash) {
    assert(s);
    const size_t index = hash % KIT_ATOM_NODE_TABLE_SIZE;
    Optional(struct kit_Atom_Node *) node = Option_None;

    for (struct kit_Atom_Node *current = atomsTable[index]; current; current = current->next) {
        if (length == current->length) {
            size_t i = 0;
            while (i < length && current->atom[i] == s[i]) {
                i++;
            }
            if (length == i) {
                node = Option_new(current);
                break;
            }
        }
    }

    return node;
}

void kit_Atom_table_clear(void) {
    for (size_t i = 0; i < KIT_ATOM_NODE_TABLE_SIZE; i++) {
        struct kit_Atom_Node *node = atomsTable[i];
        if (node) {
            for (struct kit_Atom_Node *prev = node; node; prev = node) {
                node = node->next;
                kit_Allocator_free(prev);
            }
        }
    }
}

void kit_Atom_assertValidInstance(kit_Atom atom) {
    assert(atom);
    (void) atom;
#ifndef NDEBUG
    struct kit_Atom_Node *node = ((struct kit_Atom_Node *) atom) - 1;
    Option_expect(kit_Atom_table_fetch(node->atom, node->length, node->hash), "Expected a valid atom instance.");
#endif
}

/* Jenkins one at time */
size_t kit_Atom_hash(const char *s, size_t length) {
    assert(s);
    size_t hash = 0;

    for (size_t i = 0; i < length; i++) {
        hash += (unsigned char) s[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}