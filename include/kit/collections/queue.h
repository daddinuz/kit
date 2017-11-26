/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 21, 2017 
 */

/*
 * Queues are a type of container adaptor, specifically designed to operate in a FIFO context (first-in first-out),
 * where elements are inserted into one end of the container and extracted from the other.
 */

#ifndef KIT_QUEUE_INCLUDED
#define KIT_QUEUE_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdbool.h>
#include <option/option.h>
#include <kit/compiler_steroids.h>
#include <kit/collections/result.h>

/**
 * kit_Queue interface.
 */
struct kit_Queue;

/**
 * Creates a new instance of kit_Queue using DoublyList as underlying container.
 * In case of out of memory this function returns Option_None.
 *
 * @return A new instance of kit_Queue or Option_None.
 */
extern Optional(struct kit_Queue *)
kit_Queue_fromDoublyList(void);

/**
 * Creates a new instance of kit_Queue using SinglyList as underlying container.
 * In case of out of memory this function returns Option_None.
 *
 * @return A new instance of kit_Queue or Option_None.
 */
extern Optional(struct kit_Queue *)
kit_Queue_fromSinglyList(void);

/**
 * Creates a new instance of kit_Queue using XorList as underlying container.
 * In case of out of memory this function returns Option_None.
 *
 * @return A new instance of kit_Queue or Option_None.
 */
extern Optional(struct kit_Queue *)
kit_Queue_fromXorList(void);

/**
 * Creates a new instance of kit_Queue using Vector as underlying container.
 * In case of out of memory this function returns Option_None.
 *
 * @return A new instance of kit_Queue or Option_None.
 */
extern Optional(struct kit_Queue *)
kit_Queue_fromVector(void);

/**
 * Deletes an instance of kit_Queue.
 * If @param self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_Queue_delete(struct kit_Queue *self);

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
kit_Queue_push(struct kit_Queue *self, void *e) __attribute__((__nonnull__(1)));

/**
 * Removes elements at the front of the container.
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
kit_Queue_pop(struct kit_Queue *self, void **out) __attribute__((__nonnull__));

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
kit_Queue_back(struct kit_Queue *self, void **out) __attribute__((__nonnull__));

/**
 * Gets the element stored at the front of the container.
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
kit_Queue_front(struct kit_Queue *self, void **out) __attribute__((__nonnull__));

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
kit_Queue_size(struct kit_Queue *self) __attribute__((__nonnull__));

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
kit_Queue_isEmpty(struct kit_Queue *self) __attribute__((__nonnull__));

#ifdef __cplusplus
}
#endif

#endif /* KIT_QUEUE_INCLUDED */
