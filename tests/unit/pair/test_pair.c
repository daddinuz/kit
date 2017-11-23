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
        const char *EXPECTED_FIRST = SEEDS[i];
        const char *EXPECTED_SECOND = SEEDS[i + 1];
        struct kit_Pair *sut = Option_unwrap(kit_Pair_new((void *) EXPECTED_FIRST, (void *) EXPECTED_SECOND));
        assert_equal(kit_Pair_first(sut), EXPECTED_FIRST);
        assert_string_equal(kit_Pair_first(sut), EXPECTED_FIRST);
        assert_equal(kit_Pair_second(sut), EXPECTED_SECOND);
        assert_string_equal(kit_Pair_second(sut), EXPECTED_SECOND);
        kit_Pair_delete(sut);
    }
}
