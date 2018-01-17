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
    size_t i;
    Result result;
    struct kit_Array *sut = traits_context;

    for (i = 0; i < SEEDS_SIZE; i++) {
        result = kit_Array_get(sut, i);
        assert_true(Result_isOk(result));
        assert_string_equal(SEEDS[i], (char *) Result_unwrap(result));
    }

    result = kit_Array_get(sut, i);
    assert_true(Result_isError(result));
    assert_equal(OutOfRangeError, Result_inspect(result));
}

FeatureDefine(ArrayBack) {
    Result result;
    struct kit_Array *sut = traits_context;

    result = kit_Array_back(sut);
    assert_true(Result_isOk(result));
    assert_string_equal(SEEDS[SEEDS_SIZE - 1], (char *) Result_unwrap(result));
}

FeatureDefine(ArrayFront) {
    Result result;
    struct kit_Array *sut = traits_context;

    result = kit_Array_front(sut);
    assert_true(Result_isOk(result));
    assert_string_equal(SEEDS[0], (char *) Result_unwrap(result));
}

FeatureDefine(ArrayCapacity) {
    struct kit_Array *sut = traits_context;
    assert_equal(SEEDS_SIZE, kit_Array_capacity(sut));
}
