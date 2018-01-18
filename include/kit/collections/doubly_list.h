/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   January 18, 2018
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

/**
 * Doubly linked lists are containers that allow insert and erase operations anywhere within the sequence,
 * and iteration in both directions.
 * Doubly linked lists can store each of the elements they contain in different and unrelated storage locations.
 * The ordering is kept internally by the association to each element of a link to the element preceding it
 * and a link to the element following it.
 */
struct kit_DoublyList;

/**
 * Creates a new instance of kit_DoublyList
 *
 * @return A new instance of kit_DoublyList or None.
 */
extern OptionOf(struct kit_DoublyList *)
kit_DoublyList_new(void)
__attribute__((__warn_unused_result__));

/**
 * Inserts the specified element at the specified position in this container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @param element The element to be inserted.
 * @param index The index where the element has to be placed.
 * @return 
 * - Ok => The operation was performed successfully.
 * - OutOfRangeError => The given index is out of range, nothing has been done.
 * - OutOfMemoryError => There's no more space left, nothing has been done.
 */
extern OneOf(Ok, OutOfRangeError, OutOfMemoryError)
kit_DoublyList_insert(struct kit_DoublyList *self, size_t index, void *element)
__attribute__((__warn_unused_result__, __nonnull__(1)));

/**
 * Inserts the specified element to the back of this container.
 *
 * @param self The the container instance [<b>must not be NULL</b>].
 * @param element The element to be inserted.
 * @return 
 * - Ok => The operation was performed successfully.
 * - OutOfMemoryError => There's no more space left, nothing has been done.
 */
extern OneOf(Ok, OutOfMemoryError)
kit_DoublyList_pushBack(struct kit_DoublyList *self, void *element)
__attribute__((__warn_unused_result__, __nonnull__(1)));

/**
 * Inserts the specified element to the front of this container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @param element The element to be inserted.
 * @return 
 * - Ok => The operation was performed successfully.
 * - OutOfMemoryError => There's no more space left, nothing has been done.
 */
extern OneOf(Ok, OutOfMemoryError)
kit_DoublyList_pushFront(struct kit_DoublyList *self, void *element)
__attribute__((__warn_unused_result__, __nonnull__(1)));

/**
 * Removes the element at the specified position in this container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @param index The index of the element to remove.
 * @return
 * - Ok => Wraps the removed element.
 * - OutOfRangeError => The given index is out of range, nothing has been done.
 */
extern ResultOf(void *, OutOfRangeError)
kit_DoublyList_remove(struct kit_DoublyList *self, size_t index)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Removes the element at the back of this container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return 
 * - Ok => Wraps the removed element.
 * - OutOfRangeError => No such element, nothing has been done.
 */
