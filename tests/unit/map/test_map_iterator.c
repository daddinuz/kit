/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   January 04, 2018 
 */

#include <traits-unit/traits-unit.h>
#include "fixtures/fixture_map.h"
#include "features/feature_iterable.h"

/*
 * Describe the test case
 */
Describe("MapIterator",
         Trait(
                 "HashMap",
                 Run(MapIteratorFromEmptyMap, MapIteratorFromEmptyMapHashMapFixture),
                 Run(MapIteratorRetrieveElements, MapIteratorFromSeededMapHashMapFixture),
                 Run(MapIteratorUpdateElements, MapIteratorFromSeededMapHashMapFixture),
                 Run(MapIteratorDetectModifications, MapIteratorFromEmptyMapHashMapFixture)
         ),
)
