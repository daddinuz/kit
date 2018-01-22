/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   January 20, 2018
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
