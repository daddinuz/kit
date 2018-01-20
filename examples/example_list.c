/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   January 18, 2018
 */

#include <stdio.h>
#include <kit/utils.h>
#include <kit/collections/list.h>

/*
 *  
 */
int main() {
    struct kit_List *list = Option_unwrap(kit_List_fromXorList());
    struct kit_List_Iterator *iterator = Option_unwrap(kit_List_Iterator_fromBegin(list));

    Error_unwrap(kit_List_pushBack(list, "World"));
    Error_unwrap(kit_List_pushFront(list, "Hello"));
    Error_unwrap(kit_List_insert(list, 1, " "));
    Error_unwrap(kit_List_insert(list, 3, "!"));

    kit_List_Iterator_rewindToBegin(iterator);

    for (Result result; Result_isOk(result = kit_List_Iterator_next(iterator));) {
        static size_t index = 0;
        const char *element = Result_unwrap(result);

        printf("[%zu]: %s\n", index++, element);
        Result_unwrap(kit_List_Iterator_setLast(iterator, "x"));
    }

    puts("");

    for (Result result; Result_isOk(result = kit_List_Iterator_previous(iterator));) {
        static size_t index = 0;
        const char *element = Result_unwrap(result);

        printf("[%zu]: %s\n", kit_List_size(list) - index++, element);
    }

    kit_List_Iterator_delete(kit_move((void **) &iterator));
    kit_List_delete(kit_move((void **) &list));
    return 0;
}
