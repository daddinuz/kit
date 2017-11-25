/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 25, 2017 
 */

#include <traits-unit/traits-unit.h>
#include "fixtures/fixture_sequence.h"
#include "features/feature_iterable.h"

/*
 * Describe our test case
 */
Describe("SequenceIterator",
         Trait(
                 "DoublyList",
                 Run(SequenceIteratorFromEmptySequenceBoundaries, EmptySequenceDoublyListFixture),
                 Run(SequenceIteratorFromSeededSequenceBoundaries, SeededSequenceDoublyListFixture),
                 Run(SequenceIteratorRewindFromEmptySequence, SequenceIteratorFromEmptySequenceDoublyListFixture),
                 Run(SequenceIteratorRewindFromSeededSequence, SequenceIteratorFromSeededSequenceDoublyListFixture),
                 Run(SequenceIteratorReachTheBoundariesOfSequence, SequenceIteratorFromSeededSequenceDoublyListFixture),
                 Run(SequenceIteratorUpdateRetrievedElements, SequenceIteratorFromSeededSequenceDoublyListFixture),
                 Run(SequenceIteratorDetectModifications, SequenceIteratorFromEmptySequenceDoublyListFixture)
         ),
         Trait(
                 "SinglyList",
                 Run(SequenceIteratorFromEmptySequenceBoundaries, EmptySequenceSinglyListFixture),
                 Run(SequenceIteratorFromSeededSequenceBoundaries, SeededSequenceSinglyListFixture),
                 Run(SequenceIteratorRewindFromEmptySequence, SequenceIteratorFromEmptySequenceSinglyListFixture),
                 Run(SequenceIteratorRewindFromSeededSequence, SequenceIteratorFromSeededSequenceSinglyListFixture),
                 Run(SequenceIteratorReachTheBoundariesOfSequence, SequenceIteratorFromSeededSequenceSinglyListFixture),
                 Run(SequenceIteratorUpdateRetrievedElements, SequenceIteratorFromSeededSequenceSinglyListFixture),
                 Run(SequenceIteratorDetectModifications, SequenceIteratorFromEmptySequenceSinglyListFixture)
         ),
         Trait(
                 "XorList",
                 Run(SequenceIteratorFromEmptySequenceBoundaries, EmptySequenceXorListFixture),
                 Run(SequenceIteratorFromSeededSequenceBoundaries, SeededSequenceXorListFixture),
                 Run(SequenceIteratorRewindFromEmptySequence, SequenceIteratorFromEmptySequenceXorListFixture),
                 Run(SequenceIteratorRewindFromSeededSequence, SequenceIteratorFromSeededSequenceXorListFixture),
                 Run(SequenceIteratorReachTheBoundariesOfSequence, SequenceIteratorFromSeededSequenceXorListFixture),
                 Run(SequenceIteratorUpdateRetrievedElements, SequenceIteratorFromSeededSequenceXorListFixture),
                 Run(SequenceIteratorDetectModifications, SequenceIteratorFromEmptySequenceXorListFixture)
         ),
         Trait(
                 "Vector",
                 Run(SequenceIteratorFromEmptySequenceBoundaries, EmptySequenceVectorFixture),
                 Run(SequenceIteratorFromSeededSequenceBoundaries, SeededSequenceVectorFixture),
                 Run(SequenceIteratorRewindFromEmptySequence, SequenceIteratorFromEmptySequenceVectorFixture),
                 Run(SequenceIteratorRewindFromSeededSequence, SequenceIteratorFromSeededSequenceVectorFixture),
                 Run(SequenceIteratorReachTheBoundariesOfSequence, SequenceIteratorFromSeededSequenceVectorFixture),
                 Run(SequenceIteratorUpdateRetrievedElements, SequenceIteratorFromSeededSequenceVectorFixture),
                 Run(SequenceIteratorDetectModifications, SequenceIteratorFromEmptySequenceVectorFixture)
         )
)
