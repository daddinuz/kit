/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   January 18, 2018
 */

#ifndef KIT_LIST_INCLUDED
#define KIT_LIST_INCLUDED

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
 * List provides a common interface for bi-directional iterable containers with dynamic sizes
 * that can be expanded or contracted on both ends (either its front or its back) and allow insert
 * and erase operations anywhere within the sequence.
 */
struct kit_List;

/**
 * Creates a new instance of kit_List using DoublyList as underlying container.
 * In case of out of memory this function returns MutableOption_None.
 *
 * @return A new instance of kit_List or MutableOption_None.
 */
extern OptionOf(struct kit_List *)
kit_List_fromDoublyList(void)
__attribute__((__warn_unused_result__));

/**
 * Creates a new instance of kit_List using XorList as underlying container.
 * In case of out of memory this function returns MutableOption_None.
 *
 * @return A new instance of kit_List or MutableOption_None.
 */
extern OptionOf(struct kit_List *)
kit_List_fromXorList(void)
__attribute__((__warn_unused_result__));

/**
 * Creates a new instance of kit_List using Vector as underlying container.
 * In case of out of memory this function returns MutableOption_None.
 *
 * If capacity is 0 then a default capacity will be used.
 *
 * @param capacity An hint about the average capacity.
 * @return A new instance of kit_List or MutableOption_None.
 */
extern OptionOf(struct kit_List *)
kit_List_fromVector(size_t capacity)
__attribute__((__warn_unused_result__));

/**
 * Requests the container to expand to hold at least as many elements as specified by capacity.
 * If requested capacity is less than list capacity nothing will be done.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @param capacity The minimum capacity to hold.
 * @return
 * - Ok => The operation was performed successfully.
 * - OutOfMemoryError => There's no more space left, nothing has been done.
 */
extern OneOf(Ok, OutOfMemoryError)
kit_List_expand(struct kit_List *self, size_t capacity)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Requests the container to shrink in order to hold at least the stored elements freeing resources not used.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return
 * - Ok => The operation was performed successfully.
 * - OutOfMemoryError => There's no more space left, nothing has been done.
 */
extern OneOf(Ok, OutOfMemoryError)
kit_List_shrink(struct kit_List *self)
__attribute__((__warn_unused_result__, __nonnull__));

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
kit_List_insert(struct kit_List *self, size_t index, void *element)
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
kit_List_pushBack(struct kit_List *self, void *element)
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
kit_List_pushFront(struct kit_List *self, void *element)
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
kit_List_remove(struct kit_List *self, size_t index)
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
kit_List_popBack(struct kit_List *self)
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
kit_List_popFront(struct kit_List *self)
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
kit_List_put(struct kit_List *self, size_t index, void *element)
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
kit_List_get(const struct kit_List *self, size_t index)
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
kit_List_back(const struct kit_List *self)
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
kit_List_front(const struct kit_List *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Removes all elements from the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 */
extern void
kit_List_clear(struct kit_List *self)
__attribute__((__nonnull__));

/**
 * Returns the number of elements currently stored in the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return The numbers of elements in the container.
 */
extern size_t
kit_List_size(const struct kit_List *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns the number of elements the container can store without expanding.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return The numbers of elements that can be stored before expansion.
 */
extern size_t
kit_List_capacity(const struct kit_List *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Tests if this container has no elements.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return true if the container is empty false otherwise.
 */
extern bool
kit_List_isEmpty(const struct kit_List *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Deletes this instance of kit_List.
 * If self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_List_delete(struct kit_List *self);

/**
 * List iterators permit to iterate over the elements of a list in both directions and to update the retrieved elements.
 */
struct kit_List_Iterator;

/**
 * Creates a new instance of kit_List_Iterator staring from the specified bound.
 *
 * @param container The instance of the container to iterate [<b>must not be NULL</b>].
 * @param bound The starting bound.
 * @return A new instance of kit_List_Iterator or None.
 */
extern OptionOf(struct kit_List_Iterator *)
kit_List_Iterator_new(struct kit_List *container, enum kit_Bound bound)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Creates a new instance of kit_List_Iterator starting from the begin of the container.
 *
 * @param container The instance of the container to iterate [<b>must not be NULL</b>].
 * @return A new instance of kit_List_Iterator or None.
 */
extern OptionOf(struct kit_List_Iterator *)
kit_List_Iterator_fromBegin(struct kit_List *container)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Creates a new instance of kit_List_Iterator starting from the end of the container.
 *
 * @param container The instance of the container to iterate [<b>must not be NULL</b>].
 * @return A new instance of kit_List_Iterator or None.
 */
extern OptionOf(struct kit_List_Iterator *)
kit_List_Iterator_fromEnd(struct kit_List *container)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Rewinds the iterator to the specified bound.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 * @param bound The bound where the iterator must be rewound.
 */
extern void
kit_List_Iterator_rewind(struct kit_List_Iterator *self, enum kit_Bound bound)
__attribute__((__nonnull__));

/**
 * Rewinds the iterator to the begin of the container.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 */
extern void
kit_List_Iterator_rewindToBegin(struct kit_List_Iterator *self)
__attribute__((__nonnull__));

/**
 * Rewinds the iterator to the end of the container.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 */
extern void
kit_List_Iterator_rewindToEnd(struct kit_List_Iterator *self)
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
kit_List_Iterator_next(struct kit_List_Iterator *self)
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
kit_List_Iterator_previous(struct kit_List_Iterator *self)
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
kit_List_Iterator_setLast(struct kit_List_Iterator *self, void *element)
__attribute__((__warn_unused_result__, __nonnull__(1)));

/**
 * Tests the associated container for modifications.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 * @return true if the container has been modified else false.
 */
extern bool
kit_List_Iterator_isModified(const struct kit_List_Iterator *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Deletes this instance of kit_List_Iterator.
 * If self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_List_Iterator_delete(struct kit_List_Iterator *self);

#ifdef __cplusplus
}
#endif

#endif /* KIT_LIST_INCLUDED */
