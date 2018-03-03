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

#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <kit/allocator/allocator.h>
#include <kit/collections/string.h>

#define _(x) \
    ((void) ((x) ? 1 : 0));

struct kit_String_Object {
    size_t size;
    size_t capacity;
#ifndef NDEBUG
#define KIT_STRING_IDENTITY_CODE    ((void *) 0xDEADBEAF)
    const void *identityCode;
#endif
    char raw[];
};

static bool
kit_String_trimIfFn(const char c)
__attribute__((__warn_unused_result__));

static void *
kit_String_memrchr(const void *s, int c, size_t n)
__attribute__((__warn_unused_result__, __nonnull__));

static OptionOf(struct kit_String_Object *)
kit_String_Object_new(size_t capacityHint)
__attribute__((__warn_unused_result__));

static OptionOf(struct kit_String_Object *)
kit_String_Object_expand(struct kit_String_Object **ref, size_t capacity)
__attribute__((__warn_unused_result__, __nonnull__));

static OptionOf(struct kit_String_Object *)
kit_String_Object_shrink(struct kit_String_Object **ref)
__attribute__((__warn_unused_result__, __nonnull__));

static void
kit_String_Object_delete(struct kit_String_Object *self);

static void
__kit_String_assertValidInstance(const char *file, size_t line, kit_String string)
__attribute__((__nonnull__));

static void
__kit_String_assertNotOverlapping(const char *file, size_t line, const void *p1, size_t s1, const void *p2, size_t s2)
__attribute__((__nonnull__));

#define kit_String_assertValidInstance(x) \
    __kit_String_assertValidInstance(__FILE__, __LINE__, (x))

#define kit_String_assertNotOverlapping(p1, s1, p2, s2) \
    __kit_String_assertNotOverlapping(__FILE__, __LINE__, (p1), (s1), (p2), (s2))

/*
 *
 */
OptionOf(kit_String)
kit_String_new(void) {
    return kit_String_withCapacity(0);
}

OptionOf(kit_String)
kit_String_withCapacity(size_t capacity) {
    Option option = kit_String_Object_new(capacity);

    if (Option_isSome(option)) {
        struct kit_String_Object *stringObject = Option_unwrap(option);
        return Option_new(stringObject->raw);
    }

    return None;
}

OptionOf(kit_String)
kit_String_quoted(const void *const bytes, const size_t size) {
    assert(bytes);

    const char *data = bytes;
    kit_String string = NULL;
    bool teardownRequired = false;
    Option option = kit_String_withCapacity(size + size / 3);

    if (Option_isNone(option)) {
        return None;
    }

    string = Option_unwrap(option);
    /* if we are here we have enough space to perform this operation so no checks are performed */
    _(Option_unwrap(kit_String_setBytes(&string, "\"", 1)));

    for (size_t i = 0; i < size && false == teardownRequired; i++) {
        string = Option_unwrap(option);
        switch (*data) {
            case '"': {
                option = kit_String_appendBytes(&string, "\\\"", 2);
                break;
            }
            case '\\': {
                option = kit_String_appendBytes(&string, "\\\\", 2);
                break;
            }
            case '/': {
                option = kit_String_appendBytes(&string, "\\/", 2);
                break;
            }
            case '\b': {
                option = kit_String_appendBytes(&string, "\\b", 2);
                break;
            }
            case '\f': {
                option = kit_String_appendBytes(&string, "\\f", 2);
                break;
            }
            case '\n': {
                option = kit_String_appendBytes(&string, "\\n", 2);
                break;
            }
            case '\r': {
                option = kit_String_appendBytes(&string, "\\r", 2);
                break;
            }
            case '\t': {
                option = kit_String_appendBytes(&string, "\\t", 2);
                break;
            }
            default: {
                if (isprint(*data)) {
                    option = kit_String_appendFormat(&string, "%c", *data);
                } else {
                    option = kit_String_appendFormat(&string, "\\u%04hhx", *data);
                }
                break;
            }
        }
        if (Option_isNone(option)) {
            teardownRequired = true;
            break;
        }
        data++;
    }

    if (false == teardownRequired) {
        assert(NULL == string);
        assert(Option_isSome(option));
        string = Option_unwrap(option);
        option = kit_String_appendBytes(&string, "\"", 1);
        if (Option_isNone(option)) {
            teardownRequired = true;
        }
    }

    if (teardownRequired) {
        assert(NULL != string);
        assert(Option_isNone(option));
        kit_String_delete(string);
        string = NULL;
    } else {
        assert(NULL == string);
        assert(Option_isSome(option));
        string = Option_unwrap(option);
    }

    return Option_new((void *) string);
}

