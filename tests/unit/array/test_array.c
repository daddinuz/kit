/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 22, 2017 
 */

#include <traits-unit/traits-unit.h>
#include "fixtures/fixture_array.h"
#include "features/feature_getters.h"
#include "features/feature_setters.h"

/*
 * Describe our test case
 */
Describe("Array",
         Trait(
                 "Getters",
                 Run(ArrayRaw, SeededArrayFixture),
                 Run(ArrayGet, SeededArrayFixture),
                 Run(ArrayBack, SeededArrayFixture),
                 Run(ArrayFront, SeededArrayFixture),
                 Run(ArrayCapacity, SeededArrayFixture)
         ),
         Trait(
                 "Setters",
                 Run(ArraySet, SeededArrayFixture),
                 Run(ArrayClear, SeededArrayFixture)
         )
)
