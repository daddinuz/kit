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
#include <kit/errors.h>
#include <kit/compiler_steroids.h>

struct kit_SinglyList;

/**
 * Creates a new instance of kit_SinglyList.
 * In case of out of memory this function returns None.
 *
 * @return A new instance of kit_SinglyList or None.
 */
extern OptionOf(struct kit_SinglyList *)
kit_SinglyList_new(void);

/**
 * Deletes an instance of kit_SinglyList.
 * If self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_SinglyList_delete(struct kit_SinglyList *self);

/**
 * Removes all elements from the container, leaving it with a size of 0.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 */
extern void
kit_SinglyList_clear(struct kit_SinglyList *self)
__attribute__((__nonnull__));

/**
 * Inserts elements at the given index of the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @param e The element to be inserted.
 * @param index The index where the element has to be placed.
 * @return 
 * - Ok => The operation was performed successfully, wraps the stored element.
 * - OutOfRangeError => The given index is out of range, nothing has been done.
 * - OutOfMemoryError => There's no more space left, nothing has been done.
 */
extern ResultOf(void *, OutOfRangeError, OutOfMemoryError)
kit_SinglyList_insert(struct kit_SinglyList *self, void *e, size_t index)
__attribute__((__nonnull__(1)));

/**
 * Inserts elements at the back of the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @param e The element to be inserted.
 * @return 
 * - Ok => The operation was performed successfully, wraps the stored element.
 * - OutOfMemoryError => There's no more space left, nothing has been done.
 */
extern ResultOf(void *, OutOfMemoryError)
kit_SinglyList_pushBack(struct kit_SinglyList *self, void *e)
__attribute__((__nonnull__(1)));

/**
 * Inserts elements at the front of the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @param e The element to be inserted.
 * @return 
 * - Ok => The operation was performed successfully, wraps the stored element.
 * - OutOfMemoryError => There's no more space left, nothing has been done.
 */
extern ResultOf(void *, OutOfMemoryError)
kit_SinglyList_pushFront(struct kit_SinglyList *self, void *e)
__attribute__((__nonnull__(1)));

/**
 * Removes elements at the back of the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return 
 * - Ok => The operation was performed successfully, wraps the removed element.
 * - OutOfRangeError => No such element, nothing has been done.
 */
extern ResultOf(void *, OutOfRangeError)
kit_SinglyList_popBack(struct kit_SinglyList *self)
__attribute__((__nonnull__));

/**
 * Removes elements at the front of the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return 
 * - Ok => The operation was performed successfully, wraps the removed element.
 * - OutOfRangeError => No such element, nothing has been done.
 */
extern ResultOf(void *, OutOfRangeError)
kit_SinglyList_popFront(struct kit_SinglyList *self)
__attribute__((__nonnull__));

/**
 * Removes elements at the given index of the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @param index The index of the element to remove.
 * @return 
 * - Ok => The operation was performed successfully, wraps the removed element.
 * - OutOfRangeError => The given index is out of range, nothing has been done.
 */
extern ResultOf(void *, OutOfRangeError)
kit_SinglyList_remove(struct kit_SinglyList *self, size_t index)
__attribute__((__nonnull__));

/**
 * Replaces the element at the given index.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @param e The new element.
 * @param index The index of the element to be replaced.
 * @return 
 * - Ok => wraps the previous element at the given index.
 * - OutOfRangeError => The given index is out of range, nothing has been done.
 */
extern ResultOf(void *, OutOfRangeError)
kit_SinglyList_set(struct kit_SinglyList *self, void *e, size_t index)
__attribute__((__nonnull__(1)));

/**
 * Gets the element stored at the given index.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @param index The index of the element requested.
 * @return 
 * - Ok => wraps the element at the given index.
 * - OutOfRangeError => The given index is out of range, nothing has been done.
 */
extern ResultOf(void *, OutOfRangeError)
kit_SinglyList_get(struct kit_SinglyList *self, size_t index)
__attribute__((__nonnull__));

/**
 * Gets the element stored at the back of the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return 
 * - Ok => wraps the element at back of the container.
 * - OutOfRangeError => No such element, nothing has been done.
 */
extern ResultOf(void *, OutOfRangeError)
kit_SinglyList_back(struct kit_SinglyList *self)
__attribute__((__nonnull__));

/**
 * Gets the element stored at the front of the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return 
 * - Ok => wraps the element at front of the container.
 * - OutOfRangeError => No such element, nothing has been done.
 */
extern ResultOf(void *, OutOfRangeError)
kit_SinglyList_front(struct kit_SinglyList *self)
__attribute__((__nonnull__));

/**
 * Gets the number of elements currently stored in the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return The numbers of elements in the container.
 */
extern size_t
kit_SinglyList_size(struct kit_SinglyList *self)
__attribute__((__nonnull__));

/**
 * Checks if the container is empty.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return true if the container is empty false otherwise.
 */
extern bool
kit_SinglyList_isEmpty(struct kit_SinglyList *self)
__attribute__((__nonnull__));

struct kit_SinglyList_Iterator;

/**
 * Creates a new instance of kit_SinglyList_Iterator from begin of container.
 * In case of out of memory this function returns None.
 *
 * @param container The instance of the container to iterate [<b>must not be NULL</b>].
 * @return A new instance of kit_SinglyList_Iterator or None.
 */
extern OptionOf(struct kit_SinglyList_Iterator *)
kit_SinglyList_Iterator_fromBegin(struct kit_SinglyList *container)
__attribute__((__nonnull__));

/**
 * Deletes an instance of kit_SinglyList_Iterator.
 * If self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_SinglyList_Iterator_delete(struct kit_SinglyList_Iterator *self);

/**
 * Rewinds the iterator to begin of container.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 */
extern void
kit_SinglyList_Iterator_rewindToBegin(struct kit_SinglyList_Iterator *self)
__attribute__((__nonnull__));

/**
 * Gets the next element moving forward in the container.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 * @return
 * - Ok => The operation was performed successfully, wraps the next element.
 * - OutOfRangeError => The iterator hit the end of the container, nothing has been done.
 * - ConcurrentModificationError => The container has been modified, nothing has been done.
 */
extern ResultOf(void *, OutOfRangeError, ConcurrentModificationError)
kit_SinglyList_Iterator_next(struct kit_SinglyList_Iterator *self)
__attribute__((__nonnull__));

/**
 * Replaces the last retrieved element.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 * @param e The new element.
 * @return
 * - Ok => The operation was performed successfully, wraps the next element.
 * - IllegalStateError => Neither next() nor previous() has been called, nothing has been done.
 * - ConcurrentModificationError => The container has been modified, nothing has been done.
 */
extern ResultOf(void *, IllegalStateError, ConcurrentModificationError)
kit_SinglyList_Iterator_setLast(struct kit_SinglyList_Iterator *self, void *e)
__attribute__((__nonnull__(1)));

/**
 * Checks for associated container modifications.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 * @return true if the container has been modified else false
 */
extern bool
kit_SinglyList_Iterator_isModified(struct kit_SinglyList_Iterator *self)
__attribute__((__nonnull__));

#ifdef __cplusplus
}
#endif

#endif /* KIT_SINGLY_LIST_INCLUDED */
