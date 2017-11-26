/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 26, 2017 
 */

#include <seeds.h>
#include <traits/traits.h>
#include <features/feature_remove.h>
#include <kit/collections/stack.h>

FeatureDefine(StackPop) {
    void *e;
    struct kit_Stack *sut = traits_context;

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_equal(SEEDS_SIZE - i, kit_Stack_size(sut));
        assert_false(kit_Stack_isEmpty(sut));

        e = NULL;
        assert_equal(KIT_RESULT_OK, kit_Stack_pop(sut, &e));
        assert_string_equal(SEEDS[SEEDS_SIZE - i - 1], (char *) e);

        if (i < SEEDS_SIZE - 1) {
            e = NULL;
            assert_equal(KIT_RESULT_OK, kit_Stack_back(sut, &e));
            assert_string_equal(SEEDS[SEEDS_SIZE - i - 2], (char *) e);
        }
    }

    assert_equal(0, kit_Stack_size(sut));
    assert_true(kit_Stack_isEmpty(sut));

    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Stack_pop(sut, &e));
    assert_null(e);

    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Stack_back(sut, &e));
    assert_null(e);
}
