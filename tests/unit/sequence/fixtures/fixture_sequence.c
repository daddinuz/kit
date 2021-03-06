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
#include <fixtures/fixture_sequence.h>
#include <fixtures/fixture_sequence_context.h>

/*
 * kit_SequenceType
 */
enum kit_SequenceType {
    KIT_SEQUENCE_TYPE_DOUBLY_LIST,
    KIT_SEQUENCE_TYPE_SINGLY_LIST,
    KIT_SEQUENCE_TYPE_XOR_LIST,
    KIT_SEQUENCE_TYPE_VECTOR,
};

/*
 * Helpers declarations
 */
static struct kit_Sequence *
setup_sequence_helper(enum kit_SequenceType type, const char *const *seeds, size_t seeds_size);

static struct kit_Traits_SequenceIteratorContext *
setup_sequence_iterator_helper(enum kit_SequenceType type, const char *const *seeds, size_t seeds_size);

/*
 * Setups implementations
 */
SetupDefine(EmptySequenceSinglyListSetup) {
    return setup_sequence_helper(KIT_SEQUENCE_TYPE_SINGLY_LIST, NULL, 0);
}

SetupDefine(SeededSequenceSinglyListSetup) {
    return setup_sequence_helper(KIT_SEQUENCE_TYPE_SINGLY_LIST, SEEDS, SEEDS_SIZE);
}

SetupDefine(EmptySequenceDoublyListSetup) {
    return setup_sequence_helper(KIT_SEQUENCE_TYPE_DOUBLY_LIST, NULL, 0);
}

SetupDefine(SeededSequenceDoublyListSetup) {
    return setup_sequence_helper(KIT_SEQUENCE_TYPE_DOUBLY_LIST, SEEDS, SEEDS_SIZE);
}

SetupDefine(EmptySequenceXorListSetup) {
    return setup_sequence_helper(KIT_SEQUENCE_TYPE_XOR_LIST, NULL, 0);
}

SetupDefine(SeededSequenceXorListSetup) {
    return setup_sequence_helper(KIT_SEQUENCE_TYPE_XOR_LIST, SEEDS, SEEDS_SIZE);
}

SetupDefine(EmptySequenceVectorSetup) {
    return setup_sequence_helper(KIT_SEQUENCE_TYPE_VECTOR, NULL, 0);
}

SetupDefine(SeededSequenceVectorSetup) {
    return setup_sequence_helper(KIT_SEQUENCE_TYPE_VECTOR, SEEDS, SEEDS_SIZE);
}

SetupDefine(SequenceIteratorFromEmptySequenceDoublyListSetup) {
    return setup_sequence_iterator_helper(KIT_SEQUENCE_TYPE_DOUBLY_LIST, NULL, 0);
}

SetupDefine(SequenceIteratorFromSeededSequenceDoublyListSetup) {
    return setup_sequence_iterator_helper(KIT_SEQUENCE_TYPE_DOUBLY_LIST, SEEDS, SEEDS_SIZE);
}

SetupDefine(SequenceIteratorFromEmptySequenceSinglyListSetup) {
    return setup_sequence_iterator_helper(KIT_SEQUENCE_TYPE_SINGLY_LIST, NULL, 0);
}

SetupDefine(SequenceIteratorFromSeededSequenceSinglyListSetup) {
    return setup_sequence_iterator_helper(KIT_SEQUENCE_TYPE_SINGLY_LIST, SEEDS, SEEDS_SIZE);
}

SetupDefine(SequenceIteratorFromEmptySequenceXorListSetup) {
    return setup_sequence_iterator_helper(KIT_SEQUENCE_TYPE_XOR_LIST, NULL, 0);
}

SetupDefine(SequenceIteratorFromSeededSequenceXorListSetup) {
    return setup_sequence_iterator_helper(KIT_SEQUENCE_TYPE_XOR_LIST, SEEDS, SEEDS_SIZE);
}

SetupDefine(SequenceIteratorFromEmptySequenceVectorSetup) {
    return setup_sequence_iterator_helper(KIT_SEQUENCE_TYPE_VECTOR, NULL, 0);
}

SetupDefine(SequenceIteratorFromSeededSequenceVectorSetup) {
    return setup_sequence_iterator_helper(KIT_SEQUENCE_TYPE_VECTOR, SEEDS, SEEDS_SIZE);
}

/*
 * Teardowns implementations
 */
TeardownDefine(SequenceTeardown) {
    struct kit_Sequence *sut = traits_unit_get_context();
    assert_not_null(sut);
    kit_Sequence_delete(sut);
}

