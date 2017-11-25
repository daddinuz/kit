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
    size_t i;
    void *e;
    struct kit_List *sut = traits_context;
    for (i = 0; i < SEEDS_SIZE; i++) {
        e = NULL;
        assert_equal(KIT_RESULT_OK, kit_List_get(sut, &e, i));
        assert_string_equal(SEEDS[i], (char *) e);
    }
    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_get(sut, &e, i));
    assert_null(e);
}

FeatureDefine(ListBack) {
    void *e = NULL;
    struct kit_List *sut = traits_context;
    assert_equal(KIT_RESULT_OK, kit_List_back(sut, &e));
    assert_string_equal(SEEDS[SEEDS_SIZE - 1], (char *) e);
}

FeatureDefine(ListFront) {
    void *e = NULL;
    struct kit_List *sut = traits_context;
    assert_equal(KIT_RESULT_OK, kit_List_front(sut, &e));
    assert_string_equal(SEEDS[0], (char *) e);
}

FeatureDefine(ListSize) {
    struct kit_List *sut = traits_context;
    assert_equal(SEEDS_SIZE, kit_List_size(sut));
}
