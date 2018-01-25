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

#include <stdio.h>
#include <kit/utils.h>
#include <kit/collections/sequence.h>

#define _(x)    ((void) ((x) ? 1 : 0));

/*
 *  
 */
int main() {
    struct kit_Sequence *sequence = Option_unwrap(kit_Sequence_fromSinglyList());
    struct kit_Sequence_Iterator *iterator = Option_unwrap(kit_Sequence_Iterator_fromBegin(sequence));

    Error_unwrap(kit_Sequence_pushBack(sequence, "World"));
    Error_unwrap(kit_Sequence_pushFront(sequence, "Hello"));
    Error_unwrap(kit_Sequence_insert(sequence, 1, " "));
    Error_unwrap(kit_Sequence_insert(sequence, 3, "!"));

    kit_Sequence_Iterator_rewindToBegin(iterator);

    for (Result result; Result_isOk(result = kit_Sequence_Iterator_next(iterator));) {
        static size_t index = 0;
        const char *element = Result_unwrap(result);

        printf("[%zu]: %s\n", index++, element);
        _(Result_unwrap(kit_Sequence_Iterator_setLast(iterator, "x")));
    }

    puts("");

    kit_Sequence_Iterator_rewindToBegin(iterator);

    for (Result result; Result_isOk(result = kit_Sequence_Iterator_next(iterator));) {
        static size_t index = 0;
        const char *element = Result_unwrap(result);

        printf("[%zu]: %s\n", index++, element);
    }

    kit_Sequence_Iterator_delete(kit_move((void **) &iterator));
    kit_Sequence_delete(kit_move((void **) &sequence));
    return 0;
}
