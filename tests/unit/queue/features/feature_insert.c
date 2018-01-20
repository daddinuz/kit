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
#include <kit/collections/queue.h>

FeatureDefine(QueuePush) {
    struct kit_Queue *sut = traits_context;

    assert_not_null(sut);
    assert_true(kit_Queue_isEmpty(sut));
    assert_equal(0, kit_Queue_size(sut));

    assert_equal(OutOfRangeError, Result_inspect(kit_Queue_back(sut)));
    assert_equal(OutOfRangeError, Result_inspect(kit_Queue_front(sut)));

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_equal(Ok, kit_Queue_push(sut, (void *) SEEDS[i]));
        assert_false(kit_Queue_isEmpty(sut));
        assert_equal(i + 1, kit_Queue_size(sut));

        assert_equal(SEEDS[i], Result_unwrap(kit_Queue_back(sut)));
        assert_equal(SEEDS[0], Result_unwrap(kit_Queue_front(sut)));
    }
}
