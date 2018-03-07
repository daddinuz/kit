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

#include <seeds.h>
#include <traits/traits.h>
#include <fixtures/fixture_queue.h>
#include <kit/collections/queue.h>


/*
 * kit_QueueType
 */
enum kit_QueueType {
    KIT_QUEUE_TYPE_DOUBLY_LIST,
    KIT_QUEUE_TYPE_SINGLY_LIST,
    KIT_QUEUE_TYPE_XOR_LIST,
    KIT_QUEUE_TYPE_VECTOR,
};

/*
 * Helpers declarations
 */
static struct kit_Queue *setup_helper(enum kit_QueueType type, const char *const seeds[], size_t seeds_size);

/*
 * Setups implementations
 */
SetupDefine(EmptyQueueSinglyListSetup) {
    return setup_helper(KIT_QUEUE_TYPE_SINGLY_LIST, NULL, 0);
}

SetupDefine(SeededQueueSinglyListSetup) {
    return setup_helper(KIT_QUEUE_TYPE_SINGLY_LIST, SEEDS, SEEDS_SIZE);
}

SetupDefine(EmptyQueueDoublyListSetup) {
    return setup_helper(KIT_QUEUE_TYPE_DOUBLY_LIST, NULL, 0);
}

SetupDefine(SeededQueueDoublyListSetup) {
    return setup_helper(KIT_QUEUE_TYPE_DOUBLY_LIST, SEEDS, SEEDS_SIZE);
}

SetupDefine(EmptyQueueXorListSetup) {
    return setup_helper(KIT_QUEUE_TYPE_XOR_LIST, NULL, 0);
}

SetupDefine(SeededQueueXorListSetup) {
    return setup_helper(KIT_QUEUE_TYPE_XOR_LIST, SEEDS, SEEDS_SIZE);
}

SetupDefine(EmptyQueueVectorSetup) {
    return setup_helper(KIT_QUEUE_TYPE_VECTOR, NULL, 0);
}

SetupDefine(SeededQueueVectorSetup) {
    return setup_helper(KIT_QUEUE_TYPE_VECTOR, SEEDS, SEEDS_SIZE);
}

/*
 * Teardowns implementations
 */
TeardownDefine(QueueTeardown) {
    struct kit_Queue *sut = traits_unit_get_context();
    assert_not_null(sut);
    kit_Queue_delete(sut);
}

/*
 * Fixtures implementations
 */
FixtureDefine(EmptyQueueSinglyListFixture, EmptyQueueSinglyListSetup, QueueTeardown);
FixtureDefine(SeededQueueSinglyListFixture, SeededQueueSinglyListSetup, QueueTeardown);

FixtureDefine(EmptyQueueDoublyListFixture, EmptyQueueDoublyListSetup, QueueTeardown);
FixtureDefine(SeededQueueDoublyListFixture, SeededQueueDoublyListSetup, QueueTeardown);

FixtureDefine(EmptyQueueXorListFixture, EmptyQueueXorListSetup, QueueTeardown);
FixtureDefine(SeededQueueXorListFixture, SeededQueueXorListSetup, QueueTeardown);

FixtureDefine(EmptyQueueVectorixture, EmptyQueueVectorSetup, QueueTeardown);
FixtureDefine(SeededQueueVectorFixture, SeededQueueVectorSetup, QueueTeardown);

/*
 * Helpers implementations
 */
struct kit_Queue *setup_helper(enum kit_QueueType type, const char *const seeds[], const size_t seeds_size) {
    struct kit_Queue *sut = NULL;

    switch (type) {
        case KIT_QUEUE_TYPE_DOUBLY_LIST:
            sut = Option_unwrap(kit_Queue_fromDoublyList());
            break;
        case KIT_QUEUE_TYPE_SINGLY_LIST:
            sut = Option_unwrap(kit_Queue_fromSinglyList());
            break;
        case KIT_QUEUE_TYPE_XOR_LIST:
            sut = Option_unwrap(kit_Queue_fromXorList());
            break;
        case KIT_QUEUE_TYPE_VECTOR:
            sut = Option_unwrap(kit_Queue_fromVector(0));
            break;
        default:
            traits_assert(false);
    }

    assert_not_null(sut);

    if (seeds) {
        for (size_t i = 0; i < seeds_size; i++) {
            assert_equal(Ok, kit_Queue_push(sut, (void *) seeds[i]));
        }
    }

    return sut;
}
