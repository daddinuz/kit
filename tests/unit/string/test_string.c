/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   December 12, 2017 
 */

#include <traits-unit/traits-unit.h>
#include "features/feature_essentials.h"
#include "features/feature_expandable.h"

/*
 * Describe our test case
 */
Describe("String",
         Trait(
                 "Essentials",
                 Run(StringNew),
                 Run(StringQuoted),
                 Run(StringFromBytes),
                 Run(StringFromFormat),
                 Run(StringFromLiteral),
                 Run(StringDuplicate)
         ),
         Trait(
                 "Expandable",
                 Run(StringReserve),
                 Run(StringShrink)
         )
)
