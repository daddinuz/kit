/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 25, 2017 
 */

#include <traits-unit/traits-unit.h>
#include "fixtures/fixture_list.h"
#include "features/feature_getters.h"
#include "features/feature_growable.h"
#include "features/feature_insert.h"
#include "features/feature_remove.h"
#include "features/feature_setters.h"

/*
 * Describe the test case
 */
Describe("List",
         Trait(
                 "DoublyList",
                 Run(ListInsert, EmptyListDoublyListFixture),
                 Run(ListPushBack, EmptyListDoublyListFixture),
                 Run(ListPushFront, EmptyListDoublyListFixture),
                 Run(ListClear, SeededListDoublyListFixture),
                 Run(ListRemove, SeededListDoublyListFixture),
                 Run(ListPopBack, SeededListDoublyListFixture),
                 Run(ListPopFront, SeededListDoublyListFixture),
                 Run(ListGet, SeededListDoublyListFixture),
                 Run(ListBack, SeededListDoublyListFixture),
                 Run(ListFront, SeededListDoublyListFixture),
                 Run(ListSize, SeededListDoublyListFixture),
                 Run(ListSet, SeededListDoublyListFixture),
                 Run(ListCapacity, EmptyListDoublyListFixture),
                 Run(ListReserve, EmptyListDoublyListFixture),
                 Run(ListShrink, SeededListDoublyListFixture)
         ),
         Trait(
                 "XorList",
                 Run(ListInsert, EmptyListXorListFixture),
                 Run(ListPushBack, EmptyListXorListFixture),
                 Run(ListPushFront, EmptyListXorListFixture),
                 Run(ListClear, SeededListXorListFixture),
                 Run(ListRemove, SeededListXorListFixture),
                 Run(ListPopBack, SeededListXorListFixture),
                 Run(ListPopFront, SeededListXorListFixture),
                 Run(ListGet, SeededListXorListFixture),
                 Run(ListBack, SeededListXorListFixture),
                 Run(ListFront, SeededListXorListFixture),
                 Run(ListSize, SeededListXorListFixture),
                 Run(ListSet, SeededListXorListFixture),
                 Run(ListCapacity, EmptyListXorListFixture),
                 Run(ListReserve, EmptyListXorListFixture),
                 Run(ListShrink, SeededListXorListFixture)
         ),
         Trait(
                 "Vector",
                 Run(ListInsert, EmptyListVectorFixture),
                 Run(ListPushBack, EmptyListVectorFixture),
                 Run(ListPushFront, EmptyListVectorFixture),
                 Run(ListClear, SeededListVectorFixture),
                 Run(ListRemove, SeededListVectorFixture),
                 Run(ListPopBack, SeededListVectorFixture),
                 Run(ListPopFront, SeededListVectorFixture),
                 Run(ListGet, SeededListVectorFixture),
                 Run(ListBack, SeededListVectorFixture),
                 Run(ListFront, SeededListVectorFixture),
                 Run(ListSize, SeededListVectorFixture),
                 Run(ListSet, SeededListVectorFixture),
                 Run(ListCapacity, EmptyListVectorFixture),
                 Run(ListReserve, EmptyListVectorFixture),
                 Run(ListShrink, SeededListVectorFixture)
         ),
)
