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
#include <kit/collections/pair.h.old>

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
        struct kit_Pair sut = kit_Pair_make(EXPECTED_KEY, (void *) EXPECTED_VALUE);
        assert_equal(sut.key, EXPECTED_KEY);
        assert_string_equal(sut.key, EXPECTED_KEY);
        assert_equal(sut.value, EXPECTED_VALUE);
        assert_string_equal(sut.value, EXPECTED_VALUE);
    }

    for (size_t i = 0; i < SEEDS_SIZE - 1; i += 2) {
        const char *EXPECTED_KEY = SEEDS[i];
        const char *EXPECTED_VALUE = SEEDS[i + 1];
        struct kit_Pair *sut = MutableOption_unwrap(kit_Pair_new(EXPECTED_KEY, (void *) EXPECTED_VALUE));
        assert_equal(sut->key, EXPECTED_KEY);
        assert_string_equal(sut->key, EXPECTED_KEY);
        assert_equal(sut->value, EXPECTED_VALUE);
        assert_string_equal(sut->value, EXPECTED_VALUE);
        kit_Pair_delete(sut);
    }
}