OptionOf(kit_String)
kit_String_fromPack(const char *const format, va_list pack) {
    assert(format);

    va_list packCopy;

    va_copy(packCopy, pack);
    const int formattedSize = vsnprintf(NULL, 0, format, packCopy);
    va_end(packCopy);

    if (formattedSize >= 0) {
        const size_t size = (size_t) formattedSize;
        Option option = kit_String_Object_new(size);

        if (Option_isSome(option)) {
            struct kit_String_Object *stringObject = Option_unwrap(option);
            vsnprintf(stringObject->raw, size + 1, format, pack);
            stringObject->size = size;
            return Option_new(stringObject->raw);
        }
    }

    return None;
}

OptionOf(kit_String)
kit_String_fromBytes(const void *const bytes, const size_t size) {
    assert(bytes);
    Option option = kit_String_Object_new(size);

    if (Option_isSome(option)) {
        struct kit_String_Object *stringObject = Option_unwrap(option);
        char *raw = stringObject->raw;
        kit_Allocator_copy(raw, bytes, size);
        raw[size] = '\0';
        stringObject->size = size;
        return Option_new(raw);
    }

    return None;
}

OptionOf(kit_String)
kit_String_fromFormat(const char *const format, ...) {
    assert(format);

    va_list pack;
    va_start(pack, format);
    Option option = kit_String_fromPack(format, pack);
    va_end(pack);
    return option;
}

OptionOf(kit_String)
kit_String_fromLiteral(const char *const literal) {
    assert(literal);

    return kit_String_fromBytes(literal, strlen(literal));
}

OptionOf(kit_String)
kit_String_duplicate(kit_String s) {
    assert(s);
    kit_String_assertValidInstance(s);

    return kit_String_fromBytes(s, kit_String_size(s));
}

ResultOf(kit_String, OutOfRangeError, OutOfMemoryError)
kit_String_insert(kit_String *const ref, const size_t index, kit_String other) {
    assert(ref);
    assert(*ref);
    assert(other);
    kit_String_assertValidInstance(*ref);
    kit_String_assertValidInstance(other);
    kit_String_assertNotOverlapping(*ref, kit_String_size(*ref), other, kit_String_size(other));

    return kit_String_insertBytes(ref, index, other, kit_String_size(other));
}

ResultOf(kit_String, OutOfRangeError, OutOfMemoryError)
kit_String_insertPack(kit_String *ref, size_t index, const char *format, va_list pack) {
    assert(ref);
    assert(*ref);
    assert(format);
    kit_String_assertValidInstance(*ref);

    if (index > kit_String_size(*ref)) {
        return Result_error(OutOfRangeError);
    }

    va_list packCopy;
    struct kit_String_Object *stringObject = ((struct kit_String_Object *) *ref) - 1;

    va_copy(packCopy, pack);
    const int formattedSize = vsnprintf(NULL, 0, format, packCopy);
    va_end(packCopy);

    if (formattedSize >= 0) {
        const size_t currentSize = stringObject->size;
        const size_t additionalSize = (size_t) formattedSize;
        Option option = kit_String_Object_expand(&stringObject, currentSize + additionalSize);

        if (Option_isSome(option)) {
            stringObject = Option_unwrap(option);
            char *raw = stringObject->raw;
            char previousChar = raw[index];
            kit_Allocator_move(raw + index + additionalSize, raw + index, currentSize - index);
            vsnprintf(raw + index, additionalSize + 1, format, pack);
            raw[index + additionalSize] = previousChar;
            raw[stringObject->size = currentSize + additionalSize] = '\0';
            *ref = NULL;
            return Result_ok(raw);
        }
    }

    assert(NULL != stringObject);
    return Result_error(OutOfMemoryError);
}

ResultOf(kit_String, OutOfRangeError, OutOfMemoryError)
kit_String_insertBytes(kit_String *const ref, const size_t index, const void *const bytes, const size_t size) {
    assert(ref);
    assert(*ref);
    assert(bytes);
    kit_String_assertValidInstance(*ref);
    kit_String_assertNotOverlapping(*ref, kit_String_size(*ref), bytes, size);

    if (index > kit_String_size(*ref)) {
        return Result_error(OutOfRangeError);
    }

    struct kit_String_Object *stringObject = ((struct kit_String_Object *) *ref) - 1;
    const size_t currentSize = stringObject->size;
    Option option = kit_String_Object_expand(&stringObject, currentSize + size);

    if (Option_isSome(option)) {
        assert(NULL == stringObject);
        stringObject = Option_unwrap(option);
        char *raw = stringObject->raw;
        kit_Allocator_move(raw + index + size, raw + index, currentSize - index);
        kit_Allocator_copy(raw + index, bytes, size);
        raw[stringObject->size = currentSize + size] = '\0';
        *ref = NULL;
        return Result_ok(raw);
    }

    assert(NULL != stringObject);
    return Result_error(OutOfMemoryError);
}

