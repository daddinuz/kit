/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 22, 2017 
 */

#include <seeds.h>
#include <traits/traits.h>
#include <features/feature_getters.h>
#include <kit/collections/array.h>

FeatureDefine(ArrayRaw) {
    void **raw;
    struct kit_Array *sut = traits_context;

    raw = kit_Array_raw(sut);
    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_string_equal(SEEDS[i], (char *) raw[i]);
    }
}

FeatureDefine(ArrayGet) {
    void *e;
    size_t i;
    struct kit_Array *sut = traits_context;

    for (i = 0; i < SEEDS_SIZE; i++) {
        e = NULL;
        assert_equal(KIT_RESULT_OK, kit_Array_get(sut, &e, i));
        assert_string_equal(SEEDS[i], (char *) e);
    }

    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Array_get(sut, &e, i));
    assert_null(e);
}

FeatureDefine(ArrayBack) {
    void *e = NULL;
    struct kit_Array *sut = traits_context;

    assert_equal(KIT_RESULT_OK, kit_Array_back(sut, &e));
    assert_string_equal(SEEDS[SEEDS_SIZE - 1], (char *) e);
}

FeatureDefine(ArrayFront) {
    void *e = NULL;
    struct kit_Array *sut = traits_context;

    assert_equal(KIT_RESULT_OK, kit_Array_front(sut, &e));
    assert_string_equal(SEEDS[0], (char *) e);
}

FeatureDefine(ArrayCapacity) {
    struct kit_Array *sut = traits_context;
    assert_equal(SEEDS_SIZE, kit_Array_capacity(sut));
}
