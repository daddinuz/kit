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
#include <kit/collections/string_config.h>

typedef const char *kit_String;

/**
 * Creates a new instance of kit_String with 0 size.
 * In case of OOM this function returns ImmutableOption_None.
 *
 * @param capacityHint A hint to determine the initial capacity of the string.
 * @return A new instance of kit_String or ImmutableOption_None.
 */
extern ImmutableOptional(kit_String)
kit_String_new(size_t capacityHint);

/**
 * Creates a new quoted instance of kit_String starting from bytes.
 * In case of OOM this function returns ImmutableOption_None.
 * The following quoting rules are applied:
 *      - '\"'                    -> "\\\""
 *      - '\\'                    -> "\\\\"
 *      - '\a'                    -> "\\a"
 *      - '\b'                    -> "\\b"
 *      - '\n'                    -> "\\n"
 *      - '\r'                    -> "\\r"
 *      - '\t'                    -> "\\t"
 *      - any printable character -> unchanged
 *      - others                  -> "\\x<ascii-code>" eg: '\0' -> "\\x00"
 *
 * Checked runtime errors:
 *      - @param bytes must not be NULL.
 *
 * @param bytes Bytes string is composed by.
 * @param size Size of bytes.
 * @return A new instance of kit_String or ImmutableOption_None.
 */
extern ImmutableOptional(kit_String)
kit_String_quoted(const void *bytes, size_t size)
__attribute__((__nonnull__));

extern ImmutableOptional(kit_String)
kit_String_fromPack(const char *format, va_list pack)
__attribute__((__nonnull__, __format__(__printf__, 1, 0)));

extern ImmutableOptional(kit_String)
kit_String_fromBytes(const void *bytes, size_t size)
__attribute__((__nonnull__));

extern ImmutableOptional(kit_String)
kit_String_fromFormat(const char *format, ...)
__attribute__((__nonnull__, __format__(printf, 1, 2)));

extern ImmutableOptional(kit_String)
kit_String_fromLiteral(const char *literal)
__attribute__((__nonnull__));

extern ImmutableOptional(kit_String)
kit_String_duplicate(kit_String s)
__attribute__((__nonnull__));

// takes ownership
extern ImmutableOptional(kit_String)
kit_String_clear(kit_String *ref)
__attribute__((__nonnull__));

// takes ownership
extern ImmutableOptional(kit_String)
kit_String_append(kit_String *ref, kit_String other)
__attribute__((__nonnull__));

// takes ownership
extern ImmutableOptional(kit_String)
kit_String_appendPack(kit_String *ref, const char *format, va_list pack)
__attribute__((__nonnull__, __format__(printf, 2, 0)));

// takes ownership
extern ImmutableOptional(kit_String)
kit_String_appendBytes(kit_String *ref, const void *bytes, size_t size)
__attribute__((__nonnull__));

// takes ownership
extern ImmutableOptional(kit_String)
kit_String_appendFormat(kit_String *ref, const char *format, ...)
__attribute__((__nonnull__, __format__(printf, 2, 3)));

// takes ownership
extern ImmutableOptional(kit_String)
kit_String_appendLiteral(kit_String *ref, const char *literal)
__attribute__((__nonnull__));

// takes ownership
extern ImmutableOptional(kit_String)
kit_String_set(kit_String *ref, kit_String other)
__attribute__((__nonnull__));

// takes ownership
extern ImmutableOptional(kit_String)
kit_String_setPack(kit_String *ref, const char *format, va_list pack)
__attribute__((__nonnull__, __format__(printf, 2, 0)));

// takes ownership
extern ImmutableOptional(kit_String)
kit_String_setBytes(kit_String *ref, const void *bytes, size_t size)
__attribute__((__nonnull__));

// takes ownership
extern ImmutableOptional(kit_String)
kit_String_setFormat(kit_String *ref, const char *format, ...)
__attribute__((__nonnull__, __format__(printf, 2, 3)));

// takes ownership
extern ImmutableOptional(kit_String)
kit_String_setLiteral(kit_String *ref, const char *literal)
__attribute__((__nonnull__));

// takes ownership
extern ImmutableOptional(kit_String)
kit_String_quote(kit_String *ref)
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
kit_String_delete(kit_String self);

#ifdef __cplusplus
}
#endif

#endif /* KIT_STRING_INCLUDED */
