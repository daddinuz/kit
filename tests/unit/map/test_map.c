/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   December 30, 2017 
 */

#include <traits-unit/traits-unit.h>
#include "fixtures/fixture_map.h"
#include "features/feature_insert.h"
#include "features/feature_remove.h"

/*
 * Describe the test case
 */
Describe("Map",
         Trait(
                 "HashMap",
                 Run(MapPut, EmptyMapHashMapFixture),
                 Run(MapPop, SeededMapHashMapFixture),
                 Run(MapClear, SeededMapHashMapFixture)
         ),
)
