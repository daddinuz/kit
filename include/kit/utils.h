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

#ifndef KIT_UTILS_INCLUDED
#define KIT_UTILS_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stddef.h>
#include <kit/compiler_steroids.h>

/**
 * @return The string representation of a boolean value.
 */
#define kit_truth(x) \
    (((x)) ? "true" : "false")

/**
 * Ellipsis is used when a sentinel value is needed.
 * An example of usage is in variadic functions to detect end of inputs:
 *
 * @code
 * container_load(container, "a", "b", "c", Ellipsis);
 * @endcode
 */
extern const void *const Ellipsis;

/**
 * Count items in arguments pack.
 * This function expects that pack should have been initialized by va_start at some point before the call,
 * and it is expected to be released by va_end at some point after the call.
 * Internally, the function retrieves arguments from pack, and thus the state of pack is altered by the call.
 *
 * @attention:
 *  This function iterates the argument pack until Ellipsis is hit, so last value in pack must be Ellipsis.
 *  Is an unchecked runtime error to pass a pack which does not contain Ellipsis as its last value.
 *
 * @param pack The arguments pack <b>must not be NULL</b>.
 * @return The size of the arguments pack.
 */
extern size_t
kit_packSize(va_list pack)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Swaps content of arguments.
 *
 * @param a First parameter <b>must not be NULL</b>.
 * @param b Second parameter <b>must not be NULL</b>.
 */
extern void
kit_swap(void **a, void **b)
__attribute__((__nonnull__));

/**
 * Moves ownership invalidating ref.
 *
 * @param ref The reference to the pointer to be moved <b>must not be NULL</b>.
 * @return Moved data.
 */
extern void *
kit_move(void **ref)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * This function should be treated as an helper when initializing collections that needs a comparator function.
 * Internally this function performs a raw pointers comparison so should be used only to compare atom instances.
 * 
 * @param a The first value <b>must not be NULL</b>.
 * @param b The second value <b>must not be NULL</b>.
 * @return -1 if a > b; 0 if a == 0; 1 if b > a;
 */
extern int
kit_compareFn(const void *a, const void *b)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * This function should be treated as an helper when initializing collections that needs a hash function.
 * Internally this function convert the raw pointer address to a number so should be used only to with atom instances.
 *      
 * @param key The key to be hashed <b>must not be NULL</b>.
 * @return The hash of the key.
 */
extern size_t
kit_hashFn(const void *key)
__attribute__((__warn_unused_result__, __nonnull__));

#ifdef __cplusplus
}
#endif

#endif /* KIT_UTILS_INCLUDED */
