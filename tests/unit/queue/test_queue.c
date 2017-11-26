/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 26, 2017 
 */

#include <traits-unit/traits-unit.h>
#include "fixtures/fixture_queue.h"
#include "features/feature_insert.h"
#include "features/feature_remove.h"

/*
 * Describe the test case
 */
Describe("Queue",
         Trait(
                 "SinglyList",
                 Run(QueuePush, EmptyQueueSinglyListFixture),
                 Run(QueuePop, SeededQueueSinglyListFixture)
         ),
         Trait(
                 "DoublyList",
                 Run(QueuePush, EmptyQueueDoublyListFixture),
                 Run(QueuePop, SeededQueueDoublyListFixture)
         ),
         Trait(
                 "XorList",
                 Run(QueuePush, EmptyQueueXorListFixture),
                 Run(QueuePop, SeededQueueXorListFixture)
         ),
         Trait(
                 "Vector",
                 Run(QueuePush, EmptyQueueVectorixture),
                 Run(QueuePop, SeededQueueVectorFixture)
         ),
)
