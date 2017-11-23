/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 22, 2017 
 */

#include <string.h>
#include <seeds.h>
#include <traits/traits.h>
#include <traits-unit/traits-unit.h>
#include <kit/collections/atom.h>

/*
 * Features declarations
 */
FeatureDeclare(AtomEssentials);

/*
 * Describe our test case
 */
Describe("Atom",
         Trait(
                 "Essentials",
                 Run(AtomEssentials),
         )
)

/*
 * Features declarations
 */
FeatureDefine(AtomEssentials) {
    (void) traits_context;

    {
        const char *EXPECTED_TEXT = "Hello World!";
        const size_t EXPECTED_LENGTH = strlen(EXPECTED_TEXT);

        kit_Atom atom1 = Option_unwrap(kit_Atom_put(EXPECTED_TEXT, EXPECTED_LENGTH));
        kit_Atom atom2 = Option_unwrap(kit_Atom_fromLiteral(EXPECTED_TEXT));

        assert_equal(EXPECTED_LENGTH, kit_Atom_length(atom1));
        assert_equal(atom1, Option_unwrap(kit_Atom_put(EXPECTED_TEXT, EXPECTED_LENGTH)));
        assert_string_equal(atom1, EXPECTED_TEXT);

        assert_equal(EXPECTED_LENGTH, kit_Atom_length(atom2));
        assert_equal(atom2, Option_unwrap(kit_Atom_fromLiteral(EXPECTED_TEXT)));
        assert_string_equal(atom2, EXPECTED_TEXT);

        assert_equal(Option_unwrap(kit_Atom_put(EXPECTED_TEXT, EXPECTED_LENGTH)), Option_unwrap(kit_Atom_fromLiteral(EXPECTED_TEXT)));
        assert_string_equal(Option_unwrap(kit_Atom_put(EXPECTED_TEXT, EXPECTED_LENGTH)), Option_unwrap(kit_Atom_fromLiteral(EXPECTED_TEXT)));
    }

    {
        const long SEED = 85813541;
        const char *EXPECTED_TEXT = "85813541";
        const size_t EXPECTED_LENGTH = strlen(EXPECTED_TEXT);

        kit_Atom atom = Option_unwrap(kit_Atom_fromInteger(SEED));

        assert_equal(EXPECTED_LENGTH, kit_Atom_length(atom));
        assert_equal(atom, Option_unwrap(kit_Atom_fromInteger(SEED)));
        assert_string_equal(atom, EXPECTED_TEXT);
    }

    {
        char buffer[32] = "";
        const long double SEED = 0;
        const size_t EXPECTED_LENGTH = (size_t) snprintf(buffer, sizeof(buffer) / sizeof(buffer[0]), "%Lf", SEED);
        const char *EXPECTED_TEXT = buffer;

        kit_Atom atom = Option_unwrap(kit_Atom_fromFloating(SEED));

        assert_equal(EXPECTED_LENGTH, kit_Atom_length(atom), "%s", atom);
        assert_equal(atom, Option_unwrap(kit_Atom_fromFloating(SEED)));
        assert_string_equal(atom, EXPECTED_TEXT);
    }

    {
        kit_Atom atomsList[SEEDS_SIZE];

        for (size_t i = 0; i < SEEDS_SIZE; i++) {
            atomsList[i] = Option_unwrap(kit_Atom_fromLiteral(SEEDS[i]));
            for (size_t x = 0; x <= i; x++) {
                assert_equal(strlen(SEEDS[x]), kit_Atom_length(atomsList[x]));
                assert_equal(atomsList[x], Option_unwrap(kit_Atom_fromLiteral(SEEDS[x])));
                assert_string_equal(atomsList[x], SEEDS[x]);
            }
        }
    }
}
