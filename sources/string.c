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
#include <memory.h>
#include <assert.h>
#include <kit/allocator/allocator.h>
#include <kit/collections/string.h>

#define _(x)            ((void) ((x) ? 1 : 0));

struct kit_String_Object {
    size_t size;
    size_t capacity;
#ifndef NDEBUG
#define KIT_STRING_IDENTITY_CODE    ((void *) 0xDEADBEAF)
    const void *identityCode;
#endif
    char raw[];
};

static OptionOf(struct kit_String_Object *)
kit_String_Object_new(size_t capacityHint)
__attribute__((__warn_unused_result__));

static OptionOf(struct kit_String_Object *)
kit_String_Object_reserve(struct kit_String_Object **ref, size_t capacity)
__attribute__((__warn_unused_result__, __nonnull__));

static OptionOf(struct kit_String_Object *)
kit_String_Object_shrink(struct kit_String_Object **ref)
__attribute__((__warn_unused_result__, __nonnull__));

static void
kit_String_Object_delete(struct kit_String_Object *self);

#ifdef NDEBUG
#define kit_String_assertValidInstance(x)
#define kit_String_assertNotOverlapping(p1, s1, p2, s2)
#else
static void
__kit_String_assertValidInstance(const char *file, size_t line, kit_String string)
__attribute__((__nonnull__));

static void
__kit_String_assertNotOverlapping(const char *file, size_t line, const void *p1, size_t s1, const void *p2, size_t s2)
__attribute__((__nonnull__));

#define kit_String_assertValidInstance(x)               __kit_String_assertValidInstance(__FILE__, __LINE__, (x))
#define kit_String_assertNotOverlapping(p1, s1, p2, s2) __kit_String_assertNotOverlapping(__FILE__, __LINE__, (p1), (s1), (p2), (s2))
#endif

/*
 *
 */