extern ResultOf(void *, OutOfRangeError)
kit_DoublyList_popBack(struct kit_DoublyList *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Removes the element at the front of this container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return 
 * - Ok => Wraps the removed element.
 * - OutOfRangeError => No such element, nothing has been done.
 */
extern ResultOf(void *, OutOfRangeError)
kit_DoublyList_popFront(struct kit_DoublyList *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Replaces the element at the specified position in this container with the specified element.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @param index The index of the element to be replaced.
 * @param element The new element.
 * @return
 * - Ok => Wraps the replaced element.
 * - OutOfRangeError => The given index is out of range, nothing has been done.
 */
extern ResultOf(void *, OutOfRangeError)
kit_DoublyList_put(struct kit_DoublyList *self, size_t index, void *element)
__attribute__((__warn_unused_result__, __nonnull__(1)));

/**
 * Returns the element at the specified position in this container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @param index The index of the element.
 * @return
 * - Ok => Wraps the specified element.
 * - OutOfRangeError => The given index is out of range, nothing has been done.
 */
extern ResultOf(void *, OutOfRangeError)
kit_DoublyList_get(const struct kit_DoublyList *self, size_t index)
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
kit_DoublyList_back(const struct kit_DoublyList *self)
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
kit_DoublyList_front(const struct kit_DoublyList *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Removes all elements from the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 */
extern void
kit_DoublyList_clear(struct kit_DoublyList *self)
__attribute__((__nonnull__));

/**
 * Returns the number of elements currently stored in the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return The numbers of elements in the container.
 */
extern size_t
kit_DoublyList_size(const struct kit_DoublyList *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Tests if this container has no elements.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return true if the container is empty false otherwise.
 */
extern bool
kit_DoublyList_isEmpty(const struct kit_DoublyList *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Deletes this instance of kit_DoublyList.
 * If self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_DoublyList_delete(struct kit_DoublyList *self);

/**
 * DoublyList iterators permit to iterate over the elements of a doubly list in both directions and to update the retrieved elements.
 */
struct kit_DoublyList_Iterator;

/**
 * Creates a new instance of kit_DoublyList_Iterator staring from the specified bound.
 *
 * @param container The instance of the container to iterate [<b>must not be NULL</b>].
 * @param bound The starting bound.
 * @return A new instance of kit_DoublyList_Iterator or None.
 */
extern OptionOf(struct kit_DoublyList_Iterator *)
kit_DoublyList_Iterator_new(struct kit_DoublyList *container, enum kit_Bound bound)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Creates a new instance of kit_DoublyList_Iterator starting from the begin of the container.
 *
 * @param container The instance of the container to iterate [<b>must not be NULL</b>].
 * @return A new instance of kit_DoublyList_Iterator or None.
 */
extern OptionOf(struct kit_DoublyList_Iterator *)
kit_DoublyList_Iterator_fromBegin(struct kit_DoublyList *container)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Creates a new instance of kit_DoublyList_Iterator starting from the end of the container.
 *
 * @param container The instance of the container to iterate [<b>must not be NULL</b>].
 * @return A new instance of kit_DoublyList_Iterator or None.
 */
extern OptionOf(struct kit_DoublyList_Iterator *)
kit_DoublyList_Iterator_fromEnd(struct kit_DoublyList *container)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Rewinds the iterator to the specified bound.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 * @param bound The bound where the iterator must be rewound.
 */
extern void
kit_DoublyList_Iterator_rewind(struct kit_DoublyList_Iterator *self, enum kit_Bound bound)
__attribute__((__nonnull__));

/**
 * Rewinds the iterator to the begin of the container.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 */
extern void
kit_DoublyList_Iterator_rewindToBegin(struct kit_DoublyList_Iterator *self)
__attribute__((__nonnull__));

/**
 * Rewinds the iterator to the end of the container.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 */
extern void
kit_DoublyList_Iterator_rewindToEnd(struct kit_DoublyList_Iterator *self)
__attribute__((__nonnull__));

/**
 * Returns the next element moving forward in the container.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 * @return
 * - Ok => Wraps the retrieved element.
 * - OutOfRangeError => The iterator hit the end of the container, nothing has been done.
 * - ConcurrentModificationError => The container has been modified, nothing has been done.
 */
extern ResultOf(void *, OutOfRangeError, ConcurrentModificationError)
kit_DoublyList_Iterator_next(struct kit_DoublyList_Iterator *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns the previous element moving backword in the container.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 * @return
 * - Ok => Wraps the retrieved element.
 * - OutOfRangeError => The iterator hit the end of the container, nothing has been done.
 * - ConcurrentModificationError => The container has been modified, nothing has been done.
 */
extern ResultOf(void *, OutOfRangeError, ConcurrentModificationError)
kit_DoublyList_Iterator_previous(struct kit_DoublyList_Iterator *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Replaces the last retrieved element with the specified element.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 * @param element The new element.
 * @return
 * - Ok => Wraps the replaced element.
 * - IllegalStateError => No elements have been retrieved yet, nothing has been done.
 * - ConcurrentModificationError => The container has been modified, nothing has been done.
 */
extern ResultOf(void *, IllegalStateError, ConcurrentModificationError)
kit_DoublyList_Iterator_setLast(struct kit_DoublyList_Iterator *self, void *element)
__attribute__((__warn_unused_result__, __nonnull__(1)));

/**
 * Tests the associated container for modifications.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 * @return true if the container has been modified else false.
 */
extern bool
kit_DoublyList_Iterator_isModified(const struct kit_DoublyList_Iterator *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Deletes this instance of kit_DoublyList_Iterator.
 * If self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_DoublyList_Iterator_delete(struct kit_DoublyList_Iterator *self);

#ifdef __cplusplus
}
#endif

#endif /* KIT_DOUBLY_LIST_INCLUDED */
