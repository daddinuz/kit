/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   December 06, 2017 
 */

#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <assert.h>
#include <memory.h>
#include <kit/allocator/allocator.h>
#include <kit/collections/string.h>

struct kit_String_Object {
    size_t size;
    size_t capacity;
#ifndef NDEBUG
#define KIT_STRING_IDENTITY_CODE    ((void *) 0xDEADBEAF)
    const void *identityCode;
#endif
    char raw[];
};

static MutableOptional(struct kit_String_Object *)
kit_String_Object_new(size_t capacityHint)
__attribute__((__nonnull__));

static MutableOptional(struct kit_String_Object *)
kit_String_Object_reserve(struct kit_String_Object **ref, size_t capacity)
__attribute__((__nonnull__));

static MutableOptional(struct kit_String_Object *)
kit_String_Object_shrink(struct kit_String_Object **ref)
__attribute__((__nonnull__));

static void
kit_String_Object_delete(struct kit_String_Object *self)
__attribute__((__nonnull__));

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
ImmutableOption kit_String_new(const size_t capacityHint) {
    MutableOption stringObjectOption = kit_String_Object_new(capacityHint);

    if (MutableOption_isSome(stringObjectOption)) {
        struct kit_String_Object *stringObject = MutableOption_unwrap(stringObjectOption);
        return ImmutableOption_new(stringObject->raw);
    }

    return ImmutableOption_None;
}

ImmutableOption kit_String_quoted(const void *bytes, const size_t size) {
    assert(bytes);

    const char *data = bytes;
    kit_String string = NULL;
    bool teardownRequired = false;
    ImmutableOption stringOption = kit_String_new(size + size / 3);

    if (ImmutableOption_isNone(stringOption)) {
        return ImmutableOption_None;
    }

    string = ImmutableOption_unwrap(stringOption);
    /* if we are here we have enough space to perform this operation so no checks are performed */
    ImmutableOption_unwrap(kit_String_setBytes(&string, "\"", 1));

    for (size_t i = 0; i < size && false == teardownRequired; i++) {
        string = ImmutableOption_unwrap(stringOption);
        switch (*data) {
            case '\a': {
                stringOption = kit_String_appendBytes(&string, "\\a", 2);
                if (ImmutableOption_isNone(stringOption)) {
                    teardownRequired = true;
                }
                break;
            }
            case '\b': {
                stringOption = kit_String_appendBytes(&string, "\\b", 2);
                if (ImmutableOption_isNone(stringOption)) {
                    teardownRequired = true;
                }
                break;
            }
            case '\n': {
                stringOption = kit_String_appendBytes(&string, "\\n", 2);
                if (ImmutableOption_isNone(stringOption)) {
                    teardownRequired = true;
                }
                break;
            }
            case '\r': {
                stringOption = kit_String_appendBytes(&string, "\\r", 2);
                if (ImmutableOption_isNone(stringOption)) {
                    teardownRequired = true;
                }
                break;
            }
            case '\t': {
                stringOption = kit_String_appendBytes(&string, "\\t", 2);
                if (ImmutableOption_isNone(stringOption)) {
                    teardownRequired = true;
                }
                break;
            }
            case '\\': {
                stringOption = kit_String_appendBytes(&string, "\\\\", 2);
                if (ImmutableOption_isNone(stringOption)) {
                    teardownRequired = true;
                }
                break;
            }
            case '"': {
                stringOption = kit_String_appendBytes(&string, "\\\"", 2);
                if (ImmutableOption_isNone(stringOption)) {
                    teardownRequired = true;
                }
                break;
            }
            default: {
                if (isprint(*data)) {
                    stringOption = kit_String_appendFormat(&string, "%c", *data);
                } else {
                    stringOption = kit_String_appendFormat(&string, "\\x%02x", (unsigned char) *data);
                }
                if (ImmutableOption_isNone(stringOption)) {
                    teardownRequired = true;
                }
                break;
            }
        }
        data++;
    }

    if (false == teardownRequired) {
        assert(NULL == string);
        assert(ImmutableOption_isSome(stringOption));
        string = ImmutableOption_unwrap(stringOption);
        stringOption = kit_String_appendBytes(&string, "\"", 1);
        if (ImmutableOption_isNone(stringOption)) {
            teardownRequired = true;
        }
    }

    if (teardownRequired) {
        assert(NULL != string);
        assert(ImmutableOption_isNone(stringOption));
        kit_String_delete(string);
        string = NULL;
    } else {
        assert(NULL == string);
        assert(ImmutableOption_isSome(stringOption));
        string = ImmutableOption_unwrap(stringOption);
    }

    return ImmutableOption_new((void *) string);
}

