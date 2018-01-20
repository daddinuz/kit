/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   January 20, 2018
 */

#ifndef KIT_QUEUE_INCLUDED
#define KIT_QUEUE_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdbool.h>
#include <option/option.h>
#include <kit/errors.h>
#include <kit/compiler_steroids.h>

/**
 * Queues are a type of container adaptor, specifically designed to operate in a FIFO context (first-in first-out),
 * where elements are inserted into one end of the container and extracted from the other.
 */
struct kit_Queue;

/**
 * Creates a new instance of kit_Queue using DoublyList as underlying container.
 * In case of out of memory this function returns None.
 *
 * @return A new instance of kit_Queue or None.
 */
extern OptionOf(struct kit_Queue *)
kit_Queue_fromDoublyList(void)
__attribute__((__warn_unused_result__));

/**
 * Creates a new instance of kit_Queue using SinglyList as underlying container.
 * In case of out of memory this function returns None.
 *
 * @return A new instance of kit_Queue or None.
 */
extern OptionOf(struct kit_Queue *)
kit_Queue_fromSinglyList(void)
__attribute__((__warn_unused_result__));

/**
 * Creates a new instance of kit_Queue using XorList as underlying container.
 * In case of out of memory this function returns None.
 *
 * @return A new instance of kit_Queue or None.
 */
extern OptionOf(struct kit_Queue *)
kit_Queue_fromXorList(void)
__attribute__((__warn_unused_result__));

/**
 * Creates a new instance of kit_Queue using Vector as underlying container.
 * In case of out of memory this function returns None.
 *
 * If capacity is 0 then a default capacity will be used.
 *
 * @param capacity An hint about the average capacity.
 * @return A new instance of kit_Queue or None.
 */
extern OptionOf(struct kit_Queue *)
kit_Queue_fromVector(size_t capacity)
__attribute__((__warn_unused_result__));

/**
 * Inserts the specified element at the back of the container.
 *
 * @param self The the container instance [<b>must not be NULL</b>].
 * @param element The element to be inserted.
 * @return
 * - Ok => The operation was performed successfully.
 * - OutOfMemoryError => There's no more space left, nothing has been done.
 */
extern OneOf(Ok, OutOfMemoryError)
kit_Queue_push(struct kit_Queue *self, void *element)
__attribute__((__warn_unused_result__, __nonnull__(1)));

/**
 * Removes the element at the front of the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return
 * - Ok => Wraps the removed element.
 * - OutOfRangeError => No such element, nothing has been done.
 */
extern ResultOf(void *, OutOfRangeError)
kit_Queue_pop(struct kit_Queue *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns the element stored at the back of this container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return
 * - Ok => wraps the specified element.
 * - OutOfRangeError => No such element, nothing has been done.
 */
extern ResultOf(void *, OutOfRangeError)
kit_Queue_back(const struct kit_Queue *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns the element stored at the front of this container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return
 * - Ok => wraps the specified element.
 * - OutOfRangeError => No such element, nothing has been done.
 */
extern ResultOf(void *, OutOfRangeError)
kit_Queue_front(const struct kit_Queue *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns the number of elements currently stored in the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return The numbers of elements in the container.
 */
extern size_t
kit_Queue_size(const struct kit_Queue *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Tests if this container has no elements.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return true if the container is empty false otherwise.
 */
extern bool
kit_Queue_isEmpty(const struct kit_Queue *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Deletes this instance of kit_Queue.
 * If self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_Queue_delete(struct kit_Queue *self);

#ifdef __cplusplus
}
#endif

#endif /* KIT_QUEUE_INCLUDED */
