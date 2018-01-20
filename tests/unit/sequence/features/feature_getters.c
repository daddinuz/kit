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
    Result result;
    struct kit_Sequence *sut = traits_context;

    assert_not_null(sut);
    assert_false(kit_Sequence_isEmpty(sut));
    assert_equal(SEEDS_SIZE, kit_Sequence_size(sut));

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        result = kit_Sequence_get(sut, i);
        assert_true(Result_isOk(result));
        assert_string_equal(SEEDS[i], Result_unwrap(result));
    }

    result = kit_Sequence_get(sut, SEEDS_SIZE);
    assert_true(Result_isError(result));
    assert_equal(OutOfRangeError, Result_inspect(result));

    kit_Sequence_clear(sut);
    assert_true(kit_Sequence_isEmpty(sut));
    assert_equal(0, kit_Sequence_size(sut));

    result = kit_Sequence_get(sut, 0);
    assert_true(Result_isError(result));
    assert_equal(OutOfRangeError, Result_inspect(result));
}

FeatureDefine(SequenceBack) {
    Result result;
    struct kit_Sequence *sut = traits_context;

    assert_not_null(sut);
    assert_false(kit_Sequence_isEmpty(sut));
    assert_equal(SEEDS_SIZE, kit_Sequence_size(sut));

    result = kit_Sequence_back(sut);
    assert_true(Result_isOk(result));
    assert_string_equal(SEEDS[SEEDS_SIZE - 1], Result_unwrap(result));

    kit_Sequence_clear(sut);
    assert_true(kit_Sequence_isEmpty(sut));
    assert_equal(0, kit_Sequence_size(sut));

    result = kit_Sequence_back(sut);
    assert_true(Result_isError(result));
    assert_equal(OutOfRangeError, Result_inspect(result));
}

FeatureDefine(SequenceFront) {
    Result result;
    struct kit_Sequence *sut = traits_context;

    assert_not_null(sut);
    assert_false(kit_Sequence_isEmpty(sut));
    assert_equal(SEEDS_SIZE, kit_Sequence_size(sut));

    result = kit_Sequence_front(sut);
    assert_true(Result_isOk(result));
    assert_string_equal(SEEDS[0], Result_unwrap(result));

    kit_Sequence_clear(sut);
    assert_true(kit_Sequence_isEmpty(sut));
    assert_equal(0, kit_Sequence_size(sut));

    result = kit_Sequence_front(sut);
    assert_true(Result_isError(result));
    assert_equal(OutOfRangeError, Result_inspect(result));
}
