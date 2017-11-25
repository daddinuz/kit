/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 25, 2017 
 */

#include <seeds.h>
#include <traits/traits.h>
#include <features/feature_setters.h>
#include <kit/collections/sequence.h>

FeatureDefine(SequenceSet) {
    size_t i, j;
    void *e;
    struct kit_Sequence *sut = traits_context;

    for (i = 0, j = SEEDS_SIZE - 1; i < SEEDS_SIZE; i++, j--) {
        assert_equal(KIT_RESULT_OK, kit_Sequence_set(sut, (void *) SEEDS[j], i));
        e = NULL;
        assert_equal(KIT_RESULT_OK, kit_Sequence_get(sut, &e, i));
        assert_string_equal(SEEDS[j], (char *) e);
    }
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Sequence_set(sut, "x", i));

    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_Sequence_back(sut, &e));
    assert_string_equal(SEEDS[0], (char *) e);

    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_Sequence_front(sut, &e));
    assert_string_equal(SEEDS[SEEDS_SIZE - 1], (char *) e);
}
