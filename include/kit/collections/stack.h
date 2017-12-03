/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 21, 2017 
 */

/*
 * Stacks are a type of container adaptor, specifically designed to operate in a LIFO context (last-in first-out),
 * where elements are inserted and extracted only from one end of the container.
 */

#ifndef KIT_STACK_INCLUDED
#define KIT_STACK_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdbool.h>
#include <option/option.h>
#include <kit/compiler_steroids.h>
#include <kit/collections/result.h>

/**
 * kit_Stack interface.
 */
struct kit_Stack;

/**
 * Creates a new instance of kit_Stack using DoublyList as underlying container.
 * In case of out of memory this function returns MutableOption_None.
 *
 * @return A new instance of kit_Stack or MutableOption_None.
 */
extern MutableOptional(struct kit_Stack *)
kit_Stack_fromDoublyList(void);

/**
 * Creates a new instance of kit_Stack using SinglyList as underlying container.
 * In case of out of memory this function returns MutableOption_None.
 *
 * @return A new instance of kit_Stack or MutableOption_None.
 */
extern MutableOptional(struct kit_Stack *)
kit_Stack_fromSinglyList(void);

/**
 * Creates a new instance of kit_Stack using XorList as underlying container.
 * In case of out of memory this function returns MutableOption_None.
 *
 * @return A new instance of kit_Stack or MutableOption_None.
 */
extern MutableOptional(struct kit_Stack *)
kit_Stack_fromXorList(void);

/**
 * Creates a new instance of kit_Stack using Vector as underlying container.
 * In case of out of memory this function returns MutableOption_None.
 *
 * @return A new instance of kit_Stack or MutableOption_None.
 */
extern MutableOptional(struct kit_Stack *)
kit_Stack_fromVector(void);

/**
 * Deletes an instance of kit_Stack.
 * If @param self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_Stack_delete(struct kit_Stack *self);

/**
 * Inserts elements at the back of the container.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The container instance.
 * @param e The element to be inserted.
 * @return
 *      - KIT_RESULT_OK            :   The operation was performed successfully.
 *      - KIT_RESULT_OUT_OF_MEMORY :   There's no more space left, nothing has been done.
 */
extern enum kit_Result
kit_Stack_push(struct kit_Stack *self, void *e)
__attribute__((__nonnull__(1)));

/**
 * Removes elements at the back of the container.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *      - @param out must not be NULL.
 *
 * @param self The container instance.
 * @param out The removed element.
 * @return
 *      - KIT_RESULT_OK            :   The operation was performed successfully.
 *      - KIT_RESULT_OUT_OF_RANGE  :   No such element in the container, nothing has been done.
 */
extern enum kit_Result
kit_Stack_pop(struct kit_Stack *self, void **out)
__attribute__((__nonnull__));

/**
 * Gets the element stored at the back of the container.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *      - @param out must not be NULL.
 *
 * @param self The container instance.
 * @param out The element requested.
 * @return
 *      - KIT_RESULT_OK            :   The operation was performed successfully.
 *      - KIT_RESULT_OUT_OF_RANGE  :   No such element in the container, nothing has been done.
 */
extern enum kit_Result
kit_Stack_back(struct kit_Stack *self, void **out)
__attribute__((__nonnull__));

/**
 * Gets the number of elements currently stored in the container.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The container instance.
 * @return The numbers of elements in the container.
 */
extern size_t
kit_Stack_size(struct kit_Stack *self)
__attribute__((__nonnull__));

/**
 * Checks if the container is empty.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The container instance.
 * @return true if the container is empty false otherwise.
 */
extern bool
kit_Stack_isEmpty(struct kit_Stack *self)
__attribute__((__nonnull__));

#ifdef __cplusplus
}
#endif

#endif /* KIT_STACK_INCLUDED */
