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
#include <features/feature_iterable.h>
#include <fixtures/fixture_sequence_context.h>

FeatureDefine(SequenceIteratorFromEmptySequenceBoundaries) {
    struct kit_Sequence *sequence = traits_unit_get_context();
    assert_not_null(sequence);

    struct kit_Sequence_Iterator *sut = Option_unwrap(kit_Sequence_Iterator_fromBegin(sequence));

    assert_equal(OutOfRangeError, Result_inspect(kit_Sequence_Iterator_next(sut)));
    assert_equal(IllegalStateError, Result_inspect(kit_Sequence_Iterator_setLast(sut, "x")));

    kit_Sequence_Iterator_delete(sut);
}

FeatureDefine(SequenceIteratorFromSeededSequenceBoundaries) {
    struct kit_Sequence *sequence = traits_unit_get_context();
    assert_not_null(sequence);

    struct kit_Sequence_Iterator *sut = Option_unwrap(kit_Sequence_Iterator_fromBegin(sequence));

    assert_equal(IllegalStateError, Result_inspect(kit_Sequence_Iterator_setLast(sut, "x")));
    assert_string_equal(SEEDS[0], Result_unwrap(kit_Sequence_Iterator_next(sut)));

    kit_Sequence_Iterator_delete(sut);
}

FeatureDefine(SequenceIteratorRewindFromEmptySequence) {
    struct kit_Traits_SequenceIteratorContext *context = traits_unit_get_context();
    assert_not_null(context);

    struct kit_Sequence *sequence = context->sequence;
    assert_not_null(sequence);

    struct kit_Sequence_Iterator *sut = context->sut;
    assert_not_null(sut);

    kit_Sequence_Iterator_rewindToBegin(sut);

    assert_equal(OutOfRangeError, Result_inspect(kit_Sequence_Iterator_next(sut)));
    assert_equal(IllegalStateError, Result_inspect(kit_Sequence_Iterator_setLast(sut, "x")));

    kit_Sequence_Iterator_rewindToBegin(sut);

    assert_equal(OutOfRangeError, Result_inspect(kit_Sequence_Iterator_next(sut)));
    assert_equal(IllegalStateError, Result_inspect(kit_Sequence_Iterator_setLast(sut, "x")));
}

FeatureDefine(SequenceIteratorRewindFromSeededSequence) {
    struct kit_Traits_SequenceIteratorContext *context = traits_unit_get_context();
    assert_not_null(context);

    struct kit_Sequence *sequence = context->sequence;
    assert_not_null(sequence);

    struct kit_Sequence_Iterator *sut = context->sut;
    assert_not_null(sut);

    kit_Sequence_Iterator_rewindToBegin(sut);

    assert_equal(IllegalStateError, Result_inspect(kit_Sequence_Iterator_setLast(sut, "x")));
    assert_string_equal(SEEDS[0], Result_unwrap(kit_Sequence_Iterator_next(sut)));
    assert_string_equal(SEEDS[1], Result_unwrap(kit_Sequence_Iterator_next(sut)));

    kit_Sequence_Iterator_rewindToBegin(sut);

    assert_equal(IllegalStateError, Result_inspect(kit_Sequence_Iterator_setLast(sut, "x")));
    assert_string_equal(SEEDS[0], Result_unwrap(kit_Sequence_Iterator_next(sut)));
    assert_string_equal(SEEDS[1], Result_unwrap(kit_Sequence_Iterator_next(sut)));
}

FeatureDefine(SequenceIteratorReachTheBoundariesOfSequence) {
    struct kit_Traits_SequenceIteratorContext *context = traits_unit_get_context();
    assert_not_null(context);

    struct kit_Sequence *sequence = context->sequence;
    assert_not_null(sequence);

    struct kit_Sequence_Iterator *sut = context->sut;
    assert_not_null(sut);

    kit_Sequence_Iterator_rewindToBegin(sut);

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_string_equal(SEEDS[i], Result_unwrap(kit_Sequence_Iterator_next(sut)));
    }
    assert_equal(OutOfRangeError, Result_inspect(kit_Sequence_Iterator_next(sut)));

    kit_Sequence_Iterator_rewindToBegin(sut);

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_string_equal(SEEDS[i], Result_unwrap(kit_Sequence_Iterator_next(sut)));
    }
    assert_equal(OutOfRangeError, Result_inspect(kit_Sequence_Iterator_next(sut)));
}