ResultOf(kit_String, OutOfRangeError, OutOfMemoryError)
kit_String_insertFormat(kit_String *const ref, const size_t index, const char *const format, ...) {
    assert(ref);
    assert(*ref);
    assert(format);
    kit_String_assertValidInstance(*ref);

    va_list pack;
    va_start(pack, format);
    Result result = kit_String_insertPack(ref, index, format, pack);
    va_end(pack);
    return result;
}

ResultOf(kit_String, OutOfRangeError, OutOfMemoryError)
kit_String_insertLiteral(kit_String *const ref, const size_t index, const char *const literal) {
    assert(ref);
    assert(*ref);
    assert(literal);
    kit_String_assertValidInstance(*ref);
    kit_String_assertNotOverlapping(*ref, kit_String_size(*ref), literal, strlen(literal));

    return kit_String_insertBytes(ref, index, literal, strlen(literal));
}

OptionOf(kit_String)
kit_String_append(kit_String *const ref, kit_String other) {
    assert(ref);
    assert(*ref);
    assert(other);
    kit_String_assertValidInstance(*ref);
    kit_String_assertValidInstance(other);
    kit_String_assertNotOverlapping(*ref, kit_String_size(*ref), other, kit_String_size(other));

    Result result = kit_String_insertBytes(ref, kit_String_size(*ref), other, kit_String_size(other));
    return Result_isOk(result) ? Option_new(Result_unwrap(result)) : None;
}

OptionOf(kit_String)
kit_String_appendPack(kit_String *const ref, const char *const format, va_list pack) {
    assert(ref);
    assert(*ref);
    assert(format);
    kit_String_assertValidInstance(*ref);

    Result result = kit_String_insertPack(ref, kit_String_size(*ref), format, pack);
    return Result_isOk(result) ? Option_new(Result_unwrap(result)) : None;
}

OptionOf(kit_String)
kit_String_appendBytes(kit_String *const ref, const void *const bytes, const size_t size) {
    assert(ref);
    assert(*ref);
    assert(bytes);
    kit_String_assertValidInstance(*ref);
    kit_String_assertNotOverlapping(*ref, kit_String_size(*ref), bytes, size);

    Result result = kit_String_insertBytes(ref, kit_String_size(*ref), bytes, size);
    return Result_isOk(result) ? Option_new(Result_unwrap(result)) : None;
}

OptionOf(kit_String)
kit_String_appendFormat(kit_String *const ref, const char *const format, ...) {
    assert(ref);
    assert(*ref);
    assert(format);
    kit_String_assertValidInstance(*ref);

    va_list pack;
    va_start(pack, format);
    Result result = kit_String_insertPack(ref, kit_String_size(*ref), format, pack);
    va_end(pack);
    return Result_isOk(result) ? Option_new(Result_unwrap(result)) : None;
}

OptionOf(kit_String)
kit_String_appendLiteral(kit_String *const ref, const char *const literal) {
    assert(ref);
    assert(*ref);
    assert(literal);
    kit_String_assertValidInstance(*ref);
    kit_String_assertNotOverlapping(*ref, kit_String_size(*ref), literal, strlen(literal));

    Result result = kit_String_insertLiteral(ref, kit_String_size(*ref), literal);
    return Result_isOk(result) ? Option_new(Result_unwrap(result)) : None;
}

OptionOf(kit_String)
kit_String_prepend(kit_String *const ref, kit_String other) {
    assert(ref);
    assert(*ref);
    assert(other);
    kit_String_assertValidInstance(*ref);
    kit_String_assertValidInstance(other);
    kit_String_assertNotOverlapping(*ref, kit_String_size(*ref), other, kit_String_size(other));

    Result result = kit_String_insert(ref, 0, other);
    return Result_isOk(result) ? Option_new(Result_unwrap(result)) : None;
}

OptionOf(kit_String)
kit_String_prependPack(kit_String *const ref, const char *const format, va_list pack) {
    assert(ref);
    assert(*ref);
    assert(format);
    kit_String_assertValidInstance(*ref);

    Result result = kit_String_insertPack(ref, 0, format, pack);
    return Result_isOk(result) ? Option_new(Result_unwrap(result)) : None;
}

OptionOf(kit_String)
kit_String_prependBytes(kit_String *const ref, const void *const bytes, const size_t size) {
    assert(ref);
    assert(*ref);
    assert(bytes);
    kit_String_assertValidInstance(*ref);
    kit_String_assertNotOverlapping(*ref, kit_String_size(*ref), bytes, size);

    Result result = kit_String_insertBytes(ref, 0, bytes, size);
    return Result_isOk(result) ? Option_new(Result_unwrap(result)) : None;
}