ImmutableOption kit_String_fromPack(const char *format, va_list pack) {
    assert(format);
    assert(pack);

    va_list packCopy;

    va_copy(packCopy, pack);
    const int FORMATTED_SIZE = vsnprintf(NULL, 0, format, packCopy);
    va_end(packCopy);

    if (FORMATTED_SIZE >= 0) {
        const size_t SIZE = (size_t) FORMATTED_SIZE;
        MutableOption stringObjectOption = kit_String_Object_new(SIZE);

        if (MutableOption_isSome(stringObjectOption)) {
            struct kit_String_Object *stringObject = MutableOption_unwrap(stringObjectOption);
            vsnprintf(stringObject->raw, SIZE + 1, format, pack);
            stringObject->size = SIZE;
            return ImmutableOption_new(stringObject->raw);
        }
    }

    return ImmutableOption_None;
}

ImmutableOption kit_String_fromBytes(const void *bytes, size_t size) {
    assert(bytes);
    MutableOption stringObjectOption = kit_String_Object_new(size);

    if (MutableOption_isSome(stringObjectOption)) {
        struct kit_String_Object *stringObject = MutableOption_unwrap(stringObjectOption);
        char *raw = stringObject->raw;
        MutableOption_unwrap(kit_Allocator_copy(raw, bytes, size));
        raw[size] = '\0';
        stringObject->size = size;
        return ImmutableOption_new(raw);
    }

    return ImmutableOption_None;
}

ImmutableOption kit_String_fromFormat(const char *format, ...) {
    assert(format);

    va_list pack;

    va_start(pack, format);
    ImmutableOption result = kit_String_fromPack(format, pack);
    va_end(pack);

    return result;
}

ImmutableOption kit_String_fromLiteral(const char *literal) {
    assert(literal);

    return kit_String_fromBytes(literal, strlen(literal));
}

ImmutableOption kit_String_duplicate(kit_String s) {
    assert(s);
    kit_String_assertValidInstance(s);

    return kit_String_fromBytes(s, kit_String_size(s));
}

ImmutableOption kit_String_clear(kit_String *ref) {
    assert(ref);
    assert(*ref);
    kit_String_assertValidInstance(*ref);

    struct kit_String_Object *stringObject = ((struct kit_String_Object *) *ref) - 1;
    stringObject->raw[0] = '\0';
    stringObject->size = 0;

    *ref = NULL;
    return ImmutableOption_new(stringObject->raw);
}

ImmutableOption kit_String_append(kit_String *ref, kit_String other) {
    assert(ref);
    assert(*ref);
    assert(other);
    kit_String_assertValidInstance(*ref);
    kit_String_assertValidInstance(other);
    kit_String_assertNotOverlapping(*ref, kit_String_size(*ref), other, kit_String_size(other));

    const struct kit_String_Object *otherObject = ((struct kit_String_Object *) other) - 1;
    return kit_String_appendBytes(ref, other, otherObject->size);
}

