/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 21, 2017 
 */

/*
 * Arrays are fixed-size sequence containers: they hold a specific number of elements ordered in a strict linear sequence.
 * It is as efficient in terms of storage size as an ordinary array declared with the language's bracket syntax ([]).
 * This container merely adds a layer of member and global functions to it, so that arrays can be used as other containers.
 *
 * Unlike the other containers, arrays have a fixed size therefore, they cannot be expanded or contracted dynamically
 * Zero-sized arrays are valid, but they should not be dereferenced.
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

struct kit_Array;

/**
 * Creates a new instance of kit_Array.
 * In case of out of memory this function returns None.
 *
 * @param capacity The capacity of the array.
 * @return A new instance of kit_Array or None.
 */
extern OptionOf(struct kit_Array *)
kit_Array_new(size_t capacity);

/**
 * Creates a new instance of kit_Array from a fixed sequence of elements.
 * In case of out of memory this function returns None.
 *
 * This function should never be used directly, used the exported macro instead.
 *
 * @attention
 *  This function iterates elements until Ellipsis is found, so the last element in the sequence must be Ellipsis.
 *  Is an unchecked runtime error to pass a pack which does not contain Ellipsis as its last value.
 *
 * @param e0 The first element.
 * @param ... Other elements.
 * @return A new instance of kit_Array or None.
 */
extern OptionOf(struct kit_Array *)
__kit_Array_from(void *e0, ...);

/**
 * @see __kit_Array_from(void *e0, ...)
 */
#define kit_Array_from(...) \
    __kit_Array_from(__VA_ARGS__, Ellipsis)

/**
 * Creates a new instance of kit_Array from arguments pack.
 * In case of out of memory this function returns None.
 *
 * @attention
 *  This function iterates elements until Ellipsis is found, so the last element in the sequence must be Ellipsis.
 *  Is an unchecked runtime error to pass a pack which does not contain Ellipsis as its last value.
 *
 * @param pack The arguments pack [<b>must not be NULL</b>].
 * @return A new instance of kit_Array or None.
 */
extern OptionOf(struct kit_Array *)
kit_Array_fromPack(va_list pack)
__attribute__((__nonnull__));

/**
 * Deletes an instance of kit_Array.
 * If self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_Array_delete(struct kit_Array *self);

/**
 * Sets all elements of the array to NULL.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 */
extern void
kit_Array_clear(struct kit_Array *self)
__attribute__((__nonnull__));

/**
 * Replaces the element at the given index with a new element.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @param element The new element.
 * @param index The index of the element to be replaced.
 * @return
 * - Ok => wraps the previous element at the given index.
 * - OutOfRangeError => The given index is out of range, nothing has been done.
 */
extern ResultOf(void *, OutOfRangeError)
kit_Array_set(struct kit_Array *self, void *element, size_t index)
__attribute__((__nonnull__(1)));

/**
 * Gets the element at the given index.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @param index The index of the element requested.
 * @return
 * - Ok => wraps the element at the given index.
 * - OutOfRangeError => The given index is out of range, nothing has been done.
 */
extern ResultOf(void *, OutOfRangeError)
kit_Array_get(struct kit_Array *self, size_t index)
__attribute__((__nonnull__));

/**
 * Gets the element at the back of the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return
 * - Ok => wraps the element at back of the container.
 * - OutOfRangeError => No such element, nothing has been done.
 */
extern ResultOf(void *, OutOfRangeError)
kit_Array_back(struct kit_Array *self)
__attribute__((__nonnull__));

/**
 * Gets the element at the front of the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return
 * - Ok => wraps the element at front of the container.
 * - OutOfRangeError => No such element, nothing has been done.
 */
extern ResultOf(void *, OutOfRangeError)
kit_Array_front(struct kit_Array *self)
__attribute__((__nonnull__));

/**
 * Gets the number of elements that can be stored in the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return The capacity of the container.
 */
extern size_t
kit_Array_capacity(struct kit_Array *self)
__attribute__((__nonnull__));

/**
 * Gets the raw data of the container.
 *
 * @attention
 *  Any direct modification of the raw data may break the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return The low level array of elements.
 */
extern void **
kit_Array_raw(struct kit_Array *self)
__attribute__((__nonnull__));

#ifdef __cplusplus
}
#endif

#endif /* KIT_ARRAY_INCLUDED */
