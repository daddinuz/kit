/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 22, 2017 
 */

// TODO

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
extern struct kit_Map;

// TODO remove
extern Optional(struct kit_Map *)
kit_Map_new(size_t capacityHint, int compareFn(const void *x, const void *y), size_t hashFn(const void *key));

extern void
kit_Map_clear(struct kit_Map *self) __attribute__((__nonnull__));

extern enum kit_Result
kit_Map_put(struct kit_Map *self, const void *key, void *value) __attribute__((__nonnull__(1, 2)));

extern enum kit_Result
kit_Map_get(struct kit_Map *self, const void *key, void **out) __attribute__((__nonnull__));

extern enum kit_Result
kit_Map_pop(struct kit_Map *self, const void *key, void **out) __attribute__((__nonnull__));

extern size_t
kit_Map_size(struct kit_Map *self) __attribute__((__nonnull__));

extern bool
kit_Map_isEmpty(struct kit_Map *self) __attribute__((__nonnull__));

extern size_t
kit_Map_capacity(struct kit_Map *self) __attribute__((__nonnull__));

extern enum kit_Result
kit_Map_reserve(struct kit_Map *self, size_t size) __attribute__((__nonnull__));

extern enum kit_Result
kit_Map_shrink(struct kit_Map *self) __attribute__((__nonnull__));

extern void
kit_Map_delete(struct kit_Map *self);

#ifdef __cplusplus
}
#endif

#endif /* KIT_MAP_INCLUDED */
