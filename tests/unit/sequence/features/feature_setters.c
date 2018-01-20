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

FeatureDefine(SequencePut) {
    size_t i, j;
    struct kit_Sequence *sut = traits_context;

    for (i = 0, j = SEEDS_SIZE - 1; i < SEEDS_SIZE; i++, j--) {
        void *replacedElement = (void *) SEEDS[i];

        assert_string_equal(replacedElement, Result_unwrap(kit_Sequence_put(sut, i, (void *) SEEDS[j])));
        assert_string_equal(SEEDS[j], Result_unwrap(kit_Sequence_get(sut, i)));
    }

    assert_equal(OutOfRangeError, Result_inspect(kit_Sequence_put(sut, i, "x")));
}