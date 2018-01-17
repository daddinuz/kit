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
    size_t i, j;
    Result result;
    struct kit_Array *sut = traits_context;

    for (i = 0, j = SEEDS_SIZE - 1; i < SEEDS_SIZE; i++, j--) {
        result = kit_Array_put(sut, i, (void *) SEEDS[j]);
        assert_true(Result_isOk(result));
        assert_string_equal(SEEDS[i], (char *) Result_unwrap(result));

        result = kit_Array_get(sut, i);
        assert_true(Result_isOk(result));
        assert_string_equal(SEEDS[j], (char *) Result_unwrap(result));
    }
    result = kit_Array_put(sut, i, "x");
    assert_true(Result_isError(result));
    assert_equal(OutOfRangeError, Result_inspect(result));

    result = kit_Array_back(sut);
    assert_true(Result_isOk(result));
    assert_string_equal(SEEDS[0], (char *) Result_unwrap(result));

    result = kit_Array_front(sut);
    assert_true(Result_isOk(result));
    assert_string_equal(SEEDS[SEEDS_SIZE - 1], (char *) Result_unwrap(result));
}

FeatureDefine(ArrayClear) {
    Result result;
    struct kit_Array *sut = traits_context;

    kit_Array_clear(sut);
    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        result = kit_Array_get(sut, i);
        assert_true(Result_isOk(result));
        assert_null(Result_unwrap(result));
    }
    result = kit_Array_back(sut);
    assert_true(Result_isOk(result));
    assert_null(Result_unwrap(result));

    result = kit_Array_front(sut);
    assert_true(Result_isOk(result));
    assert_null(Result_unwrap(result));
}
