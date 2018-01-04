/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   December 06, 2017 
 */

/*
 * kit_String are highly inspired by antirez's sds string library.
 * kit_String must be changed only using functions within this interface.
 * kit_String are binary safe and grows automatically.
 * kit_String are compatible with standard C string functions that accesses strings in a read only way.
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
 * If capacityHint is 0 then a default capacity will be used.
 *
 * @param capacityHint An hint about the average capacity.
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

/**
 * Creates a new instance of kit_String using printf-like format as seed, behaves like kit_String_fromFormat but takes a va_list.
 * In case of OOM this function returns ImmutableOption_None.
 *
 * Checked runtime errors:
 *      - @param format must not be NULL
 *
 * @param format The printf-like format string.
 * @param pack The args for @param format
 * @return A new instance of kit_String or ImmutableOption_None.
 */
extern ImmutableOptional(kit_String)
kit_String_fromPack(const char *format, va_list pack)
__attribute__((__nonnull__(1), __format__(__printf__, 1, 0)));

/**
 * Creates a new instance of kit_String using @param bytes as seed.
 * In case of OOM this function returns ImmutableOption_None.
 *
 * Checked runtime errors:
 *      - @param bytes must not be NULL
 *
 * @param bytes The bytes used as seed to construct the string.
 * @param size The length of @param bytes.
 * @return A new instance of kit_String or ImmutableOption_None.
 */
extern ImmutableOptional(kit_String)
kit_String_fromBytes(const void *bytes, size_t size)
__attribute__((__nonnull__));

/**
 * Creates a new instance of kit_String using printf-like format as seed.
 * In case of OOM this function returns ImmutableOption_None.
 *
 * Checked runtime errors:
 *      - @param format must not be NULL
 *
 * @param format The printf-like format string.
 * @param ... The args for @param format
 * @return A new instance of kit_String or ImmutableOption_None.
 */
extern ImmutableOptional(kit_String)
kit_String_fromFormat(const char *format, ...)
__attribute__((__nonnull__(1), __format__(printf, 1, 2)));

/**
 * Creates a new instance of kit_String using @param literal as seed.
 * In case of OOM this function returns ImmutableOption_None.
 *
 * Checked runtime errors:
 *      - @param literal must not be NULL
 *
 * @param literal The string literal used as seed to construct the string.
 * @return A new instance of kit_String or ImmutableOption_None.
 */
extern ImmutableOptional(kit_String)
kit_String_fromLiteral(const char *literal)
__attribute__((__nonnull__));

/**
 * Duplicates a string instance.
 * In case of OOM this function returns ImmutableOption_None.
 *
 * Checked runtime errors:
 *      - @param s must not be NULL and must be a valid string instance.
 *
 * @param s The string instance to be duplicated.
 * @return A new instance of kit_String or ImmutableOption_None.
 */
extern ImmutableOptional(kit_String)
kit_String_duplicate(kit_String s)
__attribute__((__nonnull__));

/**
 * Appends content to string.
 * In case of OOM this function returns ImmutableOption_None.
 *
 * Note: Takes ownership invalidating @param *ref in case of success.
 *
 * Checked runtime errors:
 *      - @param ref must not be NULL and *ref must be a valid string instance.
 *      - @param other must not be NULL and must be a valid string instance.
 *      - the strings must not overlap
 *
 * @param ref The reference to the string instance to be modified.
 * @param other The string to be appended.
 * @return The modified string instance (invalidating *ref) in case of success or ImmutableOption_None (leaving *ref untouched).
 */
extern ImmutableOptional(kit_String)
kit_String_append(kit_String *ref, kit_String other)
__attribute__((__nonnull__));

/**
 * Appends content to string using printf-like format, behaves like kit_String_appendFormat but takes a va_list.
 * In case of OOM this function returns ImmutableOption_None.
 *
 * Note: Takes ownership invalidating @param *ref in case of success.
 *
 * Checked runtime errors:
 *      - @param ref must not be NULL and *ref must be a valid string instance.
 *      - @param format must not be NULL.
 *
 * @param ref The reference to the string instance to be modified.
 * @param format The printf-like format string.
 * @param pack The args for @param format
 * @return The modified string instance (invalidating *ref) in case of success or ImmutableOption_None (leaving *ref untouched).
 */
extern ImmutableOptional(kit_String)
kit_String_appendPack(kit_String *ref, const char *format, va_list pack)
__attribute__((__nonnull__, __format__(printf, 2, 0)));

