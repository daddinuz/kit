/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 26, 2017 
 */

#include <seeds.h>
#include <traits/traits.h>
#include <features/feature_insert.h>
#include <kit/collections/stack.h>

FeatureDefine(StackPush) {
    struct kit_Stack *sut = traits_context;

    assert_not_null(sut);
    assert_true(kit_Stack_isEmpty(sut));
    assert_equal(0, kit_Stack_size(sut));

    assert_equal(OutOfRangeError, Result_inspect(kit_Stack_back(sut)));

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_equal(Ok, kit_Stack_push(sut, (void *) SEEDS[i]));
        assert_false(kit_Stack_isEmpty(sut));
        assert_equal(i + 1, kit_Stack_size(sut));
        assert_string_equal(SEEDS[i], Result_unwrap(kit_Stack_back(sut)));
    }
}
