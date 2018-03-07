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
#include <kit/collections/list.h>


FeatureDefine(ListGet) {
    Result result;
    struct kit_List *sut = traits_unit_get_context();

    assert_not_null(sut);
    assert_false(kit_List_isEmpty(sut));
    assert_equal(SEEDS_SIZE, kit_List_size(sut));

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        result = kit_List_get(sut, i);
        assert_true(Result_isOk(result));
        assert_string_equal(SEEDS[i], Result_unwrap(result));
    }

    result = kit_List_get(sut, SEEDS_SIZE);
    assert_true(Result_isError(result));
    assert_equal(OutOfRangeError, Result_inspect(result));

    kit_List_clear(sut);
    assert_true(kit_List_isEmpty(sut));
    assert_equal(0, kit_List_size(sut));

    result = kit_List_get(sut, 0);
    assert_true(Result_isError(result));
    assert_equal(OutOfRangeError, Result_inspect(result));
}

FeatureDefine(ListBack) {
    Result result;
    struct kit_List *sut = traits_unit_get_context();

    assert_not_null(sut);
    assert_false(kit_List_isEmpty(sut));
    assert_equal(SEEDS_SIZE, kit_List_size(sut));

    result = kit_List_back(sut);
    assert_true(Result_isOk(result));
    assert_string_equal(SEEDS[SEEDS_SIZE - 1], Result_unwrap(result));

    kit_List_clear(sut);
    assert_true(kit_List_isEmpty(sut));
    assert_equal(0, kit_List_size(sut));

    result = kit_List_back(sut);
    assert_true(Result_isError(result));
    assert_equal(OutOfRangeError, Result_inspect(result));
}

FeatureDefine(ListFront) {
    Result result;
    struct kit_List *sut = traits_unit_get_context();

    assert_not_null(sut);
    assert_false(kit_List_isEmpty(sut));
    assert_equal(SEEDS_SIZE, kit_List_size(sut));

    result = kit_List_front(sut);
    assert_true(Result_isOk(result));
    assert_string_equal(SEEDS[0], Result_unwrap(result));

    kit_List_clear(sut);
    assert_true(kit_List_isEmpty(sut));
    assert_equal(0, kit_List_size(sut));

    result = kit_List_front(sut);
    assert_true(Result_isError(result));
    assert_equal(OutOfRangeError, Result_inspect(result));
}
