/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 25, 2017 
 */

#include <stdio.h>
#include <kit/utils.h>
#include <kit/collections/vector.h>

/*
 *  
 */
int main() {
    struct kit_Vector *vector = Result_unwrap(kit_Vector_new());
    struct kit_Vector_Iterator *iterator = Result_unwrap(kit_Vector_Iterator_fromBegin(vector));

    vector = Result_unwrap(kit_Vector_pushBack(&vector, "World"));
    vector = Result_unwrap(kit_Vector_pushFront(&vector, "Hello"));
    vector = Result_unwrap(kit_Vector_insert(&vector, 1, " "));
    vector = Result_unwrap(kit_Vector_insert(&vector, 3, "!"));

    kit_Vector_Iterator_rewindToBegin(iterator);

    for (Result result; Result_isOk(result = kit_Vector_Iterator_next(iterator));) {
        static size_t index = 0;
        const char *element = Result_unwrap(result);

        printf("[%zu]: %s\n", index++, element);
        kit_Vector_Iterator_setLast(iterator, "x");
    }

    puts("");

    for (Result result; Result_isOk(result = kit_Vector_Iterator_previous(iterator));) {
        static size_t index = 0;
        const char *element = Result_unwrap(result);

        printf("[%zu]: %s\n", kit_Vector_size(vector) - index++, element);
    }

    kit_Vector_Iterator_delete(kit_move((void **) &iterator));
    kit_Vector_delete(kit_move((void **) &vector));
    return 0;
}