OptionOf(kit_String)
kit_String_prependFormat(kit_String *const ref, const char *const format, ...) {
    assert(ref);
    assert(*ref);
    assert(format);
    kit_String_assertValidInstance(*ref);

    va_list pack;
    va_start(pack, format);
    Result result = kit_String_insertPack(ref, 0, format, pack);
    va_end(pack);
    return Result_isOk(result) ? Option_new(Result_unwrap(result)) : None;
}

OptionOf(kit_String)
kit_String_prependLiteral(kit_String *const ref, const char *const literal) {
    assert(ref);
    assert(*ref);
    assert(literal);
    kit_String_assertValidInstance(*ref);
    kit_String_assertNotOverlapping(*ref, kit_String_size(*ref), literal, strlen(literal));

    Result result = kit_String_insertLiteral(ref, 0, literal);
    return Result_isOk(result) ? Option_new(Result_unwrap(result)) : None;
}

OptionOf(kit_String)
kit_String_set(kit_String *const ref, kit_String other) {
    assert(ref);
    assert(*ref);
    assert(other);
    kit_String_assertValidInstance(*ref);
    kit_String_assertValidInstance(other);
    kit_String_assertNotOverlapping(*ref, kit_String_size(*ref), other, kit_String_size(other));

    return kit_String_setBytes(ref, other, kit_String_size(other));
}

OptionOf(kit_String)
kit_String_setPack(kit_String *const ref, const char *const format, va_list pack) {
    assert(ref);
    assert(*ref);
    assert(format);
    kit_String_assertValidInstance(*ref);

    va_list packCopy;
    struct kit_String_Object *stringObject = ((struct kit_String_Object *) *ref) - 1;

    va_copy(packCopy, pack);
    const int formattedSize = vsnprintf(NULL, 0, format, packCopy);
    va_end(packCopy);

    if (formattedSize >= 0) {
        const size_t newSize = (size_t) formattedSize;
        Option option = kit_String_Object_expand(&stringObject, newSize);

        if (Option_isSome(option)) {
            stringObject = Option_unwrap(option);
            vsnprintf(stringObject->raw, newSize + 1, format, pack);
            stringObject->size = newSize;
            *ref = NULL;
            return Option_new(stringObject->raw);
        }
    }

    return None;
}

OptionOf(kit_String)
kit_String_setBytes(kit_String *const ref, const void *const bytes, const size_t size) {
    assert(ref);
    assert(*ref);
    assert(bytes);
    kit_String_assertValidInstance(*ref);
    kit_String_assertNotOverlapping(*ref, kit_String_size(*ref), bytes, size);

    struct kit_String_Object *stringObject = ((struct kit_String_Object *) *ref) - 1;
    Option option = kit_String_Object_expand(&stringObject, size);

    if (Option_isSome(option)) {
        assert(NULL == stringObject);
        stringObject = Option_unwrap(option);
        char *stringObjectRaw = stringObject->raw;
        kit_Allocator_copy(stringObjectRaw, bytes, size);
        stringObjectRaw[stringObject->size = size] = '\0';
        *ref = NULL;
        return Option_new(stringObjectRaw);
    }

    assert(NULL != stringObject);
    return None;
}

OptionOf(kit_String)
kit_String_setFormat(kit_String *const ref, const char *const format, ...) {
    assert(ref);
    assert(*ref);
    assert(format);
    kit_String_assertValidInstance(*ref);

    va_list pack;
    va_start(pack, format);
    Option option = kit_String_setPack(ref, format, pack);
    va_end(pack);
    return option;
}

OptionOf(kit_String)
kit_String_setLiteral(kit_String *const ref, const char *const literal) {
    assert(ref);
    assert(*ref);
    assert(literal);
    kit_String_assertValidInstance(*ref);
    kit_String_assertNotOverlapping(*ref, kit_String_size(*ref), literal, strlen(literal));

    return kit_String_setBytes(ref, literal, strlen(literal));
}

ResultOf(kit_String, OutOfRangeError)
kit_String_erase(kit_String *const ref, const size_t index, const size_t count) {
    assert(ref);
    assert(*ref);
    kit_String_assertValidInstance(*ref);

    if (count > 0) {
        // this must never return IllegalArgumentsError because start is always less or equal than end
        Result result = kit_String_eraseSlice(ref, index, index + count - 1);
        assert(Result_isOk(result) || OutOfRangeError == Result_inspect(result));
        return result;
    }

    struct kit_String_Object *stringObject = ((struct kit_String_Object *) *ref) - 1;

    if (index >= stringObject->size) {
        return Result_error(OutOfRangeError);
    }

    *ref = NULL;
    return Result_ok(stringObject->raw);
}

