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
#include <kit/collections/sequence.h>

FeatureDefine(SequenceExpand) {
    struct kit_Sequence *sut = traits_context;

    assert_not_null(sut);
    assert_true(kit_Sequence_isEmpty(sut));
    assert_equal(0, kit_Sequence_size(sut));

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_equal(Ok, kit_Sequence_expand(sut, i + 1));
        assert_greater_equal(kit_Sequence_capacity(sut), kit_Sequence_size(sut));
        assert_equal(Ok, kit_Sequence_pushBack(sut, (void *) SEEDS[i]));
        assert_equal(Ok, kit_Sequence_expand(sut, i));
        assert_greater_equal(kit_Sequence_capacity(sut), kit_Sequence_size(sut));
    }
}

FeatureDefine(SequenceShrink) {
    Result result;
    struct kit_Sequence *sut = traits_context;

    assert_not_null(sut);
    assert_false(kit_Sequence_isEmpty(sut));
    assert_equal(SEEDS_SIZE, kit_Sequence_size(sut));

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        result = kit_Sequence_popBack(sut);
        assert_true(Result_isOk(result));
        assert_equal(Ok, Result_inspect(result));
        assert_equal(Ok, kit_Sequence_shrink(sut));
        assert_greater_equal(kit_Sequence_capacity(sut), kit_Sequence_size(sut));
    }

    assert_equal(Ok, kit_Sequence_shrink(sut));
    assert_greater_equal(kit_Sequence_capacity(sut), kit_Sequence_size(sut));
}
