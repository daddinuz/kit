/*
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 *
 * Copyright (c) 2018 Davide Di Carlo
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
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
#include <kit/errors.h>
#include <kit/compiler_steroids.h>
#include <kit/collections/string_config.h>

/**
 * kit_String are highly inspired by antirez's sds string library.
 * kit_String must be changed only using functions within this interface.
 * kit_String are binary safe and grows automatically.
 * kit_String are compatible with standard C string functions that accesses strings in a read only way.
 */
typedef const char *kit_String;

/**
 * TODO docs
 * TODO test
 */
extern OptionOf(kit_String)
kit_String_new(void)
__attribute__((__warn_unused_result__));

/**
 * Creates a new instance of kit_String with 0 size.
 * In case of OOM this function returns None.
 *
 * If capacity is 0 then a default capacity will be used.
 *
 * @param capacity An hint about the average capacity.
 * @return A new instance of kit_String or None.
 */
extern OptionOf(kit_String)
kit_String_withCapacity(size_t capacity)
__attribute__((__warn_unused_result__));

/**
 * Creates a new JSON compliant quoted instance of kit_String starting from bytes.
 * In case of OOM this function returns None.
 *
 * @param bytes The sequence of bytes [<b>must not be NULL</b>].
 * @param size The size of bytes.
 * @return A new instance of kit_String or None.
 */
extern OptionOf(kit_String)
kit_String_quoted(const void *bytes, size_t size)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Creates a new instance of kit_String using printf-like format as seed, behaves like kit_String_fromFormat but takes a va_list.
 * In case of OOM this function returns None.
 *
 * @param format The printf-like format string [<b>must not be NULL</b>].
 * @param pack The args for format.
 * @return A new instance of kit_String or None.
 */
extern OptionOf(kit_String)
kit_String_fromPack(const char *format, va_list pack)
__attribute__((__warn_unused_result__, __nonnull__, __format__(__printf__, 1, 0)));

/**
 * Creates a new instance of kit_String using bytes as seed.
 * In case of OOM this function returns None.
 *
 * @param bytes The sequence of bytes [<b>must not be NULL</b>].
 * @param size The size of bytes.
 * @return A new instance of kit_String or None.
 */
extern OptionOf(kit_String)
kit_String_fromBytes(const void *bytes, size_t size)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Creates a new instance of kit_String using printf-like format as seed.
 * In case of OOM this function returns None.
 *
 * @param format The printf-like format string [<b>must not be NULL</b>].
 * @param ... The args for format.
 * @return A new instance of kit_String or None.
 */
extern OptionOf(kit_String)
kit_String_fromFormat(const char *format, ...)
__attribute__((__warn_unused_result__, __nonnull__(1), __format__(printf, 1, 2)));

/**
 * Creates a new instance of kit_String using literal as seed.
 * In case of OOM this function returns None.
 *
 * @param literal The string literal used as seed to construct the string [<b>must not be NULL</b>].
 * @return A new instance of kit_String or None.
 */
extern OptionOf(kit_String)
kit_String_fromLiteral(const char *literal)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Duplicates a string instance.
 * In case of OOM this function returns None.
 *
 * @attention
 *  This function requires a kit_String instance (not just any string!).
 *
 * @param s The string instance to be duplicated [<b>must not be NULL</b>].
 * @return A new instance of kit_String or None.
 */
extern OptionOf(kit_String)
kit_String_duplicate(kit_String s)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * TODO docs
 * TODO test
 */
extern ResultOf(kit_String, OutOfRangeError, OutOfMemoryError)
kit_String_insert(kit_String *ref, size_t index, kit_String other)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * TODO docs
 * TODO test
 */
extern ResultOf(kit_String, OutOfRangeError, OutOfMemoryError)
kit_String_insertPack(kit_String *ref, size_t index, const char *format, va_list pack)
__attribute__((__warn_unused_result__, __nonnull__, __format__(printf, 3, 0)));

/**
 * TODO docs
 * TODO test
 */
extern ResultOf(kit_String, OutOfRangeError, OutOfMemoryError)
kit_String_insertBytes(kit_String *ref, size_t index, const void *bytes, size_t size)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * TODO docs
 * TODO test
 */
extern ResultOf(kit_String, OutOfRangeError, OutOfMemoryError)
kit_String_insertFormat(kit_String *ref, size_t index, const char *format, ...)
__attribute__((__warn_unused_result__, __nonnull__, __format__(printf, 3, 4)));

/**
 * TODO docs
 * TODO test
 */
