/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 25, 2017 
 */

#ifndef KIT_FIXTURE_SEQUENCE_INCLUDED
#define KIT_FIXTURE_SEQUENCE_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <traits-unit/traits-unit.h>

/*
 * Sequence
 */
FixtureDeclare(EmptySequenceDoublyListFixture);
FixtureDeclare(SeededSequenceDoublyListFixture);

FixtureDeclare(EmptySequenceSinglyListFixture);
FixtureDeclare(SeededSequenceSinglyListFixture);

FixtureDeclare(EmptySequenceXorListFixture);
FixtureDeclare(SeededSequenceXorListFixture);

FixtureDeclare(EmptySequenceVectorFixture);
FixtureDeclare(SeededSequenceVectorFixture);

/*
 * SequenceIterator
 */
FixtureDeclare(SequenceIteratorFromEmptySequenceDoublyListFixture);
FixtureDeclare(SequenceIteratorFromSeededSequenceDoublyListFixture);

FixtureDeclare(SequenceIteratorFromEmptySequenceSinglyListFixture);
FixtureDeclare(SequenceIteratorFromSeededSequenceSinglyListFixture);

FixtureDeclare(SequenceIteratorFromEmptySequenceXorListFixture);
FixtureDeclare(SequenceIteratorFromSeededSequenceXorListFixture);

FixtureDeclare(SequenceIteratorFromEmptySequenceVectorFixture);
FixtureDeclare(SequenceIteratorFromSeededSequenceVectorFixture);

#ifdef __cplusplus
}
#endif

#endif /* KIT_FIXTURE_SEQUENCE_INCLUDED */
