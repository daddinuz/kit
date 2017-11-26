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
    void *e = NULL;
    struct kit_Queue *sut = traits_context;

    assert_equal(0, kit_Queue_size(sut));
    assert_true(kit_Queue_isEmpty(sut));

    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Queue_back(sut, &e));
    assert_null(e);

    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Queue_front(sut, &e));
    assert_null(e);

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_equal(KIT_RESULT_OK, kit_Queue_push(sut, (void *) SEEDS[i]));
        assert_equal(i + 1, kit_Queue_size(sut));
        assert_false(kit_Queue_isEmpty(sut));

        e = NULL;
        assert_equal(KIT_RESULT_OK, kit_Queue_back(sut, &e));
        assert_string_equal(SEEDS[i], (char *) e);

        e = NULL;
        assert_equal(KIT_RESULT_OK, kit_Queue_front(sut, &e));
        assert_string_equal(SEEDS[0], (char *) e);
    }
}