ResultOf(kit_String, OutOfRangeError, IllegalArgumentsError)
kit_String_eraseSlice(kit_String *const ref, const size_t start, const size_t end) {
    assert(ref);
    assert(*ref);
    kit_String_assertValidInstance(*ref);

    struct kit_String_Object *stringObject = ((struct kit_String_Object *) *ref) - 1;

    if (start > end) {
        return Result_error(IllegalArgumentsError);
    }

    if (end >= stringObject->size) {
        return Result_error(OutOfRangeError);
    }

    const size_t actualEnd = end + 1;
    char *raw = stringObject->raw;
    const size_t size = (stringObject->size -= actualEnd - start);
    kit_Allocator_move(raw + start, raw + actualEnd, size);
    raw[size] = '\0';

    *ref = NULL;
    return Result_ok(raw);
}

kit_String
kit_String_removeFirstMatchingBytes(kit_String *const ref, const void *const bytes, const size_t size) {
    assert(ref);
    assert(*ref);
    assert(bytes);
    kit_String_assertValidInstance(*ref);

    const size_t index = kit_String_findFirstBytes(*ref, bytes, size);

    if (index == SIZE_MAX) {
        kit_String string = *ref;
        *ref = NULL;
        return string;
    }

    return Result_unwrap(kit_String_erase(ref, index, size));
}

kit_String
kit_String_removeFirstMatchingLiteral(kit_String *const ref, const char *const literal) {
    assert(ref);
    assert(*ref);
    assert(literal);
    kit_String_assertValidInstance(*ref);

    return kit_String_removeFirstMatchingBytes(ref, literal, strlen(literal));
}

kit_String
kit_String_removeLastMatchingBytes(kit_String *const ref, const void *const bytes, const size_t size) {
    assert(ref);
    assert(*ref);
    assert(bytes);
    kit_String_assertValidInstance(*ref);

    const size_t index = kit_String_findLastBytes(*ref, bytes, size);

    if (index == SIZE_MAX) {
        kit_String string = *ref;
        *ref = NULL;
        return string;
    }

    return Result_unwrap(kit_String_erase(ref, index, size));
}

kit_String
kit_String_removeLastMatchingLiteral(kit_String *const ref, const char *const literal) {
    assert(ref);
    assert(*ref);
    assert(literal);
    kit_String_assertValidInstance(*ref);

    return kit_String_removeLastMatchingBytes(ref, literal, strlen(literal));
}

kit_String
kit_String_removeAllMatchingBytes(kit_String *const ref, const void *const bytes, const size_t size) {
    assert(ref);
    assert(*ref);
    assert(bytes);
    kit_String_assertValidInstance(*ref);

    kit_String self = *ref;
    for (size_t index = kit_String_findFirstBytesFromIndex(self, 0, bytes, size);
         index < kit_String_size(self);
         index = kit_String_findFirstBytesFromIndex(self, index, bytes, size)) {
        self = Result_unwrap(kit_String_erase(&self, index, size));
    }

    *ref = NULL;
    return self;
}

kit_String
kit_String_removeAllMatchingLiteral(kit_String *const ref, const char *const literal) {
    assert(ref);
    assert(*ref);
    assert(literal);
    kit_String_assertValidInstance(*ref);

    return kit_String_removeAllMatchingBytes(ref, literal, strlen(literal));
}

kit_String
kit_String_trimLeft(kit_String *const ref) {
    assert(ref);
    assert(*ref);
    kit_String_assertValidInstance(*ref);

    return kit_String_trimLeftIf(ref, kit_String_trimIfFn);
}

kit_String
kit_String_trimRight(kit_String *const ref) {
    assert(ref);
    assert(*ref);
    kit_String_assertValidInstance(*ref);

    return kit_String_trimRightIf(ref, kit_String_trimIfFn);
}

kit_String
kit_String_trim(kit_String *const ref) {
    assert(ref);
    assert(*ref);
    kit_String_assertValidInstance(*ref);

    return kit_String_trimIf(ref, kit_String_trimIfFn);
}

kit_String
kit_String_trimLeftIf(kit_String *const ref, bool (*const ifFn)(const char)) {
    assert(ref);
    assert(*ref);
    assert(ifFn);
    kit_String_assertValidInstance(*ref);

    kit_String string = *ref;

    if (kit_String_isEmpty(string)) {
        *ref = NULL;
        return string;
    } else {
        const struct kit_String_Object *stringObject = ((struct kit_String_Object *) string) - 1;
        const size_t size = stringObject->size;
        const char *raw = stringObject->raw;
        size_t count;
        char c;

        for (count = 0; count < size; count++) {
            c = raw[0];
            if (!ifFn(c)) {
                break;
            }
            raw++;
        }

        return Result_unwrap(kit_String_erase(ref, 0, count));
    }
}

