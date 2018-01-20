/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   January 20, 2018
 */

#ifndef KIT_SEQUENCE_INCLUDED
#define KIT_SEQUENCE_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdbool.h>
#include <option/option.h>
#include <kit/errors.h>
#include <kit/compiler_steroids.h>

/**
 * Sequence provides a common interface for mono-directional iterable containers with dynamic sizes
 * that can be expanded or contracted on both ends (either its front or its back) and allow insert
 * and erase operations anywhere within the sequence.
 */
struct kit_Sequence;

/**
 * Creates a new instance of kit_Sequence using DoublyList as underlying container.
 * In case of out of memory this function returns None.
 *
 * @return A new instance of kit_Sequence or None.
 */
extern OptionOf(struct kit_Sequence *)
kit_Sequence_fromDoublyList(void)
__attribute__((__warn_unused_result__));

/**
 * Creates a new instance of kit_Sequence using SinglyList as underlying container.
 * In case of out of memory this function returns None.
 *
 * @return A new instance of kit_Sequence or None.
 */
extern OptionOf(struct kit_Sequence *)
kit_Sequence_fromSinglyList(void)
__attribute__((__warn_unused_result__));

/**
 * Creates a new instance of kit_Sequence using XorList as underlying container.
 * In case of out of memory this function returns None.
 *
 * @return A new instance of kit_Sequence or None.
 */
extern OptionOf(struct kit_Sequence *)
kit_Sequence_fromXorList(void)
__attribute__((__warn_unused_result__));

/**
 * Creates a new instance of kit_Sequence using Vector as underlying container.
 * In case of out of memory this function returns None.
 *
 * If capacity is 0 then a default capacity will be used.
 *
 * @param capacity An hint about the average capacity.
 * @return A new instance of kit_Sequence or None.
 */
extern OptionOf(struct kit_Sequence *)
kit_Sequence_fromVector(size_t capacity)
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
kit_Sequence_expand(struct kit_Sequence *self, size_t capacity)
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
kit_Sequence_shrink(struct kit_Sequence *self)
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
kit_Sequence_insert(struct kit_Sequence *self, size_t index, void *element)
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
kit_Sequence_pushBack(struct kit_Sequence *self, void *element)
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
kit_Sequence_pushFront(struct kit_Sequence *self, void *element)
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
kit_Sequence_remove(struct kit_Sequence *self, size_t index)
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
kit_Sequence_popBack(struct kit_Sequence *self)
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
kit_Sequence_popFront(struct kit_Sequence *self)
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
kit_Sequence_put(struct kit_Sequence *self, size_t index, void *element)
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
kit_Sequence_get(const struct kit_Sequence *self, size_t index)
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
kit_Sequence_back(const struct kit_Sequence *self)
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
kit_Sequence_front(const struct kit_Sequence *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Removes all elements from the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 */
extern void
kit_Sequence_clear(struct kit_Sequence *self)
__attribute__((__nonnull__));

/**
 * Returns the number of elements currently stored in the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return The numbers of elements in the container.
 */
extern size_t
kit_Sequence_size(const struct kit_Sequence *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns the number of elements the container can store without expanding.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return The numbers of elements that can be stored before expansion.
 */
extern size_t
kit_Sequence_capacity(const struct kit_Sequence *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Tests if this container has no elements.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return true if the container is empty false otherwise.
 */
extern bool
kit_Sequence_isEmpty(const struct kit_Sequence *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Deletes this instance of kit_Sequence.
 * If self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_Sequence_delete(struct kit_Sequence *self);

/**
 * List iterators permit to iterate over the elements of a sequence in forward direction and to update the retrieved elements.
 */
struct kit_Sequence_Iterator;

/**
 * Creates a new instance of kit_Sequence_Iterator starting from the begin of the container.
 *
 * @param container The instance of the container to iterate [<b>must not be NULL</b>].
 * @return A new instance of kit_Sequence_Iterator or None.
 */
extern OptionOf(struct kit_Sequence_Iterator *)
kit_Sequence_Iterator_fromBegin(struct kit_Sequence *container)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Rewinds the iterator to the begin of the container.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 */
extern void
kit_Sequence_Iterator_rewindToBegin(struct kit_Sequence_Iterator *self)
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
kit_Sequence_Iterator_next(struct kit_Sequence_Iterator *self)
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
kit_Sequence_Iterator_setLast(struct kit_Sequence_Iterator *self, void *element)
__attribute__((__warn_unused_result__, __nonnull__(1)));

/**
 * Tests the associated container for modifications.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 * @return true if the container has been modified else false.
 */
extern bool
kit_Sequence_Iterator_isModified(const struct kit_Sequence_Iterator *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Deletes this instance of kit_Sequence_Iterator.
 * If self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_Sequence_Iterator_delete(struct kit_Sequence_Iterator *self);

#ifdef __cplusplus
}
#endif

#endif /* KIT_SEQUENCE_INCLUDED */