extern ResultOf(kit_String, OutOfRangeError, OutOfMemoryError)
kit_String_insertLiteral(kit_String *ref, size_t index, const char *literal)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Appends content to string.
 * In case of OOM this function returns None.
 *
 * Note: Takes ownership invalidating *ref in case of success.
 *
 * @attention
 *  This function requires *ref to be a kit_String instance (not just any string!).
 *  This function requires other to be a kit_String instance (not just any string!).
 *  This function requires that the strings must not overlap.
 *
 * @param ref The reference to the string instance to be modified [<b>must not be NULL</b>].
 * @param other The string to be appended [<b>must not be NULL</b>].
 * @return The modified string instance (invalidating *ref) in case of success or None (leaving *ref untouched).
 */
extern OptionOf(kit_String)
kit_String_append(kit_String *ref, kit_String other)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Appends content to string using printf-like format, behaves like kit_String_appendFormat but takes a va_list.
 * In case of OOM this function returns None.
 *
 * Note: Takes ownership invalidating *ref in case of success.
 *
 * @attention
 *  This function requires *ref to be a kit_String instance (not just any string!).
 *
 * @param ref The reference to the string instance to be modified [<b>must not be NULL</b>].
 * @param format The printf-like format string [<b>must not be NULL</b>].
 * @param pack The args for format [<b>must not be NULL</b>].
 * @return The modified string instance (invalidating *ref) in case of success or None (leaving *ref untouched).
 */
extern OptionOf(kit_String)
kit_String_appendPack(kit_String *ref, const char *format, va_list pack)
__attribute__((__warn_unused_result__, __nonnull__, __format__(printf, 2, 0)));

/**
 * Appends bytes to string.
 * In case of OOM this function returns None.
 *
 * Note: Takes ownership invalidating *ref in case of success.
 *
 * @attention
 *  This function requires *ref to be a kit_String instance (not just any string!).
 *  This function requires that the string and bytes must not overlap.
 *
 * @param ref The reference to the string instance to be modified [<b>must not be NULL</b>].
 * @param bytes The bytes used as seed to construct the string [<b>must not be NULL</b>].
 * @param size The size of bytes.
 * @return The modified string instance (invalidating *ref) in case of success or None (leaving *ref untouched).
 */
extern OptionOf(kit_String)
kit_String_appendBytes(kit_String *ref, const void *bytes, size_t size)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Appends content to string using printf-like format.
 * In case of OOM this function returns None.
 *
 * Note: Takes ownership invalidating *ref in case of success.
 *
 * @attention
 *  This function requires *ref to be a kit_String instance (not just any string!).
 *
 * @param ref The reference to the string instance to be modified [<b>must not be NULL</b>].
 * @param format The printf-like format string [<b>must not be NULL</b>].
 * @param ... The args for format
 * @return The modified string instance (invalidating *ref) in case of success or None (leaving *ref untouched).
 */
extern OptionOf(kit_String)
kit_String_appendFormat(kit_String *ref, const char *format, ...)
__attribute__((__warn_unused_result__, __nonnull__, __format__(printf, 2, 3)));

/**
 * Appends literal to string.
 * In case of OOM this function returns None.
 *
 * Note: Takes ownership invalidating *ref in case of success.
 *
 * @attention
 *  This function requires *ref to be a kit_String instance (not just any string!).
 *  This function requires that the strings must not overlap.
 *
 * @param ref The reference to the string instance to be modified [<b>must not be NULL</b>].
 * @param literal The string literal to be appended [<b>must not be NULL</b>].
 * @return The modified string instance (invalidating *ref) in case of success or None (leaving *ref untouched).
 */
extern OptionOf(kit_String)
kit_String_appendLiteral(kit_String *ref, const char *literal)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * TODO test
 *
 * Prepends content to string.
 * In case of OOM this function returns None.
 *
 * Note: Takes ownership invalidating *ref in case of success.
 *
 * @attention
 *  This function requires *ref to be a kit_String instance (not just any string!).
 *  This function requires other to be a kit_String instance (not just any string!).
 *  This function requires that the strings must not overlap.
 *
 * @param ref The reference to the string instance to be modified [<b>must not be NULL</b>].
 * @param other The string to be prepended [<b>must not be NULL</b>].
 * @return The modified string instance (invalidating *ref) in case of success or None (leaving *ref untouched).
 */