ImmutableOption kit_String_appendPack(kit_String *ref, const char *format, va_list pack) {
    assert(ref);
    assert(*ref);
    assert(format);
    assert(pack);

    va_list packCopy;
    struct kit_String_Object *stringObject = ((struct kit_String_Object *) *ref) - 1;

    va_copy(packCopy, pack);
    const int FORMATTED_SIZE = vsnprintf(NULL, 0, format, packCopy);
    va_end(packCopy);

    if (FORMATTED_SIZE >= 0) {
        const size_t CURRENT_SIZE = stringObject->size;
        const size_t ADDITIONAL_SIZE = (size_t) FORMATTED_SIZE;
        MutableOption stringObjectOption = kit_String_Object_reserve(&stringObject, CURRENT_SIZE + ADDITIONAL_SIZE);

        if (MutableOption_isSome(stringObjectOption)) {
            stringObject = MutableOption_unwrap(stringObjectOption);
            vsnprintf(stringObject->raw + CURRENT_SIZE, ADDITIONAL_SIZE + 1, format, pack);
            stringObject->size += ADDITIONAL_SIZE;
            *ref = NULL;
            return ImmutableOption_new(stringObject->raw);
        }
    }

    return ImmutableOption_None;
}

ImmutableOption kit_String_appendBytes(kit_String *ref, const void *bytes, const size_t size) {
    assert(ref);
    assert(*ref);
    assert(bytes);
    kit_String_assertValidInstance(*ref);
    kit_String_assertNotOverlapping(*ref, kit_String_size(*ref), bytes, size);

    struct kit_String_Object *stringObject = ((struct kit_String_Object *) *ref) - 1;
    const size_t stringObjectSize = stringObject->size;
    MutableOption stringObjectOption = kit_String_Object_reserve(&stringObject, stringObjectSize + size);

    if (MutableOption_isSome(stringObjectOption)) {
        assert(NULL == stringObject);
        stringObject = MutableOption_unwrap(stringObjectOption);
        char *stringObjectRaw = stringObject->raw;
        MutableOption_unwrap(kit_Allocator_copy(stringObjectRaw + stringObjectSize, bytes, size));
        stringObjectRaw[stringObject->size = stringObjectSize + size] = '\0';
        *ref = NULL;
        return ImmutableOption_new(stringObjectRaw);
    }

    assert(NULL != stringObject);
    return ImmutableOption_None;
}

ImmutableOption kit_String_appendFormat(kit_String *ref, const char *format, ...) {
    assert(ref);
    assert(*ref);
    assert(format);

    va_list pack;

    va_start(pack, format);
    ImmutableOption result = kit_String_appendPack(ref, format, pack);
    va_end(pack);

    assert(ImmutableOption_isSome(result) ? NULL == *ref : NULL != *ref);
    return result;
}

ImmutableOption kit_String_appendLiteral(kit_String *ref, const char *literal) {
    assert(ref);
    assert(*ref);
    assert(literal);
    kit_String_assertValidInstance(*ref);

    const size_t SIZE = strlen(literal);
    kit_String_assertNotOverlapping(*ref, kit_String_size(*ref), literal, SIZE);

    return kit_String_appendBytes(ref, literal, SIZE);
}

ImmutableOption kit_String_set(kit_String *ref, kit_String other) {
    assert(ref);
    assert(*ref);
    assert(other);
    kit_String_assertValidInstance(*ref);
    kit_String_assertValidInstance(other);
    kit_String_assertNotOverlapping(*ref, kit_String_size(*ref), other, kit_String_size(other));

    const struct kit_String_Object *otherObject = ((struct kit_String_Object *) other) - 1;
    return kit_String_setBytes(ref, other, otherObject->size);
}

ImmutableOption kit_String_setPack(kit_String *ref, const char *format, va_list pack) {
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
        MutableOption stringObjectOption = kit_String_Object_reserve(&stringObject, NEW_SIZE);

        if (MutableOption_isSome(stringObjectOption)) {
            stringObject = MutableOption_unwrap(stringObjectOption);
            vsnprintf(stringObject->raw, NEW_SIZE + 1, format, pack);
            stringObject->size = NEW_SIZE;
            *ref = NULL;
            return ImmutableOption_new(stringObject->raw);
        }
    }

    return ImmutableOption_None;
}

