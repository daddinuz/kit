/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 21, 2017 
 */

/*
 * Doubly linked lists are containers that allow insert and erase operations anywhere within the sequence,
 * and iteration in both directions.
 * Doubly linked lists can store each of the elements they contain in different and unrelated storage locations.
 * The ordering is kept internally by the association to each element of a link to the element preceding it
 * and a link to the element following it.
 */

#ifndef KIT_DOUBLY_LIST_INCLUDED
#define KIT_DOUBLY_LIST_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdbool.h>
#include <option/option.h>
#include <kit/errors.h>
#include <kit/compiler_steroids.h>
#include <kit/collections/bound.h>

struct kit_DoublyList;

/**
 * Creates a new instance of kit_DoublyList.
 * In case of out of memory this function returns None.
 *
 * @return A new instance of kit_DoublyList or None.
 */
extern OptionOf(struct kit_DoublyList *)
kit_DoublyList_new(void);

/**
 * Deletes an instance of kit_DoublyList.
 * If self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_DoublyList_delete(struct kit_DoublyList *self);

/**
 * Removes all elements from the container, leaving it with a size of 0.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 */
extern void
kit_DoublyList_clear(struct kit_DoublyList *self)
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
kit_DoublyList_insert(struct kit_DoublyList *self, void *e, size_t index)
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
kit_DoublyList_pushBack(struct kit_DoublyList *self, void *e)
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
kit_DoublyList_pushFront(struct kit_DoublyList *self, void *e)
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
kit_DoublyList_popBack(struct kit_DoublyList *self)
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
kit_DoublyList_popFront(struct kit_DoublyList *self)
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
kit_DoublyList_remove(struct kit_DoublyList *self, size_t index)
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
kit_DoublyList_set(struct kit_DoublyList *self, void *e, size_t index)
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
kit_DoublyList_get(struct kit_DoublyList *self, size_t index)
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
kit_DoublyList_back(struct kit_DoublyList *self)
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
kit_DoublyList_front(struct kit_DoublyList *self)
__attribute__((__nonnull__));

/**
 * Gets the number of elements currently stored in the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return The numbers of elements in the container.
 */
extern size_t
kit_DoublyList_size(struct kit_DoublyList *self)
__attribute__((__nonnull__));

/**
 * Checks if the container is empty.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return true if the container is empty false otherwise.
 */
extern bool
kit_DoublyList_isEmpty(struct kit_DoublyList *self)
__attribute__((__nonnull__));

struct kit_DoublyList_Iterator;

/**
 * Creates a new instance of kit_DoublyList_Iterator.
 * In case of out of memory this function returns None.
 *
 * @param container The instance of the container to iterate [<b>must not be NULL</b>].
 * @param bound The start bound.
 * @return A new instance of kit_DoublyList_Iterator or None.
 */
extern OptionOf(struct kit_DoublyList_Iterator *)
kit_DoublyList_Iterator_new(struct kit_DoublyList *container, enum kit_Bound bound)
__attribute__((__nonnull__));

/**
 * Creates a new instance of kit_DoublyList_Iterator from begin of container.
 * In case of out of memory this function returns None.
 *
 * @param container The instance of the container to iterate [<b>must not be NULL</b>].
 * @return A new instance of kit_DoublyList_Iterator or None.
 */
extern OptionOf(struct kit_DoublyList_Iterator *)
kit_DoublyList_Iterator_fromBegin(struct kit_DoublyList *container)
__attribute__((__nonnull__));

/**
 * Creates a new instance of kit_DoublyList_Iterator from end of container.
 * In case of out of memory this function returns None.
 *
 * @param container The instance of the container to iterate [<b>must not be NULL</b>].
 * @return A new instance of kit_DoublyList_Iterator or None.
 */
extern OptionOf(struct kit_DoublyList_Iterator *)
kit_DoublyList_Iterator_fromEnd(struct kit_DoublyList *container)
__attribute__((__nonnull__));

/**
 * Deletes an instance of kit_DoublyList_Iterator.
 * If self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_DoublyList_Iterator_delete(struct kit_DoublyList_Iterator *self);

/**
 * Rewinds the iterator.
 *
 * @param container The instance of the container to iterate [<b>must not be NULL</b>].
 * @param bound The start bound.
 */
extern void
kit_DoublyList_Iterator_rewind(struct kit_DoublyList_Iterator *self, enum kit_Bound bound)
__attribute__((__nonnull__));

/**
 * Rewinds the iterator to begin of container.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 */
extern void
kit_DoublyList_Iterator_rewindToBegin(struct kit_DoublyList_Iterator *self)
__attribute__((__nonnull__));

/**
 * Rewinds the iterator to end of container.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 */
extern void
kit_DoublyList_Iterator_rewindToEnd(struct kit_DoublyList_Iterator *self)
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
kit_DoublyList_Iterator_next(struct kit_DoublyList_Iterator *self)
__attribute__((__nonnull__));

/**
 * Gets the previous element moving backward in the container.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 * @return
 * - Ok => The operation was performed successfully, wraps the previous element.
 * - OutOfRangeError => The iterator hit the end of the container, nothing has been done.
 * - ConcurrentModificationError => The container has been modified, nothing has been done.
 */
extern ResultOf(void *, OutOfRangeError, ConcurrentModificationError)
kit_DoublyList_Iterator_previous(struct kit_DoublyList_Iterator *self)
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
kit_DoublyList_Iterator_setLast(struct kit_DoublyList_Iterator *self, void *e)
__attribute__((__nonnull__(1)));

/**
 * Checks for associated container modifications.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 * @return true if the container has been modified else false
 */
extern bool
kit_DoublyList_Iterator_isModified(struct kit_DoublyList_Iterator *self)
__attribute__((__nonnull__));

#ifdef __cplusplus
}
#endif

#endif /* KIT_DOUBLY_LIST_INCLUDED */
