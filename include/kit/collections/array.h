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

#ifndef KIT_ARRAY_INCLUDED
#define KIT_ARRAY_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include <option/option.h>
#include <kit/utils.h>
#include <kit/errors.h>
#include <kit/compiler_steroids.h>

/**
 * Arrays are fixed-size sequence containers: they hold a specific number of elements ordered in a strict linear sequence.
 * It is as efficient in terms of storage size as an ordinary array declared with the language's bracket syntax ([]).
 * This container merely adds a layer of member and global functions to it, so that arrays can be used as other containers.
 * Unlike the other containers, arrays have a fixed size therefore, they cannot be expanded or contracted dynamically
 * Zero-sized arrays are valid, but they should not be accessed.
 */
struct kit_Array;

/**
 * Creates a new instance of kit_Array with a specified capacity.
 *
 * @param capacity The capacity of the container.
 * @return A new instance of kit_Array of None.
 */
extern OptionOf(struct kit_Array *)
kit_Array_new(size_t capacity)
__attribute__((__warn_unused_result__));

/**
 * Creates a new instance of kit_Array from a fixed sequence of elements.
 *
 * @attention
 *  This function should never be used directly since it iterates elements until Ellipsis is found, so that the last 
 *  element in the sequence must be Ellipsis; is an unchecked runtime error pass a sequence of arguments that 
 *  does not contain Ellipsis as its last value.
 *
 * @param e0 The first element.
 * @param ... Other elements.
 * @return A new instance of kit_Array of None.
 */
extern OptionOf(struct kit_Array *)
__kit_Array_from(void *e0, ...)
__attribute__((__warn_unused_result__));

/**
 * @see __kit_Array_from(void *e0, ...)
 */
#define kit_Array_from(...) \
    __kit_Array_from(__VA_ARGS__, Ellipsis)

/**
 * Creates a new instance of kit_Array from arguments pack.
 *
 * @attention
 *  This function iterates arguments pack until Ellipsis is found, so the last element in the sequence must be Ellipsis.
 *  Is an unchecked runtime error to pass a pack which does not contain Ellipsis as its last value.
 *
 * @param pack The arguments pack [<b>must not be NULL</b>].
 * @return A new instance of kit_Array of None.
 */
extern OptionOf(struct kit_Array *)
kit_Array_fromPack(va_list pack)
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
kit_Array_put(struct kit_Array *self, size_t index, void *element)
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
kit_Array_get(const struct kit_Array *self, size_t index)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns the element stored at the back of this container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return
 * - Ok => Wraps the specified element.
 * - OutOfRangeError => No such element, nothing has been done.
 */
extern ResultOf(void *, OutOfRangeError)
kit_Array_back(const struct kit_Array *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns the element stored at the front of this container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return
 * - Ok => Wraps the specified element.
 * - OutOfRangeError => No such element, nothing has been done.
 */
extern ResultOf(void *, OutOfRangeError)
kit_Array_front(const struct kit_Array *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Removes all elements from the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 */
extern void
kit_Array_clear(struct kit_Array *self)
__attribute__((__nonnull__));

/**
 * Returns the number of elements the container can store without expanding.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return The numbers of elements that can be stored before expansion.
 */
extern size_t
kit_Array_capacity(const struct kit_Array *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns the raw data of the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return The low level array of elements.
 */
extern void **
kit_Array_raw(const struct kit_Array *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Deletes this instance of kit_Array.
 * If self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_Array_delete(struct kit_Array *self);

#ifdef __cplusplus
}
#endif

#endif /* KIT_ARRAY_INCLUDED */
