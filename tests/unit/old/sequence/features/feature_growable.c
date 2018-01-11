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
#include <kit/collections/sequence.h.old>

FeatureDefine(SequenceCapacity) {
    struct kit_Sequence *sut = traits_context;

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_greater_equal(kit_Sequence_capacity(sut), kit_Sequence_size(sut));
        kit_Sequence_pushBack(sut, (void *) SEEDS[i]);
    }
    assert_greater_equal(kit_Sequence_capacity(sut), kit_Sequence_size(sut));

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        void *e = NULL;
        assert_greater_equal(kit_Sequence_capacity(sut), kit_Sequence_size(sut));
        kit_Sequence_popBack(sut, &e);
    }
    assert_greater_equal(kit_Sequence_capacity(sut), kit_Sequence_size(sut));
}

FeatureDefine(SequenceReserve) {
    struct kit_Sequence *sut = traits_context;

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        kit_Sequence_reserve(sut, i + 1);
        assert_greater_equal(kit_Sequence_capacity(sut), kit_Sequence_size(sut));
        kit_Sequence_pushBack(sut, (void *) SEEDS[i]);
        kit_Sequence_reserve(sut, i);
        assert_greater_equal(kit_Sequence_capacity(sut), kit_Sequence_size(sut));
    }

    kit_Sequence_reserve(sut, SEEDS_SIZE);
    assert_greater_equal(kit_Sequence_capacity(sut), kit_Sequence_size(sut));
    kit_Sequence_reserve(sut, SEEDS_SIZE - 1);
    assert_greater_equal(kit_Sequence_capacity(sut), kit_Sequence_size(sut));
}

FeatureDefine(SequenceShrink) {
    struct kit_Sequence *sut = traits_context;

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        void *e = NULL;
        kit_Sequence_popBack(sut, &e);
        kit_Sequence_shrink(sut);
        assert_greater_equal(kit_Sequence_capacity(sut), kit_Sequence_size(sut));
    }
    kit_Sequence_shrink(sut);
    assert_greater_equal(kit_Sequence_capacity(sut), kit_Sequence_size(sut));
}