ImmutableOption kit_String_setBytes(kit_String *ref, const void *bytes, size_t size) {
    assert(ref);
    assert(*ref);
    assert(bytes);
    kit_String_assertValidInstance(*ref);
    kit_String_assertNotOverlapping(*ref, kit_String_size(*ref), bytes, size);

    struct kit_String_Object *stringObject = ((struct kit_String_Object *) *ref) - 1;
    MutableOption stringObjectOption = kit_String_Object_reserve(&stringObject, size);

    if (MutableOption_isSome(stringObjectOption)) {
        assert(NULL == stringObject);
        stringObject = MutableOption_unwrap(stringObjectOption);
        char *stringObjectRaw = stringObject->raw;
        MutableOption_unwrap(kit_Allocator_copy(stringObjectRaw, bytes, size));
        stringObjectRaw[stringObject->size = size] = '\0';
        *ref = NULL;
        return ImmutableOption_new(stringObjectRaw);
    }

    assert(NULL != stringObject);
    return ImmutableOption_None;
}

ImmutableOption kit_String_setFormat(kit_String *ref, const char *format, ...) {
    assert(ref);
    assert(*ref);
    assert(format);

    va_list pack;

    va_start(pack, format);
    ImmutableOption result = kit_String_setPack(ref, format, pack);
    va_end(pack);

    assert(ImmutableOption_isSome(result) ? NULL == *ref : NULL != *ref);
    return result;
}

ImmutableOption kit_String_setLiteral(kit_String *ref, const char *literal) {
    assert(ref);
    assert(*ref);
    assert(literal);
    kit_String_assertValidInstance(*ref);

    const size_t SIZE = strlen(literal);
    kit_String_assertNotOverlapping(*ref, kit_String_size(*ref), literal, SIZE);

    return kit_String_setBytes(ref, literal, SIZE);
}

ImmutableOption kit_String_quote(kit_String *ref) {
    assert(ref);
    assert(*ref);
    kit_String_assertValidInstance(*ref);

    struct kit_String_Object *stringObject = ((struct kit_String_Object *) *ref) - 1;
    ImmutableOption option = kit_String_quoted(stringObject->raw, stringObject->size);

    if (ImmutableOption_isSome(option)) {
        kit_String_delete(*ref);
        *ref = NULL;
    }

    return option;
}

ImmutableOption kit_String_reserve(kit_String *ref, size_t capacity) {
    assert(ref);
    assert(*ref);
    kit_String_assertValidInstance(*ref);

    struct kit_String_Object *stringObject = ((struct kit_String_Object *) *ref) - 1;
    MutableOption stringObjectOption = kit_String_Object_reserve(&stringObject, capacity);

    if (MutableOption_isSome(stringObjectOption)) {
        assert(NULL == stringObject);
        stringObject = MutableOption_unwrap(stringObjectOption);
        *ref = NULL;
        return ImmutableOption_new(stringObject->raw);
    } else {
        assert(NULL != stringObject);
        return ImmutableOption_None;
    }
}

ImmutableOption kit_String_shrink(kit_String *ref) {
    assert(ref);
    assert(*ref);
    kit_String_assertValidInstance(*ref);

    struct kit_String_Object *stringObject = ((struct kit_String_Object *) *ref) - 1;
    MutableOption stringObjectOption = kit_String_Object_shrink(&stringObject);

    if (MutableOption_isSome(stringObjectOption)) {
        assert(NULL == stringObject);
        stringObject = MutableOption_unwrap(stringObjectOption);
        *ref = NULL;
        return ImmutableOption_new(stringObject->raw);
    } else {
        assert(NULL != stringObject);
        return ImmutableOption_None;
    }
}

size_t kit_String_size(kit_String self) {
    assert(self);
    kit_String_assertValidInstance(self);

    struct kit_String_Object *stringObject = ((struct kit_String_Object *) self) - 1;
    return stringObject->size;
}

size_t kit_String_capacity(kit_String self) {
    assert(self);
    kit_String_assertValidInstance(self);

    struct kit_String_Object *stringObject = ((struct kit_String_Object *) self) - 1;
    return stringObject->capacity;
}

bool kit_String_isEqual(kit_String self, kit_String other) {
    assert(self);
    assert(other);
    kit_String_assertValidInstance(self);
    kit_String_assertValidInstance(other);

    struct kit_String_Object *selfObject = ((struct kit_String_Object *) self) - 1;
    struct kit_String_Object *otherObject = ((struct kit_String_Object *) self) - 1;
    return (selfObject->size == otherObject->size) && (0 == memcmp(self, other, selfObject->size));
}

