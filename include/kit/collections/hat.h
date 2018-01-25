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

#ifndef KIT_HAT_INCLUDED
#define KIT_HAT_INCLUDED

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
 * Hats (hashed array tree) are containers representing arrays that can change in size.
 * Its primary objective is to reduce the amount of element copying due to automatic array resizing operations,
 * and to improve memory usage patterns.
 *
 * Unlike arrays, their size can change dynamically, with their storage being handled automatically by the container.
 * Internally, a hashed array tree has a top-level directory containing a power of two number of leaf arrays.
 * All leaf arrays are the same size as the top-level directory.
 * This structure superficially resembles a hash table with array-based collision chains, which is the basis
 * for the name hashed array tree.
 */
struct kit_Hat;

/**
 * Creates a new instance of kit_Hat with a default capacity.
 * @see hat_config.h
 *
 * @return A new instance of kit_Hat or None.
 */
extern OptionOf(struct kit_Hat *)
kit_Hat_new(void)
__attribute__((__warn_unused_result__));

/**
 * Creates a new instance of kit_Hat with at least specified capacity.
 *
 * @attention
 *  If specified capacity is 0 then default capacity will be used.
 *
 * @see hat_config.h
 *
 * @return A new instance of kit_Hat or None.
 */
extern OptionOf(struct kit_Hat *)
kit_Hat_withCapacity(size_t capacity)
__attribute__((__warn_unused_result__));

/**
 * Requests the container to expand to hold at least as many elements as specified by capacity.
 * If requested capacity is less than hat capacity nothing will be done.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @param capacity The minimum capacity to hold.
 * @return
 * - Ok => The operation was performed successfully.
 * - OutOfMemoryError => There's no more space left, nothing has been done.
 */
extern OneOf(Ok, OutOfMemoryError)
kit_Hat_expand(struct kit_Hat *self, size_t capacity)
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
kit_Hat_shrink(struct kit_Hat *self)
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
kit_Hat_insert(struct kit_Hat *self, size_t index, void *element)
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
kit_Hat_pushBack(struct kit_Hat *self, void *element)
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
kit_Hat_pushFront(struct kit_Hat *self, void *element)
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
kit_Hat_remove(struct kit_Hat *self, size_t index)
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
kit_Hat_popBack(struct kit_Hat *self)
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
kit_Hat_popFront(struct kit_Hat *self)
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
kit_Hat_put(struct kit_Hat *self, size_t index, void *element)
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
kit_Hat_get(const struct kit_Hat *self, size_t index)
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
kit_Hat_back(const struct kit_Hat *self)
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
kit_Hat_front(const struct kit_Hat *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Removes all elements from the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 */
extern void
kit_Hat_clear(struct kit_Hat *self)
__attribute__((__nonnull__));

/**
 * Returns the number of elements currently stored in the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return The numbers of elements in the container.
 */
extern size_t
kit_Hat_size(const struct kit_Hat *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns the number of elements the container can store without expanding.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return The numbers of elements that can be stored before expansion.
 */
extern size_t
kit_Hat_capacity(const struct kit_Hat *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Tests if this container has no elements.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return true if the container is empty false otherwise.
 */
extern bool
kit_Hat_isEmpty(const struct kit_Hat *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns the raw data of the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return The low level array of elements.
 */
extern void **
kit_Hat_raw(const struct kit_Hat *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Deletes this instance of kit_Hat.
 * If self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_Hat_delete(struct kit_Hat *self);

/**
 * Hat iterators permit to iterate over the elements of a hat in both directions and to update the retrieved elements.
 */
struct kit_Hat_Iterator;

/**
 * Creates a new instance of kit_Hat_Iterator staring from the specified bound.
 *
 * @param container The instance of the container to iterate [<b>must not be NULL</b>].
 * @param bound The starting bound.
 * @return A new instance of kit_Hat_Iterator or None.
 */
extern OptionOf(struct kit_Hat_Iterator *)
kit_Hat_Iterator_new(struct kit_Hat *container, enum kit_Bound bound)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Creates a new instance of kit_Hat_Iterator starting from the begin of the container.
 *
 * @param container The instance of the container to iterate [<b>must not be NULL</b>].
 * @return A new instance of kit_Hat_Iterator or None.
 */
extern OptionOf(struct kit_Hat_Iterator *)
kit_Hat_Iterator_fromBegin(struct kit_Hat *container)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Creates a new instance of kit_Hat_Iterator starting from the end of the container.
 *
 * @param container The instance of the container to iterate [<b>must not be NULL</b>].
 * @return A new instance of kit_Hat_Iterator or None.
 */
extern OptionOf(struct kit_Hat_Iterator *)
kit_Hat_Iterator_fromEnd(struct kit_Hat *container)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Rewinds the iterator to the specified bound.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 * @param bound The bound where the iterator must be rewound.
 */
extern void
kit_Hat_Iterator_rewind(struct kit_Hat_Iterator *self, enum kit_Bound bound)
__attribute__((__nonnull__));

/**
 * Rewinds the iterator to the begin of the container.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 */
extern void
kit_Hat_Iterator_rewindToBegin(struct kit_Hat_Iterator *self)
__attribute__((__nonnull__));

/**
 * Rewinds the iterator to the end of the container.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 */
extern void
kit_Hat_Iterator_rewindToEnd(struct kit_Hat_Iterator *self)
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
kit_Hat_Iterator_next(struct kit_Hat_Iterator *self)
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
kit_Hat_Iterator_previous(struct kit_Hat_Iterator *self)
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
kit_Hat_Iterator_setLast(struct kit_Hat_Iterator *self, void *element)
__attribute__((__warn_unused_result__, __nonnull__(1)));

/**
 * Tests the associated container for modifications.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 * @return true if the container has been modified else false.
 */
extern bool
kit_Hat_Iterator_isModified(const struct kit_Hat_Iterator *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Deletes this instance of kit_Hat_Iterator.
 * If self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_Hat_Iterator_delete(struct kit_Hat_Iterator *self);

#ifdef __cplusplus
}
#endif

#endif /* KIT_HAT_INCLUDED */
