/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 23, 2017 
 */

/*
 * List provides a common interface for bi-directional iterable containers with dynamic sizes
 * that can be expanded or contracted on both ends (either its front or its back) and allow insert
 * and erase operations anywhere within the sequence.
 */

#ifndef KIT_LIST_INCLUDED
#define KIT_LIST_INCLUDED

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
 * kit_List interface.
 */
struct kit_List;

/**
 * Creates a new instance of kit_List using DoublyList as underlying container.
 * In case of out of memory this function returns MutableOption_None.
 *
 * @return A new instance of kit_List or MutableOption_None.
 */
extern MutableOptional(struct kit_List *)
kit_List_fromDoublyList(void);

/**
 * Creates a new instance of kit_List using XorList as underlying container.
 * In case of out of memory this function returns MutableOption_None.
 *
 * @return A new instance of kit_List or MutableOption_None.
 */
extern MutableOptional(struct kit_List *)
kit_List_fromXorList(void);

/**
 * Creates a new instance of kit_List using Vector as underlying container.
 * In case of out of memory this function returns MutableOption_None.
 *
 * @return A new instance of kit_List or MutableOption_None.
 */
extern MutableOptional(struct kit_List *)
kit_List_fromVector(size_t capacityHint);

/**
 * Deletes an instance of kit_List.
 * If @param self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_List_delete(struct kit_List *self);

/**
 * Removes all elements from the container, leaving it with a size of 0.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The container instance.
 */
extern void
kit_List_clear(struct kit_List *self)
__attribute__((__nonnull__));

/**
 * Inserts elements at the given index of the container.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The container instance.
 * @param e The element to be inserted.
 * @param index The index where the element has to be placed.
 * @return
 *      - KIT_RESULT_OK            :   The operation was performed successfully.
 *      - KIT_RESULT_OUT_OF_RANGE  :   The given index is out of range, nothing has been done.
 *      - KIT_RESULT_OUT_OF_MEMORY :   There's no more space left, nothing has been done.
 */
extern enum kit_Result
kit_List_insert(struct kit_List *self, void *e, size_t index)
__attribute__((__nonnull__(1)));

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
kit_List_pushBack(struct kit_List *self, void *e)
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
kit_List_pushFront(struct kit_List *self, void *e)
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
kit_List_popBack(struct kit_List *self, void **out)
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
kit_List_popFront(struct kit_List *self, void **out)
__attribute__((__nonnull__));

/**
 * Removes elements at the given index of the container.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *      - @param out must not be NULL.
 *
 * @param self The container instance.
 * @param out The removed element.
 * @param index The index of the element to remove.
 * @return
 *      - KIT_RESULT_OK            :   The operation was performed successfully.
 *      - KIT_RESULT_OUT_OF_RANGE  :   No such element in the container, nothing has been done.
 */
extern enum kit_Result
kit_List_remove(struct kit_List *self, void **out, size_t index)
__attribute__((__nonnull__));

/**
 * Replaces the element at the given index.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The container instance.
 * @param e The new element.
 * @param index The index of the element to be replaced.
 * @return
 *      - KIT_RESULT_OK            :   The operation was performed successfully.
 *      - KIT_RESULT_OUT_OF_RANGE  :   The given index is out of range, nothing has been done.
 */
extern enum kit_Result
kit_List_set(struct kit_List *self, void *e, size_t index)
__attribute__((__nonnull__(1)));

/**
 * Gets the element stored at the given index.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *      - @param out must not be NULL.
 *
 * @param self The container instance.
 * @param out The element requested.
 * @param index The index of the element requested.
 * @return
 *      - KIT_RESULT_OK            :   The operation was performed successfully.
 *      - KIT_RESULT_OUT_OF_RANGE  :   The given index is out of range, nothing has been done.
 */
extern enum kit_Result
kit_List_get(struct kit_List *self, void **out, size_t index)
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
kit_List_back(struct kit_List *self, void **out)
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
kit_List_front(struct kit_List *self, void **out)
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
kit_List_size(struct kit_List *self)
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
kit_List_isEmpty(struct kit_List *self)
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
kit_List_capacity(struct kit_List *self)
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
kit_List_reserve(struct kit_List *self, size_t size)
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
kit_List_shrink(struct kit_List *self)
__attribute__((__nonnull__));

/**
 * kit_List_Iterator interface.
 */
struct kit_List_Iterator;

/**
 * Creates a new instance of kit_List_Iterator.
 * In case of out of memory this function returns MutableOption_None.
 *
 * Checked runtime errors:
 *      - @param container must not be NULL.
 *      - @param bound must be KIT_BOUND_BEGIN or KIT_BOUND_END.
 *
 * @param container The instance of the container to iterate.
 * @param bound The start bound.
 * @return A new instance of kit_List_Iterator or MutableOption_None.
 */
extern MutableOptional(struct kit_List_Iterator *)
kit_List_Iterator_new(struct kit_List *container, enum kit_Bound bound)
__attribute__((__nonnull__));

/**
 * Creates a new instance of kit_List_Iterator from begin of container.
 * In case of out of memory this function returns MutableOption_None.
 *
 * Checked runtime errors:
 *      - @param container must not be NULL.
 *
 * @param container The instance of the container to iterate.
 * @return A new instance of kit_List_Iterator or MutableOption_None.
 */
extern MutableOptional(struct kit_List_Iterator *)
kit_List_Iterator_fromBegin(struct kit_List *container)
__attribute__((__nonnull__));

/**
 * Creates a new instance of kit_List_Iterator from end of container.
 * In case of out of memory this function returns MutableOption_None.
 *
 * Checked runtime errors:
 *      - @param container must not be NULL.
 *
 * @param container The instance of the container to iterate.
 * @return A new instance of kit_List_Iterator or MutableOption_None.
 */
extern MutableOptional(struct kit_List_Iterator *)
kit_List_Iterator_fromEnd(struct kit_List *container)
__attribute__((__nonnull__));

/**
 * Deletes an instance of kit_List_Iterator.
 * If @param self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_List_Iterator_delete(struct kit_List_Iterator *self);

/**
 * Rewinds the iterator.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *      - @param bound must be KIT_BOUND_BEGIN or KIT_BOUND_END.
 *
 * @param self The instance of the iterator to be rewound.
 * @param bound The start bound.
 */
extern void
kit_List_Iterator_rewind(struct kit_List_Iterator *self, enum kit_Bound bound)
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
kit_List_Iterator_rewindToBegin(struct kit_List_Iterator *self)
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
kit_List_Iterator_rewindToEnd(struct kit_List_Iterator *self)
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
kit_List_Iterator_next(struct kit_List_Iterator *self, void **out)
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
kit_List_Iterator_previous(struct kit_List_Iterator *self, void **out)
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
kit_List_Iterator_setLast(struct kit_List_Iterator *self, void *e)
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
kit_List_Iterator_isModified(struct kit_List_Iterator *self)
__attribute__((__nonnull__));

#ifdef __cplusplus
}
#endif

#endif /* KIT_LIST_INCLUDED */
