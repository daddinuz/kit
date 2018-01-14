/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   December 01, 2017 
 */

#ifndef KIT_HASH_MAP_INCLUDED
#define KIT_HASH_MAP_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdbool.h>
#include <option/option.h>
#include <kit/errors.h>
#include <kit/compiler_steroids.h>
#include <kit/collections/pair.h>

struct kit_HashMap;

/**
 * Creates a new instance of kit_HashMap.
 * In case of out of memory this function returns None.
 *
 * If capacityHint is 0 then a default capacity will be used.
 *
 * @param capacityHint The maximum expected capacity for this map.
 * @param compareFn The function used to compare keys [<b>must not be NULL</b>].
 * @param hashFn The function used to hash keys [<b>must not be NULL</b>].
 * @return A new instance of kit_HashMap or None.
 */
extern OptionOf(struct kit_HashMap *)
kit_HashMap_new(size_t capacityHint, int compareFn(const void *x, const void *y), size_t hashFn(const void *key))
__attribute__((__nonnull__));

/**
 * Deletes an instance of kit_HashMap.
 * If self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_HashMap_delete(struct kit_HashMap *self);

/**
 * Adds a pair to the map.
 * The operation performed is actually an insert or update.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @param pair The pair to be added [<b>pair must not be NULL</b>].
 * @return
 * - Ok => wraps the previous value at the given key if present else NULL.
 * - OutOfMemoryError => There's no more space left, nothing has been done.
 */
extern ResultOf(void *, OutOfMemoryError)
kit_HashMap_add(struct kit_HashMap *self, struct kit_Pair *pair)
__attribute__((__nonnull__));

/**
 * Puts a couple of values to the map.
 * The operation performed is actually an insert or update.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @param key The key to be added [<b>must not be NULL</b>].
 * @param value The value for the given key.
 * @return
 * - Ok => wraps the previous value at the given key if present else NULL.
 * - OutOfMemoryError => There's no more space left, nothing has been done.
 */
extern ResultOf(void *, OutOfMemoryError)
kit_HashMap_put(struct kit_HashMap *self, const void *key, void *value)
__attribute__((__nonnull__(1, 2)));

/**
 * Gets the value at the given key.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @param key The key to look for [<b>must not be NULL</b>].
 * @return
 * - Ok => wraps the value at the given key.
 * - OutOfRangeError => No such key, nothing has been done.
 */
extern ResultOf(void *, OutOfRangeError)
kit_HashMap_get(struct kit_HashMap *self, const void *key)
__attribute__((__nonnull__));

/**
 * Checks if a key is present in the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @param key The key to look for [<b>must not be NULL</b>].
 * @return true if the key is present else false
 */
extern bool
kit_HashMap_has(struct kit_HashMap *self, const void *key)
__attribute__((__nonnull__));

/**
 * Removes an element from the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @param key The key to be removed [<b>must not be NULL</b>].
 * @return
 * - Ok => wraps the value at the given key.
 * - OutOfRangeError => No such key, nothing has been done.
 */
extern ResultOf(void *, OutOfRangeError)
kit_HashMap_pop(struct kit_HashMap *self, const void *key)
__attribute__((__nonnull__));

/**
 * Removes all elements from the container, leaving it with a size of 0.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 */
extern void
kit_HashMap_clear(struct kit_HashMap *self)
__attribute__((__nonnull__));

/**
 * Gets the number of elements currently stored in the container.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return The numbers of elements in the container.
 */
extern size_t
kit_HashMap_size(struct kit_HashMap *self)
__attribute__((__nonnull__));

/**
 * Checks if the container is empty.
 *
 * @param self The container instance [<b>must not be NULL</b>].
 * @return true if the container is empty false otherwise.
 */
extern bool
kit_HashMap_isEmpty(struct kit_HashMap *self)
__attribute__((__nonnull__));

struct kit_HashMap_Iterator;

/**
 * Creates a new instance of kit_HashMap_Iterator.
 * In case of out of memory this function returns None.
 *
 * @param container The instance of the container to iterate [<b>must not be NULL</b>].
 * @return A new instance of kit_HashMap_Iterator or None.
 */
extern OptionOf(struct kit_HashMap_Iterator *)
kit_HashMap_Iterator_new(struct kit_HashMap *container)
__attribute__((__nonnull__));

/**
 * Deletes an instance of kit_HashMap_Iterator.
 * If self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_HashMap_Iterator_delete(struct kit_HashMap_Iterator *self);

/**
 * Rewinds the iterator.
 *
 * @param self The instance of the iterator to be rewound [<b>must not be NULL</b>].
 */
extern void
kit_HashMap_Iterator_rewind(struct kit_HashMap_Iterator *self)
__attribute__((__nonnull__));

/**
 * Gets the next pair in the map.
 *
 * Note: Takes ownership invalidating *ref in case of success.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 * @param ref The reference to the pair in which the result will be store [<b>must not be NULL</b>].
 * @return
 * - Ok => wraps the pair at the given key (same of out parameter).
 * - OutOfRangeError => The iterator hit the end of the container, nothing has been done.
 * - ConcurrentModificationError => The container has been modified, nothing has been done.
 */
extern ResultOf(struct kit_Pair *, OutOfRangeError, ConcurrentModificationError)
kit_HashMap_Iterator_next(struct kit_HashMap_Iterator *self, struct kit_Pair **ref)
__attribute__((__nonnull__));

/**
 * Updates the value of the last retrieved pair.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 * @param value The new value.
 * @return
 * - Ok => wraps the previous value of the last key.
 * - IllegalStateError => Neither next() or previous() has been called, nothing has been done.
 * - ConcurrentModificationError => The container has been modified, nothing has been done.
 */
extern ResultOf(void *, IllegalStateError, ConcurrentModificationError)
kit_HashMap_Iterator_setLast(struct kit_HashMap_Iterator *self, void *value)
__attribute__((__nonnull__(1)));

/**
 * Checks for associated container modifications.
 *
 * @param self The iterator instance [<b>must not be NULL</b>].
 * @return true if the container has been modified else false
 */
extern bool
kit_HashMap_Iterator_isModified(struct kit_HashMap_Iterator *self)
__attribute__((__nonnull__));

#ifdef __cplusplus
}
#endif

#endif /* KIT_HASH_MAP_INCLUDED */
