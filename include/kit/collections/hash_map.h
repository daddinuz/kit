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
#include <kit/compiler_steroids.h>
#include <kit/collections/result.h>

/**
 * kit_HashMap interface.
 */
struct kit_HashMap;

/**
 *
 * @param capacityHint
 * @param compareFn
 * @param hashFn
 * @return
 */
extern MutableOptional(struct kit_HashMap *)
kit_HashMap_new(size_t capacityHint, int compareFn(const void *x, const void *y), size_t hashFn(const void *key))
__attribute__((__nonnull__));

/**
 *
 * @param self
 */
extern void
kit_HashMap_delete(struct kit_HashMap *self);

/**
 *
 * @param self
 * @param key
 * @param value
 * @return
 */
extern enum kit_Result
kit_HashMap_put(struct kit_HashMap *self, const void *key, void *value)
__attribute__((__nonnull__(1, 2)));

/**
 *
 * @param self
 * @param key
 * @param out
 * @return
 */
extern enum kit_Result
kit_HashMap_get(struct kit_HashMap *self, const void *key, void **out)
__attribute__((__nonnull__));

/**
 *
 * @param self
 * @param key
 * @return
 */
extern bool
kit_HashMap_has(struct kit_HashMap *self, const void *key)
__attribute__((__nonnull__));

/**
 *
 * @param self
 * @param key
 * @param out
 * @return
 */
extern enum kit_Result
kit_HashMap_pop(struct kit_HashMap *self, const void *key, void **out)
__attribute__((__nonnull__));

/**
 *
 * @param self
 */
extern void
kit_HashMap_clear(struct kit_HashMap *self)
__attribute__((__nonnull__));

/**
 *
 * @param self
 * @return
 */
extern size_t
kit_HashMap_size(struct kit_HashMap *self)
__attribute__((__nonnull__));

/**
 *
 * @param self
 * @return
 */
extern bool
kit_HashMap_isEmpty(struct kit_HashMap *self)
__attribute__((__nonnull__));

/*
 * 
 */

struct kit_HashMap_Iterator;

extern MutableOptional(struct kit_HashMap_Iterator *)
kit_HashMap_Iterator_new(struct kit_HashMap *container)
__attribute__((__nonnull__));

extern void
kit_HashMap_Iterator_delete(struct kit_HashMap_Iterator *self);

extern void
kit_HashMap_Iterator_rewind(struct kit_HashMap_Iterator *self)
__attribute__((__nonnull__));

extern enum kit_Result
kit_HashMap_Iterator_next(struct kit_HashMap_Iterator *self, const void **keyOut, void **valueOut)
__attribute__((__nonnull__));

extern enum kit_Result
kit_HashMap_Iterator_setLast(struct kit_HashMap_Iterator *self, void *value)
__attribute__((__nonnull__(1)));

extern bool
kit_HashMap_Iterator_isModified(struct kit_HashMap_Iterator *self)
__attribute__((__nonnull__));

#ifdef __cplusplus
}
#endif

#endif /* KIT_HASH_MAP_INCLUDED */