extern OptionOf(kit_String)
kit_String_prepend(kit_String *ref, kit_String other)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * TODO test
 *
 * Prepends content to string using printf-like format, behaves like kit_String_prependFormat but takes a va_list.
 * In case of OOM this function returns None.
 *
 * Note: Takes ownership invalidating *ref in case of success.
 *
 * @attention
 *  This function requires *ref to be a kit_String instance (not just any string!).
 *
 * @param ref The reference to the string instance to be modified [<b>must not be NULL</b>].
 * @param format The printf-like format string [<b>must not be NULL</b>].
 * @param pack The args for format [<b>must not be NULL</b>].
 * @return The modified string instance (invalidating *ref) in case of success or None (leaving *ref untouched).
 */
extern OptionOf(kit_String)
kit_String_prependPack(kit_String *ref, const char *format, va_list pack)
__attribute__((__warn_unused_result__, __nonnull__, __format__(printf, 2, 0)));

/**
 * TODO test
 *
 * Prepends bytes to string.
 * In case of OOM this function returns None.
 *
 * Note: Takes ownership invalidating *ref in case of success.
 *
 * @attention
 *  This function requires *ref to be a kit_String instance (not just any string!).
 *  This function requires that the string and bytes must not overlap.
 *
 * @param ref The reference to the string instance to be modified [<b>must not be NULL</b>].
 * @param bytes The bytes used as seed to construct the string [<b>must not be NULL</b>].
 * @param size The size of bytes.
 * @return The modified string instance (invalidating *ref) in case of success or None (leaving *ref untouched).
 */
extern OptionOf(kit_String)
kit_String_prependBytes(kit_String *ref, const void *bytes, size_t size)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * TODO test
 *
 * Prepends content to string using printf-like format.
 * In case of OOM this function returns None.
 *
 * Note: Takes ownership invalidating *ref in case of success.
 *
 * @attention
 *  This function requires *ref to be a kit_String instance (not just any string!).
 *
 * @param ref The reference to the string instance to be modified [<b>must not be NULL</b>].
 * @param format The printf-like format string [<b>must not be NULL</b>].
 * @param ... The args for format
 * @return The modified string instance (invalidating *ref) in case of success or None (leaving *ref untouched).
 */
extern OptionOf(kit_String)
kit_String_prependFormat(kit_String *ref, const char *format, ...)
__attribute__((__warn_unused_result__, __nonnull__, __format__(printf, 2, 3)));

/**
 * TODO test
 *
 * Prepends literal to string.
 * In case of OOM this function returns None.
 *
 * Note: Takes ownership invalidating *ref in case of success.
 *
 * @attention
 *  This function requires *ref to be a kit_String instance (not just any string!).
 *  This function requires that the strings must not overlap.
 *
 * @param ref The reference to the string instance to be modified [<b>must not be NULL</b>].
 * @param literal The string literal to be prepended [<b>must not be NULL</b>].
 * @return The modified string instance (invalidating *ref) in case of success or None (leaving *ref untouched).
 */
extern OptionOf(kit_String)
kit_String_prependLiteral(kit_String *ref, const char *literal)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Sets the content of string.
 * In case of OOM this function returns None.
 *
 * Note: Takes ownership invalidating *ref in case of success.
 *
 * @attention
 *  This function requires *ref to be a kit_String instance (not just any string!).
 *  This function requires other to be a kit_String instance (not just any string!).
 *  This function requires that the strings must not overlap.
 *
 * @param ref The reference to the string instance to be modified [<b>must not be NULL</b>].
 * @param other The string to be appended [<b>must not be NULL</b>].
 * @return The modified string instance (invalidating *ref) in case of success or None (leaving *ref untouched).
 */
extern OptionOf(kit_String)
kit_String_set(kit_String *ref, kit_String other)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Sets content of string using printf-like format, behaves like kit_String_setFormat but takes a va_list.
 * In case of OOM this function returns None.
 *
 * Note: Takes ownership invalidating *ref in case of success.
 *
  * @attention
 *  This function requires *ref to be a kit_String instance (not just any string!).
 *
 * @param ref The reference to the string instance to be modified [<b>must not be NULL</b>].
 * @param format The printf-like format string [<b>must not be NULL</b>].
 * @param pack The args for format.
 * @return The modified string instance (invalidating *ref) in case of success or None (leaving *ref untouched).
 */
extern OptionOf(kit_String)
kit_String_setPack(kit_String *ref, const char *format, va_list pack)
__attribute__((__warn_unused_result__, __nonnull__, __format__(printf, 2, 0)));

