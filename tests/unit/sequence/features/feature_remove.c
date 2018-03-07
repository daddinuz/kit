/*
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 *
 * Copyright (c) 2018 Davide Di Carlo
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <seeds.h>
#include <traits/traits.h>
#include <features/feature_remove.h>
#include <kit/collections/sequence.h>

FeatureDefine(SequenceClear) {
    struct kit_Sequence *sut = traits_unit_get_context();

    assert_not_null(sut);
    assert_false(kit_Sequence_isEmpty(sut));
    assert_equal(SEEDS_SIZE, kit_Sequence_size(sut));
    assert_greater_equal(kit_Sequence_capacity(sut), kit_Sequence_size(sut));
    assert_equal(Ok, Result_inspect(kit_Sequence_front(sut)));
    assert_equal(Ok, Result_inspect(kit_Sequence_get(sut, SEEDS_SIZE / 2)));
    assert_equal(Ok, Result_inspect(kit_Sequence_back(sut)));

    kit_Sequence_clear(sut);

    assert_true(kit_Sequence_isEmpty(sut));
    assert_equal(0, kit_Sequence_size(sut));
    assert_greater_equal(kit_Sequence_capacity(sut), kit_Sequence_size(sut));
    assert_equal(OutOfRangeError, Result_inspect(kit_Sequence_front(sut)));
    assert_equal(OutOfRangeError, Result_inspect(kit_Sequence_get(sut, SEEDS_SIZE / 2)));
    assert_equal(OutOfRangeError, Result_inspect(kit_Sequence_back(sut)));
}

FeatureDefine(SequenceRemove) {
    struct kit_Sequence *sut = traits_unit_get_context();

    assert_not_null(sut);
    assert_false(kit_Sequence_isEmpty(sut));
    assert_equal(SEEDS_SIZE, kit_Sequence_size(sut));
    assert_greater_equal(kit_Sequence_capacity(sut), kit_Sequence_size(sut));

    assert_equal(OutOfRangeError, Result_inspect(kit_Sequence_remove(sut, SEEDS_SIZE)));
    assert_string_equal(SEEDS[0], Result_unwrap(kit_Sequence_remove(sut, 0)));
    assert_string_equal(SEEDS[4], Result_unwrap(kit_Sequence_remove(sut, 3)));
    assert_string_equal(SEEDS[2], Result_unwrap(kit_Sequence_remove(sut, 1)));
    assert_string_equal(SEEDS[3], Result_unwrap(kit_Sequence_remove(sut, 1)));
    assert_string_equal(SEEDS[1], Result_unwrap(kit_Sequence_remove(sut, 0)));

    assert_equal(SEEDS_SIZE - 5, kit_Sequence_size(sut));
    assert_greater_equal(kit_Sequence_capacity(sut), kit_Sequence_size(sut));

    const size_t size = kit_Sequence_size(sut);
    for (size_t i = 0; i < size; i++) {
        assert_true(Result_isOk(kit_Sequence_remove(sut, 0)));
    }

    assert_equal(0, kit_Sequence_size(sut));
    assert_true(kit_Sequence_isEmpty(sut));
    assert_greater_equal(kit_Sequence_capacity(sut), kit_Sequence_size(sut));
    assert_equal(OutOfRangeError, Result_inspect(kit_Sequence_remove(sut, 0)));
}

FeatureDefine(SequencePopBack) {
    struct kit_Sequence *sut = traits_unit_get_context();

    assert_not_null(sut);
    assert_false(kit_Sequence_isEmpty(sut));
    assert_equal(SEEDS_SIZE, kit_Sequence_size(sut));
    assert_greater_equal(kit_Sequence_capacity(sut), kit_Sequence_size(sut));

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_false(kit_Sequence_isEmpty(sut));
        assert_equal(SEEDS_SIZE - i, kit_Sequence_size(sut));
        assert_string_equal(SEEDS[SEEDS_SIZE - i - 1], Result_unwrap(kit_Sequence_popBack(sut)));

        if (i < SEEDS_SIZE - 1) {
            assert_string_equal(SEEDS[SEEDS_SIZE - i - 2], Result_unwrap(kit_Sequence_back(sut)));
            assert_string_equal(SEEDS[0], Result_unwrap(kit_Sequence_front(sut)));
        }
    }

    assert_true(kit_Sequence_isEmpty(sut));
    assert_equal(0, kit_Sequence_size(sut));
    assert_greater_equal(kit_Sequence_capacity(sut), kit_Sequence_size(sut));
    assert_equal(OutOfRangeError, Result_inspect(kit_Sequence_front(sut)));
    assert_equal(OutOfRangeError, Result_inspect(kit_Sequence_get(sut, SEEDS_SIZE / 2)));
    assert_equal(OutOfRangeError, Result_inspect(kit_Sequence_back(sut)));
}

FeatureDefine(SequencePopFront) {
    struct kit_Sequence *sut = traits_unit_get_context();

    assert_not_null(sut);
    assert_false(kit_Sequence_isEmpty(sut));
    assert_equal(SEEDS_SIZE, kit_Sequence_size(sut));
    assert_greater_equal(kit_Sequence_capacity(sut), kit_Sequence_size(sut));

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_false(kit_Sequence_isEmpty(sut));
        assert_equal(SEEDS_SIZE - i, kit_Sequence_size(sut));
        assert_string_equal(SEEDS[i], Result_unwrap(kit_Sequence_popFront(sut)));

        if (i < SEEDS_SIZE - 1) {
            assert_string_equal(SEEDS[SEEDS_SIZE - 1], Result_unwrap(kit_Sequence_back(sut)));
            assert_string_equal(SEEDS[i + 1], Result_unwrap(kit_Sequence_front(sut)));
        }
    }

    assert_true(kit_Sequence_isEmpty(sut));
    assert_equal(0, kit_Sequence_size(sut));
    assert_greater_equal(kit_Sequence_capacity(sut), kit_Sequence_size(sut));
    assert_equal(OutOfRangeError, Result_inspect(kit_Sequence_front(sut)));
    assert_equal(OutOfRangeError, Result_inspect(kit_Sequence_get(sut, SEEDS_SIZE / 2)));
    assert_equal(OutOfRangeError, Result_inspect(kit_Sequence_back(sut)));
}
