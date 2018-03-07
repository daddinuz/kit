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
#include <traits-unit/traits-unit.h>
#include <kit/collections/pair.h>

/*
 * Features declarations
 */
FeatureDeclare(PairEssentials);

/*
 * Describe our test case
 */
Describe("Pair",
         Trait(
                 "Essentials",
                 Run(PairEssentials),
         )
)

/*
 * Features declarations
 */
FeatureDefine(PairEssentials) {
    for (size_t i = 0; i < SEEDS_SIZE - 1; i += 2) {
        const char *EXPECTED_KEY = SEEDS[i];
        const char *EXPECTED_VALUE = SEEDS[i + 1];
        struct kit_Pair *sut = Option_unwrap(kit_Pair_new(EXPECTED_KEY, (void *) EXPECTED_VALUE));
        assert_equal(kit_Pair_getKey(sut), EXPECTED_KEY);
        assert_string_equal(kit_Pair_getKey(sut), EXPECTED_KEY);
        assert_equal(kit_Pair_getValue(sut), EXPECTED_VALUE);
        assert_string_equal(kit_Pair_getValue(sut), EXPECTED_VALUE);
        kit_Pair_delete(sut);
    }
}