kit_String
kit_String_trimRightIf(kit_String *const ref, bool (*const ifFn)(const char)) {
    assert(ref);
    assert(*ref);
    assert(ifFn);
    kit_String_assertValidInstance(*ref);

    kit_String string = *ref;

    if (kit_String_isEmpty(string)) {
        *ref = NULL;
        return string;
    } else {
        const struct kit_String_Object *stringObject = ((struct kit_String_Object *) string) - 1;
        const size_t size = stringObject->size;
        const char *raw = stringObject->raw + size - 1;
        size_t count;
        char c;

        for (count = 0; count < size; count++) {
            c = raw[0];
            if (!ifFn(c)) {
                break;
            }
            raw--;
        }

        return Result_unwrap(kit_String_erase(ref, count > 0 ? size - count : 0, count));
    }
}

kit_String
kit_String_trimIf(kit_String *const ref, bool (*const ifFn)(const char)) {
    assert(ref);
    assert(*ref);
    assert(ifFn);
    kit_String_assertValidInstance(*ref);

    kit_String string = kit_String_trimLeftIf(ref, ifFn);
    return kit_String_trimRightIf(&string, ifFn);
}

OptionOf(kit_String)
kit_String_quote(kit_String *const ref) {
    assert(ref);
    assert(*ref);
    kit_String_assertValidInstance(*ref);

    struct kit_String_Object *stringObject = ((struct kit_String_Object *) *ref) - 1;
    Option option = kit_String_quoted(stringObject->raw, stringObject->size);

    if (Option_isSome(option)) {
        kit_String_delete(*ref);
        *ref = NULL;
    }

    return option;
}

OptionOf(kit_String)
kit_String_clear(kit_String *const ref) {
    assert(ref);
    assert(*ref);
    kit_String_assertValidInstance(*ref);

    struct kit_String_Object *stringObject = ((struct kit_String_Object *) *ref) - 1;
    stringObject->raw[0] = '\0';
    stringObject->size = 0;

    *ref = NULL;
    return Option_new(stringObject->raw);
}

OptionOf(kit_String)
kit_String_expand(kit_String *ref, size_t capacity) {
    assert(ref);
    assert(*ref);
    kit_String_assertValidInstance(*ref);

    struct kit_String_Object *stringObject = ((struct kit_String_Object *) *ref) - 1;
    Option option = kit_String_Object_expand(&stringObject, capacity);

    if (Option_isSome(option)) {
        assert(NULL == stringObject);
        stringObject = Option_unwrap(option);
        *ref = NULL;
        return Option_new(stringObject->raw);
    } else {
        assert(NULL != stringObject);
        return None;
    }
}

OptionOf(kit_String)
kit_String_shrink(kit_String *const ref) {
    assert(ref);
    assert(*ref);
    kit_String_assertValidInstance(*ref);

    struct kit_String_Object *stringObject = ((struct kit_String_Object *) *ref) - 1;
    Option option = kit_String_Object_shrink(&stringObject);

    if (Option_isSome(option)) {
        assert(NULL == stringObject);
        stringObject = Option_unwrap(option);
        *ref = NULL;
        return Option_new(stringObject->raw);
    } else {
        assert(NULL != stringObject);
        return None;
    }
}

size_t
kit_String_findFirstFromIndex(kit_String self, const size_t startIndex, kit_String substring) {
    assert(self);
    assert(substring);
    kit_String_assertValidInstance(self);
    kit_String_assertValidInstance(substring);

    return kit_String_findFirstBytesFromIndex(self, startIndex, substring, kit_String_size(substring));
}

size_t
kit_String_findFirstLiteralFromIndex(kit_String self, const size_t startIndex, const char *const literal) {
    assert(self);
    assert(literal);
    kit_String_assertValidInstance(self);

    return kit_String_findFirstBytesFromIndex(self, startIndex, literal, strlen(literal));
}

size_t
kit_String_findFirstBytesFromIndex(
        kit_String self, const size_t startIndex, const void *const bytes, const size_t size
) {
    assert(self);
    assert(bytes);
    kit_String_assertValidInstance(self);

    const size_t selfSize = kit_String_size(self);

    if (0 < size && size <= selfSize && startIndex < selfSize) {
        size_t matchIndex = startIndex;
        char *matchString = NULL;
        const char *byteString = bytes;

        while ((matchString = memchr(self + matchIndex, byteString[0], selfSize - matchIndex))) {
            matchIndex = matchString - self;
            if (((matchIndex + size) <= selfSize) && (memcmp(self + matchIndex, byteString, size) == 0)) {
                return matchIndex;
            } else {
                matchIndex++;
            }
        }
    }

    return SIZE_MAX;
}

size_t
kit_String_findLastFromIndex(kit_String self, const size_t startIndex, kit_String substring) {
    assert(self);
    assert(substring);
    kit_String_assertValidInstance(self);
    kit_String_assertValidInstance(substring);

    return kit_String_findLastBytesFromIndex(self, startIndex, substring, kit_String_size(substring));
}

