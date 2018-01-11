/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 21, 2017 
 */

/*
 * Pairs couple together a key with a paired value.
 * The key of a pair must not be NULL.
 */

#ifndef KIT_PAIR_INCLUDED
#define KIT_PAIR_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <option/option.h>
#include <kit/compiler_steroids.h>

struct kit_Pair {
    const void *key;
    void *value;
};

/**
 * Makes and initializes a kit_Pair struct.
 *
 * @param key The key element [<b>must not be NULL</b>].
 * @param value The value element.
 * @return An initialized kit_Pair struct.
 */
extern struct kit_Pair
kit_Pair_make(const void *key, void *value)
__attribute__((__nonnull__(1)));

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
