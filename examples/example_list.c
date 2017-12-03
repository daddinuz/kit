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
#include <kit/collections/list.h>

/*
 *  
 */
int main() {
    size_t index;
    struct kit_List *list = MutableOption_unwrap(kit_List_fromVector(16));
    struct kit_List_Iterator *iterator = MutableOption_unwrap(kit_List_Iterator_fromBegin(list));

    kit_List_pushBack(list, "World");
    kit_List_pushFront(list, "Hello");
    kit_List_insert(list, " ", 1);
    kit_List_insert(list, "!", 3);

    index = 0;
    kit_List_Iterator_rewindToBegin(iterator);
    for (void *e = NULL; KIT_RESULT_OK == kit_List_Iterator_next(iterator, &e); e = NULL, index++) {
        printf("[%zu]: %s\n", index, (char *) e);
        kit_List_Iterator_setLast(iterator, "x");
    }

    puts("");

    for (void *e = NULL; KIT_RESULT_OK == kit_List_Iterator_previous(iterator, &e); e = NULL, index--) {
        printf("[%zu]: %s\n", index - 1, (char *) e);
    }

    kit_invalidate((void **) &iterator, kit_List_Iterator_delete);
    kit_invalidate((void **) &list, kit_List_delete);
    return 0;
}
