/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 26, 2017 
 */

#ifndef KIT_FIXTURE_STACK_INCLUDED
#define KIT_FIXTURE_STACK_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <traits-unit/traits-unit.h>

FixtureDeclare(EmptyStackSinglyListFixture);
FixtureDeclare(SeededStackSinglyListFixture);

FixtureDeclare(EmptyStackDoublyListFixture);
FixtureDeclare(SeededStackDoublyListFixture);

FixtureDeclare(EmptyStackXorListFixture);
FixtureDeclare(SeededStackXorListFixture);

FixtureDeclare(EmptyStackVectorFixture);
FixtureDeclare(SeededStackVectorFixture);

#ifdef __cplusplus
}
#endif

#endif /* KIT_FIXTURE_STACK_INCLUDED */
