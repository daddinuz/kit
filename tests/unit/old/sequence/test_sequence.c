/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 25, 2017 
 */

#include <traits-unit/traits-unit.h>
#include "fixtures/fixture_sequence.h"
#include "features/feature_getters.h"
#include "features/feature_growable.h"
#include "features/feature_insert.h"
#include "features/feature_remove.h"
#include "features/feature_setters.h"

/*
 * Describe the test case
 */
Describe("Sequence",
         Trait(
                 "DoublyList",
                 Run(SequenceInsert, EmptySequenceDoublyListFixture),
                 Run(SequencePushBack, EmptySequenceDoublyListFixture),
                 Run(SequencePushFront, EmptySequenceDoublyListFixture),
                 Run(SequenceClear, SeededSequenceDoublyListFixture),
                 Run(SequenceRemove, SeededSequenceDoublyListFixture),
                 Run(SequencePopBack, SeededSequenceDoublyListFixture),
                 Run(SequencePopFront, SeededSequenceDoublyListFixture),
                 Run(SequenceGet, SeededSequenceDoublyListFixture),
                 Run(SequenceBack, SeededSequenceDoublyListFixture),
                 Run(SequenceFront, SeededSequenceDoublyListFixture),
                 Run(SequenceSize, SeededSequenceDoublyListFixture),
                 Run(SequenceSet, SeededSequenceDoublyListFixture),
                 Run(SequenceCapacity, EmptySequenceDoublyListFixture),
                 Run(SequenceReserve, EmptySequenceDoublyListFixture),
                 Run(SequenceShrink, SeededSequenceDoublyListFixture)
         ),
         Trait(
                 "SinglyList",
                 Run(SequenceInsert, EmptySequenceSinglyListFixture),
                 Run(SequencePushBack, EmptySequenceSinglyListFixture),
                 Run(SequencePushFront, EmptySequenceSinglyListFixture),
                 Run(SequenceClear, SeededSequenceSinglyListFixture),
                 Run(SequenceRemove, SeededSequenceSinglyListFixture),
                 Run(SequencePopBack, SeededSequenceSinglyListFixture),
                 Run(SequencePopFront, SeededSequenceSinglyListFixture),
                 Run(SequenceGet, SeededSequenceSinglyListFixture),
                 Run(SequenceBack, SeededSequenceSinglyListFixture),
                 Run(SequenceFront, SeededSequenceSinglyListFixture),
                 Run(SequenceSize, SeededSequenceSinglyListFixture),
                 Run(SequenceSet, SeededSequenceSinglyListFixture),
                 Run(SequenceCapacity, EmptySequenceSinglyListFixture),
                 Run(SequenceReserve, EmptySequenceSinglyListFixture),
                 Run(SequenceShrink, SeededSequenceSinglyListFixture)
         ),
         Trait(
                 "XorList",
                 Run(SequenceInsert, EmptySequenceXorListFixture),
                 Run(SequencePushBack, EmptySequenceXorListFixture),
                 Run(SequencePushFront, EmptySequenceXorListFixture),
                 Run(SequenceClear, SeededSequenceXorListFixture),
                 Run(SequenceRemove, SeededSequenceXorListFixture),
                 Run(SequencePopBack, SeededSequenceXorListFixture),
                 Run(SequencePopFront, SeededSequenceXorListFixture),
                 Run(SequenceGet, SeededSequenceXorListFixture),
                 Run(SequenceBack, SeededSequenceXorListFixture),
                 Run(SequenceFront, SeededSequenceXorListFixture),
                 Run(SequenceSize, SeededSequenceXorListFixture),
                 Run(SequenceSet, SeededSequenceXorListFixture),
                 Run(SequenceCapacity, EmptySequenceXorListFixture),
                 Run(SequenceReserve, EmptySequenceXorListFixture),
                 Run(SequenceShrink, SeededSequenceXorListFixture)
         ),
         Trait(
                 "Vector",
                 Run(SequenceInsert, EmptySequenceVectorFixture),
                 Run(SequencePushBack, EmptySequenceVectorFixture),
                 Run(SequencePushFront, EmptySequenceVectorFixture),
                 Run(SequenceClear, SeededSequenceVectorFixture),
                 Run(SequenceRemove, SeededSequenceVectorFixture),
                 Run(SequencePopBack, SeededSequenceVectorFixture),
                 Run(SequencePopFront, SeededSequenceVectorFixture),
                 Run(SequenceGet, SeededSequenceVectorFixture),
                 Run(SequenceBack, SeededSequenceVectorFixture),
                 Run(SequenceFront, SeededSequenceVectorFixture),
                 Run(SequenceSize, SeededSequenceVectorFixture),
                 Run(SequenceSet, SeededSequenceVectorFixture),
                 Run(SequenceCapacity, EmptySequenceVectorFixture),
                 Run(SequenceReserve, EmptySequenceVectorFixture),
                 Run(SequenceShrink, SeededSequenceVectorFixture)
         ),
)