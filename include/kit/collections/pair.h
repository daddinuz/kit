/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   January 16, 2018
 */

#ifndef KIT_PAIR_INCLUDED
#define KIT_PAIR_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <option/option.h>
#include <kit/compiler_steroids.h>

/**
 * Pairs couple together a key with a paired value.
 * The key of a pair must not be NULL.
 */
struct kit_Pair;

/**
 * Creates a new instance of kit_Pair.
 * In case of out of memory this function returns None.
 *
 * @param key The key element [<b>must not be NULL</b>].
 * @param value The value element.
 * @return A new instance of kit_Pair or None.
 */
extern OptionOf(struct kit_Pair *)
kit_Pair_new(const void *key, void *value)
__attribute__((__warn_unused_result__, __nonnull__(1)));

/**
 * Gets the key element of the pair.
 *
 * @param self The kit_Pair instance [<b>mut not be NULL</b>].
 * @return The key element.
 */
extern const void *
kit_Pair_getKey(struct kit_Pair *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Gets the value element of the pair.
 *
 * @param self The kit_Pair instance [<b>mut not be NULL</b>].
 * @return The value element.
 */
extern void *
kit_Pair_getValue(struct kit_Pair *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Sets the key element of the pair.
 *
 * @param self The kit_Pair instance [<b>mut not be NULL</b>].
 * @param key The key element [<b>must not be NULL</b>].
 */
extern void
kit_Pair_setKey(struct kit_Pair *self, const void *key)
__attribute__((__nonnull__));

/**
 * Sets the value element of the pair.
 *
 * @param self The kit_Pair instance [<b>mut not be NULL</b>].
 * @param value The value element.
 */
extern void
kit_Pair_setValue(struct kit_Pair *self, void *value)
__attribute__((__nonnull__(1)));

/**
 * Deletes an instance of kit_Pair.
 * If self is NULL no action will be performed.
 *
 * @param self The kit_Pair instance to be deleted.
 */
extern void
kit_Pair_delete(struct kit_Pair *self);

#ifdef __cplusplus
}
#endif

#endif /* KIT_PAIR_INCLUDED */
