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
#include <kit/collections/list.h>

FeatureDefine(ListClear) {
    void *e = NULL;
    struct kit_List *sut = traits_context;

    kit_List_clear(sut);
    assert_equal(0, kit_List_size(sut));
    assert_true(kit_List_isEmpty(sut));
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_front(sut, &e));
    assert_null(e);
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_back(sut, &e));
    assert_null(e);
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_get(sut, &e, 0));
    assert_null(e);
}

FeatureDefine(ListRemove) {
    void *e;
    struct kit_List *sut = traits_context;

    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_remove(sut, &e, SEEDS_SIZE));
    assert_null(e);

    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_List_remove(sut, &e, 0));
    assert_string_equal(SEEDS[0], (char *) e);

    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_List_remove(sut, &e, 3));
    assert_string_equal(SEEDS[4], (char *) e);

    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_List_remove(sut, &e, 1));
    assert_string_equal(SEEDS[2], (char *) e);

    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_List_remove(sut, &e, 1));
    assert_string_equal(SEEDS[3], (char *) e);

    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_List_remove(sut, &e, 0));
    assert_string_equal(SEEDS[1], (char *) e);

    assert_equal(SEEDS_SIZE - 5, kit_List_size(sut));
    assert_false(kit_List_isEmpty(sut));

    const size_t size = kit_List_size(sut);
    for (size_t i = 0; i < size; i++) {
        assert_equal(KIT_RESULT_OK, kit_List_remove(sut, &e, 0));
    }

    assert_equal(0, kit_List_size(sut));
    assert_true(kit_List_isEmpty(sut));

    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_remove(sut, &e, 0));
    assert_null(e);
}

FeatureDefine(ListPopBack) {
    void *e;
    struct kit_List *sut = traits_context;

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_equal(SEEDS_SIZE - i, kit_List_size(sut));
        assert_false(kit_List_isEmpty(sut));

        e = NULL;
        assert_equal(KIT_RESULT_OK, kit_List_popBack(sut, &e));
        assert_string_equal(SEEDS[SEEDS_SIZE - i - 1], (char *) e);

        if (i < SEEDS_SIZE - 1) {
            e = NULL;
            assert_equal(KIT_RESULT_OK, kit_List_back(sut, &e));
            assert_string_equal(SEEDS[SEEDS_SIZE - i - 2], (char *) e);

            e = NULL;
            assert_equal(KIT_RESULT_OK, kit_List_front(sut, &e));
            assert_string_equal(SEEDS[0], (char *) e);
        }
    }

    assert_equal(0, kit_List_size(sut));
    assert_true(kit_List_isEmpty(sut));

    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_popBack(sut, &e));
    assert_null(e);

    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_back(sut, &e));
    assert_null(e);

    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_front(sut, &e));
    assert_null(e);
}

FeatureDefine(ListPopFront) {
    void *e;
    struct kit_List *sut = traits_context;

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_equal(SEEDS_SIZE - i, kit_List_size(sut));
        assert_false(kit_List_isEmpty(sut));

        e = NULL;
        assert_equal(KIT_RESULT_OK, kit_List_popFront(sut, &e));
        assert_string_equal(SEEDS[i], (char *) e);

        if (i < SEEDS_SIZE - 1) {
            e = NULL;
            assert_equal(KIT_RESULT_OK, kit_List_back(sut, &e));
            assert_string_equal(SEEDS[SEEDS_SIZE - 1], (char *) e);

            e = NULL;
            assert_equal(KIT_RESULT_OK, kit_List_front(sut, &e));
            assert_string_equal(SEEDS[i + 1], (char *) e);
        }
    }

    assert_equal(0, kit_List_size(sut));
    assert_true(kit_List_isEmpty(sut));

    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_popFront(sut, &e));
    assert_null(e);

    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_back(sut, &e));
    assert_null(e);

    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_front(sut, &e));
    assert_null(e);
}
