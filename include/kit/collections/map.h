/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 22, 2017 
 */

/*
 * 
 */

#ifndef KIT_MAP_INCLUDED
#define KIT_MAP_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdbool.h>
#include <option/option.h>
#include <kit/compiler_steroids.h>
#include <kit/collections/pair.h>
#include <kit/collections/result.h>

/**
 * kit_Map interface.
 */
struct kit_Map;

/**
 * Creates a new instance of kit_Map using HashMap as underlying container.
 * In case of out of memory this function returns MutableOption_None.
 *
 * Checked runtime errors:
 *      - @param compareFn must not be NULL.
 *      - @param hashFn must not be NULL.
 *
 * @param capacityHint The maximum expected capacity for this map.
 * @param compareFn The function used to compare keys.
 * @param hashFn The function used to hash keys.
 * @return A new instance of kit_Map or MutableOption_None.
 */
extern MutableOptional(struct kit_Map *)
kit_Map_fromHashMap(size_t capacityHint, int compareFn(const void *x, const void *y), size_t hashFn(const void *key))
__attribute__((__nonnull__));

/**
 * Deletes an instance of kit_Map.
 * If @param self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_Map_delete(struct kit_Map *self);

/**
 * Adds a pair to the map.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *      - @param pair.key must not be NULL.
 *
 * @param self The container instance.
 * @param pair The pair to be added.
 * @return
 *      - KIT_RESULT_OK            :   The operation was performed successfully.
 *      - KIT_RESULT_OUT_OF_MEMORY :   There's no more space left, nothing has been done.
 */
extern enum kit_Result
kit_Map_add(struct kit_Map *self, struct kit_Pair pair)
__attribute__((__nonnull__));

/**
 * Puts a couple to the map.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *      - @param key must not be NULL.
 *
 * @param self The container instance.
 * @param key The key to be added.
 * @param value The value for the given key.
 * @return
 *      - KIT_RESULT_OK            :   The operation was performed successfully.
 *      - KIT_RESULT_OUT_OF_MEMORY :   There's no more space left, nothing has been done.
 */
extern enum kit_Result
kit_Map_put(struct kit_Map *self, const void *key, void *value)
__attribute__((__nonnull__(1, 2)));

/**
 * Gets the value at the given key.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *      - @param key must not be NULL.
 *      - @param out must not be NULL.
 *
 * @param self The container instance.
 * @param key The key to look for.
 * @param out The requested element.
 * @return
 *      - KIT_RESULT_OK            :   The operation was performed successfully.
 *      - KIT_RESULT_OUT_OF_RANGE  :   No such element in the container, nothing has been done.
 */
extern enum kit_Result
kit_Map_get(struct kit_Map *self, const void *key, struct kit_Pair *out)
__attribute__((__nonnull__));

/**
 *
 * @param self
 * @param key
 * @return
 */
extern bool
kit_Map_has(struct kit_Map *self, const void *key)
__attribute__((__nonnull__));

/**
 *
 * @param self
 * @param key
 * @param out
 * @return
 */
extern enum kit_Result
kit_Map_pop(struct kit_Map *self, const void *key, struct kit_Pair *out)
__attribute__((__nonnull__));

/**
 *
 * @param self
 */
extern void
kit_Map_clear(struct kit_Map *self)
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
kit_Map_size(struct kit_Map *self)
__attribute__((__nonnull__));

/**
 * Checks if the container is empty.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The container instance.
 * @return true if the container is empty false otherwise.
 */
extern bool
kit_Map_isEmpty(struct kit_Map *self)
__attribute__((__nonnull__));

/**
 * kit_Map_Iterator interface.
 */
struct kit_Map_Iterator;

/**
 *
 * @param container
 * @return
 */
extern MutableOptional(struct kit_Map_Iterator *)
kit_Map_Iterator_new(struct kit_Map *container)
__attribute__((__nonnull__));

/**
 *
 * @param self
 */
extern void
kit_Map_Iterator_delete(struct kit_Map_Iterator *self);

/**
 *
 * @param self
 */
extern void
kit_Map_Iterator_rewind(struct kit_Map_Iterator *self)
__attribute__((__nonnull__));

/**
 *
 * @param self
 * @param out
 * @return
 */
extern enum kit_Result
kit_Map_Iterator_next(struct kit_Map_Iterator *self, struct kit_Pair *out)
__attribute__((__nonnull__));

/**
 *
 * @param self
 * @param value
 * @return
 */
extern enum kit_Result
kit_Map_Iterator_setLast(struct kit_Map_Iterator *self, void *value)
__attribute__((__nonnull__(1)));

/**
 *
 * @param self
 * @return
 */
extern bool
kit_Map_Iterator_isModified(struct kit_Map_Iterator *self)
__attribute__((__nonnull__));

#ifdef __cplusplus
}
#endif

#endif /* KIT_MAP_INCLUDED */
