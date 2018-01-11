/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   December 15, 2017 
 */

#include <traits/traits.h>
#include <features/feature_expandable.h>
#include <kit/collections/string.h.old>

#define I(x)    ImmutableOption_unwrap((x))

FeatureDefine(StringReserve) {
    (void) traits_context;

    kit_String sut;

    {
        const char LITERAL[] = "";
        const size_t LITERAL_SIZE = sizeof(LITERAL) - 1;

        sut = I(kit_String_fromLiteral(LITERAL));
        assert_not_null(sut);
        assert_string_equal(sut, LITERAL);
        assert_true(kit_String_isEmpty(sut));
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);

        ImmutableOption option = kit_String_reserve(
                &sut, KIT_STRING_DEFAULT_CAPACITY - 1
        );
        assert_true(ImmutableOption_isSome(option));
        assert_null(sut);

        sut = ImmutableOption_unwrap(option);
        assert_string_equal(sut, LITERAL);
        assert_true(kit_String_isEmpty(sut));
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);
    }

    kit_String_delete(sut);

    {
        const char LITERAL[] = "";
        const size_t LITERAL_SIZE = sizeof(LITERAL) - 1;

        sut = I(kit_String_fromLiteral(LITERAL));
        assert_not_null(sut);
        assert_string_equal(sut, LITERAL);
        assert_true(kit_String_isEmpty(sut));
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);

        ImmutableOption option = kit_String_reserve(
                &sut, KIT_STRING_DEFAULT_CAPACITY + KIT_STRING_MINIMUM_RESERVATION - 1
        );
        assert_true(ImmutableOption_isSome(option));
        assert_null(sut);

        sut = ImmutableOption_unwrap(option);
        assert_string_equal(sut, LITERAL);
        assert_true(kit_String_isEmpty(sut));
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY + KIT_STRING_MINIMUM_RESERVATION);
    }

    kit_String_delete(sut);

    {
        const char LITERAL[] = "";
        const size_t LITERAL_SIZE = sizeof(LITERAL) - 1;

        sut = I(kit_String_fromLiteral(LITERAL));
        assert_not_null(sut);
        assert_string_equal(sut, LITERAL);
        assert_true(kit_String_isEmpty(sut));
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);

        ImmutableOption option = kit_String_reserve(
                &sut, KIT_STRING_DEFAULT_CAPACITY + KIT_STRING_MINIMUM_RESERVATION + 1
        );
        assert_true(ImmutableOption_isSome(option));
        assert_null(sut);

        sut = ImmutableOption_unwrap(option);
        assert_string_equal(sut, LITERAL);
        assert_true(kit_String_isEmpty(sut));
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY + KIT_STRING_MINIMUM_RESERVATION + 1);
    }

    kit_String_delete(sut);

    {
        const char LITERAL[] = "Hello World!\n";
        const size_t LITERAL_SIZE = sizeof(LITERAL) - 1;

        sut = I(kit_String_fromLiteral(LITERAL));
        assert_not_null(sut);
        assert_string_equal(sut, LITERAL);
        assert_false(kit_String_isEmpty(sut));
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);

        ImmutableOption option = kit_String_reserve(
                &sut, KIT_STRING_DEFAULT_CAPACITY + KIT_STRING_MINIMUM_RESERVATION - 1
        );
        assert_true(ImmutableOption_isSome(option));
        assert_null(sut);

        sut = ImmutableOption_unwrap(option);
        assert_string_equal(sut, LITERAL);
        assert_false(kit_String_isEmpty(sut));
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY + KIT_STRING_MINIMUM_RESERVATION);
    }

    kit_String_delete(sut);

    {
        const char LITERAL[] = "Hello World!\n";
        const size_t LITERAL_SIZE = sizeof(LITERAL) - 1;

        sut = I(kit_String_fromLiteral(LITERAL));
        assert_not_null(sut);
        assert_string_equal(sut, LITERAL);
        assert_false(kit_String_isEmpty(sut));
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);

        ImmutableOption option = kit_String_reserve(
                &sut, KIT_STRING_DEFAULT_CAPACITY + KIT_STRING_MINIMUM_RESERVATION + 1
        );
        assert_true(ImmutableOption_isSome(option));
        assert_null(sut);

        sut = ImmutableOption_unwrap(option);
        assert_string_equal(sut, LITERAL);
        assert_false(kit_String_isEmpty(sut));
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY + KIT_STRING_MINIMUM_RESERVATION + 1);
    }

    kit_String_delete(sut);
}

FeatureDefine(StringShrink) {
    (void) traits_context;

    kit_String sut;

    {
        const char LITERAL[] = "";
        const size_t LITERAL_SIZE = sizeof(LITERAL) - 1;

        sut = I(kit_String_fromLiteral(LITERAL));
        assert_not_null(sut);
        assert_string_equal(sut, LITERAL);
        assert_true(kit_String_isEmpty(sut));
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);

        ImmutableOption option = kit_String_shrink(&sut);
        assert_true(ImmutableOption_isSome(option));
        assert_null(sut);

        sut = ImmutableOption_unwrap(option);
        assert_string_equal(sut, LITERAL);
        assert_true(kit_String_isEmpty(sut));
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);
    }

    kit_String_delete(sut);

    {
        const char LITERAL[] = "Hello Wold!\n";
        const size_t LITERAL_SIZE = sizeof(LITERAL) - 1;

        sut = I(kit_String_fromLiteral(LITERAL));
        assert_not_null(sut);
        assert_string_equal(sut, LITERAL);
        assert_false(kit_String_isEmpty(sut));
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);

        ImmutableOption option = kit_String_shrink(&sut);
        assert_true(ImmutableOption_isSome(option));
        assert_null(sut);

        sut = ImmutableOption_unwrap(option);
        assert_string_equal(sut, LITERAL);
        assert_false(kit_String_isEmpty(sut));
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);
    }

    kit_String_delete(sut);

    {
        const char LITERAL[] = "Hello Wold!\n";
        const size_t LITERAL_SIZE = sizeof(LITERAL) - 1;

        sut = I(kit_String_fromLiteral(LITERAL));
        assert_not_null(sut);
        assert_string_equal(sut, LITERAL);
        assert_false(kit_String_isEmpty(sut));
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);

        ImmutableOption option = kit_String_reserve(
                &sut, KIT_STRING_DEFAULT_CAPACITY + KIT_STRING_MINIMUM_RESERVATION + 1
        );
        assert_true(ImmutableOption_isSome(option));
        assert_null(sut);

        sut = ImmutableOption_unwrap(option);
        assert_string_equal(sut, LITERAL);
        assert_false(kit_String_isEmpty(sut));
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY + KIT_STRING_MINIMUM_RESERVATION + 1);

        option = kit_String_shrink(&sut);
        assert_true(ImmutableOption_isSome(option));
        assert_null(sut);

        sut = ImmutableOption_unwrap(option);
        assert_string_equal(sut, LITERAL);
        assert_false(kit_String_isEmpty(sut));
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);
    }

    kit_String_delete(sut);
}