OptionOf(kit_String)
kit_String_new(const size_t capacityHint) {
    Option stringObjectOption = kit_String_Object_new(capacityHint);

    if (Option_isSome(stringObjectOption)) {
        struct kit_String_Object *stringObject = Option_unwrap(stringObjectOption);
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
    Option stringOption = kit_String_new(size + size / 3);

    if (Option_isNone(stringOption)) {
        return None;
    }

    string = Option_unwrap(stringOption);
    /* if we are here we have enough space to perform this operation so no checks are performed */
    _(Option_unwrap(kit_String_setBytes(&string, "\"", 1)));

    for (size_t i = 0; i < size && false == teardownRequired; i++) {
        string = Option_unwrap(stringOption);
        switch (*data) {
            case '"': {
                stringOption = kit_String_appendBytes(&string, "\\\"", 2);
                break;
            }
            case '\\': {
                stringOption = kit_String_appendBytes(&string, "\\\\", 2);
                break;
            }
            case '/': {
                stringOption = kit_String_appendBytes(&string, "\\/", 2);
                break;
            }
            case '\b': {
                stringOption = kit_String_appendBytes(&string, "\\b", 2);
                break;
            }
            case '\f': {
                stringOption = kit_String_appendBytes(&string, "\\f", 2);
                break;
            }
            case '\n': {
                stringOption = kit_String_appendBytes(&string, "\\n", 2);
                break;
            }
            case '\r': {
                stringOption = kit_String_appendBytes(&string, "\\r", 2);
                break;
            }
            case '\t': {
                stringOption = kit_String_appendBytes(&string, "\\t", 2);
                break;
            }
            default: {
                if (isprint(*data)) {
                    stringOption = kit_String_appendFormat(&string, "%c", *data);
                } else {
                    stringOption = kit_String_appendFormat(&string, "\\u%04hhx", *data);
                }
                break;
            }
        }
        if (Option_isNone(stringOption)) {
            teardownRequired = true;
            break;
        }
        data++;
    }

    if (false == teardownRequired) {
        assert(NULL == string);
        assert(Option_isSome(stringOption));
        string = Option_unwrap(stringOption);
        stringOption = kit_String_appendBytes(&string, "\"", 1);
        if (Option_isNone(stringOption)) {
            teardownRequired = true;
        }
    }

    if (teardownRequired) {
        assert(NULL != string);
        assert(Option_isNone(stringOption));
        kit_String_delete(string);
        string = NULL;
    } else {
        assert(NULL == string);
        assert(Option_isSome(stringOption));
        string = Option_unwrap(stringOption);
    }

    return Option_new((void *) string);
}

OptionOf(kit_String)
kit_String_fromPack(const char *const format, va_list pack) {
    assert(format);

    va_list packCopy;

    va_copy(packCopy, pack);
    const int FORMATTED_SIZE = vsnprintf(NULL, 0, format, packCopy);
    va_end(packCopy);

    if (FORMATTED_SIZE >= 0) {
        const size_t SIZE = (size_t) FORMATTED_SIZE;
        Option stringObjectOption = kit_String_Object_new(SIZE);

        if (Option_isSome(stringObjectOption)) {
            struct kit_String_Object *stringObject = Option_unwrap(stringObjectOption);
            vsnprintf(stringObject->raw, SIZE + 1, format, pack);
            stringObject->size = SIZE;
            return Option_new(stringObject->raw);
        }
    }

    return None;
}

OptionOf(kit_String)
kit_String_fromBytes(const void *const bytes, const size_t size) {
    assert(bytes);
    Option stringObjectOption = kit_String_Object_new(size);

    if (Option_isSome(stringObjectOption)) {
        struct kit_String_Object *stringObject = Option_unwrap(stringObjectOption);
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
    Option result = kit_String_fromPack(format, pack);
    va_end(pack);

    return result;
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
kit_String_append(kit_String *const ref, kit_String other) {
    assert(ref);
    assert(*ref);
    assert(other);
    kit_String_assertValidInstance(*ref);
    kit_String_assertValidInstance(other);
    kit_String_assertNotOverlapping(*ref, kit_String_size(*ref), other, kit_String_size(other));

    const struct kit_String_Object *otherObject = ((struct kit_String_Object *) other) - 1;
    return kit_String_appendBytes(ref, other, otherObject->size);
}

OptionOf(kit_String)
kit_String_appendPack(kit_String *const ref, const char *const format, va_list pack) {
    assert(ref);
    assert(*ref);
    assert(format);

    va_list packCopy;
    struct kit_String_Object *stringObject = ((struct kit_String_Object *) *ref) - 1;

    va_copy(packCopy, pack);
    const int FORMATTED_SIZE = vsnprintf(NULL, 0, format, packCopy);
    va_end(packCopy);

    if (FORMATTED_SIZE >= 0) {
        const size_t CURRENT_SIZE = stringObject->size;
        const size_t ADDITIONAL_SIZE = (size_t) FORMATTED_SIZE;
        Option stringObjectOption = kit_String_Object_reserve(&stringObject, CURRENT_SIZE + ADDITIONAL_SIZE);

        if (Option_isSome(stringObjectOption)) {
            stringObject = Option_unwrap(stringObjectOption);
            vsnprintf(stringObject->raw + CURRENT_SIZE, ADDITIONAL_SIZE + 1, format, pack);
            stringObject->size += ADDITIONAL_SIZE;
            *ref = NULL;
            return Option_new(stringObject->raw);
        }
    }

    return None;
}

OptionOf(kit_String)
kit_String_appendBytes(kit_String *const ref, const void *const bytes, const size_t size) {
    assert(ref);
    assert(*ref);
    assert(bytes);
    kit_String_assertValidInstance(*ref);
    kit_String_assertNotOverlapping(*ref, kit_String_size(*ref), bytes, size);

    struct kit_String_Object *stringObject = ((struct kit_String_Object *) *ref) - 1;
    const size_t stringObjectSize = stringObject->size;
    Option stringObjectOption = kit_String_Object_reserve(&stringObject, stringObjectSize + size);

    if (Option_isSome(stringObjectOption)) {
        assert(NULL == stringObject);
        stringObject = Option_unwrap(stringObjectOption);
        char *stringObjectRaw = stringObject->raw;
        kit_Allocator_copy(stringObjectRaw + stringObjectSize, bytes, size);
        stringObjectRaw[stringObject->size = stringObjectSize + size] = '\0';
        *ref = NULL;
        return Option_new(stringObjectRaw);
    }

    assert(NULL != stringObject);
    return None;
}

OptionOf(kit_String)
kit_String_appendFormat(kit_String *const ref, const char *const format, ...) {
    assert(ref);
    assert(*ref);
    assert(format);

    va_list pack;

    va_start(pack, format);
    Option result = kit_String_appendPack(ref, format, pack);
    va_end(pack);

    assert(Option_isSome(result) ? NULL == *ref : NULL != *ref);
    return result;
}

OptionOf(kit_String)
kit_String_appendLiteral(kit_String *const ref, const char *const literal) {
    assert(ref);
    assert(*ref);
    assert(literal);
    kit_String_assertValidInstance(*ref);

    const size_t SIZE = strlen(literal);
    kit_String_assertNotOverlapping(*ref, kit_String_size(*ref), literal, SIZE);

    return kit_String_appendBytes(ref, literal, SIZE);
}

OptionOf(kit_String)
kit_String_set(kit_String *const ref, kit_String other) {
    assert(ref);
    assert(*ref);
    assert(other);
    kit_String_assertValidInstance(*ref);
    kit_String_assertValidInstance(other);
    kit_String_assertNotOverlapping(*ref, kit_String_size(*ref), other, kit_String_size(other));

    const struct kit_String_Object *otherObject = ((struct kit_String_Object *) other) - 1;
    return kit_String_setBytes(ref, other, otherObject->size);
}

OptionOf(kit_String)
kit_String_setPack(kit_String *const ref, const char *const format, va_list pack) {
    assert(ref);
    assert(*ref);
    assert(format);

    va_list packCopy;
    struct kit_String_Object *stringObject = ((struct kit_String_Object *) *ref) - 1;

    va_copy(packCopy, pack);
    const int FORMATTED_SIZE = vsnprintf(NULL, 0, format, packCopy);
    va_end(packCopy);

    if (FORMATTED_SIZE >= 0) {
        const size_t NEW_SIZE = (size_t) FORMATTED_SIZE;
        Option stringObjectOption = kit_String_Object_reserve(&stringObject, NEW_SIZE);

        if (Option_isSome(stringObjectOption)) {
            stringObject = Option_unwrap(stringObjectOption);
            vsnprintf(stringObject->raw, NEW_SIZE + 1, format, pack);
            stringObject->size = NEW_SIZE;
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
    Option stringObjectOption = kit_String_Object_reserve(&stringObject, size);

    if (Option_isSome(stringObjectOption)) {
        assert(NULL == stringObject);
        stringObject = Option_unwrap(stringObjectOption);
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

    va_list pack;

    va_start(pack, format);
    Option result = kit_String_setPack(ref, format, pack);
    va_end(pack);

    assert(Option_isSome(result) ? NULL == *ref : NULL != *ref);
    return result;
}

OptionOf(kit_String)
kit_String_setLiteral(kit_String *const ref, const char *const literal) {
    assert(ref);
    assert(*ref);
    assert(literal);
    kit_String_assertValidInstance(*ref);

    const size_t SIZE = strlen(literal);
    kit_String_assertNotOverlapping(*ref, kit_String_size(*ref), literal, SIZE);

    return kit_String_setBytes(ref, literal, SIZE);
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
kit_String_reserve(kit_String *const ref, const size_t capacity) {
    assert(ref);
    assert(*ref);
    kit_String_assertValidInstance(*ref);

    struct kit_String_Object *stringObject = ((struct kit_String_Object *) *ref) - 1;
    Option stringObjectOption = kit_String_Object_reserve(&stringObject, capacity);

    if (Option_isSome(stringObjectOption)) {
        assert(NULL == stringObject);
        stringObject = Option_unwrap(stringObjectOption);
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
    Option stringObjectOption = kit_String_Object_shrink(&stringObject);

    if (Option_isSome(stringObjectOption)) {
        assert(NULL == stringObject);
        stringObject = Option_unwrap(stringObjectOption);
        *ref = NULL;
        return Option_new(stringObject->raw);
    } else {
        assert(NULL != stringObject);
        return None;
    }
}

size_t
kit_String_size(kit_String self) {
    assert(self);
    kit_String_assertValidInstance(self);

    struct kit_String_Object *stringObject = ((struct kit_String_Object *) self) - 1;
    return stringObject->size;
}

size_t
kit_String_capacity(kit_String self) {
    assert(self);
    kit_String_assertValidInstance(self);

    struct kit_String_Object *stringObject = ((struct kit_String_Object *) self) - 1;
    return stringObject->capacity;
}

bool
kit_String_isEqual(kit_String self, kit_String other) {
    assert(self);
    assert(other);
    kit_String_assertValidInstance(self);
    kit_String_assertValidInstance(other);

    struct kit_String_Object *selfObject = ((struct kit_String_Object *) self) - 1;
    struct kit_String_Object *otherObject = ((struct kit_String_Object *) other) - 1;
    return (selfObject->size == otherObject->size) && (0 == memcmp(self, other, selfObject->size));
}

bool
kit_String_isEmpty(kit_String self) {
    assert(self);
    kit_String_assertValidInstance(self);

    struct kit_String_Object *selfObject = ((struct kit_String_Object *) self) - 1;
    return 0 == selfObject->size;
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
OptionOf(struct kit_String_Object *)
kit_String_Object_new(const size_t capacityHint) {
    struct kit_String_Object *stringObject;
    const size_t capacity = capacityHint > KIT_STRING_DEFAULT_CAPACITY ? capacityHint : KIT_STRING_DEFAULT_CAPACITY;
    Option stringObjectOption = kit_Allocator_malloc(sizeof(*stringObject) + capacity + 1);

    if (Option_isSome(stringObjectOption)) {
        stringObject = Option_unwrap(stringObjectOption);
        stringObject->size = 0;
        stringObject->capacity = capacity;
#ifndef NDEBUG
        stringObject->identityCode = KIT_STRING_IDENTITY_CODE;
#endif
        stringObject->raw[0] = stringObject->raw[capacity] = '\0';
    }

    return stringObjectOption;
}

OptionOf(struct kit_String_Object *)
kit_String_Object_reserve(struct kit_String_Object **const ref, const size_t capacity) {
    assert(ref);
    assert(*ref);

    struct kit_String_Object *stringObject = *ref;

    if (stringObject->capacity < capacity) {
        const size_t newCapacity = (capacity - stringObject->capacity > KIT_STRING_MINIMUM_RESERVATION) ?
                                   capacity : stringObject->capacity + KIT_STRING_MINIMUM_RESERVATION;
        Option stringObjectOption = kit_Allocator_ralloc(stringObject, sizeof(*stringObject) + newCapacity + 1);
        if (Option_isSome(stringObjectOption)) {
            stringObject = Option_unwrap(stringObjectOption);
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
        Option stringObjectOption = kit_Allocator_ralloc(stringObject, sizeof(*stringObject) + newCapacity + 1);
        if (Option_isSome(stringObjectOption)) {
            stringObject = Option_unwrap(stringObjectOption);
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

#ifndef NDEBUG

void
__kit_String_assertValidInstance(const char *const file, const size_t line, kit_String string) {
    assert(file);
    assert(string);
    const struct kit_String_Object *stringObject = ((struct kit_String_Object *) string) - 1;

    if (stringObject->identityCode != KIT_STRING_IDENTITY_CODE) {
        _(Option_expect(None, "Expected a valid string instance.\n%s:%zu", file, line));
    }
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
}

#endif
