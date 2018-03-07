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
#include <features/feature_setters.h>
#include <kit/collections/sequence.h>

FeatureDefine(SequencePut) {
    size_t i, j;
    struct kit_Sequence *sut = traits_unit_get_context();

    for (i = 0, j = SEEDS_SIZE - 1; i < SEEDS_SIZE; i++, j--) {
        void *replacedElement = (void *) SEEDS[i];

        assert_string_equal(replacedElement, Result_unwrap(kit_Sequence_put(sut, i, (void *) SEEDS[j])));
        assert_string_equal(SEEDS[j], Result_unwrap(kit_Sequence_get(sut, i)));
    }

    assert_equal(OutOfRangeError, Result_inspect(kit_Sequence_put(sut, i, "x")));
}
