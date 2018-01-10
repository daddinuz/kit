/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 25, 2017 
 */

#include <stdio.h>
#include <stdlib.h>
#include <kit/utils.h>
#include <kit/collections/sequence.h>

/*
 *  
 */
int main() {
    size_t index;
    struct kit_Sequence *sequence = MutableOption_unwrap(kit_Sequence_fromSinglyList());
    struct kit_Sequence_Iterator *iterator = MutableOption_unwrap(kit_Sequence_Iterator_new(sequence));

    kit_Sequence_pushBack(sequence, "World");
    kit_Sequence_pushFront(sequence, "Hello");
    kit_Sequence_insert(sequence, " ", 1);
    kit_Sequence_insert(sequence, "!", 3);

    index = 0;
    kit_Sequence_Iterator_rewind(iterator);
    for (void *e = NULL; KIT_RESULT_OK == kit_Sequence_Iterator_next(iterator, &e); e = NULL, index++) {
        printf("[%zu]: %s\n", index, (char *) e);
        kit_Sequence_Iterator_setLast(iterator, "x");
    }

    puts("");

    index = 0;
    kit_Sequence_Iterator_rewind(iterator);
    for (void *e = NULL; KIT_RESULT_OK == kit_Sequence_Iterator_next(iterator, &e); e = NULL, index++) {
        printf("[%zu]: %s\n", index, (char *) e);
    }

    kit_Sequence_Iterator_delete(kit_move((void **) &iterator));
    kit_Sequence_delete(kit_move((void **) &sequence));
    return 0;
}
