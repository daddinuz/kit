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
#include <kit/compiler_steroids.h>
#include <kit/collections/result.h>

/**
 * kit_Array interface.
 */
struct kit_Array;

/**
 * Creates a new instance of kit_Array.
 * In case of out of memory this function returns MutableOption_None.
 *
 * @param capacity The capacity of the array.
 * @return A new instance of kit_Array or MutableOption_None.
 */
extern MutableOptional(struct kit_Array *)
kit_Array_new(size_t capacity);

/**
 * Creates a new instance of kit_Array from a fixed sequence of elements.
 * In case of out of memory this function returns MutableOption_None.
 *
 * WARNING:
 *  This function iterates elements until Ellipsis is hit, so last value in @param pack must be Ellipsis.
 *  Is an unchecked runtime error to pass a @param pack which does not contain Ellipsis as its last value.
 *
 * @param e0 The first element.
 * @param ... Other elements.
 * @return A new instance of kit_Array or MutableOption_None.
 */
extern MutableOptional(struct kit_Array *)
__kit_Array_from(void *e0, ...);

#define kit_Array_from(...) __kit_Array_from(__VA_ARGS__, Ellipsis)

/**
 * Creates a new instance of kit_Array from arguments pack.
 * In case of out of memory this function returns MutableOption_None.
 *
 * WARNING:
 *  This function iterates the argument pack until Ellipsis is hit, so last value in @param pack must be Ellipsis.
 *  Is an unchecked runtime error to pass a @param pack which does not contain Ellipsis as its last value.
 *
 * Checked runtime errors:
 *      - @param pack must not be NULL.
 *
 * @param pack The arguments pack.
 * @return A new instance of kit_Array or MutableOption_None.
 */
extern MutableOptional(struct kit_Array *)
kit_Array_fromPack(va_list pack);

/**
 * Deletes an instance of kit_Array.
 * If @param self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_Array_delete(struct kit_Array *self);

/**
 * Sets all elements of the array to NULL (will not modify the size of the array).
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The container instance.
 */
extern void
kit_Array_clear(struct kit_Array *self)
__attribute__((__nonnull__));

/**
 * Replaces the element at the given index.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The container instance.
 * @param e The new element.
 * @param index The index of the element to be replaced.
 * @return
 *      - KIT_RESULT_OK            :   The operation was performed successfully.
 *      - KIT_RESULT_OUT_OF_RANGE  :   The given index is out of range, nothing has been done.
 */
extern enum kit_Result
kit_Array_set(struct kit_Array *self, void *e, size_t index)
__attribute__((__nonnull__(1)));

/**
 * Gets the element stored at the given index.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *      - @param out must not be NULL.
 *
 * @param self The container instance.
 * @param out The element requested.
 * @param index The index of the element requested.
 * @return
 *      - KIT_RESULT_OK            :   The operation was performed successfully.
 *      - KIT_RESULT_OUT_OF_RANGE  :   The given index is out of range, nothing has been done.
 */
extern enum kit_Result
kit_Array_get(struct kit_Array *self, void **out, size_t index)
__attribute__((__nonnull__));

/**
 * Gets the element stored at the back of the container.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *      - @param out must not be NULL.
 *
 * @param self The container instance.
 * @param out The element requested.
 * @return
 *      - KIT_RESULT_OK            :   The operation was performed successfully.
 *      - KIT_RESULT_OUT_OF_RANGE  :   No such element in the container, nothing has been done.
 */
extern enum kit_Result
kit_Array_back(struct kit_Array *self, void **out)
__attribute__((__nonnull__));

/**
 * Gets the element stored at the front of the container.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *      - @param out must not be NULL.
 *
 * @param self The container instance.
 * @param out The element requested.
 * @return
 *      - KIT_RESULT_OK            :   The operation was performed successfully.
 *      - KIT_RESULT_OUT_OF_RANGE  :   No such element in the container, nothing has been done.
 */
extern enum kit_Result
kit_Array_front(struct kit_Array *self, void **out)
__attribute__((__nonnull__));

/**
 * Gets the number of elements currently stored in the container.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The container instance.
 * @return The numbers of elements in the container.
 */
extern size_t
kit_Array_capacity(struct kit_Array *self)
__attribute__((__nonnull__));

/**
 * [Unsafe method]
 * Gets the raw data of the container.
 * Any direct modification of the raw data may break the container.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The container instance.
 * @return The low level array of elements.
 */
extern void **
kit_Array_raw(struct kit_Array *self)
__attribute__((__nonnull__));

#ifdef __cplusplus
}
#endif

#endif /* KIT_ARRAY_INCLUDED */