bool kit_String_isEmpty(kit_String self) {
    assert(self);
    kit_String_assertValidInstance(self);

    struct kit_String_Object *selfObject = ((struct kit_String_Object *) self) - 1;
    return 0 == selfObject->size;
}

void kit_String_delete(kit_String self) {
    if (self) {
        kit_String_assertValidInstance(self);
        struct kit_String_Object *stringObject = ((struct kit_String_Object *) self) - 1;
        kit_String_Object_delete(stringObject);
    }
}

/*
 *
 */
MutableOption kit_String_Object_new(const size_t capacityHint) {
    struct kit_String_Object *stringObject;
    const size_t capacity = capacityHint > KIT_STRING_DEFAULT_CAPACITY ? capacityHint : KIT_STRING_DEFAULT_CAPACITY;
    MutableOption stringObjectOption = kit_Allocator_malloc(sizeof(*stringObject) + capacity + 1);

    if (MutableOption_isSome(stringObjectOption)) {
        stringObject = MutableOption_unwrap(stringObjectOption);
        stringObject->size = 0;
        stringObject->capacity = capacity;
#ifndef NDEBUG
        stringObject->identityCode = KIT_STRING_IDENTITY_CODE;
#endif
        stringObject->raw[0] = stringObject->raw[capacity] = '\0';
    }

    return stringObjectOption;
}

MutableOption kit_String_Object_reserve(struct kit_String_Object **ref, const size_t capacity) {
    assert(ref);
    assert(*ref);

    struct kit_String_Object *stringObject = *ref;

    if (stringObject->capacity < capacity) {
        MutableOption stringObjectOption = kit_Allocator_ralloc(stringObject, sizeof(*stringObject) + capacity + 1);
        if (MutableOption_isSome(stringObjectOption)) {
            stringObject = MutableOption_unwrap(stringObjectOption);
            stringObject->capacity = capacity;
            stringObject->raw[capacity] = '\0';
        } else {
            return MutableOption_None;
        }
    }

    *ref = NULL;
    return MutableOption_new(stringObject);
}

MutableOption kit_String_Object_shrink(struct kit_String_Object **ref) {
    assert(ref);
    assert(*ref);

    struct kit_String_Object *stringObject = *ref;

    if (stringObject->capacity > KIT_STRING_DEFAULT_CAPACITY) {
        const size_t size = stringObject->size;
        const size_t newCapacity = size > KIT_STRING_DEFAULT_CAPACITY ? size : KIT_STRING_DEFAULT_CAPACITY;
        MutableOption stringObjectOption = kit_Allocator_ralloc(stringObject, sizeof(*stringObject) + newCapacity + 1);
        if (MutableOption_isSome(stringObjectOption)) {
            stringObject = MutableOption_unwrap(stringObjectOption);
            stringObject->capacity = newCapacity;
            stringObject->raw[newCapacity] = '\0';
        } else {
            return MutableOption_None;
        }
    }

    *ref = NULL;
    return MutableOption_new(stringObject);
}

void kit_String_Object_delete(struct kit_String_Object *self) {
    if (self) {
        kit_Allocator_free(self);
    }
}

#ifndef NDEBUG

void __kit_String_assertValidInstance(const char *file, const size_t line, kit_String string) {
    assert(file);
    assert(string);
    const struct kit_String_Object *stringObject = ((struct kit_String_Object *) string) - 1;

    if (stringObject->identityCode != KIT_STRING_IDENTITY_CODE) {
        char buffer[1024] = "";
        snprintf(buffer, sizeof(buffer) - 1, "Expected a valid string instance.\n%s:%zu", file, line);
        MutableOption_expect(MutableOption_None, buffer);
    }
}

void __kit_String_assertNotOverlapping(
        const char *file, const size_t line, const void *p1, const size_t s1, const void *p2, const size_t s2
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
        char buffer[1024] = "";
        snprintf(buffer, sizeof(buffer) - 1, "Expected non-overlapping strings.\n%s:%zu", file, line);
        MutableOption_expect(MutableOption_None, buffer);
    }
}

#endif
