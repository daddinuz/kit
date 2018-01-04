/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 26, 2017 
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
    struct kit_Queue *sut = traits_context;
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
            sut = MutableOption_unwrap(kit_Queue_fromDoublyList());
            break;
        case KIT_QUEUE_TYPE_SINGLY_LIST:
            sut = MutableOption_unwrap(kit_Queue_fromSinglyList());
            break;
        case KIT_QUEUE_TYPE_XOR_LIST:
            sut = MutableOption_unwrap(kit_Queue_fromXorList());
            break;
        case KIT_QUEUE_TYPE_VECTOR:
            sut = MutableOption_unwrap(kit_Queue_fromVector(0));
            break;
        default:
            traits_assert(false);
    }

    assert_not_null(sut);

    if (seeds) {
        for (size_t i = 0; i < seeds_size; i++) {
            assert_equal(KIT_RESULT_OK, kit_Queue_push(sut, (void *) seeds[i]));
        }
    }

    return sut;
}
