/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 25, 2017 
 */

#include <seeds.h>
#include <traits/traits.h>
#include <features/feature_getters.h>
#include <kit/collections/list.h>

FeatureDefine(ListGet) {
    Result result;
    struct kit_List *sut = traits_context;

    assert_not_null(sut);
    assert_false(kit_List_isEmpty(sut));
    assert_equal(SEEDS_SIZE, kit_List_size(sut));

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        result = kit_List_get(sut, i);
        assert_true(Result_isOk(result));
        assert_string_equal(SEEDS[i], Result_unwrap(result));
    }

    result = kit_List_get(sut, SEEDS_SIZE);
    assert_true(Result_isError(result));
    assert_equal(OutOfRangeError, Result_inspect(result));

    kit_List_clear(sut);
    assert_true(kit_List_isEmpty(sut));
    assert_equal(0, kit_List_size(sut));

    result = kit_List_get(sut, 0);
    assert_true(Result_isError(result));
    assert_equal(OutOfRangeError, Result_inspect(result));
}

FeatureDefine(ListBack) {
    Result result;
    struct kit_List *sut = traits_context;

    assert_not_null(sut);
    assert_false(kit_List_isEmpty(sut));
    assert_equal(SEEDS_SIZE, kit_List_size(sut));

    result = kit_List_back(sut);
    assert_true(Result_isOk(result));
    assert_string_equal(SEEDS[SEEDS_SIZE - 1], Result_unwrap(result));

    kit_List_clear(sut);
    assert_true(kit_List_isEmpty(sut));
    assert_equal(0, kit_List_size(sut));

    result = kit_List_back(sut);
    assert_true(Result_isError(result));
    assert_equal(OutOfRangeError, Result_inspect(result));
}

FeatureDefine(ListFront) {
    Result result;
    struct kit_List *sut = traits_context;

    assert_not_null(sut);
    assert_false(kit_List_isEmpty(sut));
    assert_equal(SEEDS_SIZE, kit_List_size(sut));

    result = kit_List_front(sut);
    assert_true(Result_isOk(result));
    assert_string_equal(SEEDS[0], Result_unwrap(result));

    kit_List_clear(sut);
    assert_true(kit_List_isEmpty(sut));
    assert_equal(0, kit_List_size(sut));

    result = kit_List_front(sut);
    assert_true(Result_isError(result));
    assert_equal(OutOfRangeError, Result_inspect(result));
}
