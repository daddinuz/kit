/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 25, 2017 
 */

#include <stdio.h>
#include <kit/utils.h>
#include <kit/collections/array.h>

/*
 * 
 */
int main() {
    size_t index;
    struct kit_Array *array = Option_unwrap(kit_Array_new(4));

    kit_Array_set(array, "World", 2);
    kit_Array_set(array, "Hello", 0);
    kit_Array_set(array, " ", 1);
    kit_Array_set(array, "!", 3);

    index = 0;
    for (const size_t capacity = kit_Array_capacity(array); index < capacity; index++) {
        void *element = NULL;
        kit_Array_get(array, &element, index);
        printf("[%zu]: %s\n", index, (char *) element);
    }

    kit_invalidate((void **) &array, kit_Array_delete);
    return 0;
}
