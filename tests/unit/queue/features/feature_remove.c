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
    void *e;
    struct kit_Queue *sut = traits_context;

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_equal(SEEDS_SIZE - i, kit_Queue_size(sut));
        assert_false(kit_Queue_isEmpty(sut));

        e = NULL;
        assert_equal(KIT_RESULT_OK, kit_Queue_pop(sut, &e));
        assert_string_equal(SEEDS[i], (char *) e);

        if (i < SEEDS_SIZE - 1) {
            e = NULL;
            assert_equal(KIT_RESULT_OK, kit_Queue_back(sut, &e));
            assert_string_equal(SEEDS[SEEDS_SIZE - 1], (char *) e);

            e = NULL;
            assert_equal(KIT_RESULT_OK, kit_Queue_front(sut, &e));
            assert_string_equal(SEEDS[i + 1], (char *) e);
        }
    }

    assert_equal(0, kit_Queue_size(sut));
    assert_true(kit_Queue_isEmpty(sut));

    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Queue_pop(sut, &e));
    assert_null(e);

    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Queue_back(sut, &e));
    assert_null(e);

    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Queue_front(sut, &e));
    assert_null(e);
}
