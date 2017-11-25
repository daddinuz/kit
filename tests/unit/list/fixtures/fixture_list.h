/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 25, 2017 
 */

#ifndef KIT_FIXTURE_LIST_INCLUDED
#define KIT_FIXTURE_LIST_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <traits-unit/traits-unit.h>

/*
 * List
 */
FixtureDeclare(EmptyListDoublyListFixture);
FixtureDeclare(SeededListDoublyListFixture);

FixtureDeclare(EmptyListXorListFixture);
FixtureDeclare(SeededListXorListFixture);

FixtureDeclare(EmptyListVectorFixture);
FixtureDeclare(SeededListVectorFixture);

/*
 * ListIterator
 */
FixtureDeclare(ListIteratorFromEmptyListDoublyListFixture);
FixtureDeclare(ListIteratorFromSeededListDoublyListFixture);

FixtureDeclare(ListIteratorFromEmptyListXorListFixture);
FixtureDeclare(ListIteratorFromSeededListXorListFixture);

FixtureDeclare(ListIteratorFromEmptyListVectorFixture);
FixtureDeclare(ListIteratorFromSeededListVectorFixture);

#ifdef __cplusplus
}
#endif

#endif /* KIT_FIXTURE_LIST_INCLUDED */
