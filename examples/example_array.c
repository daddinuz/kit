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
    struct kit_Array *array = Result_unwrap(kit_Array_from("Hello", " ", "World", "!"));

    for (size_t index = 0, _CAPACITY = kit_Array_capacity(array); index < _CAPACITY; index++) {
        const char *element = Result_unwrap(kit_Array_get(array, index));
        printf("[%zu]: %s\n", index, element);
    }

    kit_Array_delete(kit_move((void **) &array));
    return 0;
}
