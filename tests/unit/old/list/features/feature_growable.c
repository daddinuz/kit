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
#include <kit/collections/list.h.old>

FeatureDefine(ListCapacity) {
    struct kit_List *sut = traits_context;

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_greater_equal(kit_List_capacity(sut), kit_List_size(sut));
        kit_List_pushBack(sut, (void *) SEEDS[i]);
    }
    assert_greater_equal(kit_List_capacity(sut), kit_List_size(sut));

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        void *e = NULL;
        assert_greater_equal(kit_List_capacity(sut), kit_List_size(sut));
        kit_List_popBack(sut, &e);
    }
    assert_greater_equal(kit_List_capacity(sut), kit_List_size(sut));
}

FeatureDefine(ListReserve) {
    struct kit_List *sut = traits_context;

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        kit_List_reserve(sut, i + 1);
        assert_greater_equal(kit_List_capacity(sut), kit_List_size(sut));
        kit_List_pushBack(sut, (void *) SEEDS[i]);
        kit_List_reserve(sut, i);
        assert_greater_equal(kit_List_capacity(sut), kit_List_size(sut));
    }

    kit_List_reserve(sut, SEEDS_SIZE);
    assert_greater_equal(kit_List_capacity(sut), kit_List_size(sut));
    kit_List_reserve(sut, SEEDS_SIZE - 1);
    assert_greater_equal(kit_List_capacity(sut), kit_List_size(sut));
}

FeatureDefine(ListShrink) {
    struct kit_List *sut = traits_context;

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        void *e = NULL;
        kit_List_popBack(sut, &e);
        kit_List_shrink(sut);
        assert_greater_equal(kit_List_capacity(sut), kit_List_size(sut));
    }
    kit_List_shrink(sut);
    assert_greater_equal(kit_List_capacity(sut), kit_List_size(sut));
}