TeardownDefine(SequenceIteratorTeardown) {
    struct kit_Traits_SequenceIteratorContext *context = traits_unit_get_context();
    assert_not_null(context);
    assert_not_null(context->sequence);
    assert_not_null(context->sut);
    kit_Sequence_delete(context->sequence);
    kit_Sequence_Iterator_delete(context->sut);
    free(context);
}

/*
 * Fixtures implementations
 */
FixtureDefine(EmptySequenceSinglyListFixture, EmptySequenceSinglyListSetup, SequenceTeardown);
FixtureDefine(SeededSequenceSinglyListFixture, SeededSequenceSinglyListSetup, SequenceTeardown);

FixtureDefine(EmptySequenceDoublyListFixture, EmptySequenceDoublyListSetup, SequenceTeardown);
FixtureDefine(SeededSequenceDoublyListFixture, SeededSequenceDoublyListSetup, SequenceTeardown);

FixtureDefine(EmptySequenceXorListFixture, EmptySequenceXorListSetup, SequenceTeardown);
FixtureDefine(SeededSequenceXorListFixture, SeededSequenceXorListSetup, SequenceTeardown);

FixtureDefine(EmptySequenceVectorFixture, EmptySequenceVectorSetup, SequenceTeardown);
FixtureDefine(SeededSequenceVectorFixture, SeededSequenceVectorSetup, SequenceTeardown);

FixtureDefine(SequenceIteratorFromEmptySequenceDoublyListFixture, SequenceIteratorFromEmptySequenceDoublyListSetup,
              SequenceIteratorTeardown);
FixtureDefine(SequenceIteratorFromSeededSequenceDoublyListFixture, SequenceIteratorFromSeededSequenceDoublyListSetup,
              SequenceIteratorTeardown);

FixtureDefine(SequenceIteratorFromEmptySequenceSinglyListFixture, SequenceIteratorFromEmptySequenceSinglyListSetup,
              SequenceIteratorTeardown);
FixtureDefine(SequenceIteratorFromSeededSequenceSinglyListFixture, SequenceIteratorFromSeededSequenceSinglyListSetup,
              SequenceIteratorTeardown);

FixtureDefine(SequenceIteratorFromEmptySequenceXorListFixture, SequenceIteratorFromEmptySequenceXorListSetup,
              SequenceIteratorTeardown);
FixtureDefine(SequenceIteratorFromSeededSequenceXorListFixture, SequenceIteratorFromSeededSequenceXorListSetup,
              SequenceIteratorTeardown);

FixtureDefine(SequenceIteratorFromEmptySequenceVectorFixture, SequenceIteratorFromEmptySequenceVectorSetup,
              SequenceIteratorTeardown);
FixtureDefine(SequenceIteratorFromSeededSequenceVectorFixture, SequenceIteratorFromSeededSequenceVectorSetup,
              SequenceIteratorTeardown);

/*
 * Helpers implementations
 */
struct kit_Sequence *
setup_sequence_helper(const enum kit_SequenceType type, const char *const seeds[], const size_t seeds_size) {
    assert_true((seeds && seeds_size) > 0 || (NULL == seeds && seeds_size == 0));
    struct kit_Sequence *sut = NULL;

    switch (type) {
        case KIT_SEQUENCE_TYPE_DOUBLY_LIST:
            sut = Option_unwrap(kit_Sequence_fromDoublyList());
            break;
        case KIT_SEQUENCE_TYPE_SINGLY_LIST:
            sut = Option_unwrap(kit_Sequence_fromSinglyList());
            break;
        case KIT_SEQUENCE_TYPE_XOR_LIST:
            sut = Option_unwrap(kit_Sequence_fromXorList());
            break;
        case KIT_SEQUENCE_TYPE_VECTOR:
            sut = Option_unwrap(kit_Sequence_fromVector(16));
            break;
        default:
            traits_assert(false);
    }

    assert_not_null(sut);

    if (seeds) {
        for (size_t i = 0; i < seeds_size; i++) {
            assert_equal(Ok, kit_Sequence_pushBack(sut, (void *) seeds[i]));
        }
    }

    return sut;
}

struct kit_Traits_SequenceIteratorContext *
setup_sequence_iterator_helper(enum kit_SequenceType type, const char *const *seeds, size_t seeds_size) {
    assert_true((seeds && seeds_size) > 0 || (NULL == seeds && seeds_size == 0));

    struct kit_Traits_SequenceIteratorContext *context = calloc(1, sizeof(*context));
    assert_not_null(context);

    context->sequence = setup_sequence_helper(type, seeds, seeds_size);
    assert_not_null(context->sequence);

    context->sut = Option_unwrap(kit_Sequence_Iterator_fromBegin(context->sequence));
    assert_not_null(context->sut);

    return context;
}
