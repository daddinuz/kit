/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 23, 2017 
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
    (void) traits_context;

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
