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
#include <kit/collections/queue.h>

FeatureDefine(QueuePop) {
    struct kit_Queue *sut = traits_context;

    assert_not_null(sut);
    assert_false(kit_Queue_isEmpty(sut));
    assert_equal(SEEDS_SIZE, kit_Queue_size(sut));

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_false(kit_Queue_isEmpty(sut));
        assert_equal(SEEDS_SIZE - i, kit_Queue_size(sut));

        assert_string_equal(SEEDS[i], Result_unwrap(kit_Queue_pop(sut)));

        if (i < SEEDS_SIZE - 1) {
            assert_equal(SEEDS[SEEDS_SIZE - 1], Result_unwrap(kit_Queue_back(sut)));
            assert_equal(SEEDS[i + 1], Result_unwrap(kit_Queue_front(sut)));
        }
    }

    assert_true(kit_Queue_isEmpty(sut));
    assert_equal(0, kit_Queue_size(sut));

    assert_equal(OutOfRangeError, Result_inspect(kit_Queue_pop(sut)));
    assert_equal(OutOfRangeError, Result_inspect(kit_Queue_back(sut)));
    assert_equal(OutOfRangeError, Result_inspect(kit_Queue_front(sut)));
}