size_t
kit_String_findLastLiteralFromIndex(kit_String self, const size_t startIndex, const char *const literal) {
    assert(self);
    assert(literal);
    kit_String_assertValidInstance(self);

    return kit_String_findLastBytesFromIndex(self, startIndex, literal, strlen(literal));
}

size_t
kit_String_findLastBytesFromIndex(
        kit_String self, const size_t startIndex, const void *const bytes, const size_t size
) {
    assert(self);
    assert(bytes);
    kit_String_assertValidInstance(self);

    const size_t selfSize = kit_String_size(self);

    if (0 < size && size <= selfSize && startIndex < selfSize) {
        size_t matchIndex = startIndex;
        char *matchString = NULL;
        const char *byteString = bytes;

        while ((matchString = kit_String_memrchr(self, byteString[0], matchIndex))) {
            matchIndex = matchString - self;
            if (((matchIndex + size) <= selfSize) && (memcmp(self + matchIndex, byteString, size) == 0)) {
                return matchIndex;
            } else {
                matchIndex--;
            }
        }
    }

    return SIZE_MAX;
}

size_t
kit_String_findFirst(kit_String self, kit_String substring) {
    assert(self);
    assert(substring);
    kit_String_assertValidInstance(self);
    kit_String_assertValidInstance(substring);

    return kit_String_findFirstBytesFromIndex(self, 0, substring, kit_String_size(substring));
}

size_t
kit_String_findFirstLiteral(kit_String self, const char *const literal) {
    assert(self);
    assert(literal);
    kit_String_assertValidInstance(self);

    return kit_String_findFirstBytesFromIndex(self, 0, literal, strlen(literal));
}

size_t
kit_String_findFirstBytes(kit_String self, const void *const bytes, const size_t size) {
    assert(self);
    assert(bytes);
    kit_String_assertValidInstance(self);

    return kit_String_findFirstBytesFromIndex(self, 0, bytes, size);
}

size_t
kit_String_findLast(kit_String self, kit_String substring) {
    assert(self);
    assert(substring);
    kit_String_assertValidInstance(self);
    kit_String_assertValidInstance(substring);

    const size_t selfSize = kit_String_size(self);
    return kit_String_findLastBytesFromIndex(
            self, selfSize > 0 ? selfSize - 1 : 0, substring, kit_String_size(substring)
    );
}

size_t
kit_String_findLastLiteral(kit_String self, const char *const literal) {
    assert(self);
    assert(literal);
    kit_String_assertValidInstance(self);

    const size_t selfSize = kit_String_size(self);
    return kit_String_findLastBytesFromIndex(
            self, selfSize > 0 ? selfSize - 1 : 0, literal, strlen(literal)
    );
}

size_t
kit_String_findLastBytes(kit_String self, const void *const bytes, const size_t size) {
    assert(self);
    assert(bytes);
    kit_String_assertValidInstance(self);

    const size_t selfSize = kit_String_size(self);
    return kit_String_findLastBytesFromIndex(
            self, selfSize > 0 ? selfSize - 1 : 0, bytes, size
    );
}

size_t
kit_String_size(kit_String self) {
    assert(self);
    kit_String_assertValidInstance(self);

    const struct kit_String_Object *stringObject = ((struct kit_String_Object *) self) - 1;
    return stringObject->size;
}

size_t
kit_String_capacity(kit_String self) {
    assert(self);
    kit_String_assertValidInstance(self);

    const struct kit_String_Object *stringObject = ((struct kit_String_Object *) self) - 1;
    return stringObject->capacity;
}

bool
kit_String_isEqual(kit_String self, kit_String other) {
    assert(self);
    assert(other);
    kit_String_assertValidInstance(self);
    kit_String_assertValidInstance(other);

    const size_t selfSize = kit_String_size(self);
    return (selfSize == kit_String_size(other)) && (0 == memcmp(self, other, selfSize));
}

bool
kit_String_isEmpty(kit_String self) {
    assert(self);
    kit_String_assertValidInstance(self);

    return 0 == kit_String_size(self);
}

void
kit_String_lower(kit_String self) {
    assert(self);
    kit_String_assertValidInstance(self);

    struct kit_String_Object *stringObject = ((struct kit_String_Object *) self) - 1;
    for (size_t i = 0; i < stringObject->size; i++) {
        stringObject->raw[i] = (char) tolower(stringObject->raw[i]);
    }
}

void
kit_String_upper(kit_String self) {
    assert(self);
    kit_String_assertValidInstance(self);

    struct kit_String_Object *stringObject = ((struct kit_String_Object *) self) - 1;
    for (size_t i = 0; i < stringObject->size; i++) {
        stringObject->raw[i] = (char) toupper(stringObject->raw[i]);
    }
}

