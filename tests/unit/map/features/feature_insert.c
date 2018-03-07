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
#include <features/feature_insert.h>
#include <kit/collections/map.h>
#include <kit/collections/atom.h>


#define EXPECTED_SIZE   (SEEDS_SIZE / 2)
#define COUPLES         (EXPECTED_SIZE * 2)

FeatureDefine(MapPut) {
    Result result;
    struct kit_Map *sut = traits_unit_get_context();
    assert_not_null(sut);

    assert_true(kit_Map_isEmpty(sut));
    assert_equal(0, kit_Map_size(sut));

    for (size_t i = 0, s = 1; i < COUPLES; s++) {
        kit_Atom key = Option_unwrap(kit_Atom_fromLiteral(SEEDS[i++]));
        char *value = (char *) SEEDS[i++];

        assert_false(kit_Map_has(sut, key));

        result = kit_Map_get(sut, key);
        assert_true(Result_isError(result));
        assert_equal(OutOfRangeError, Result_inspect(result));

        result = kit_Map_put(sut, key, value);
        assert_true(Result_isOk(result));
        assert_null(Result_unwrap(result));

        assert_true(kit_Map_has(sut, key));

        result = kit_Map_get(sut, key);
        assert_true(Result_isOk(result));
        assert_string_equal(value, Result_unwrap(result));

        assert_false(kit_Map_isEmpty(sut));
        assert_equal(s, kit_Map_size(sut));
    }

    assert_false(kit_Map_isEmpty(sut));
    assert_equal(EXPECTED_SIZE, kit_Map_size(sut));

    for (size_t i = 0; i < COUPLES;) {
        kit_Atom key = Option_unwrap(kit_Atom_fromLiteral(SEEDS[i++]));
        char *value = (char *) SEEDS[i++];
        char newValue[] = "x";

        assert_true(kit_Map_has(sut, key));
        assert_false(kit_Map_isEmpty(sut));
        assert_equal(EXPECTED_SIZE, kit_Map_size(sut));

        result = kit_Map_get(sut, key);
        assert_true(Result_isOk(result));
        assert_string_equal(value, Result_unwrap(result));

        result = kit_Map_put(sut, key, newValue);
        assert_true(Result_isOk(result));
        assert_string_equal(value, Result_unwrap(result));

        assert_false(kit_Map_isEmpty(sut));
        assert_true(kit_Map_has(sut, key));
        assert_equal(EXPECTED_SIZE, kit_Map_size(sut));

        result = kit_Map_get(sut, key);
        assert_true(Result_isOk(result));
        assert_string_equal(newValue, Result_unwrap(result));
    }

    assert_false(kit_Map_isEmpty(sut));
    assert_equal(EXPECTED_SIZE, kit_Map_size(sut));
}
