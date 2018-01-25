/*
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 *
 * Copyright (c) 2018 Davide Di Carlo
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <traits-unit/traits-unit.h>
#include "fixtures/fixture_list.h"
#include "features/feature_getters.h"
#include "features/feature_growable.h"
#include "features/feature_insert.h"
#include "features/feature_remove.h"
#include "features/feature_setters.h"

/*
 * Describe the test case
 */
Describe("List",
         Trait(
                 "DoublyList",
                 Run(ListInsert, EmptyListDoublyListFixture),
                 Run(ListPushBack, EmptyListDoublyListFixture),
                 Run(ListPushFront, EmptyListDoublyListFixture),
                 Run(ListClear, SeededListDoublyListFixture),
                 Run(ListRemove, SeededListDoublyListFixture),
                 Run(ListPopBack, SeededListDoublyListFixture),
                 Run(ListPopFront, SeededListDoublyListFixture),
                 Run(ListGet, SeededListDoublyListFixture),
                 Run(ListBack, SeededListDoublyListFixture),
                 Run(ListFront, SeededListDoublyListFixture),
                 Run(ListPut, SeededListDoublyListFixture),
                 Run(ListExpand, EmptyListDoublyListFixture),
                 Run(ListShrink, SeededListDoublyListFixture)
         ),
         Trait(
                 "XorList",
                 Run(ListInsert, EmptyListXorListFixture),
                 Run(ListPushBack, EmptyListXorListFixture),
                 Run(ListPushFront, EmptyListXorListFixture),
                 Run(ListClear, SeededListXorListFixture),
                 Run(ListRemove, SeededListXorListFixture),
                 Run(ListPopBack, SeededListXorListFixture),
                 Run(ListPopFront, SeededListXorListFixture),
                 Run(ListGet, SeededListXorListFixture),
                 Run(ListBack, SeededListXorListFixture),
                 Run(ListFront, SeededListXorListFixture),
                 Run(ListPut, SeededListXorListFixture),
                 Run(ListExpand, EmptyListXorListFixture),
                 Run(ListShrink, SeededListXorListFixture)
         ),
         Trait(
                 "Vector",
                 Run(ListInsert, EmptyListVectorFixture),
                 Run(ListPushBack, EmptyListVectorFixture),
                 Run(ListPushFront, EmptyListVectorFixture),
                 Run(ListClear, SeededListVectorFixture),
                 Run(ListRemove, SeededListVectorFixture),
                 Run(ListPopBack, SeededListVectorFixture),
                 Run(ListPopFront, SeededListVectorFixture),
                 Run(ListGet, SeededListVectorFixture),
                 Run(ListBack, SeededListVectorFixture),
                 Run(ListFront, SeededListVectorFixture),
                 Run(ListPut, SeededListVectorFixture),
                 Run(ListExpand, EmptyListVectorFixture),
                 Run(ListShrink, SeededListVectorFixture)
         )
)
