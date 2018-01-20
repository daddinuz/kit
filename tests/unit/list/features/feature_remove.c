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
    struct kit_List *sut = traits_context;

    assert_not_null(sut);
    assert_false(kit_List_isEmpty(sut));
    assert_equal(SEEDS_SIZE, kit_List_size(sut));
    assert_greater_equal(kit_List_capacity(sut), kit_List_size(sut));
    assert_equal(Ok, Result_inspect(kit_List_front(sut)));
    assert_equal(Ok, Result_inspect(kit_List_get(sut, SEEDS_SIZE / 2)));
    assert_equal(Ok, Result_inspect(kit_List_back(sut)));

    kit_List_clear(sut);

    assert_true(kit_List_isEmpty(sut));
    assert_equal(0, kit_List_size(sut));
    assert_greater_equal(kit_List_capacity(sut), kit_List_size(sut));
    assert_equal(OutOfRangeError, Result_inspect(kit_List_front(sut)));
    assert_equal(OutOfRangeError, Result_inspect(kit_List_get(sut, SEEDS_SIZE / 2)));
    assert_equal(OutOfRangeError, Result_inspect(kit_List_back(sut)));
}

FeatureDefine(ListRemove) {
    struct kit_List *sut = traits_context;

    assert_not_null(sut);
    assert_false(kit_List_isEmpty(sut));
    assert_equal(SEEDS_SIZE, kit_List_size(sut));
    assert_greater_equal(kit_List_capacity(sut), kit_List_size(sut));

    assert_equal(OutOfRangeError, Result_inspect(kit_List_remove(sut, SEEDS_SIZE)));
    assert_string_equal(SEEDS[0], Result_unwrap(kit_List_remove(sut, 0)));
    assert_string_equal(SEEDS[4], Result_unwrap(kit_List_remove(sut, 3)));
    assert_string_equal(SEEDS[2], Result_unwrap(kit_List_remove(sut, 1)));
    assert_string_equal(SEEDS[3], Result_unwrap(kit_List_remove(sut, 1)));
    assert_string_equal(SEEDS[1], Result_unwrap(kit_List_remove(sut, 0)));

    assert_equal(SEEDS_SIZE - 5, kit_List_size(sut));
    assert_greater_equal(kit_List_capacity(sut), kit_List_size(sut));

    const size_t size = kit_List_size(sut);
    for (size_t i = 0; i < size; i++) {
        assert_true(Result_isOk(kit_List_remove(sut, 0)));
    }

    assert_equal(0, kit_List_size(sut));
    assert_true(kit_List_isEmpty(sut));
    assert_greater_equal(kit_List_capacity(sut), kit_List_size(sut));
    assert_equal(OutOfRangeError, Result_inspect(kit_List_remove(sut, 0)));
}

FeatureDefine(ListPopBack) {
    struct kit_List *sut = traits_context;

    assert_not_null(sut);
    assert_false(kit_List_isEmpty(sut));
    assert_equal(SEEDS_SIZE, kit_List_size(sut));
    assert_greater_equal(kit_List_capacity(sut), kit_List_size(sut));

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_false(kit_List_isEmpty(sut));
        assert_equal(SEEDS_SIZE - i, kit_List_size(sut));
        assert_string_equal(SEEDS[SEEDS_SIZE - i - 1], Result_unwrap(kit_List_popBack(sut)));

        if (i < SEEDS_SIZE - 1) {
            assert_string_equal(SEEDS[SEEDS_SIZE - i - 2], Result_unwrap(kit_List_back(sut)));
            assert_string_equal(SEEDS[0], Result_unwrap(kit_List_front(sut)));
        }
    }

    assert_true(kit_List_isEmpty(sut));
    assert_equal(0, kit_List_size(sut));
    assert_greater_equal(kit_List_capacity(sut), kit_List_size(sut));
    assert_equal(OutOfRangeError, Result_inspect(kit_List_front(sut)));
    assert_equal(OutOfRangeError, Result_inspect(kit_List_get(sut, SEEDS_SIZE / 2)));
    assert_equal(OutOfRangeError, Result_inspect(kit_List_back(sut)));
}

FeatureDefine(ListPopFront) {
    struct kit_List *sut = traits_context;

    assert_not_null(sut);
    assert_false(kit_List_isEmpty(sut));
    assert_equal(SEEDS_SIZE, kit_List_size(sut));
    assert_greater_equal(kit_List_capacity(sut), kit_List_size(sut));

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_false(kit_List_isEmpty(sut));
        assert_equal(SEEDS_SIZE - i, kit_List_size(sut));
        assert_string_equal(SEEDS[i], Result_unwrap(kit_List_popFront(sut)));

        if (i < SEEDS_SIZE - 1) {
            assert_string_equal(SEEDS[SEEDS_SIZE - 1], Result_unwrap(kit_List_back(sut)));
            assert_string_equal(SEEDS[i + 1], Result_unwrap(kit_List_front(sut)));
        }
    }

    assert_true(kit_List_isEmpty(sut));
    assert_equal(0, kit_List_size(sut));
    assert_greater_equal(kit_List_capacity(sut), kit_List_size(sut));
    assert_equal(OutOfRangeError, Result_inspect(kit_List_front(sut)));
    assert_equal(OutOfRangeError, Result_inspect(kit_List_get(sut, SEEDS_SIZE / 2)));
    assert_equal(OutOfRangeError, Result_inspect(kit_List_back(sut)));
}
