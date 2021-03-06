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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <kit/allocator/allocator.h>
#include <kit/collections/atom.h>

#define _(x)            ((void) ((x) ? 1 : 0));

#define KIT_ATOM_NODE_TABLE_SIZE    (2039)

struct kit_Atom_Node {
    size_t hash;
    size_t length;
    struct kit_Atom_Node *next;
    kit_Atom atom;
};

static OptionOf(struct kit_Atom_Node *)
kit_Atom_table_put(const char *bytes, size_t length, size_t hash)
__attribute__((__warn_unused_result__, __nonnull__));

static OptionOf(struct kit_Atom_Node *)
kit_Atom_table_fetch(const char *bytes, size_t length, size_t hash)
__attribute__((__warn_unused_result__, __nonnull__));

static void
kit_Atom_table_clear(void);

static void
kit_Atom_assertValidInstance(kit_Atom atom);

static size_t
kit_Atom_hash(const char *bytes, size_t length)
__attribute__((__warn_unused_result__, __nonnull__));

static bool clearCallbackRegistered = false;
static struct kit_Atom_Node *atomsTable[KIT_ATOM_NODE_TABLE_SIZE] = {0};

OptionOf(kit_Atom)
kit_Atom_put(const void *const bytes, const size_t length) {
    assert(bytes);
    Option nodeOption = kit_Atom_table_put(bytes, length, kit_Atom_hash(bytes, length));

    if (Option_isSome(nodeOption)) {
        const struct kit_Atom_Node *node = Option_unwrap(nodeOption);
        return Option_new((void *) node->atom);
    }

    return None;
}

OptionOf(kit_Atom)
kit_Atom_fromLiteral(const char *const literal) {
    assert(literal);
    return kit_Atom_put(literal, strlen(literal));
}

OptionOf(kit_Atom)
kit_Atom_fromInteger(const long long n) {
    char buffer[32] = {0};
    const size_t bufferSize = sizeof(buffer) / sizeof(buffer[0]);
    const int length = snprintf(buffer, bufferSize, "%lld", n);
    assert(0 < length && length < (int) bufferSize);
    return kit_Atom_put(buffer, (size_t) length);
}

OptionOf(kit_Atom)
kit_Atom_fromFloating(const long double n) {
    char buffer[32] = {0};
    const size_t bufferSize = sizeof(buffer) / sizeof(buffer[0]);
    const int length = snprintf(buffer, bufferSize, "%Lf", n);
    assert(0 < length && length < (int) bufferSize);
    return kit_Atom_put(buffer, (size_t) length);
}

size_t
kit_Atom_length(kit_Atom atom) {
    assert(atom);
    kit_Atom_assertValidInstance(atom);
    struct kit_Atom_Node *node = ((struct kit_Atom_Node *) atom) - 1;
    return node->length;
}

/*
 * Internals
 */
OptionOf(struct kit_Atom_Node *)
kit_Atom_table_put(const char *const bytes, const size_t length, const size_t hash) {
    assert(bytes);
    Option nodeOption = kit_Atom_table_fetch(bytes, length, hash);

    if (Option_isNone(nodeOption)) {
        struct kit_Atom_Node *node = NULL;
        const size_t index = hash % KIT_ATOM_NODE_TABLE_SIZE;
        nodeOption = kit_Allocator_calloc(1, sizeof(*node) + length + 1);
        if (Option_isSome(nodeOption)) {
            node = Option_unwrap(nodeOption);
            /* construct node */
            node->hash = hash;
            node->length = length;
            node->atom = (char *) (node + 1);
            kit_Allocator_copy((void *) node->atom, bytes, length);
            /* add to table */
            node->next = atomsTable[index];
            atomsTable[index] = node;
        }
        nodeOption = Option_new(node);
    }

    if (!clearCallbackRegistered) {
        atexit(kit_Atom_table_clear);
        clearCallbackRegistered = true;
    }

    return nodeOption;
}

OptionOf(struct kit_Atom_Node *)
kit_Atom_table_fetch(const char *const bytes, const size_t length, const size_t hash) {
    assert(bytes);
    const size_t index = hash % KIT_ATOM_NODE_TABLE_SIZE;
    Option nodeOption = None;

    for (struct kit_Atom_Node *current = atomsTable[index]; current; current = current->next) {
        if (length == current->length) {
            size_t i = 0;
            while (i < length && current->atom[i] == bytes[i]) {
                i++;
            }
            if (length == i) {
                nodeOption = Option_new(current);
                break;
            }
        }
    }

    return nodeOption;
}

void
kit_Atom_table_clear(void) {
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

void
kit_Atom_assertValidInstance(kit_Atom atom) {
    assert(atom);
    (void) atom;
#ifndef NDEBUG
    struct kit_Atom_Node *node = ((struct kit_Atom_Node *) atom) - 1;
    _(Option_expect(kit_Atom_table_fetch(node->atom, node->length, node->hash), "Expected a valid atom instance."));
#endif
}

size_t
kit_Atom_hash(const char *const bytes, const size_t length) {
    /* Jenkins one at time */
    assert(bytes);
    size_t hash = 0;

    for (size_t i = 0; i < length; i++) {
        hash += (unsigned char) bytes[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}