/**
 * Sets bytes of string.
 * In case of OOM this function returns None.
 *
 * Note: Takes ownership invalidating *ref in case of success.
 *
 * @attention
 *  This function requires *ref to be a kit_String instance (not just any string!).
 *  This function requires that the string and bytes must not overlap.
 *
 * @param ref The reference to the string instance to be modified [<b>must not be NULL</b>].
 * @param bytes The bytes used as seed to construct the string [<b>must not be NULL</b>].
 * @param size The size of bytes.
 * @return The modified string instance (invalidating *ref) in case of success or None (leaving *ref untouched).
 */
extern OptionOf(kit_String)
kit_String_setBytes(kit_String *ref, const void *bytes, size_t size)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Sets content of string using printf-like format.
 * In case of OOM this function returns None.
 *
 * Note: Takes ownership invalidating *ref in case of success.
 *
 * @attention
 *  This function requires *ref to be a kit_String instance (not just any string!).
 *
 * @param ref The reference to the string instance to be modified [<b>must not be NULL</b>].
 * @param format The printf-like format string [<b>must not be NULL</b>].
 * @param ... The args for format.
 * @return The modified string instance (invalidating *ref) in case of success or None (leaving *ref untouched).
 */
extern OptionOf(kit_String)
kit_String_setFormat(kit_String *ref, const char *format, ...)
__attribute__((__warn_unused_result__, __nonnull__, __format__(printf, 2, 3)));

/**
 * Sets content of string.
 * In case of OOM this function returns None.
 *
 * Note: Takes ownership invalidating *ref in case of success.
 *
 * @attention
 *  This function requires *ref to be a kit_String instance (not just any string!).
 *  This function requires that the strings must not overlap.
 *
 * @param ref The reference to the string instance to be modified [<b>must not be NULL</b>].
 * @param literal The string literal to be appended [<b>must not be NULL</b>].
 * @return The modified string instance (invalidating *ref) in case of success or None (leaving *ref untouched).
 */
extern OptionOf(kit_String)
kit_String_setLiteral(kit_String *ref, const char *literal)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * TODO docs
 * TODO test
 */
extern ResultOf(kit_String, OutOfRangeError)
kit_String_erase(kit_String *ref, size_t index, size_t count)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * TODO docs
 * TODO test
 */
extern ResultOf(kit_String, OutOfRangeError, IllegalArgumentsError)
kit_String_eraseSlice(kit_String *ref, size_t start, size_t end)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * TODO docs
 * TODO test
 */
extern kit_String
kit_String_removeFirstMatchingBytes(kit_String *ref, const void *bytes, size_t size)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * TODO docs
 * TODO test
 */
extern kit_String
kit_String_removeFirstMatchingLiteral(kit_String *ref, const char *literal)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * TODO docs
 * TODO test
 */
extern kit_String
kit_String_removeLastMatchingBytes(kit_String *ref, const void *bytes, size_t size)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * TODO docs
 * TODO test
 */
extern kit_String
kit_String_removeLastMatchingLiteral(kit_String *ref, const char *literal)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * TODO docs
 * TODO test
 */
extern kit_String
kit_String_removeAllMatchingBytes(kit_String *ref, const void *bytes, size_t size)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * TODO docs
 * TODO test
 */
extern kit_String
kit_String_removeAllMatchingLiteral(kit_String *ref, const char *literal)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * TODO docs
 * TODO test
 */
extern kit_String
kit_String_trimLeft(kit_String *ref)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * TODO docs
 * TODO test
 */
extern kit_String
kit_String_trimRight(kit_String *ref)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * TODO docs
 * TODO test
 */
extern kit_String
kit_String_trim(kit_String *ref)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * TODO docs
 * TODO test
 */
extern kit_String
kit_String_trimLeftIf(kit_String *ref, bool ifFn(const char c))
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * TODO docs
 * TODO test
 */
extern kit_String
kit_String_trimRightIf(kit_String *ref, bool ifFn(const char c))
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * TODO docs
 * TODO test
 */
extern kit_String
kit_String_trimIf(kit_String *ref, bool ifFn(const char c))
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Modifies string quoting (JSON compliant) is content.
 * In case of OOM this function returns None.
 *
 * Note: Takes ownership invalidating *ref in case of success.
 *
 * @attention
 *  This function requires *ref to be a kit_String instance (not just any string!).
 *
 * @param ref The reference to the string instance to be modified [<b>must not be NULL</b>].
 * @return The modified string instance (invalidating *ref) in case of success or None (leaving *ref untouched).
 */
