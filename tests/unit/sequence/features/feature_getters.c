/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 25, 2017 
 */

#include <seeds.h>
#include <traits/traits.h>
#include <features/feature_getters.h>
#include <kit/collections/sequence.h>

FeatureDefine(SequenceGet) {
    size_t i;
    void *e;
    struct kit_Sequence *sut = traits_context;
    for (i = 0; i < SEEDS_SIZE; i++) {
        e = NULL;
        assert_equal(KIT_RESULT_OK, kit_Sequence_get(sut, &e, i));
        assert_string_equal(SEEDS[i], (char *) e);
    }
    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Sequence_get(sut, &e, i));
    assert_null(e);
}

FeatureDefine(SequenceBack) {
    void *e = NULL;
    struct kit_Sequence *sut = traits_context;
    assert_equal(KIT_RESULT_OK, kit_Sequence_back(sut, &e));
    assert_string_equal(SEEDS[SEEDS_SIZE - 1], (char *) e);
}

FeatureDefine(SequenceFront) {
    void *e = NULL;
    struct kit_Sequence *sut = traits_context;
    assert_equal(KIT_RESULT_OK, kit_Sequence_front(sut, &e));
    assert_string_equal(SEEDS[0], (char *) e);
}

FeatureDefine(SequenceSize) {
    struct kit_Sequence *sut = traits_context;
    assert_equal(SEEDS_SIZE, kit_Sequence_size(sut));
}
