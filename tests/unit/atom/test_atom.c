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

    {
        const char *EXPECTED_TEXT = "Hello World!";
        const size_t EXPECTED_LENGTH = strlen(EXPECTED_TEXT);

        const kit_Atom atom1 = Option_unwrap(kit_Atom_put(EXPECTED_TEXT, EXPECTED_LENGTH));
        const kit_Atom atom2 = Option_unwrap(kit_Atom_fromLiteral(EXPECTED_TEXT));

        assert_equal(EXPECTED_LENGTH, kit_Atom_length(atom1));
        assert_equal(atom1, Option_unwrap(kit_Atom_put(EXPECTED_TEXT, EXPECTED_LENGTH)));
        assert_string_equal(atom1, EXPECTED_TEXT);

        assert_equal(EXPECTED_LENGTH, kit_Atom_length(atom2));
        assert_equal(atom2, Option_unwrap(kit_Atom_fromLiteral(EXPECTED_TEXT)));
        assert_string_equal(atom2, EXPECTED_TEXT);

        assert_equal(Option_unwrap(kit_Atom_put(EXPECTED_TEXT, EXPECTED_LENGTH)),
                     Option_unwrap(kit_Atom_fromLiteral(EXPECTED_TEXT)));
        assert_string_equal(Option_unwrap(kit_Atom_put(EXPECTED_TEXT, EXPECTED_LENGTH)),
                            Option_unwrap(kit_Atom_fromLiteral(EXPECTED_TEXT)));
    }

    {
        const long SEED = 85813541;
        const char *EXPECTED_TEXT = "85813541";
        const size_t EXPECTED_LENGTH = strlen(EXPECTED_TEXT);

        const kit_Atom atom = Option_unwrap(kit_Atom_fromInteger(SEED));

        assert_equal(EXPECTED_LENGTH, kit_Atom_length(atom));
        assert_equal(atom, Option_unwrap(kit_Atom_fromInteger(SEED)));
        assert_string_equal(atom, EXPECTED_TEXT);
    }

    {
        char buffer[32] = "";
        const long double SEED = 0;
        const size_t EXPECTED_LENGTH = (size_t) snprintf(buffer, sizeof(buffer) / sizeof(buffer[0]), "%Lf", SEED);
        const char *EXPECTED_TEXT = buffer;

        const kit_Atom atom = Option_unwrap(kit_Atom_fromFloating(SEED));

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
