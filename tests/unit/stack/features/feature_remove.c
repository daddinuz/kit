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
#include <kit/collections/stack.h>

FeatureDefine(StackPop) {
    struct kit_Stack *sut = traits_context;

    assert_not_null(sut);
    assert_false(kit_Stack_isEmpty(sut));
    assert_equal(SEEDS_SIZE, kit_Stack_size(sut));

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_false(kit_Stack_isEmpty(sut));
        assert_equal(SEEDS_SIZE - i, kit_Stack_size(sut));

        assert_string_equal(SEEDS[SEEDS_SIZE - i - 1], Result_unwrap(kit_Stack_pop(sut)));

        if (i < SEEDS_SIZE - 1) {
            assert_string_equal(SEEDS[SEEDS_SIZE - i - 2], Result_unwrap(kit_Stack_back(sut)));
        }
    }

    assert_true(kit_Stack_isEmpty(sut));
    assert_equal(0, kit_Stack_size(sut));

    assert_equal(OutOfRangeError, Result_inspect(kit_Stack_pop(sut)));
    assert_equal(OutOfRangeError, Result_inspect(kit_Stack_back(sut)));
}
