/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   December 06, 2017 
 */

#ifndef KIT_STRING_INCLUDED
#define KIT_STRING_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include <option/option.h>
#include <kit/compiler_steroids.h>

typedef const char *kit_String;

extern ImmutableOptional(kit_String)
kit_String_new(size_t capacityHint);

extern ImmutableOptional(kit_String)
kit_String_format(const char *format, ...)
__attribute__((__nonnull__, __format__(printf, 1, 2)));

extern ImmutableOptional(kit_String)
kit_String_fromPack(const char *format, va_list pack)
__attribute__((__nonnull__));

extern ImmutableOptional(kit_String)
kit_String_fromLiteral(const char *literal)
__attribute__((__nonnull__));

extern ImmutableOptional(kit_String)
kit_String_fromBytes(const void *bytes, size_t size)
__attribute__((__nonnull__));

extern ImmutableOptional(kit_String)
kit_String_duplicate(kit_String s)
__attribute__((__nonnull__));

// takes ownership
extern ImmutableOptional(kit_String)
kit_String_append(kit_String *ref, kit_String other)
__attribute__((__nonnull__));

// takes ownership
extern ImmutableOptional(kit_String)
kit_String_appendLiteral(kit_String *ref, const char *literal)
__attribute__((__nonnull__));

// takes ownership
extern ImmutableOptional(kit_String)
kit_String_appendBytes(kit_String *ref, const void *bytes, size_t size)
__attribute__((__nonnull__));

// takes ownership
extern ImmutableOptional(kit_String)
kit_String_reserve(kit_String *ref, size_t capacity)
__attribute__((__nonnull__));

// takes ownership
extern ImmutableOptional(kit_String)
kit_String_shrink(kit_String *ref)
__attribute__((__nonnull__));

extern size_t
kit_String_size(kit_String self)
__attribute__((__nonnull__));

extern size_t
kit_String_capacity(kit_String self)
__attribute__((__nonnull__));

extern bool
kit_String_isEqual(kit_String self, kit_String other)
__attribute__((__nonnull__));

extern bool
kit_String_isEmpty(kit_String self)
__attribute__((__nonnull__));

extern void
kit_String_clear(kit_String self)
__attribute__((__nonnull__));

extern void
kit_String_delete(kit_String self);

#ifdef __cplusplus
}
#endif

#endif /* KIT_STRING_INCLUDED */
