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

#ifndef KIT_XOR_LIST_INCLUDED
#define KIT_XOR_LIST_INCLUDED

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
 * XOR linked lists is a data structure that takes advantage of the bitwise XOR operation to decrease storage
 * requirements for doubly linked lists.
 * XOR linked lists like doubly linked lists are containers that allow insert and erase operations anywhere
 * within the sequence, and iteration in both directions.
 * XOR linked lists can store each of the elements they contain in different and unrelated storage locations.
 * The ordering is kept internally by the association to each element of a link that compresses the next and previous
 * information into one address field by storing the bitwise XOR of the address for previous and the address
 * for next in one field.
 */
struct kit_XorList;

/**
 * Creates a new instance of kit_XorList
 *
 * @return A new instance of kit_XorList or None.
 */
extern OptionOf(struct kit_XorList *)
kit_XorList_new(void)
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
kit_XorList_insert(struct kit_XorList *self, size_t index, void *element)
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
kit_XorList_pushBack(struct kit_XorList *self, void *element)
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
kit_XorList_pushFront(struct kit_XorList *self, void *element)
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
kit_XorList_remove(struct kit_XorList *self, size_t index)
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
kit_XorList_popBack(struct kit_XorList *self)
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
kit_XorList_popFront(struct kit_XorList *self)
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
kit_XorList_put(struct kit_XorList *self, size_t index, void *element)
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
kit_XorList_get(const struct kit_XorList *self, size_t index)
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
kit_XorList_back(const struct kit_XorList *self)
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
kit_XorList_front(const struct kit_XorList *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Removes all elements from the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 */
extern void
kit_XorList_clear(struct kit_XorList *self)
__attribute__((__nonnull__));

/**
 * Returns the number of elements currently stored in the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return The numbers of elements in the container.
 */
extern size_t
kit_XorList_size(const struct kit_XorList *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Tests if this container has no elements.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return true if the container is empty false otherwise.
 */
extern bool
kit_XorList_isEmpty(const struct kit_XorList *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Deletes this instance of kit_XorList.
 * If self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_XorList_delete(struct kit_XorList *self);

/**
 * XorList iterators permit to iterate over the elements of a xor list in both directions and to update the retrieved elements.
 */
struct kit_XorList_Iterator;

/**
 * Creates a new instance of kit_XorList_Iterator staring from the specified bound.
 *
 * @param container The instance of the container to iterate [<b>must not be NULL</b>].
 * @param bound The starting bound.
 * @return A new instance of kit_XorList_Iterator or None.
 */
extern OptionOf(struct kit_XorList_Iterator *)
kit_XorList_Iterator_new(struct kit_XorList *container, enum kit_Bound bound)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Creates a new instance of kit_XorList_Iterator starting from the begin of the container.
 *
 * @param container The instance of the container to iterate [<b>must not be NULL</b>].
 * @return A new instance of kit_XorList_Iterator or None.
 */
extern OptionOf(struct kit_XorList_Iterator *)
kit_XorList_Iterator_fromBegin(struct kit_XorList *container)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Creates a new instance of kit_XorList_Iterator starting from the end of the container.
 *
 * @param container The instance of the container to iterate [<b>must not be NULL</b>].
 * @return A new instance of kit_XorList_Iterator or None.
 */
extern OptionOf(struct kit_XorList_Iterator *)
kit_XorList_Iterator_fromEnd(struct kit_XorList *container)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Rewinds the iterator to the specified bound.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 * @param bound The bound where the iterator must be rewound.
 */
extern void
kit_XorList_Iterator_rewind(struct kit_XorList_Iterator *self, enum kit_Bound bound)
__attribute__((__nonnull__));

/**
 * Rewinds the iterator to the begin of the container.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 */
extern void
kit_XorList_Iterator_rewindToBegin(struct kit_XorList_Iterator *self)
__attribute__((__nonnull__));

/**
 * Rewinds the iterator to the end of the container.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 */
extern void
kit_XorList_Iterator_rewindToEnd(struct kit_XorList_Iterator *self)
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
kit_XorList_Iterator_next(struct kit_XorList_Iterator *self)
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
kit_XorList_Iterator_previous(struct kit_XorList_Iterator *self)
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
kit_XorList_Iterator_setLast(struct kit_XorList_Iterator *self, void *element)
__attribute__((__warn_unused_result__, __nonnull__(1)));

/**
 * Tests the associated container for modifications.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 * @return true if the container has been modified else false.
 */
extern bool
kit_XorList_Iterator_isModified(const struct kit_XorList_Iterator *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Deletes this instance of kit_XorList_Iterator.
 * If self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_XorList_Iterator_delete(struct kit_XorList_Iterator *self);

#ifdef __cplusplus
}
#endif

#endif /* KIT_XOR_LIST_INCLUDED */
