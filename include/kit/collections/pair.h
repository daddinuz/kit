/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 21, 2017 
 */

#ifndef KIT_PAIR_INCLUDED
#define KIT_PAIR_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <option/option.h>
#include <kit/compiler_steroids.h>

/**
 * kit_Pair interface.
 */
extern struct kit_Pair;

/**
 * Creates a new instance of kit_Pair.
 * In case of out of memory this function returns Option_None.
 *
 * @param first The first element.
 * @param second The second element.
 * @return A new instance of kit_Pair or Option_None.
 */
extern Optional(struct kit_Pair *)
kit_Pair_new(void *first, void *second);

/**
 * Deletes an instance of kit_Pair.
 * If @param self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_Pair_delete(struct kit_Pair *self);

/**
 * Gets the first element of the container.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The container instance.
 * @return The first element of the pair.
 */
extern void *
kit_Pair_first(struct kit_Pair *self) __attribute__((__nonnull__));

/**
 * Gets the second element of the container.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The container instance.
 * @return The second element of the pair.
 */
extern void *
kit_Pair_second(struct kit_Pair *self) __attribute__((__nonnull__));

#ifdef __cplusplus
}
#endif

#endif /* KIT_PAIR_INCLUDED */
