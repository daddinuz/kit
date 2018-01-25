/*
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 *
 * Copyright (c) 2018 Davide Di Carlo
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef KIT_DEQUE_INCLUDED
#define KIT_DEQUE_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdbool.h>
#include <option/option.h>
#include <kit/errors.h>
#include <kit/compiler_steroids.h>

/**
 * Deque provides a common interface for bi-directional iterable containers with dynamic sizes
 * that can be expanded or contracted on both ends (either its front or its back).
 * Deque are not guaranteed to store all its elements in contiguous storage locations.
 */
struct kit_Deque;

/**
 * Creates a new instance of kit_Deque using DoublyList as underlying container.
 * In case of out of memory this function returns None.
 *
 * @return A new instance of kit_Deque or None.
 */
extern OptionOf(struct kit_Deque *)
kit_Deque_fromDoublyList(void)
__attribute__((__warn_unused_result__));

/**
 * Creates a new instance of kit_Deque using XorList as underlying container.
 * In case of out of memory this function returns None.
 *
 * @return A new instance of kit_Deque or None.
 */
extern OptionOf(struct kit_Deque *)
kit_Deque_fromXorList(void)
__attribute__((__warn_unused_result__));

/**
 * Creates a new instance of kit_Deque using Vector as underlying container.
 * In case of out of memory this function returns None.
 *
 * If capacity is 0 then a default capacity will be used.
 *
 * @param capacity An hint about the average capacity.
 * @return A new instance of kit_Deque or None.
 */
extern OptionOf(struct kit_Deque *)
kit_Deque_fromVector(size_t capacity)
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
kit_Deque_expand(struct kit_Deque *self, size_t capacity)
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
kit_Deque_shrink(struct kit_Deque *self)
__attribute__((__warn_unused_result__, __nonnull__));

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
kit_Deque_pushBack(struct kit_Deque *self, void *element)
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
kit_Deque_pushFront(struct kit_Deque *self, void *element)
__attribute__((__warn_unused_result__, __nonnull__(1)));

/**
 * Removes the element at the back of this container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return
 * - Ok => Wraps the removed element.
 * - OutOfRangeError => No such element, nothing has been done.
 */
extern ResultOf(void *, OutOfRangeError)
kit_Deque_popBack(struct kit_Deque *self)
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
kit_Deque_popFront(struct kit_Deque *self)
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
kit_Deque_back(const struct kit_Deque *self)
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
kit_Deque_front(const struct kit_Deque *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Removes all elements from the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 */
extern void
kit_Deque_clear(struct kit_Deque *self)
__attribute__((__nonnull__));

/**
 * Returns the number of elements currently stored in the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return The numbers of elements in the container.
 */
extern size_t
kit_Deque_size(const struct kit_Deque *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns the number of elements the container can store without expanding.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return The numbers of elements that can be stored before expansion.
 */
extern size_t
kit_Deque_capacity(const struct kit_Deque *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Tests if this container has no elements.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return true if the container is empty false otherwise.
 */
extern bool
kit_Deque_isEmpty(const struct kit_Deque *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Deletes this instance of kit_Deque.
 * If self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_Deque_delete(struct kit_Deque *self);

/**
 * Deque iterators permit to iterate over the elements of a deque in both directions and to update the retrieved elements.
 */
struct kit_Deque_Iterator;

/**
 * Creates a new instance of kit_Deque_Iterator staring from the specified bound.
 *
 * @param container The instance of the container to iterate [<b>must not be NULL</b>].
 * @param bound The starting bound.
 * @return A new instance of kit_Deque_Iterator or None.
 */
extern OptionOf(struct kit_Deque_Iterator *)
kit_Deque_Iterator_new(struct kit_Deque *container, enum kit_Bound bound)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Creates a new instance of kit_Deque_Iterator starting from the begin of the container.
 *
 * @param container The instance of the container to iterate [<b>must not be NULL</b>].
 * @return A new instance of kit_Deque_Iterator or None.
 */
extern OptionOf(struct kit_Deque_Iterator *)
kit_Deque_Iterator_fromBegin(struct kit_Deque *container)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Creates a new instance of kit_Deque_Iterator starting from the end of the container.
 *
 * @param container The instance of the container to iterate [<b>must not be NULL</b>].
 * @return A new instance of kit_Deque_Iterator or None.
 */
extern OptionOf(struct kit_Deque_Iterator *)
kit_Deque_Iterator_fromEnd(struct kit_Deque *container)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Rewinds the iterator to the specified bound.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 * @param bound The bound where the iterator must be rewound.
 */
extern void
kit_Deque_Iterator_rewind(struct kit_Deque_Iterator *self, enum kit_Bound bound)
__attribute__((__nonnull__));

/**
 * Rewinds the iterator to the begin of the container.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 */
extern void
kit_Deque_Iterator_rewindToBegin(struct kit_Deque_Iterator *self)
__attribute__((__nonnull__));

/**
 * Rewinds the iterator to the end of the container.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 */
extern void
kit_Deque_Iterator_rewindToEnd(struct kit_Deque_Iterator *self)
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
kit_Deque_Iterator_next(struct kit_Deque_Iterator *self)
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
kit_Deque_Iterator_previous(struct kit_Deque_Iterator *self)
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
kit_Deque_Iterator_setLast(struct kit_Deque_Iterator *self, void *element)
__attribute__((__warn_unused_result__, __nonnull__(1)));

/**
 * Tests the associated container for modifications.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 * @return true if the container has been modified else false.
 */
extern bool
kit_Deque_Iterator_isModified(const struct kit_Deque_Iterator *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Deletes this instance of kit_Deque_Iterator.
 * If self is NULL no action will be performed.
 *
 *
 * @param self The instance to be deleted.
 */
extern void
kit_Deque_Iterator_delete(struct kit_Deque_Iterator *self);

#ifdef __cplusplus
}
#endif

#endif /* KIT_DEQUE_INCLUDED */