/**
 * Appends bytes to string.
 * In case of OOM this function returns ImmutableOption_None.
 *
 * Note: Takes ownership invalidating @param *ref in case of success.
 *
 * Checked runtime errors:
 *      - @param ref must not be NULL and *ref must be a valid string instance.
 *      - @param bytes must not be NULL.
 *      - the strings must not overlap
 *
 * @param ref The reference to the string instance to be modified.
 * @param bytes The bytes used as seed to construct the string.
 * @param size The length of @param bytes.
 * @return The modified string instance (invalidating *ref) in case of success or ImmutableOption_None (leaving *ref untouched).
 */
extern ImmutableOptional(kit_String)
kit_String_appendBytes(kit_String *ref, const void *bytes, size_t size)
__attribute__((__nonnull__));

/**
 * Appends content to string using printf-like format.
 * In case of OOM this function returns ImmutableOption_None.
 *
 * Note: Takes ownership invalidating @param *ref in case of success.
 *
 * Checked runtime errors:
 *      - @param ref must not be NULL and *ref must be a valid string instance.
 *      - @param format must not be NULL.
 *
 * @param ref The reference to the string instance to be modified.
 * @param format The printf-like format string.
 * @param ... The args for @param format
 * @return The modified string instance (invalidating *ref) in case of success or ImmutableOption_None (leaving *ref untouched).
 */
extern ImmutableOptional(kit_String)
kit_String_appendFormat(kit_String *ref, const char *format, ...)
__attribute__((__nonnull__, __format__(printf, 2, 3)));

/**
 * Appends literal to string.
 * In case of OOM this function returns ImmutableOption_None.
 *
 * Note: Takes ownership invalidating @param *ref in case of success.
 *
 * Checked runtime errors:
 *      - @param ref must not be NULL and *ref must be a valid string instance.
 *      - @param literal must not be NULL.
 *      - the strings must not overlap
 *
 * @param ref The reference to the string instance to be modified.
 * @param literal The string literal to be appended.
 * @return The modified string instance (invalidating *ref) in case of success or ImmutableOption_None (leaving *ref untouched).
 */
extern ImmutableOptional(kit_String)
kit_String_appendLiteral(kit_String *ref, const char *literal)
__attribute__((__nonnull__));

/**
 * Sets the content of string.
 * In case of OOM this function returns ImmutableOption_None.
 *
 * Note: Takes ownership invalidating @param *ref in case of success.
 *
 * Checked runtime errors:
 *      - @param ref must not be NULL and *ref must be a valid string instance.
 *      - @param other must not be NULL and must be a valid string instance.
 *      - the strings must not overlap
 *
 * @param ref The reference to the string instance to be modified.
 * @param other The string to be appended.
 * @return The modified string instance (invalidating *ref) in case of success or ImmutableOption_None (leaving *ref untouched).
 */
extern ImmutableOptional(kit_String)
kit_String_set(kit_String *ref, kit_String other)
__attribute__((__nonnull__));

/**
 * Sets content of string using printf-like format, behaves like kit_String_setFormat but takes a va_list.
 * In case of OOM this function returns ImmutableOption_None.
 *
 * Note: Takes ownership invalidating @param *ref in case of success.
 *
 * Checked runtime errors:
 *      - @param ref must not be NULL and *ref must be a valid string instance.
 *      - @param format must not be NULL.
 *
 * @param ref The reference to the string instance to be modified.
 * @param format The printf-like format string.
 * @param pack The args for @param format
 * @return The modified string instance (invalidating *ref) in case of success or ImmutableOption_None (leaving *ref untouched).
 */
extern ImmutableOptional(kit_String)
kit_String_setPack(kit_String *ref, const char *format, va_list pack)
__attribute__((__nonnull__, __format__(printf, 2, 0)));

/**
 * Sets bytes of string.
 * In case of OOM this function returns ImmutableOption_None.
 *
 * Note: Takes ownership invalidating @param *ref in case of success.
 *
 * Checked runtime errors:
 *      - @param ref must not be NULL and *ref must be a valid string instance.
 *      - @param bytes must not be NULL.
 *      - the strings must not overlap
 *
 * @param ref The reference to the string instance to be modified.
 * @param bytes The bytes used as seed to construct the string.
 * @param size The length of @param bytes.
 * @return The modified string instance (invalidating *ref) in case of success or ImmutableOption_None (leaving *ref untouched).
 */
extern ImmutableOptional(kit_String)
kit_String_setBytes(kit_String *ref, const void *bytes, size_t size)
__attribute__((__nonnull__));

/**
 * Sets content of string using printf-like format.
 * In case of OOM this function returns ImmutableOption_None.
 *
 * Note: Takes ownership invalidating @param *ref in case of success.
 *
 * Checked runtime errors:
 *      - @param ref must not be NULL and *ref must be a valid string instance.
 *      - @param format must not be NULL.
 *
 * @param ref The reference to the string instance to be modified.
 * @param format The printf-like format string.
 * @param ... The args for @param format
 * @return The modified string instance (invalidating *ref) in case of success or ImmutableOption_None (leaving *ref untouched).
 */
