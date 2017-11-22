/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 22, 2017
 */

#include <seeds.h>
#include <traits/traits.h>
#include <features/feature_setters.h>
#include <kit/collections/array.h>

FeatureDefine(ArraySet) {
    void *e;
    size_t i, j;
    struct kit_Array *sut = traits_context;

    for (i = 0, j = SEEDS_SIZE - 1; i < SEEDS_SIZE; i++, j--) {
        assert_equal(KIT_RESULT_OK, kit_Array_set(sut, (void *) SEEDS[j], i));
        e = NULL;
        assert_equal(KIT_RESULT_OK, kit_Array_get(sut, &e, i));
        assert_string_equal(SEEDS[j], (char *) e);
    }
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Array_set(sut, "x", i));

    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_Array_back(sut, &e));
    assert_string_equal(SEEDS[0], (char *) e);

    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_Array_front(sut, &e));
    assert_string_equal(SEEDS[SEEDS_SIZE - 1], (char *) e);
}

FeatureDefine(ArrayClear) {
    void *e;
    struct kit_Array *sut = traits_context;

    kit_Array_clear(sut);
    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        e = "x";
        assert_equal(KIT_RESULT_OK, kit_Array_get(sut, &e, i));
        assert_null(e);
    }
    e = "x";
    assert_equal(KIT_RESULT_OK, kit_Array_back(sut, &e));
    assert_null(e);

    e = "x";
    assert_equal(KIT_RESULT_OK, kit_Array_front(sut, &e));
    assert_null(e);
}
