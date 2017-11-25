/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 25, 2017 
 */

#include <seeds.h>
#include <traits/traits.h>
#include <features/feature_iterable.h>
#include <fixtures/fixture_sequence_context.h>

FeatureDefine(SequenceIteratorFromEmptySequenceBoundaries) {
    void *e;
    struct kit_Sequence *sequence = traits_context;
    assert_not_null(sequence);
    struct kit_Sequence_Iterator *sut = Option_unwrap(kit_Sequence_Iterator_new(sequence));

    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Sequence_Iterator_next(sut, &e));
    assert_null(e);
    assert_equal(KIT_RESULT_ILLEGAL_STATE_ERROR, kit_Sequence_Iterator_setLast(sut, "x"));
    kit_Sequence_Iterator_delete(sut);
}

FeatureDefine(SequenceIteratorFromSeededSequenceBoundaries) {
    void *e;
    struct kit_Sequence *sequence = traits_context;
    assert_not_null(sequence);
    struct kit_Sequence_Iterator *sut = Option_unwrap(kit_Sequence_Iterator_new(sequence));

    assert_equal(KIT_RESULT_ILLEGAL_STATE_ERROR, kit_Sequence_Iterator_setLast(sut, "x"));
    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_Sequence_Iterator_next(sut, &e));
    assert_string_equal(SEEDS[0], e);
    kit_Sequence_Iterator_delete(sut);
}

FeatureDefine(SequenceIteratorRewindFromEmptySequence) {
    void *e;
    struct kit_Traits_SequenceIteratorContext *context = traits_context;
    struct kit_Sequence *sequence = context->sequence;
    assert_not_null(sequence);
    struct kit_Sequence_Iterator *sut = context->sut;
    assert_not_null(sut);

    kit_Sequence_Iterator_rewind(sut);
    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Sequence_Iterator_next(sut, &e));
    assert_null(e);
    assert_equal(KIT_RESULT_ILLEGAL_STATE_ERROR, kit_Sequence_Iterator_setLast(sut, "x"));
}

FeatureDefine(SequenceIteratorRewindFromSeededSequence) {
    void *e;
    struct kit_Traits_SequenceIteratorContext *context = traits_context;
    struct kit_Sequence *sequence = context->sequence;
    assert_not_null(sequence);
    struct kit_Sequence_Iterator *sut = context->sut;
    assert_not_null(sut);

    for (int i = 0; i < 2; i++) {
        kit_Sequence_Iterator_rewind(sut);
        assert_equal(KIT_RESULT_ILLEGAL_STATE_ERROR, kit_Sequence_Iterator_setLast(sut, "x"));
        e = NULL;
        assert_equal(KIT_RESULT_OK, kit_Sequence_Iterator_next(sut, &e));
        assert_string_equal(SEEDS[0], e);
        e = NULL;
        assert_equal(KIT_RESULT_OK, kit_Sequence_Iterator_next(sut, &e));
        assert_string_equal(SEEDS[1], e);
    }
}

FeatureDefine(SequenceIteratorReachTheBoundariesOfSequence) {
    void *e;
    struct kit_Traits_SequenceIteratorContext *context = traits_context;
    struct kit_Sequence *sequence = context->sequence;
    assert_not_null(sequence);
    struct kit_Sequence_Iterator *sut = context->sut;
    assert_not_null(sut);

    kit_Sequence_Iterator_rewind(sut);
    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        e = NULL;
        assert_equal(KIT_RESULT_OK, kit_Sequence_Iterator_next(sut, &e));
        assert_string_equal(SEEDS[i], e);
    }
    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Sequence_Iterator_next(sut, &e));
    assert_null(e);
}

FeatureDefine(SequenceIteratorUpdateRetrievedElements) {
    void *e;
    struct kit_Traits_SequenceIteratorContext *context = traits_context;
    struct kit_Sequence *sequence = context->sequence;
    assert_not_null(sequence);
    struct kit_Sequence_Iterator *sut = context->sut;
    assert_not_null(sut);

    kit_Sequence_Iterator_rewind(sut);
    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        e = NULL;
        assert_equal(KIT_RESULT_OK, kit_Sequence_Iterator_next(sut, &e));
        assert_string_equal(SEEDS[i], e);
        kit_Sequence_Iterator_setLast(sut, "x");
    }
    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Sequence_Iterator_next(sut, &e));
    assert_null(e);

    kit_Sequence_Iterator_rewind(sut);
    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        e = NULL;
        assert_equal(KIT_RESULT_OK, kit_Sequence_Iterator_next(sut, &e));
        assert_string_equal("x", e);
    }
    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Sequence_Iterator_next(sut, &e));
    assert_null(e);
}

FeatureDefine(SequenceIteratorDetectModifications) {
    void *e;
    struct kit_Traits_SequenceIteratorContext *context = traits_context;
    struct kit_Sequence *sequence = context->sequence;
    assert_not_null(sequence);
    struct kit_Sequence_Iterator *sut = context->sut;
    assert_not_null(sut);

    assert_false(kit_Sequence_Iterator_isModified(sut));

    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Sequence_Iterator_next(sut, &e));
    assert_null(e);
    assert_equal(KIT_RESULT_ILLEGAL_STATE_ERROR, kit_Sequence_Iterator_setLast(sut, "o"));

    kit_Sequence_pushFront(sequence, "y");
    assert_true(kit_Sequence_Iterator_isModified(sut));
    e = NULL;
    assert_equal(KIT_RESULT_CONCURRENT_MODIFICATION_ERROR, kit_Sequence_Iterator_next(sut, &e));
    assert_null(e);
    assert_equal(KIT_RESULT_CONCURRENT_MODIFICATION_ERROR, kit_Sequence_Iterator_setLast(sut, "o"));

    kit_Sequence_Iterator_rewind(sut);
    assert_false(kit_Sequence_Iterator_isModified(sut));
    assert_equal(KIT_RESULT_ILLEGAL_STATE_ERROR, kit_Sequence_Iterator_setLast(sut, "o"));
    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_Sequence_Iterator_next(sut, &e));
    assert_equal("y", e);
    assert_equal(KIT_RESULT_OK, kit_Sequence_Iterator_setLast(sut, "x"));

    kit_Sequence_pushBack(sequence, "y");
    assert_true(kit_Sequence_Iterator_isModified(sut));
    e = NULL;
    assert_equal(KIT_RESULT_CONCURRENT_MODIFICATION_ERROR, kit_Sequence_Iterator_next(sut, &e));
    assert_null(e);
    assert_equal(KIT_RESULT_CONCURRENT_MODIFICATION_ERROR, kit_Sequence_Iterator_setLast(sut, "o"));

    kit_Sequence_Iterator_rewind(sut);
    assert_false(kit_Sequence_Iterator_isModified(sut));
    assert_equal(KIT_RESULT_ILLEGAL_STATE_ERROR, kit_Sequence_Iterator_setLast(sut, "o"));
    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_Sequence_Iterator_next(sut, &e));
    assert_equal("x", e);
    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_Sequence_Iterator_next(sut, &e));
    assert_equal("y", e);
    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Sequence_Iterator_next(sut, &e));
    assert_null(e);
}
