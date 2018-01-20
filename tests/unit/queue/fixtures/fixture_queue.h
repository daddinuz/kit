/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 26, 2017 
 */

#ifndef KIT_FIXTURE_QUEUE_INCLUDED
#define KIT_FIXTURE_QUEUE_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <traits-unit/traits-unit.h>

FixtureDeclare(EmptyQueueSinglyListFixture);
FixtureDeclare(SeededQueueSinglyListFixture);

FixtureDeclare(EmptyQueueDoublyListFixture);
FixtureDeclare(SeededQueueDoublyListFixture);

FixtureDeclare(EmptyQueueXorListFixture);
FixtureDeclare(SeededQueueXorListFixture);

FixtureDeclare(EmptyQueueVectorixture);
FixtureDeclare(SeededQueueVectorFixture);

#ifdef __cplusplus
}
#endif

#endif /* KIT_FIXTURE_QUEUE_INCLUDED */
