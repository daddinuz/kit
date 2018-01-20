/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 26, 2017 
 */

#include <seeds.h>
#include <traits/traits.h>
#include <features/feature_growable.h>
#include <kit/collections/list.h>

FeatureDefine(ListExpand) {
    struct kit_List *sut = traits_context;

    assert_not_null(sut);
    assert_true(kit_List_isEmpty(sut));
    assert_equal(0, kit_List_size(sut));

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_equal(Ok, kit_List_expand(sut, i + 1));
        assert_greater_equal(kit_List_capacity(sut), kit_List_size(sut));
        assert_equal(Ok, kit_List_pushBack(sut, (void *) SEEDS[i]));
        assert_equal(Ok, kit_List_expand(sut, i));
        assert_greater_equal(kit_List_capacity(sut), kit_List_size(sut));
    }
}

FeatureDefine(ListShrink) {
    Result result;
    struct kit_List *sut = traits_context;

    assert_not_null(sut);
    assert_false(kit_List_isEmpty(sut));
    assert_equal(SEEDS_SIZE, kit_List_size(sut));

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        result = kit_List_popBack(sut);
        assert_true(Result_isOk(result));
        assert_equal(Ok, Result_inspect(result));
        assert_equal(Ok, kit_List_shrink(sut));
        assert_greater_equal(kit_List_capacity(sut), kit_List_size(sut));
    }

    assert_equal(Ok, kit_List_shrink(sut));
    assert_greater_equal(kit_List_capacity(sut), kit_List_size(sut));
}
