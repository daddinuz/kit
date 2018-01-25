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

#ifndef KIT_STACK_INCLUDED
#define KIT_STACK_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdbool.h>
#include <option/option.h>
#include <kit/errors.h>
#include <kit/compiler_steroids.h>

/**
 * Stacks are a type of container adaptor, specifically designed to operate in a LIFO context (last-in first-out),
 * where elements are inserted and extracted only from one end of the container.
 */
struct kit_Stack;

/**
 * Creates a new instance of kit_Stack using DoublyList as underlying container.
 * In case of out of memory this function returns None.
 *
 * @return A new instance of kit_Stack or None.
 */
extern OptionOf(struct kit_Stack *)
kit_Stack_fromDoublyList(void)
__attribute__((__warn_unused_result__));

/**
 * Creates a new instance of kit_Stack using SinglyList as underlying container.
 * In case of out of memory this function returns None.
 *
 * @return A new instance of kit_Stack or None.
 */
extern OptionOf(struct kit_Stack *)
kit_Stack_fromSinglyList(void)
__attribute__((__warn_unused_result__));

/**
 * Creates a new instance of kit_Stack using XorList as underlying container.
 * In case of out of memory this function returns None.
 *
 * @return A new instance of kit_Stack or None.
 */
extern OptionOf(struct kit_Stack *)
kit_Stack_fromXorList(void)
__attribute__((__warn_unused_result__));

/**
 * Creates a new instance of kit_Stack using Vector as underlying container.
 * In case of out of memory this function returns None.
 *
 * If capacity is 0 then a default capacity will be used.
 *
 * @param capacity An hint about the average capacity.
 * @return A new instance of kit_Stack or None.
 */
extern OptionOf(struct kit_Stack *)
kit_Stack_fromVector(size_t capacity)
__attribute__((__warn_unused_result__));

/**
 * Inserts the specified element at the back of the container.
 *
 * @param self The the container instance [<b>must not be NULL</b>].
 * @param element The element to be inserted.
 * @return
 * - Ok => The operation was performed successfully.
 * - OutOfMemoryError => There's no more space left, nothing has been done.
 */
extern OneOf(Ok, OutOfMemoryError)
kit_Stack_push(struct kit_Stack *self, void *element)
__attribute__((__warn_unused_result__, __nonnull__(1)));

/**
 * Removes the element at the back of the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return
 * - Ok => Wraps the removed element.
 * - OutOfRangeError => No such element, nothing has been done.
 */
extern ResultOf(void *, OutOfRangeError)
kit_Stack_pop(struct kit_Stack *self)
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
kit_Stack_back(const struct kit_Stack *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns the number of elements currently stored in the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return The numbers of elements in the container.
 */
extern size_t
kit_Stack_size(const struct kit_Stack *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Tests if this container has no elements.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return true if the container is empty false otherwise.
 */
extern bool
kit_Stack_isEmpty(const struct kit_Stack *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Deletes this instance of kit_Stack.
 * If self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_Stack_delete(struct kit_Stack *self);

#ifdef __cplusplus
}
#endif

#endif /* KIT_STACK_INCLUDED */
