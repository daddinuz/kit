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
#include <kit/collections/result.h>

/**
 * kit_Map interface.
 */
struct kit_Map;

/**
 *
 * @param capacityHint
 * @param compareFn
 * @param hashFn
 * @return
 */
extern MutableOptional(struct kit_Map *)
kit_Map_fromHashMap(size_t capacityHint, int compareFn(const void *x, const void *y), size_t hashFn(const void *key))
__attribute__((__nonnull__));

/**
 *
 * @param self
 */
extern void
kit_Map_delete(struct kit_Map *self);

/**
 *
 * @param self
 * @param key
 * @param value
 * @return
 */
extern enum kit_Result
kit_Map_put(struct kit_Map *self, const void *key, void *value)
__attribute__((__nonnull__(1, 2)));

/**
 *
 * @param self
 * @param key
 * @param out
 * @return
 */
extern enum kit_Result
kit_Map_get(struct kit_Map *self, const void *key, void **out)
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
kit_Map_pop(struct kit_Map *self, const void *key, void **out)
__attribute__((__nonnull__));

/**
 *
 * @param self
 */
extern void
kit_Map_clear(struct kit_Map *self)
__attribute__((__nonnull__));

/**
 *
 * @param self
 * @return
 */
extern size_t
kit_Map_size(struct kit_Map *self)
__attribute__((__nonnull__));

/**
 *
 * @param self
 * @return
 */
extern bool
kit_Map_isEmpty(struct kit_Map *self)
__attribute__((__nonnull__));

#ifdef __cplusplus
}
#endif

#endif /* KIT_MAP_INCLUDED */
