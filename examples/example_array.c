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
    struct kit_Array *array = MutableOption_unwrap(kit_Array_from("Hello", " ", "World", "!"));
    const size_t capacity = kit_Array_capacity(array);

    for (size_t index = 0; index < capacity; index++) {
        void *element = NULL;
        kit_Array_get(array, &element, index);
        printf("[%zu]: %s\n", index, (char *) element);
    }

    kit_Array_delete(kit_move((void **) &array));
    return 0;
}
