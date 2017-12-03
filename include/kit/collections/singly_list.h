/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 21, 2017 
 */

/*
 * Singly linked lists are containers that allow insert and erase operations anywhere within the sequence,
 * and iteration in forward direction.
 * Singly linked lists can store each of the elements they contain in different and unrelated storage locations.
 * The ordering is kept internally by the association to each element of a link to the element following it.
 */

#ifndef KIT_SINGLY_LIST_INCLUDED
#define KIT_SINGLY_LIST_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdbool.h>
#include <option/option.h>
#include <kit/compiler_steroids.h>
#include <kit/collections/result.h>

/**
 * kit_SinglyList interface.
 */
struct kit_SinglyList;

/**
 * Creates a new instance of kit_SinglyList.
 * In case of out of memory this function returns MutableOption_None.
 *
 * @return A new instance of kit_SinglyList or MutableOption_None.
 */
extern MutableOptional(struct kit_SinglyList *)
kit_SinglyList_new(void);

/**
 * Deletes an instance of kit_SinglyList.
 * If @param self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_SinglyList_delete(struct kit_SinglyList *self);

/**
 * Removes all elements from the container, leaving it with a size of 0.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The container instance.
 */
extern void
kit_SinglyList_clear(struct kit_SinglyList *self)
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
kit_SinglyList_insert(struct kit_SinglyList *self, void *e, size_t index)
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
kit_SinglyList_pushBack(struct kit_SinglyList *self, void *e)
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
kit_SinglyList_pushFront(struct kit_SinglyList *self, void *e)
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
kit_SinglyList_popBack(struct kit_SinglyList *self, void **out)
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
kit_SinglyList_popFront(struct kit_SinglyList *self, void **out)
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
kit_SinglyList_remove(struct kit_SinglyList *self, void **out, size_t index)
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
kit_SinglyList_set(struct kit_SinglyList *self, void *e, size_t index)
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
kit_SinglyList_get(struct kit_SinglyList *self, void **out, size_t index)
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
kit_SinglyList_back(struct kit_SinglyList *self, void **out)
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
kit_SinglyList_front(struct kit_SinglyList *self, void **out)
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
kit_SinglyList_size(struct kit_SinglyList *self)
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
kit_SinglyList_isEmpty(struct kit_SinglyList *self)
__attribute__((__nonnull__));

/**
 * kit_SinglyList_Iterator interface.
 */
struct kit_SinglyList_Iterator;

/**
 * Creates a new instance of kit_SinglyList_Iterator from begin of container.
 * In case of out of memory this function returns MutableOption_None.
 *
 * Checked runtime errors:
 *      - @param container must not be NULL.
 *
 * @param container The instance of the container to iterate.
 * @return A new instance of kit_SinglyList_Iterator or MutableOption_None.
 */
extern MutableOptional(struct kit_SinglyList_Iterator *)
kit_SinglyList_Iterator_fromBegin(struct kit_SinglyList *container)
__attribute__((__nonnull__));

/**
 * Deletes an instance of kit_SinglyList_Iterator.
 * If @param self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_SinglyList_Iterator_delete(struct kit_SinglyList_Iterator *self);

/**
 * Rewinds the iterator to begin of container.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The iterator instance.
 */
extern void
kit_SinglyList_Iterator_rewindToBegin(struct kit_SinglyList_Iterator *self)
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
kit_SinglyList_Iterator_next(struct kit_SinglyList_Iterator *self, void **out)
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
kit_SinglyList_Iterator_setLast(struct kit_SinglyList_Iterator *self, void *e)
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
kit_SinglyList_Iterator_isModified(struct kit_SinglyList_Iterator *self)
__attribute__((__nonnull__));

#ifdef __cplusplus
}
#endif

#endif /* KIT_SINGLY_LIST_INCLUDED */