FeatureDefine(SequenceIteratorUpdateRetrievedElements) {
    struct kit_Traits_SequenceIteratorContext *context = traits_unit_get_context();
    assert_not_null(context);

    struct kit_Sequence *sequence = context->sequence;
    assert_not_null(sequence);

    struct kit_Sequence_Iterator *sut = context->sut;
    assert_not_null(sut);

    kit_Sequence_Iterator_rewindToBegin(sut);

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_string_equal(SEEDS[i], Result_unwrap(kit_Sequence_Iterator_next(sut)));
        assert_string_equal(SEEDS[i], Result_unwrap(kit_Sequence_Iterator_setLast(sut, "x")));
    }
    assert_equal(OutOfRangeError, Result_inspect(kit_Sequence_Iterator_next(sut)));

    kit_Sequence_Iterator_rewindToBegin(sut);

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_string_equal("x", Result_unwrap(kit_Sequence_Iterator_next(sut)));
        assert_string_equal("x", Result_unwrap(kit_Sequence_Iterator_setLast(sut, "y")));
    }
    assert_equal(OutOfRangeError, Result_inspect(kit_Sequence_Iterator_next(sut)));

    kit_Sequence_Iterator_rewindToBegin(sut);

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_string_equal("y", Result_unwrap(kit_Sequence_Iterator_next(sut)));
        assert_string_equal("y", Result_unwrap(kit_Sequence_Iterator_setLast(sut, "z")));
    }
    assert_equal(OutOfRangeError, Result_inspect(kit_Sequence_Iterator_next(sut)));
}

FeatureDefine(SequenceIteratorDetectModifications) {
    struct kit_Traits_SequenceIteratorContext *context = traits_unit_get_context();
    assert_not_null(context);

    struct kit_Sequence *sequence = context->sequence;
    assert_not_null(sequence);

    struct kit_Sequence_Iterator *sut = context->sut;
    assert_not_null(sut);

    assert_false(kit_Sequence_Iterator_isModified(sut));

    assert_equal(OutOfRangeError, Result_inspect(kit_Sequence_Iterator_next(sut)));
    assert_equal(IllegalStateError, Result_inspect(kit_Sequence_Iterator_setLast(sut, "x")));

    assert_equal(Ok, kit_Sequence_pushFront(sequence, "x"));
    assert_true(kit_Sequence_Iterator_isModified(sut));

    assert_equal(ConcurrentModificationError, Result_inspect(kit_Sequence_Iterator_next(sut)));
    assert_equal(ConcurrentModificationError, Result_inspect(kit_Sequence_Iterator_setLast(sut, "x")));

    kit_Sequence_Iterator_rewindToBegin(sut);
    assert_false(kit_Sequence_Iterator_isModified(sut));

    assert_equal(IllegalStateError, Result_inspect(kit_Sequence_Iterator_setLast(sut, "x")));
    assert_equal("x", Result_unwrap(kit_Sequence_Iterator_next(sut)));

    assert_equal(OutOfRangeError, Result_inspect(kit_Sequence_Iterator_next(sut)));
    assert_equal("x", Result_unwrap(kit_Sequence_Iterator_setLast(sut, "o")));
    assert_equal("o", Result_unwrap(kit_Sequence_Iterator_setLast(sut, "x")));
    assert_equal(OutOfRangeError, Result_inspect(kit_Sequence_Iterator_next(sut)));

    assert_equal(Ok, kit_Sequence_pushBack(sequence, "y"));
    assert_true(kit_Sequence_Iterator_isModified(sut));

    assert_equal(ConcurrentModificationError, Result_inspect(kit_Sequence_Iterator_next(sut)));
    assert_equal(ConcurrentModificationError, Result_inspect(kit_Sequence_Iterator_setLast(sut, "x")));

    kit_Sequence_Iterator_rewindToBegin(sut);
    assert_false(kit_Sequence_Iterator_isModified(sut));

    assert_equal(IllegalStateError, Result_inspect(kit_Sequence_Iterator_setLast(sut, "o")));
    assert_equal("x", Result_unwrap(kit_Sequence_Iterator_next(sut)));
    assert_equal("x", Result_unwrap(kit_Sequence_Iterator_setLast(sut, "a")));
    assert_equal("y", Result_unwrap(kit_Sequence_Iterator_next(sut)));
    assert_equal("y", Result_unwrap(kit_Sequence_Iterator_setLast(sut, "b")));
    assert_equal(OutOfRangeError, Result_inspect(kit_Sequence_Iterator_next(sut)));

    kit_Sequence_Iterator_rewindToBegin(sut);
    assert_false(kit_Sequence_Iterator_isModified(sut));

    assert_equal("a", Result_unwrap(kit_Sequence_Iterator_next(sut)));
    assert_equal("b", Result_unwrap(kit_Sequence_Iterator_next(sut)));
}
