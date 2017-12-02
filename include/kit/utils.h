/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 21, 2017 
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
#define kit_truth(x)    (((x)) ? "true" : "false")

/**
 * Ellipsis is used when a sentinel value is needed.
 * An example of usage is in variadic functions to detect end of inputs:
 * ```
 *      container_load(container, "a", "b", "c", Ellipsis);
 * ```
 */
extern const void *const Ellipsis;

/**
 * Count items in arguments pack.
 * This function expects that @param pack should have been initialized by va_start at some point before the call,
 * and it is expected to be released by va_end at some point after the call.
 * Internally, the function retrieves arguments from @param pack, and thus the state of @param pack is altered by the call.
 *
 * WARNING:
 *  This function iterates the argument pack until Ellipsis is hit, so last value in @param pack must be Ellipsis.
 *  Is an unchecked runtime error to pass a @param pack which does not contain Ellipsis as its last value.
 *
 * Checked runtime errors:
 *      - @param pack must not be NULL.
 *
 * @param pack The arguments pack.
 * @return The size of the arguments pack.
 */
extern size_t
kit_packSize(va_list pack);

/**
 * Swaps content of @param a and @param b
 *
 * Checked runtime errors:
 *      - @param a must not be NULL.
 *      - @param b must not be NULL.
 *
 * @param a First parameter.
 * @param b Second parameter.
 */
extern void
kit_swap(void **a, void **b)
__attribute__((__nonnull__));

/**
 * Destructs data at (*ref) and assigns NULL invalidating the pointer.
 * Usually used as a safer alternative to free.
 *
 * e.g.
 * ```
 *      data_t *someData = data_new(...);
 *      kit_invalidate(&someData, data_delete);
 * ```
 *
 * Checked runtime errors:
 *      - @param ref must not be NULL.
 *      - @param destructor must not be NULL.
 *
 * @param ref The reference to the pointer to be destructed.
 * @param destructor The destructor function to invoke.
 */
extern void
kit_invalidate(void **ref, void (*destructor)())
__attribute__((__nonnull__));

/**
 * This function should be treated as an helper when initializing collections that needs a comparator function.
 * Internally this function performs a raw pointers comparison so should be used only to compare atom instances.  
 * 
 * Checked runtime errors:
 *      - @param a must not be NULL.
 *      - @param b must not be NULL.
 * 
 * @param a The first value.
 * @param b The second value.
 * @return -1 if a > b; 0 if a == 0; 1 if b > a;
 */
extern int
kit_compareFn(const void *a, const void *b);

/**
 * This function should be treated as an helper when initializing collections that needs a hash function.
 * Internally this function convert the raw pointer address to a number so should be used only to with atom instances.  
 * 
 * Checked runtime errors:
 *      - @param key must not be NULL.
 *      
 * @param key The key to be hashed.
 * @return The hash of the key.
 */
extern size_t
kit_hashFn(const void *key);

#ifdef __cplusplus
}
#endif

#endif /* KIT_UTILS_INCLUDED */
