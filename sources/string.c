/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   December 06, 2017 
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <kit/allocator/allocator.h>
#include <kit/collections/string.h>

#define KIT_STRING_IDENTITY_CODE    ((void *) 0xDEADBEAF)
#define KIT_STRING_DEFAULT_CAPACITY 126

struct kit_String_Object {
    size_t size;
    size_t capacity;
#ifndef NDEBUG
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

static void
__kit_String_assertValidInstance(const char *file, const char *function, size_t line, kit_String string)
__attribute__((__nonnull__));

#define kit_String_assertValidInstance(x)   __kit_String_assertValidInstance(__FILE__, __func__, __LINE__, (x))

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

ImmutableOption kit_String_format(const char *format, ...) {
    assert(format);

    va_list args;
    va_start(args, format);
    const int needed = vsnprintf(NULL, 0, format, args);
    va_end(args);

    if (needed >= 0) {
        const size_t size = (size_t) needed;
        MutableOption stringObjectOption = kit_String_Object_new(size);

        if (MutableOption_isSome(stringObjectOption)) {
            struct kit_String_Object *stringObject = MutableOption_unwrap(stringObjectOption);
            va_start(args, format);
            vsnprintf(stringObject->raw, size + 1, format, args);
            va_end(args);
            stringObject->size = size;
            return ImmutableOption_new(stringObject->raw);
        }
    }

    return ImmutableOption_None;
}

ImmutableOption kit_String_fromLiteral(const char *literal) {
    assert(literal);
    return kit_String_fromBytes(literal, strlen(literal));
}

ImmutableOption kit_String_fromBytes(const void *bytes, size_t size) {
    assert(bytes);
    MutableOption stringObjectOption = kit_String_Object_new(size);

    if (MutableOption_isSome(stringObjectOption)) {
        struct kit_String_Object *stringObject = MutableOption_unwrap(stringObjectOption);
        char *raw = stringObject->raw;
        strncpy(raw, bytes, size);
        raw[size] = '\0';
        stringObject->size = size;
        return ImmutableOption_new(raw);
    }

    return ImmutableOption_None;
}

ImmutableOption kit_String_duplicate(kit_String s) {
    assert(s);
    kit_String_assertValidInstance(s);

    return kit_String_fromBytes(s, kit_String_size(s));
}

ImmutableOption kit_String_append(kit_String *ref, kit_String other) {
    assert(ref);
    assert(*ref);
    assert(other);
    assert(*ref != other);
    kit_String_assertValidInstance(*ref);
    kit_String_assertValidInstance(other);

    const struct kit_String_Object *otherObject = ((struct kit_String_Object *) other) - 1;
    return kit_String_appendBytes(ref, other, otherObject->size);
}

ImmutableOption kit_String_appendLiteral(kit_String *ref, const char *literal) {
    assert(ref);
    assert(*ref);
    assert(literal);
    assert((void *) *ref != literal);
    kit_String_assertValidInstance(*ref);

    return kit_String_appendBytes(ref, literal, strlen(literal));
}

ImmutableOption kit_String_appendBytes(kit_String *ref, const void *bytes, const size_t size) {
    assert(ref);
    assert(*ref);
    assert(bytes);
    assert((void *) *ref != bytes);
    kit_String_assertValidInstance(*ref);

    struct kit_String_Object *stringObject = ((struct kit_String_Object *) *ref) - 1;
    const size_t stringObjectSize = stringObject->size;
    MutableOption stringObjectOption = kit_String_Object_reserve(&stringObject, stringObjectSize + size);

    if (MutableOption_isSome(stringObjectOption)) {
        assert(NULL == stringObject);
        stringObject = MutableOption_unwrap(stringObjectOption);
        char *stringObjectRaw = stringObject->raw;
        strncpy(stringObjectRaw + stringObjectSize, bytes, size);
        stringObjectRaw[stringObject->size = stringObjectSize + size] = '\0';
        *ref = NULL;
        return ImmutableOption_new(stringObjectRaw);
    }

    assert(NULL != stringObject);
    return ImmutableOption_None;
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
    return (selfObject->size == otherObject->size) && (0 == strcmp(self, other));
}

bool kit_String_isEmpty(kit_String self) {
    assert(self);
    kit_String_assertValidInstance(self);

    struct kit_String_Object *selfObject = ((struct kit_String_Object *) self) - 1;
    return 0 == selfObject->size;
}

void kit_String_clear(kit_String self) {
    assert(self);
    kit_String_assertValidInstance(self);

    struct kit_String_Object *stringObject = ((struct kit_String_Object *) self) - 1;
    stringObject->raw[0] = '\0';
    stringObject->size = 0;
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
void __kit_String_assertValidInstance(const char *file, const char *function, const size_t line, kit_String string) {
    assert(string);
    (void) string;
#ifndef NDEBUG
    struct kit_String_Object *stringObject = ((struct kit_String_Object *) string) - 1;
    if (stringObject->identityCode != KIT_STRING_IDENTITY_CODE) {
        char buffer[1024] = "";
        snprintf(buffer, sizeof(buffer) - 1, "Expected a valid string instance.\n%s:%zu@%s", file, line, function);
        MutableOption_expect(MutableOption_None, buffer);
    }
#endif
}

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