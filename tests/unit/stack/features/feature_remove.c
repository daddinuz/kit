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
    struct kit_Stack *sut = traits_context;

    assert_not_null(sut);
    assert_false(kit_Stack_isEmpty(sut));
    assert_equal(SEEDS_SIZE, kit_Stack_size(sut));

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_false(kit_Stack_isEmpty(sut));
        assert_equal(SEEDS_SIZE - i, kit_Stack_size(sut));

        assert_string_equal(SEEDS[SEEDS_SIZE - i - 1], Result_unwrap(kit_Stack_pop(sut)));

        if (i < SEEDS_SIZE - 1) {
            assert_string_equal(SEEDS[SEEDS_SIZE - i - 2], Result_unwrap(kit_Stack_back(sut)));
        }
    }

    assert_true(kit_Stack_isEmpty(sut));
    assert_equal(0, kit_Stack_size(sut));

    assert_equal(OutOfRangeError, Result_inspect(kit_Stack_pop(sut)));
    assert_equal(OutOfRangeError, Result_inspect(kit_Stack_back(sut)));
}
