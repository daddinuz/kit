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
#include <kit/collections/list.h>

FeatureDefine(ListInsert) {
    struct kit_List *sut = traits_context;

    assert_not_null(sut);
    assert_true(kit_List_isEmpty(sut));
    assert_equal(0, kit_List_size(sut));
    assert_greater_equal(kit_List_capacity(sut), kit_List_size(sut));
    assert_equal(OutOfRangeError, Result_inspect(kit_List_front(sut)));
    assert_equal(OutOfRangeError, Result_inspect(kit_List_get(sut, 0)));
    assert_equal(OutOfRangeError, Result_inspect(kit_List_back(sut)));

    assert_equal(Ok, kit_List_insert(sut, 0, "a"));
    assert_false(kit_List_isEmpty(sut));
    assert_equal(1, kit_List_size(sut));
    assert_greater_equal(kit_List_capacity(sut), kit_List_size(sut));
    assert_string_equal("a", Result_unwrap(kit_List_front(sut)), "\n\n%s\n\n", (const char *) Result_unwrap(kit_List_front(sut)));
    assert_string_equal("a", Result_unwrap(kit_List_get(sut, 0)));
    assert_string_equal("a", Result_unwrap(kit_List_back(sut)));

    assert_equal(Ok, kit_List_insert(sut, 1, "c"));
    assert_false(kit_List_isEmpty(sut));
    assert_equal(2, kit_List_size(sut));
    assert_greater_equal(kit_List_capacity(sut), kit_List_size(sut));
    assert_string_equal("a", Result_unwrap(kit_List_front(sut)));
    assert_string_equal("a", Result_unwrap(kit_List_get(sut, 0)));
    assert_string_equal("c", Result_unwrap(kit_List_get(sut, 1)));
    assert_string_equal("c", Result_unwrap(kit_List_back(sut)));

    assert_equal(Ok, kit_List_insert(sut, 1, "b"));
    assert_false(kit_List_isEmpty(sut));
    assert_equal(3, kit_List_size(sut));
    assert_greater_equal(kit_List_capacity(sut), kit_List_size(sut));
    assert_string_equal("a", Result_unwrap(kit_List_front(sut)));
    assert_string_equal("a", Result_unwrap(kit_List_get(sut, 0)));
    assert_string_equal("b", Result_unwrap(kit_List_get(sut, 1)));
    assert_string_equal("c", Result_unwrap(kit_List_get(sut, 2)));
    assert_string_equal("c", Result_unwrap(kit_List_back(sut)));
}

FeatureDefine(ListPushBack) {
    struct kit_List *sut = traits_context;

    assert_not_null(sut);
    assert_true(kit_List_isEmpty(sut));
    assert_equal(0, kit_List_size(sut));
    assert_greater_equal(kit_List_capacity(sut), kit_List_size(sut));
    assert_equal(OutOfRangeError, Result_inspect(kit_List_front(sut)));
    assert_equal(OutOfRangeError, Result_inspect(kit_List_get(sut, 0)));
    assert_equal(OutOfRangeError, Result_inspect(kit_List_back(sut)));

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_equal(Ok, kit_List_pushBack(sut, (void *) SEEDS[i]));
        assert_false(kit_List_isEmpty(sut));
        assert_equal(i + 1, kit_List_size(sut));
        assert_greater_equal(kit_List_capacity(sut), kit_List_size(sut));

        assert_string_equal(SEEDS[0], Result_unwrap(kit_List_front(sut)));
        for (size_t x = 0; x < i; x++) {
            assert_string_equal(SEEDS[x], Result_unwrap(kit_List_get(sut, x)));
        }
        assert_string_equal(SEEDS[i], Result_unwrap(kit_List_back(sut)));
    }
}

FeatureDefine(ListPushFront) {
    struct kit_List *sut = traits_context;

    assert_not_null(sut);
    assert_true(kit_List_isEmpty(sut));
    assert_equal(0, kit_List_size(sut));
    assert_greater_equal(kit_List_capacity(sut), kit_List_size(sut));
    assert_equal(OutOfRangeError, Result_inspect(kit_List_front(sut)));
    assert_equal(OutOfRangeError, Result_inspect(kit_List_get(sut, 0)));
    assert_equal(OutOfRangeError, Result_inspect(kit_List_back(sut)));

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_equal(Ok, kit_List_pushFront(sut, (void *) SEEDS[i]));
        assert_false(kit_List_isEmpty(sut));
        assert_equal(i + 1, kit_List_size(sut));
        assert_greater_equal(kit_List_capacity(sut), kit_List_size(sut));

        assert_string_equal(SEEDS[i], Result_unwrap(kit_List_front(sut)));
        for (size_t x = 0; x < i; x++) {
            assert_string_equal(SEEDS[i - x], Result_unwrap(kit_List_get(sut, x)));
        }
        assert_string_equal(SEEDS[0], Result_unwrap(kit_List_back(sut)));
    }
}