extern OptionOf(kit_String)
kit_String_quote(kit_String *ref)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Clears the string resetting its size to 0.
 * This function will not modify the capacity of the string.
 *
 * Note: Takes ownership invalidating *ref in case of success.
 *
 * @attention
 *  This function requires *ref to be a kit_String instance (not just any string!).
 *
 * @param ref The reference to the string instance to be modified [<b>must not be NULL</b>].
 * @return The modified string instance (invalidating *ref) in case of success or None (leaving *ref untouched).
 */
extern OptionOf(kit_String)
kit_String_clear(kit_String *ref)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Explicitly request an expansion to hold at least as many elements as capacity.
 * If requested capacity is less than current capacity nothing will be done.
 *
 * Note: Takes ownership invalidating *ref in case of success.
 *
 * @attention
 *  This function requires *ref to be a kit_String instance (not just any string!).
 *
 * @param ref The reference to the string instance to be modified [<b>must not be NULL</b>].
 * @param capacity The minimum capacity to hold.
 * @return The modified string instance (invalidating *ref) in case of success or None (leaving *ref untouched).
 */
extern OptionOf(kit_String)
kit_String_expand(kit_String *ref, size_t capacity)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Requests the container to shrink in order to fit at least the stored elements freeing resources not used.
 * The request may be ignored by the container if the current size is less than the default capacity.
 *
 * Note: Takes ownership invalidating *ref in case of success.
 *
 * @attention
 *  This function requires *ref to be a kit_String instance (not just any string!).
 *
 * @param ref The reference to the string instance to be modified [<b>must not be NULL</b>].
 * @return The modified string instance (invalidating *ref) in case of success or None (leaving *ref untouched).
 */
extern OptionOf(kit_String)
kit_String_shrink(kit_String *ref)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * TODO docs
 * TODO test
 */
extern size_t
kit_String_findFirstFromIndex(kit_String self, size_t startIndex, kit_String substring)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * TODO docs
 * TODO test
 */
extern size_t
kit_String_findFirstLiteralFromIndex(kit_String self, size_t startIndex, const char *literal)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * TODO docs
 * TODO test
 */
extern size_t
kit_String_findFirstBytesFromIndex(kit_String self, size_t startIndex, const void *bytes, size_t size)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * TODO docs
 * TODO test
 */
extern size_t
kit_String_findLastFromIndex(kit_String self, size_t startIndex, kit_String substring)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * TODO docs
 * TODO test
 */
extern size_t
kit_String_findLastLiteralFromIndex(kit_String self, size_t startIndex, const char *literal)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * TODO docs
 * TODO test
 */
extern size_t
kit_String_findLastBytesFromIndex(kit_String self, size_t startIndex, const void *bytes, size_t size)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * TODO docs
 * TODO test
 */
extern size_t
kit_String_findFirst(kit_String self, kit_String substring)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * TODO docs
 * TODO test
 */
extern size_t
kit_String_findFirstLiteral(kit_String self, const char *literal)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * TODO docs
 * TODO test
 */
extern size_t
kit_String_findFirstBytes(kit_String self, const void *bytes, size_t size)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * TODO docs
 * TODO test
 */
extern size_t
kit_String_findLast(kit_String self, kit_String substring)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * TODO docs
 * TODO test
 */
extern size_t
kit_String_findLastLiteral(kit_String self, const char *literal)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * TODO docs
 * TODO test
 */
extern size_t
kit_String_findLastBytes(kit_String self, const void *bytes, size_t size)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Gets the size of the string.
 *
 * @param self The string instance [<b>must not be NULL</b>].
 * @return The size of the string.
 */
extern size_t
kit_String_size(kit_String self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Gets the capacity of the string before expansion.
 *
 * @param self The string instance [<b>must not be NULL</b>].
 * @return The capacity of the string.
 */
extern size_t
kit_String_capacity(kit_String self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Checks if the string is equal to the another.
 *
 * @param self The string instance [<b>must not be NULL</b>].
 * @param other The other string instance [<b>must not be NULL</b>].
 * @return true if the strings are equal false otherwise.
 */
extern bool
kit_String_isEqual(kit_String self, kit_String other)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Checks if the string is empty.
 *
 * @param self The string instance [<b>must not be NULL</b>].
 * @return true if the string is empty false otherwise.
 */
extern bool
kit_String_isEmpty(kit_String self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Deletes an instance of kit_String.
 * If self is NULL no action will be performed.
 *
 * @param self The string instance to be deleted.
 */
extern void
kit_String_delete(kit_String self);

#ifdef __cplusplus
}
#endif

#endif /* KIT_STRING_INCLUDED */
