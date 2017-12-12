/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   December 12, 2017 
 */

#include <traits-unit/traits-unit.h>
#include "features/feature_essentials.h"

/*
 * Describe our test case
 */
Describe("String",
         Trait(
                 "Essentials",
                 Run(StringNew),
                 Run(StringQuoted)
         )
)