void
kit_String_delete(kit_String self) {
    if (self) {
        kit_String_assertValidInstance(self);
        struct kit_String_Object *stringObject = ((struct kit_String_Object *) self) - 1;
        kit_String_Object_delete(stringObject);
    }
}

/*
 * Internals
 */
bool
kit_String_trimIfFn(const char c) {
    return isspace(c) || isblank(c) || !isprint(c);
}

void *
kit_String_memrchr(const void *s, int c, size_t n) {
    assert(s);

    if (n != 0) {
        const unsigned char ch = (unsigned char) c;
        const unsigned char *cp = ((unsigned char *) s) + n;

        do {
            if (*(--cp) == ch) {
                return ((void *) cp);
            }
        } while (--n != 0);
    }

    return NULL;
}

OptionOf(struct kit_String_Object *)
kit_String_Object_new(const size_t capacityHint) {
    struct kit_String_Object *stringObject;
    const size_t capacity = capacityHint > KIT_STRING_DEFAULT_CAPACITY ? capacityHint : KIT_STRING_DEFAULT_CAPACITY;
    Option option = kit_Allocator_malloc(sizeof(*stringObject) + capacity + 1);

    if (Option_isSome(option)) {
        stringObject = Option_unwrap(option);
        stringObject->size = 0;
        stringObject->capacity = capacity;
#ifndef NDEBUG
        stringObject->identityCode = KIT_STRING_IDENTITY_CODE;
#endif
        stringObject->raw[0] = stringObject->raw[capacity] = '\0';
    }

    return option;
}

OptionOf(struct kit_String_Object *)
kit_String_Object_expand(struct kit_String_Object **const ref, const size_t capacity) {
    assert(ref);
    assert(*ref);

    struct kit_String_Object *stringObject = *ref;

    if (stringObject->capacity < capacity) {
        const size_t newCapacity = (capacity - stringObject->capacity > KIT_STRING_MINIMUM_RESERVATION) ?
                                   capacity : stringObject->capacity + KIT_STRING_MINIMUM_RESERVATION;
        Option option = kit_Allocator_ralloc(stringObject, sizeof(*stringObject) + newCapacity + 1);
        if (Option_isSome(option)) {
            stringObject = Option_unwrap(option);
            stringObject->capacity = newCapacity;
            stringObject->raw[newCapacity] = '\0';
        } else {
            return None;
        }
    }

    *ref = NULL;
    return Option_new(stringObject);
}

OptionOf(struct kit_String_Object *)
kit_String_Object_shrink(struct kit_String_Object **const ref) {
    assert(ref);
    assert(*ref);

    struct kit_String_Object *stringObject = *ref;

    if (stringObject->capacity > KIT_STRING_DEFAULT_CAPACITY) {
        const size_t size = stringObject->size;
        const size_t newCapacity = size > KIT_STRING_DEFAULT_CAPACITY ? size : KIT_STRING_DEFAULT_CAPACITY;
        Option option = kit_Allocator_ralloc(stringObject, sizeof(*stringObject) + newCapacity + 1);
        if (Option_isSome(option)) {
            stringObject = Option_unwrap(option);
            stringObject->capacity = newCapacity;
            stringObject->raw[newCapacity] = '\0';
        } else {
            return None;
        }
    }

    *ref = NULL;
    return Option_new(stringObject);
}

void
kit_String_Object_delete(struct kit_String_Object *self) {
    if (self) {
        kit_Allocator_free(self);
    }
}

void
__kit_String_assertValidInstance(const char *const file, const size_t line, kit_String string) {
    assert(file);
    assert(string);
#ifdef NDEBUG
    (void) file;
    (void) line;
    (void) string;
#else
    const struct kit_String_Object *stringObject = ((struct kit_String_Object *) string) - 1;
    if (stringObject->identityCode != KIT_STRING_IDENTITY_CODE) {
        _(Option_expect(None, "Expected a valid string instance.\n%s:%zu", file, line));
    }
#endif
}

void
__kit_String_assertNotOverlapping(
        const char *const file, const size_t line,
        const void *const p1, const size_t s1,
        const void *const p2, const size_t s2
) {
    assert(file);
    assert(p1);
    assert(p2);
#ifdef NDEBUG
    (void) file;
    (void) line;
    (void) p1;
    (void) s1;
    (void) p2;
    (void) s1;
#else
    const uintptr_t a1 = (uintptr_t) p1;
    const uintptr_t a2 = (uintptr_t) p2;

    /*                  a1               a1 + s1
     *                  |________________|
     * a2           a2 + s2                 a2           a2 + s2
     * |____________|                       |____________|
     */

    if (!((a2 + s2) < a1 || (a1 + s1) < a2)) {
        _(Option_expect(None, "Expected non-overlapping strings.\n%s:%zu", file, line));
    }
#endif
}
