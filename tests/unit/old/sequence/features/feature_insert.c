/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 25, 2017 
 */

#include <seeds.h>
#include <traits/traits.h>
#include <features/feature_insert.h>
#include <kit/collections/sequence.h.old>

FeatureDefine(SequenceInsert) {
    void *e;
    struct kit_Sequence *sut = traits_context;

    assert_equal(0, kit_Sequence_size(sut));
    assert_true(kit_Sequence_isEmpty(sut));

    assert_equal(KIT_RESULT_OK, kit_Sequence_insert(sut, "a", 0));
    assert_false(kit_Sequence_isEmpty(sut));
    assert_equal(1, kit_Sequence_size(sut));
    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_Sequence_get(sut, &e, 0));
    assert_string_equal("a", (char *) e);
    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Sequence_get(sut, &e, 1));
    assert_null(e);
    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_Sequence_front(sut, &e));
    assert_string_equal("a", (char *) e);
    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_Sequence_back(sut, &e));
    assert_string_equal("a", (char *) e);

    assert_equal(KIT_RESULT_OK, kit_Sequence_insert(sut, "c", 1));
    assert_false(kit_Sequence_isEmpty(sut));
    assert_equal(2, kit_Sequence_size(sut));
    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_Sequence_get(sut, &e, 0));
    assert_string_equal("a", (char *) e);
    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_Sequence_get(sut, &e, 1));
    assert_string_equal("c", (char *) e);
    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Sequence_get(sut, &e, 2));
    assert_null(e);
    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_Sequence_front(sut, &e));
    assert_string_equal("a", (char *) e);
    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_Sequence_back(sut, &e));
    assert_string_equal("c", (char *) e);

    assert_equal(KIT_RESULT_OK, kit_Sequence_insert(sut, "b", 1));
    assert_false(kit_Sequence_isEmpty(sut));
    assert_equal(3, kit_Sequence_size(sut));
    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_Sequence_get(sut, &e, 0));
    assert_string_equal("a", (char *) e);
    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_Sequence_get(sut, &e, 1));
    assert_string_equal("b", (char *) e);
    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_Sequence_get(sut, &e, 2));
    assert_string_equal("c", (char *) e);
    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Sequence_get(sut, &e, 3));
    assert_null(e);
    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_Sequence_front(sut, &e));
    assert_string_equal("a", (char *) e);
    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_Sequence_back(sut, &e));
    assert_string_equal("c", (char *) e);
}

FeatureDefine(SequencePushBack) {
    void *e;
    struct kit_Sequence *sut = traits_context;

    assert_equal(0, kit_Sequence_size(sut));
    assert_true(kit_Sequence_isEmpty(sut));

    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Sequence_back(sut, &e));
    assert_null(e);

    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Sequence_front(sut, &e));
    assert_null(e);

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_equal(KIT_RESULT_OK, kit_Sequence_pushBack(sut, (void *) SEEDS[i]));
        assert_equal(i + 1, kit_Sequence_size(sut));
        assert_false(kit_Sequence_isEmpty(sut));

        e = NULL;
        assert_equal(KIT_RESULT_OK, kit_Sequence_back(sut, &e));
        assert_string_equal(SEEDS[i], (char *) e);

        e = NULL;
        assert_equal(KIT_RESULT_OK, kit_Sequence_front(sut, &e));
        assert_string_equal(SEEDS[0], (char *) e);
    }
}

FeatureDefine(SequencePushFront) {
    void *e;
    struct kit_Sequence *sut = traits_context;

    assert_equal(0, kit_Sequence_size(sut));
    assert_true(kit_Sequence_isEmpty(sut));

    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Sequence_back(sut, &e));
    assert_null(e);

    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Sequence_front(sut, &e));
    assert_null(e);

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_equal(KIT_RESULT_OK, kit_Sequence_pushFront(sut, (void *) SEEDS[i]));
        assert_equal(i + 1, kit_Sequence_size(sut));
        assert_false(kit_Sequence_isEmpty(sut));

        e = NULL;
        assert_equal(KIT_RESULT_OK, kit_Sequence_back(sut, &e));
        assert_string_equal(SEEDS[0], (char *) e);

        e = NULL;
        assert_equal(KIT_RESULT_OK, kit_Sequence_front(sut, &e));
        assert_string_equal(SEEDS[i], (char *) e);
    }
}
