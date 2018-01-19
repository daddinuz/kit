/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 25, 2017 
 */

#include <traits-unit/traits-unit.h>
#include "fixtures/fixture_list.h"
#include "features/feature_iterable.h"

/*
 * Describe our test case
 */
Describe("ListIterator",
         Trait(
                 "DoublyList",
                 Run(ListIteratorFromEmptyListBoundaries, EmptyListDoublyListFixture),
                 Run(ListIteratorFromSeededListBoundaries, SeededListDoublyListFixture),
                 Run(ListIteratorRewindFromEmptyList, ListIteratorFromEmptyListDoublyListFixture),
                 Run(ListIteratorRewindFromSeededList, ListIteratorFromSeededListDoublyListFixture),
                 Run(ListIteratorReachTheBoundariesOfList, ListIteratorFromSeededListDoublyListFixture),
                 Run(ListIteratorUpdateRetrievedElements, ListIteratorFromSeededListDoublyListFixture),
                 Run(ListIteratorDetectModifications, ListIteratorFromEmptyListDoublyListFixture)
         ),
         Trait(
                 "XorList",
                 Run(ListIteratorFromEmptyListBoundaries, EmptyListXorListFixture),
                 Run(ListIteratorFromSeededListBoundaries, SeededListXorListFixture),
                 Run(ListIteratorRewindFromEmptyList, ListIteratorFromEmptyListXorListFixture),
                 Run(ListIteratorRewindFromSeededList, ListIteratorFromSeededListXorListFixture),
                 Run(ListIteratorReachTheBoundariesOfList, ListIteratorFromSeededListXorListFixture),
                 Run(ListIteratorUpdateRetrievedElements, ListIteratorFromSeededListXorListFixture),
                 Run(ListIteratorDetectModifications, ListIteratorFromEmptyListXorListFixture)
         ),
         Trait(
                 "Vector",
                 Run(ListIteratorFromEmptyListBoundaries, EmptyListVectorFixture),
                 Run(ListIteratorFromSeededListBoundaries, SeededListVectorFixture),
                 Run(ListIteratorRewindFromEmptyList, ListIteratorFromEmptyListVectorFixture),
                 Run(ListIteratorRewindFromSeededList, ListIteratorFromSeededListVectorFixture),
                 Run(ListIteratorReachTheBoundariesOfList, ListIteratorFromSeededListVectorFixture),
                 Run(ListIteratorUpdateRetrievedElements, ListIteratorFromSeededListVectorFixture),
                 Run(ListIteratorDetectModifications, ListIteratorFromEmptyListVectorFixture)
         )
)
