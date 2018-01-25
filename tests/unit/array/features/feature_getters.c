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
#include <features/feature_getters.h>
#include <kit/collections/array.h>

FeatureDefine(ArrayRaw) {
    void **raw;
    struct kit_Array *sut = traits_context;

    raw = kit_Array_raw(sut);
    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_string_equal(SEEDS[i], (char *) raw[i]);
    }
}

FeatureDefine(ArrayGet) {
    size_t i;
    Result result;
    struct kit_Array *sut = traits_context;

    for (i = 0; i < SEEDS_SIZE; i++) {
        result = kit_Array_get(sut, i);
        assert_true(Result_isOk(result));
        assert_string_equal(SEEDS[i], (char *) Result_unwrap(result));
    }

    result = kit_Array_get(sut, i);
    assert_true(Result_isError(result));
    assert_equal(OutOfRangeError, Result_inspect(result));
}

FeatureDefine(ArrayBack) {
    Result result;
    struct kit_Array *sut = traits_context;

    result = kit_Array_back(sut);
    assert_true(Result_isOk(result));
    assert_string_equal(SEEDS[SEEDS_SIZE - 1], (char *) Result_unwrap(result));
}

FeatureDefine(ArrayFront) {
    Result result;
    struct kit_Array *sut = traits_context;

    result = kit_Array_front(sut);
    assert_true(Result_isOk(result));
    assert_string_equal(SEEDS[0], (char *) Result_unwrap(result));
}

FeatureDefine(ArrayCapacity) {
    struct kit_Array *sut = traits_context;
    assert_equal(SEEDS_SIZE, kit_Array_capacity(sut));
}
