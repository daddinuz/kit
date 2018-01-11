/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 25, 2017 
 */

#include <seeds.h>
#include <traits/traits.h>
#include <features/feature_remove.h>
#include <kit/collections/sequence.h.old>

FeatureDefine(SequenceClear) {
    void *e = NULL;
    struct kit_Sequence *sut = traits_context;

    kit_Sequence_clear(sut);
    assert_equal(0, kit_Sequence_size(sut));
    assert_true(kit_Sequence_isEmpty(sut));
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Sequence_front(sut, &e));
    assert_null(e);
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Sequence_back(sut, &e));
    assert_null(e);
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Sequence_get(sut, &e, 0));
    assert_null(e);
}

FeatureDefine(SequenceRemove) {
    void *e;
    struct kit_Sequence *sut = traits_context;

    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Sequence_remove(sut, &e, SEEDS_SIZE));
    assert_null(e);

    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_Sequence_remove(sut, &e, 0));
    assert_string_equal(SEEDS[0], (char *) e);

    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_Sequence_remove(sut, &e, 3));
    assert_string_equal(SEEDS[4], (char *) e);

    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_Sequence_remove(sut, &e, 1));
    assert_string_equal(SEEDS[2], (char *) e);

    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_Sequence_remove(sut, &e, 1));
    assert_string_equal(SEEDS[3], (char *) e);

    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_Sequence_remove(sut, &e, 0));
    assert_string_equal(SEEDS[1], (char *) e);

    assert_equal(SEEDS_SIZE - 5, kit_Sequence_size(sut));
    assert_false(kit_Sequence_isEmpty(sut));

    const size_t size = kit_Sequence_size(sut);
    for (size_t i = 0; i < size; i++) {
        assert_equal(KIT_RESULT_OK, kit_Sequence_remove(sut, &e, 0));
    }

    assert_equal(0, kit_Sequence_size(sut));
    assert_true(kit_Sequence_isEmpty(sut));

    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Sequence_remove(sut, &e, 0));
    assert_null(e);
}

FeatureDefine(SequencePopBack) {
    void *e;
    struct kit_Sequence *sut = traits_context;

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_equal(SEEDS_SIZE - i, kit_Sequence_size(sut));
        assert_false(kit_Sequence_isEmpty(sut));

        e = NULL;
        assert_equal(KIT_RESULT_OK, kit_Sequence_popBack(sut, &e));
        assert_string_equal(SEEDS[SEEDS_SIZE - i - 1], (char *) e);

        if (i < SEEDS_SIZE - 1) {
            e = NULL;
            assert_equal(KIT_RESULT_OK, kit_Sequence_back(sut, &e));
            assert_string_equal(SEEDS[SEEDS_SIZE - i - 2], (char *) e);

            e = NULL;
            assert_equal(KIT_RESULT_OK, kit_Sequence_front(sut, &e));
            assert_string_equal(SEEDS[0], (char *) e);
        }
    }

    assert_equal(0, kit_Sequence_size(sut));
    assert_true(kit_Sequence_isEmpty(sut));

    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Sequence_popBack(sut, &e));
    assert_null(e);

    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Sequence_back(sut, &e));
    assert_null(e);

    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Sequence_front(sut, &e));
    assert_null(e);
}

FeatureDefine(SequencePopFront) {
    void *e;
    struct kit_Sequence *sut = traits_context;

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_equal(SEEDS_SIZE - i, kit_Sequence_size(sut));
        assert_false(kit_Sequence_isEmpty(sut));

        e = NULL;
        assert_equal(KIT_RESULT_OK, kit_Sequence_popFront(sut, &e));
        assert_string_equal(SEEDS[i], (char *) e);

        if (i < SEEDS_SIZE - 1) {
            e = NULL;
            assert_equal(KIT_RESULT_OK, kit_Sequence_back(sut, &e));
            assert_string_equal(SEEDS[SEEDS_SIZE - 1], (char *) e);

            e = NULL;
            assert_equal(KIT_RESULT_OK, kit_Sequence_front(sut, &e));
            assert_string_equal(SEEDS[i + 1], (char *) e);
        }
    }

    assert_equal(0, kit_Sequence_size(sut));
    assert_true(kit_Sequence_isEmpty(sut));

    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Sequence_popFront(sut, &e));
    assert_null(e);

    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Sequence_back(sut, &e));
    assert_null(e);

    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Sequence_front(sut, &e));
    assert_null(e);
}
