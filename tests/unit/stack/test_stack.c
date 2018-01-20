/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 26, 2017 
 */

#include <traits-unit/traits-unit.h>
#include "fixtures/fixture_stack.h"
#include "features/feature_insert.h"
#include "features/feature_remove.h"

/*
 * Describe the test case
 */
Describe("Stack",
         Trait(
                 "SinglyList",
                 Run(StackPush, EmptyStackSinglyListFixture),
                 Run(StackPop, SeededStackSinglyListFixture)
         ),
         Trait(
                 "DoublyList",
                 Run(StackPush, EmptyStackDoublyListFixture),
                 Run(StackPop, SeededStackDoublyListFixture)
         ),
         Trait(
                 "XorList",
                 Run(StackPush, EmptyStackXorListFixture),
                 Run(StackPop, SeededStackXorListFixture)
         ),
         Trait(
                 "Vector",
                 Run(StackPush, EmptyStackVectorFixture),
                 Run(StackPop, SeededStackVectorFixture)
         ),
)
