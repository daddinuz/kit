/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 23, 2017 
 */

/*
 * Deque provides a common interface for bi-directional iterable containers with dynamic sizes
 * that can be expanded or contracted on both ends (either its front or its back).
 * Deque are not guaranteed to store all its elements in contiguous storage locations.
 */

// TODO

#ifndef KIT_DEQUE_INCLUDED
#define KIT_DEQUE_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdbool.h>
#include <option/option.h>
#include <kit/compiler_steroids.h>
#include <kit/collections/bound.h>
#include <kit/collections/result.h>

/**
 * kit_Deque interface.
 */
struct kit_Deque;

/**
 * Creates a new instance of kit_Deque using DoublyList as underlying container.
 * In case of out of memory this function returns MutableOption_None.
 *
 * @return A new instance of kit_Deque or MutableOption_None.
 */
extern MutableOptional(struct kit_Deque *)
kit_Deque_fromDoublyList(void);

/**
 * Creates a new instance of kit_Deque using SinglyList as underlying container.
 * In case of out of memory this function returns MutableOption_None.
 *
 * @return A new instance of kit_Deque or MutableOption_None.
 */
extern MutableOptional(struct kit_Deque *)
kit_Deque_fromSinglyList(void);

/**
 * Creates a new instance of kit_Deque using XorList as underlying container.
 * In case of out of memory this function returns MutableOption_None.
 *
 * @return A new instance of kit_Deque or MutableOption_None.
 */
extern MutableOptional(struct kit_Deque *)
kit_Deque_fromXorList(void);

/**
 * Creates a new instance of kit_Deque using Hat as underlying container.
 * In case of out of memory this function returns MutableOption_None.
 *
 * @return A new instance of kit_Deque or MutableOption_None.
 */
extern MutableOptional(struct kit_Deque *)
kit_Deque_fromHat(size_t capacityHint);

/**
 * Creates a new instance of kit_Deque using Vector as underlying container.
 * In case of out of memory this function returns MutableOption_None.
 *
 * @return A new instance of kit_Deque or MutableOption_None.
 */
extern MutableOptional(struct kit_Deque *)
kit_Deque_fromVector(size_t capacityHint);

/**
 * Deletes an instance of kit_Deque.
 * If @param self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_Deque_delete(struct kit_Deque *self);

/**
 * Removes all elements from the container, leaving it with a size of 0.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The container instance.
 */
extern void
kit_Deque_clear(struct kit_Deque *self)
__attribute__((__nonnull__));

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
kit_Deque_pushBack(struct kit_Deque *self, void *e)
__attribute__((__nonnull__(1)));

/**
 * Inserts elements at the front of the container.
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
kit_Deque_pushFront(struct kit_Deque *self, void *e)
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
kit_Deque_popBack(struct kit_Deque *self, void **out)
__attribute__((__nonnull__));

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
kit_Deque_popFront(struct kit_Deque *self, void **out)
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
kit_Deque_back(struct kit_Deque *self, void **out)
__attribute__((__nonnull__));

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
kit_Deque_front(struct kit_Deque *self, void **out)
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
kit_Deque_size(struct kit_Deque *self)
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
kit_Deque_isEmpty(struct kit_Deque *self)
__attribute__((__nonnull__));

/**
 * Gets the number of elements the container can store before expansion.
 * (When size is equal to capacity the container will expand).
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The container instance.
 * @return The numbers of elements that can be stored before expansion.
 */
extern size_t
kit_Deque_capacity(struct kit_Deque *self)
__attribute__((__nonnull__));

/**
 * Requests an expansion to hold at least @param size elements.
 * (This method may ignore the request if the container does not support reserve)
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The container instance.
 * @return
 *      - KIT_RESULT_OK            :   The operation was performed successfully.
 *      - KIT_RESULT_OUT_OF_MEMORY :   There's no more space left, nothing has been done.
 */
extern enum kit_Result
kit_Deque_reserve(struct kit_Deque *self, size_t size)
__attribute__((__nonnull__));

/**
 * Requests the container to shrink in order to fit the stored elements freeing resources not used.
 * (This method may ignore the request if the container does not support shrink)
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The container instance.
 * @return
 *      - KIT_RESULT_OK            :   The operation was performed successfully.
 *      - KIT_RESULT_OUT_OF_MEMORY :   Unable to relocate memory, nothing has been done.
 */
extern enum kit_Result
kit_Deque_shrink(struct kit_Deque *self)
__attribute__((__nonnull__));

/**
 * kit_Deque_Iterator interface.
 */
struct kit_Deque_Iterator;