extern ImmutableOptional(kit_String)
kit_String_setFormat(kit_String *ref, const char *format, ...)
__attribute__((__nonnull__, __format__(printf, 2, 3)));

/**
 * Sets content of string.
 * In case of OOM this function returns ImmutableOption_None.
 *
 * Note: Takes ownership invalidating @param *ref in case of success.
 *
 * Checked runtime errors:
 *      - @param ref must not be NULL and *ref must be a valid string instance.
 *      - @param literal must not be NULL.
 *      - the strings must not overlap
 *
 * @param ref The reference to the string instance to be modified.
 * @param literal The string literal to be appended.
 * @return The modified string instance (invalidating *ref) in case of success or ImmutableOption_None (leaving *ref untouched).
 */
extern ImmutableOptional(kit_String)
kit_String_setLiteral(kit_String *ref, const char *literal)
__attribute__((__nonnull__));

/**
 * Modifies string quoting is content.
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
 * Note: Takes ownership invalidating @param *ref in case of success.
 *
 * Checked runtime errors:
 *      - @param ref must not be NULL and *ref must be a valid string instance.
 *
 * @param ref The reference to the string instance to be modified.
 * @return The modified string instance (invalidating *ref) in case of success or ImmutableOption_None (leaving *ref untouched).
 */
extern ImmutableOptional(kit_String)
kit_String_quote(kit_String *ref)
__attribute__((__nonnull__));

/**
 * Clears the string resetting its size to 0.
 * This function will not modify the capacity of the string.
 *
 * Note: Takes ownership invalidating @param *ref in case of success.
 *
 * Checked runtime errors:
 *      - @param ref must not be NULL and *ref must be a valid string instance.
 *
 * @param ref The reference to the string instance to be modified.
 * @return The modified string instance (invalidating *ref) in case of success or ImmutableOption_None (leaving *ref untouched).
 */
extern ImmutableOptional(kit_String)
kit_String_clear(kit_String *ref)
__attribute__((__nonnull__));

/**
 * Explicitly request an expansion to hold at least as many elements as @param capacity.
 * If requested capacity is less than current capacity nothing will be done.
 *
 * Note: Takes ownership invalidating @param *ref in case of success.
 *
 * Checked runtime errors:
 *      - @param ref must not be NULL and *ref must be a valid string instance.
 *
 * @param ref The reference to the string instance to be modified.
 * @param capacity The minimum capacity to hold.
 * @return The modified string instance (invalidating *ref) in case of success or ImmutableOption_None (leaving *ref untouched).
 */
extern ImmutableOptional(kit_String)
kit_String_reserve(kit_String *ref, size_t capacity)
__attribute__((__nonnull__));

/**
 * Requests the container to shrink in order to fit at least the stored elements freeing resources not used.
 * The request may be ignored by the container if the current size is less than the default capacity.
 *
 * Note: Takes ownership invalidating @param *ref in case of success.
 *
 * Checked runtime errors:
 *      - @param ref must not be NULL and *ref must be a valid string instance.
 *
 * @param ref The reference to the string instance to be modified.
 * @return The modified string instance (invalidating *ref) in case of success or ImmutableOption_None (leaving *ref untouched).
 */
extern ImmutableOptional(kit_String)
kit_String_shrink(kit_String *ref)
__attribute__((__nonnull__));

/**
 * Gets the size of the string.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The container instance.
 * @return The size of the string.
 */
extern size_t
kit_String_size(kit_String self)
__attribute__((__nonnull__));

/**
 * Gets the capacity of the string before expansion.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The container instance.
 * @return The capacity of the string.
 */
extern size_t
kit_String_capacity(kit_String self)
__attribute__((__nonnull__));

/**
 * Checks if the string is equal to the another.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *      - @param other must not be NULL.
 *
 * @param self The string instance.
 * @param other The other string instance.
 * @return true if the strings are equal false otherwise.
 */
extern bool
kit_String_isEqual(kit_String self, kit_String other)
__attribute__((__nonnull__));

/**
 * Checks if the string is empty.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The string instance.
 * @return true if the string is empty false otherwise.
 */
extern bool
kit_String_isEmpty(kit_String self)
__attribute__((__nonnull__));

/**
 * Deletes an instance of kit_String.
 * If @param self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_String_delete(kit_String self);

#ifdef __cplusplus
}
#endif

#endif /* KIT_STRING_INCLUDED */