/**
 * Creates a new instance of kit_Deque_Iterator.
 * In case of out of memory this function returns MutableOption_None.
 *
 * Checked runtime errors:
 *      - @param container must not be NULL.
 *      - @param bound must be KIT_BOUND_BEGIN or KIT_BOUND_END.
 *
 * @param container The instance of the container to iterate.
 * @param bound The start bound.
 * @return A new instance of kit_Deque_Iterator or MutableOption_None.
 */
extern MutableOptional(struct kit_Deque_Iterator *)
kit_Deque_Iterator_new(struct kit_Deque *container, enum kit_Bound bound)
__attribute__((__nonnull__));

/**
 * Creates a new instance of kit_Deque_Iterator from begin of container.
 * In case of out of memory this function returns MutableOption_None.
 *
 * Checked runtime errors:
 *      - @param container must not be NULL.
 *
 * @param container The instance of the container to iterate.
 * @return A new instance of kit_Deque_Iterator or MutableOption_None.
 */
extern MutableOptional(struct kit_Deque_Iterator *)
kit_Deque_Iterator_fromBegin(struct kit_Deque *container)
__attribute__((__nonnull__));

/**
 * Creates a new instance of kit_Deque_Iterator from end of container.
 * In case of out of memory this function returns MutableOption_None.
 *
 * Checked runtime errors:
 *      - @param container must not be NULL.
 *
 * @param container The instance of the container to iterate.
 * @return A new instance of kit_Deque_Iterator or MutableOption_None.
 */
extern MutableOptional(struct kit_Deque_Iterator *)
kit_Deque_Iterator_fromEnd(struct kit_Deque *container)
__attribute__((__nonnull__));

/**
 * Deletes an instance of kit_Deque_Iterator.
 * If @param self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_Deque_Iterator_delete(struct kit_Deque_Iterator *self);

/**
 * Rewinds the iterator.
 *
 * Checked runtime errors:
 *      - @param container must not be NULL.
 *      - @param bound must be KIT_BOUND_BEGIN or KIT_BOUND_END.
 *
 * @param container The instance of the container to iterate.
 * @param bound The start bound.
 */
extern void
kit_Deque_Iterator_rewind(struct kit_Deque_Iterator *self, enum kit_Bound bound)
__attribute__((__nonnull__));

/**
 * Rewinds the iterator to begin of container.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The iterator instance.
 */
extern void
kit_Deque_Iterator_rewindToBegin(struct kit_Deque_Iterator *self)
__attribute__((__nonnull__));

/**
 * Rewinds the iterator to end of container.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The iterator instance.
 */
extern void
kit_Deque_Iterator_rewindToEnd(struct kit_Deque_Iterator *self)
__attribute__((__nonnull__));

/**
 * Gets the next element moving forward in the container.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *      - @param out must not be NULL.
 *
 * @param self The iterator instance.
 * @param out The retrieved element.
 * @return
 *      - KIT_RESULT_OK                        :   The operation was performed successfully.
 *      - KIT_RESULT_OUT_OF_RANGE              :   The iterator hit the end of the container, nothing has been done.
 *      - KIT_RESULT_CONCURRENT_MODIFICATION   :   The container has been modified, nothing has been done.
 */
extern enum kit_Result
kit_Deque_Iterator_next(struct kit_Deque_Iterator *self, void **out)
__attribute__((__nonnull__));

/**
 * Gets the previous element moving backward in the container.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *      - @param out must not be NULL.
 *
 * @param self The iterator instance.
 * @param out The retrieved element.
 * @return
 *      - KIT_RESULT_OK                        :   The operation was performed successfully.
 *      - KIT_RESULT_OUT_OF_RANGE              :   The iterator hit the begin of the container, nothing has been done.
 *      - KIT_RESULT_CONCURRENT_MODIFICATION   :   The container has been modified, nothing has been done.
 */
extern enum kit_Result
kit_Deque_Iterator_previous(struct kit_Deque_Iterator *self, void **out)
__attribute__((__nonnull__));

/**
 * Replaces the last retrieved element.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The iterator instance.
 * @param e The new element.
 * @return
 *      - KIT_RESULT_OK                        :   The operation was performed successfully.
 *      - KIT_RESULT_ILLEGAL_STATE             :   Neither next() or previous() has been called, nothing has been done.
 *      - KIT_RESULT_CONCURRENT_MODIFICATION   :   The container has been modified, nothing has been done.
 */
extern enum kit_Result
kit_Deque_Iterator_setLast(struct kit_Deque_Iterator *self, void *e)
__attribute__((__nonnull__(1)));

/**
 * Checks for associated container modifications.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The iterator instance.
 * @return true if the container has been modified else false
 */
extern bool
kit_Deque_Iterator_isModified(struct kit_Deque_Iterator *self)
__attribute__((__nonnull__));

#ifdef __cplusplus
}
#endif

#endif /* KIT_DEQUE_INCLUDED */
