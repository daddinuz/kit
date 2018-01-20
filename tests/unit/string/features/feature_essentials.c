/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   December 12, 2017 
 */

#include <traits/traits.h>
#include <features/feature_essentials.h>
#include <kit/collections/string.h>

#define u(x)    Option_unwrap((x))

FeatureDefine(StringNew) {
    (void) traits_context;

    kit_String sut = NULL;

    {
        sut = u(kit_String_new(0));
        assert_not_null(sut);
        assert_string_equal("", sut);
        assert_equal(kit_String_size(sut), 0);
        assert_true(kit_String_isEmpty(sut));
        assert_equal(KIT_STRING_DEFAULT_CAPACITY, kit_String_capacity(sut));
    }

    kit_String_delete(sut);

    {
        sut = u(kit_String_new(KIT_STRING_DEFAULT_CAPACITY - 1));
        assert_not_null(sut);
        assert_string_equal("", sut);
        assert_equal(kit_String_size(sut), 0);
        assert_true(kit_String_isEmpty(sut));
        assert_equal(KIT_STRING_DEFAULT_CAPACITY, kit_String_capacity(sut));
    }

    kit_String_delete(sut);

    {
        sut = u(kit_String_new(KIT_STRING_DEFAULT_CAPACITY));
        assert_not_null(sut);
        assert_string_equal("", sut);
        assert_equal(kit_String_size(sut), 0);
        assert_true(kit_String_isEmpty(sut));
        assert_equal(KIT_STRING_DEFAULT_CAPACITY, kit_String_capacity(sut));
    }

    kit_String_delete(sut);

    {
        sut = u(kit_String_new(KIT_STRING_DEFAULT_CAPACITY + 1));
        assert_not_null(sut);
        assert_string_equal("", sut);
        assert_equal(kit_String_size(sut), 0);
        assert_true(kit_String_isEmpty(sut));
        assert_equal(KIT_STRING_DEFAULT_CAPACITY + 1, kit_String_capacity(sut));
    }

    kit_String_delete(sut);
}

FeatureDefine(StringQuoted) {
    (void) traits_context;

    kit_String sut = NULL;

    {
        const char BYTES[] = "";
        const char EXPECTED[] = "\"\"";
        const size_t BYTES_SIZE = 0;
        const size_t EXPECTED_SIZE = sizeof(EXPECTED) - 1;
        const size_t EXPECTED_CAPACITY = KIT_STRING_DEFAULT_CAPACITY;

        sut = u(kit_String_quoted(BYTES, BYTES_SIZE));
        assert_not_null(sut);
        assert_string_equal(sut, EXPECTED);
        assert_equal(kit_String_size(sut), EXPECTED_SIZE);
        assert_false(kit_String_isEmpty(sut));
        assert_greater_equal(kit_String_capacity(sut), EXPECTED_CAPACITY);
    }

    kit_String_delete(sut);

    {
        const char BYTES[] = "\a\b\n\r\t\\\"\0abc123!";
        const char EXPECTED[] = "\"\\a\\b\\n\\r\\t\\\\\\\"\\x00abc123!\"";
        const size_t BYTES_SIZE = sizeof(BYTES) - 1;
        const size_t EXPECTED_SIZE = sizeof(EXPECTED) - 1;
        assert_less(EXPECTED_SIZE, KIT_STRING_DEFAULT_CAPACITY);
        const size_t EXPECTED_CAPACITY = KIT_STRING_DEFAULT_CAPACITY;

        sut = u(kit_String_quoted(BYTES, BYTES_SIZE));
        assert_not_null(sut);
        assert_string_equal(sut, EXPECTED);
        assert_equal(kit_String_size(sut), EXPECTED_SIZE);
        assert_false(kit_String_isEmpty(sut));
        assert_greater_equal(kit_String_capacity(sut), EXPECTED_CAPACITY);
    }

    kit_String_delete(sut);

    {
        const char BYTES[] = "\0\a\b\n\r\t\\\"\0abc123!\0";
        const char EXPECTED[] = "\"\\x00\\a\\b\\n\\r\\t\\\\\\\"\\x00abc123!\\x00\"";
        const size_t BYTES_SIZE = sizeof(BYTES) - 1;
        const size_t EXPECTED_SIZE = sizeof(EXPECTED) - 1;
        assert_less(EXPECTED_SIZE, KIT_STRING_DEFAULT_CAPACITY);
        const size_t EXPECTED_CAPACITY = KIT_STRING_DEFAULT_CAPACITY;

        sut = u(kit_String_quoted(BYTES, BYTES_SIZE));
        assert_not_null(sut);
        assert_string_equal(sut, EXPECTED);
        assert_equal(kit_String_size(sut), EXPECTED_SIZE);
        assert_false(kit_String_isEmpty(sut));
        assert_greater_equal(kit_String_capacity(sut), EXPECTED_CAPACITY);
    }

    kit_String_delete(sut);

    {
        const char BYTES[] = "\0\\\"\a\b\n\r\t\t\r\n\b\a\"\\\0ABC\0\\\"\a\b\n\r\t\t\r\n\b\a\"\\\0DEF\0\\\"\a\b\n\r\t\t\r\n\b\a\"\\\0GHI\0\\\"\a\b\n\r\t\t\r\n\b\a\"\\\0LMN\0\\\"\a\b\n\r\t\t\r\n\b\a\"\\\0OPQ\0\\\"\a\b\n\r\t\t\r\n\b\a\"\\\0RST\0\\\"\a\b\n\r\t\t\r\n\b\a\"\\\0UVZ\0\\\"\a\b\n\r\t\t\r\n\b\a\"\\\0";
        const char EXPECTED[] = "\"\\x00\\\\\\\"\\a\\b\\n\\r\\t\\t\\r\\n\\b\\a\\\"\\\\\\x00ABC\\x00\\\\\\\"\\a\\b\\n\\r\\t\\t\\r\\n\\b\\a\\\"\\\\\\x00DEF\\x00\\\\\\\"\\a\\b\\n\\r\\t\\t\\r\\n\\b\\a\\\"\\\\\\x00GHI\\x00\\\\\\\"\\a\\b\\n\\r\\t\\t\\r\\n\\b\\a\\\"\\\\\\x00LMN\\x00\\\\\\\"\\a\\b\\n\\r\\t\\t\\r\\n\\b\\a\\\"\\\\\\x00OPQ\\x00\\\\\\\"\\a\\b\\n\\r\\t\\t\\r\\n\\b\\a\\\"\\\\\\x00RST\\x00\\\\\\\"\\a\\b\\n\\r\\t\\t\\r\\n\\b\\a\\\"\\\\\\x00UVZ\\x00\\\\\\\"\\a\\b\\n\\r\\t\\t\\r\\n\\b\\a\\\"\\\\\\x00\"";
        const size_t BYTES_SIZE = sizeof(BYTES) - 1;
        const size_t EXPECTED_SIZE = sizeof(EXPECTED) - 1;
        assert_greater(EXPECTED_SIZE, KIT_STRING_DEFAULT_CAPACITY);
        const size_t EXPECTED_CAPACITY = EXPECTED_SIZE;

        sut = u(kit_String_quoted(BYTES, BYTES_SIZE));
        assert_not_null(sut);
        assert_string_equal(sut, EXPECTED);
        assert_equal(kit_String_size(sut), EXPECTED_SIZE);
        assert_false(kit_String_isEmpty(sut));
        assert_greater_equal(kit_String_capacity(sut), EXPECTED_CAPACITY);
    }

    kit_String_delete(sut);
}

FeatureDefine(StringFromBytes) {
    (void) traits_context;

    kit_String sut = NULL;

    {
        const char BYTES[] = "";
        const size_t BYTES_SIZE = sizeof(BYTES) - 1;
        const size_t EXPECTED_CAPACITY = KIT_STRING_DEFAULT_CAPACITY;

        sut = u(kit_String_fromBytes(BYTES, BYTES_SIZE));
        assert_not_null(sut);
        assert_equal(kit_String_size(sut), BYTES_SIZE);
        assert_true(kit_String_isEmpty(sut));
        assert_equal(0, memcmp(BYTES, sut, BYTES_SIZE));
        assert_greater_equal(kit_String_capacity(sut), EXPECTED_CAPACITY);
    }

    kit_String_delete(sut);

    {
        const char BYTES[] = "\a\b\n\r\t\\\"\0abc123!";
        const size_t BYTES_SIZE = sizeof(BYTES) - 1;
        assert_less(BYTES_SIZE, KIT_STRING_DEFAULT_CAPACITY);
        const size_t EXPECTED_CAPACITY = KIT_STRING_DEFAULT_CAPACITY;

        sut = u(kit_String_fromBytes(BYTES, BYTES_SIZE));
        assert_not_null(sut);
        assert_equal(kit_String_size(sut), BYTES_SIZE);
        assert_false(kit_String_isEmpty(sut));
        assert_equal(0, memcmp(BYTES, sut, BYTES_SIZE));
        assert_greater_equal(kit_String_capacity(sut), EXPECTED_CAPACITY);
    }

    kit_String_delete(sut);

    {
        const char BYTES[] = "\0\\\"\a\b\n\r\t\t\r\n\b\a\"\\\0ABC\0\\\"\a\b\n\r\t\t\r\n\b\a\"\\\0DEF\0\\\"\a\b\n\r\t\t\r\n\b\a\"\\\0GHI\0\\\"\a\b\n\r\t\t\r\n\b\a\"\\\0LMN\0\\\"\a\b\n\r\t\t\r\n\b\a\"\\\0OPQ\0\\\"\a\b\n\r\t\t\r\n\b\a\"\\\0RST\0\\\"\a\b\n\r\t\t\r\n\b\a\"\\\0UVZ\0\\\"\a\b\n\r\t\t\r\n\b\a\"\\\0";
        const size_t BYTES_SIZE = sizeof(BYTES) - 1;
        assert_greater(BYTES_SIZE, KIT_STRING_DEFAULT_CAPACITY);
        const size_t EXPECTED_CAPACITY = BYTES_SIZE;

        sut = u(kit_String_fromBytes(BYTES, BYTES_SIZE));
        assert_not_null(sut);
        assert_equal(kit_String_size(sut), BYTES_SIZE);
        assert_false(kit_String_isEmpty(sut));
        assert_equal(0, memcmp(BYTES, sut, BYTES_SIZE));
        assert_greater_equal(kit_String_capacity(sut), EXPECTED_CAPACITY);
    }

    kit_String_delete(sut);
}

FeatureDefine(StringFromFormat) {
    (void) traits_context;

    kit_String sut = NULL;

    {
#define FORMAT      "Hello World!"

        char EXPECTED[1024];
        snprintf(EXPECTED, sizeof(EXPECTED) - 1, FORMAT);
        const size_t EXPECTED_SIZE = strlen(EXPECTED);
        assert_less(EXPECTED_SIZE, KIT_STRING_DEFAULT_CAPACITY);
        const size_t EXPECTED_CAPACITY = KIT_STRING_DEFAULT_CAPACITY;

        sut = u(kit_String_fromFormat(FORMAT));
        assert_not_null(sut);
        assert_string_equal(sut, EXPECTED);
        assert_equal(kit_String_size(sut), EXPECTED_SIZE);
        assert_false(kit_String_isEmpty(sut));
        assert_greater_equal(kit_String_capacity(sut), EXPECTED_CAPACITY);

#undef FORMAT
    }

    kit_String_delete(sut);

    {
#define FORMAT      "%s", ""

        char EXPECTED[1024];
        snprintf(EXPECTED, sizeof(EXPECTED) - 1, FORMAT);
        const size_t EXPECTED_SIZE = strlen(EXPECTED);
        assert_less(EXPECTED_SIZE, KIT_STRING_DEFAULT_CAPACITY);
        const size_t EXPECTED_CAPACITY = KIT_STRING_DEFAULT_CAPACITY;

        sut = u(kit_String_fromFormat(FORMAT));
        assert_not_null(sut);
        assert_string_equal(sut, EXPECTED);
        assert_equal(kit_String_size(sut), EXPECTED_SIZE);
        assert_true(kit_String_isEmpty(sut));
        assert_greater_equal(kit_String_capacity(sut), EXPECTED_CAPACITY);

#undef FORMAT
    }

    kit_String_delete(sut);

    {
#define FORMAT      "%s%c%s!%c", "Hello", ' ', "World", '\n'

        char EXPECTED[1024];
        snprintf(EXPECTED, sizeof(EXPECTED) - 1, FORMAT);
        const size_t EXPECTED_SIZE = strlen(EXPECTED);
        assert_less(EXPECTED_SIZE, KIT_STRING_DEFAULT_CAPACITY);
        const size_t EXPECTED_CAPACITY = KIT_STRING_DEFAULT_CAPACITY;

        sut = u(kit_String_fromFormat(FORMAT));
        assert_not_null(sut);
        assert_string_equal(sut, EXPECTED);
        assert_equal(kit_String_size(sut), EXPECTED_SIZE);
        assert_false(kit_String_isEmpty(sut));
        assert_greater_equal(kit_String_capacity(sut), EXPECTED_CAPACITY);

#undef FORMAT
    }

    kit_String_delete(sut);

    {
#define FORMAT      "%*s %20d %-15zu %.5f %Lf %p %c", 25, "AaA", -543532, 629870197LU, 98763.4865f, 98739847.4L, NULL, '!'

        char EXPECTED[1024];
        snprintf(EXPECTED, sizeof(EXPECTED) - 1, FORMAT);
        const size_t EXPECTED_SIZE = strlen(EXPECTED);
        assert_less(EXPECTED_SIZE, KIT_STRING_DEFAULT_CAPACITY);
        const size_t EXPECTED_CAPACITY = KIT_STRING_DEFAULT_CAPACITY;

        sut = u(kit_String_fromFormat(FORMAT));
        assert_not_null(sut);
        assert_string_equal(sut, EXPECTED);
        assert_equal(kit_String_size(sut), EXPECTED_SIZE);
        assert_false(kit_String_isEmpty(sut));
        assert_greater_equal(kit_String_capacity(sut), EXPECTED_CAPACITY);

#undef FORMAT
    }

    kit_String_delete(sut);

    {
#define FORMAT      "%*s %20d %-15zu %.5f %Lf %p %0*i", 25, "AaA", -543532, 629870197LU, 98763.4865f, 98739847.4L, NULL, 35, 0

        char EXPECTED[1024];
        snprintf(EXPECTED, sizeof(EXPECTED) - 1, FORMAT);
        const size_t EXPECTED_SIZE = strlen(EXPECTED);
        assert_greater(EXPECTED_SIZE, KIT_STRING_DEFAULT_CAPACITY);
        const size_t EXPECTED_CAPACITY = EXPECTED_SIZE;

        sut = u(kit_String_fromFormat(FORMAT));
        assert_not_null(sut);
        assert_string_equal(sut, EXPECTED);
        assert_equal(kit_String_size(sut), EXPECTED_SIZE);
        assert_false(kit_String_isEmpty(sut));
        assert_greater_equal(EXPECTED_CAPACITY, kit_String_capacity(sut));

#undef FORMAT
    }

    kit_String_delete(sut);
}

FeatureDefine(StringFromLiteral) {
    (void) traits_context;

    kit_String sut = NULL;

    {
        const char LITERAL[] = "";
        const size_t LITERAL_SIZE = sizeof(LITERAL) - 1;
        const size_t EXPECTED_CAPACITY = KIT_STRING_DEFAULT_CAPACITY;

        sut = u(kit_String_fromLiteral(LITERAL));
        assert_not_null(sut);
        assert_string_equal(sut, LITERAL);
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_true(kit_String_isEmpty(sut));
        assert_greater_equal(kit_String_capacity(sut), EXPECTED_CAPACITY);
    }

    kit_String_delete(sut);

    {
        const char LITERAL[] = "Hello World!\n";
        const size_t LITERAL_SIZE = strlen(LITERAL);
        assert_equal(sizeof(LITERAL) - 1, LITERAL_SIZE);
        assert_less(LITERAL_SIZE, KIT_STRING_DEFAULT_CAPACITY);
        const size_t EXPECTED_CAPACITY = KIT_STRING_DEFAULT_CAPACITY;

        sut = u(kit_String_fromLiteral(LITERAL));
        assert_not_null(sut);
        assert_string_equal(sut, LITERAL);
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_false(kit_String_isEmpty(sut));
        assert_greater_equal(kit_String_capacity(sut), EXPECTED_CAPACITY);
    }

    kit_String_delete(sut);

    {
        const char LITERAL[] = "\0Hello World!\n";
        const size_t LITERAL_SIZE = strlen(LITERAL);
        assert_equal(0, LITERAL_SIZE);
        assert_less(LITERAL_SIZE, KIT_STRING_DEFAULT_CAPACITY);
        const size_t EXPECTED_CAPACITY = KIT_STRING_DEFAULT_CAPACITY;

        sut = u(kit_String_fromLiteral(LITERAL));
        assert_not_null(sut);
        assert_string_equal(sut, LITERAL);
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_true(kit_String_isEmpty(sut));
        assert_greater_equal(kit_String_capacity(sut), EXPECTED_CAPACITY);
    }

    kit_String_delete(sut);

    {
        const char LITERAL[] = "Hello\0World!\n";
        const size_t LITERAL_SIZE = strlen(LITERAL);
        traits_assert(0 < LITERAL_SIZE && LITERAL_SIZE < sizeof(LITERAL) - 1);
        assert_less(LITERAL_SIZE, KIT_STRING_DEFAULT_CAPACITY);
        const size_t EXPECTED_CAPACITY = KIT_STRING_DEFAULT_CAPACITY;

        sut = u(kit_String_fromLiteral(LITERAL));
        assert_not_null(sut);
        assert_string_equal(sut, LITERAL);
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_false(kit_String_isEmpty(sut));
        assert_greater_equal(kit_String_capacity(sut), EXPECTED_CAPACITY);
    }

    kit_String_delete(sut);

    {
        const char LITERAL[] = \
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "\0"
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum ";

        const size_t LITERAL_SIZE = strlen(LITERAL);
        traits_assert(KIT_STRING_DEFAULT_CAPACITY < LITERAL_SIZE && LITERAL_SIZE < sizeof(LITERAL) - 1);
        const size_t EXPECTED_CAPACITY = LITERAL_SIZE;

        sut = u(kit_String_fromLiteral(LITERAL));
        assert_not_null(sut);
        assert_string_equal(sut, LITERAL);
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_false(kit_String_isEmpty(sut));
        assert_greater_equal(kit_String_capacity(sut), EXPECTED_CAPACITY);
    }

    kit_String_delete(sut);

    {
        const char LITERAL[] = \
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum ";

        const size_t LITERAL_SIZE = strlen(LITERAL);
        traits_assert(KIT_STRING_DEFAULT_CAPACITY < LITERAL_SIZE && LITERAL_SIZE == sizeof(LITERAL) - 1);
        const size_t EXPECTED_CAPACITY = LITERAL_SIZE;

        sut = u(kit_String_fromLiteral(LITERAL));
        assert_not_null(sut);
        assert_string_equal(sut, LITERAL);
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_false(kit_String_isEmpty(sut));
        assert_greater_equal(kit_String_capacity(sut), EXPECTED_CAPACITY);
    }

    kit_String_delete(sut);
}

FeatureDefine(StringDuplicate) {
    (void) traits_context;

    kit_String sut = NULL;

    {
        kit_String string = u(kit_String_fromLiteral(""));
        sut = u(kit_String_duplicate(string));

        assert_not_equal(sut, string);
        assert_string_equal(sut, string);
        assert_equal(kit_String_size(sut), kit_String_size(string));
        assert_less_equal(kit_String_capacity(sut), kit_String_capacity(string));
        assert_greater_equal(kit_String_capacity(sut), kit_String_size(sut));

        kit_String_delete(string);
    }

    kit_String_delete(sut);

    {
        kit_String string = u(kit_String_fromLiteral("Hello World!"));
        sut = u(kit_String_duplicate(string));

        assert_not_equal(sut, string);
        assert_string_equal(sut, string);
        assert_equal(kit_String_size(sut), kit_String_size(string));
        assert_less_equal(kit_String_capacity(sut), kit_String_capacity(string));
        assert_greater_equal(kit_String_capacity(sut), kit_String_size(sut));

        kit_String_delete(string);
    }

    kit_String_delete(sut);

    {
        kit_String string = u(kit_String_fromLiteral("Hello\0World!"));
        sut = u(kit_String_duplicate(string));

        assert_not_equal(sut, string);
        assert_string_equal(sut, string);
        assert_equal(kit_String_size(sut), kit_String_size(string));
        assert_less_equal(kit_String_capacity(sut), kit_String_capacity(string));
        assert_greater_equal(kit_String_capacity(sut), kit_String_size(sut));

        kit_String_delete(string);
    }

    kit_String_delete(sut);

    {
        kit_String string = u(kit_String_fromLiteral("\0Hello World!"));
        sut = u(kit_String_duplicate(string));

        assert_not_equal(sut, string);
        assert_string_equal(sut, string);
        assert_equal(kit_String_size(sut), kit_String_size(string));
        assert_less_equal(kit_String_capacity(sut), kit_String_capacity(string));
        assert_greater_equal(kit_String_capacity(sut), kit_String_size(sut));

        kit_String_delete(string);
    }

    kit_String_delete(sut);

    {
        const char LITERAL[] = \
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "\0"
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum "
                "Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum Lorem Ipsum ";
        const size_t LITERAL_SIZE = strlen(LITERAL);

        kit_String string = u(kit_String_fromLiteral(LITERAL));
        sut = u(kit_String_duplicate(string));

        assert_not_equal(sut, string);
        assert_string_equal(sut, string);
        assert_equal(LITERAL_SIZE, kit_String_size(string));
        assert_equal(kit_String_size(sut), kit_String_size(string));
        assert_less_equal(kit_String_capacity(sut), kit_String_capacity(string));
        assert_greater_equal(kit_String_capacity(sut), kit_String_size(sut));

        kit_String_delete(string);
    }

    kit_String_delete(sut);

    {
        const char BYTES[] = "\a\b\t3rd3rf3f\r\n45h6ujh5ygt4\0\\\"!!@°#n9b6v6754w24qx\a55b8in\r2dd2\tdd2d2d2\075rv62df";
        kit_String string = u(kit_String_fromBytes(BYTES, sizeof(BYTES) - 1));
        sut = u(kit_String_duplicate(string));

        assert_not_equal(sut, string);
        assert_string_equal(sut, string);
        assert_equal(kit_String_size(sut), kit_String_size(string));
        assert_less_equal(kit_String_capacity(sut), kit_String_capacity(string));
        assert_greater_equal(kit_String_capacity(sut), kit_String_size(sut));

        kit_String_delete(string);
    }

    kit_String_delete(sut);

    {
        const char BYTES[] = \
                "Lorem \aIpsum \bLorem \tIpsum \nLorem \rIpsum \0Lorem \\Ipsum \"Lorem !Ipsum @Lorem \0Ipsum \aLorem "
                "Lorem \aIpsum \bLorem \tIpsum \nLorem \rIpsum \0Lorem \\Ipsum \"Lorem !Ipsum @Lorem \0Ipsum \aLorem "
                "Lorem \aIpsum \bLorem \tIpsum \nLorem \rIpsum \0Lorem \\Ipsum \"Lorem !Ipsum @Lorem \0Ipsum \aLorem "
                "Lorem \aIpsum \bLorem \tIpsum \nLorem \rIpsum \0Lorem \\Ipsum \"Lorem !Ipsum @Lorem \0Ipsum \aLorem "
                "Lorem \aIpsum \bLorem \tIpsum \nLorem \rIpsum \0Lorem \\Ipsum \"Lorem !Ipsum @Lorem \0Ipsum \aLorem "
                "Lorem \aIpsum \bLorem \tIpsum \nLorem \rIpsum \0Lorem \\Ipsum \"Lorem !Ipsum @Lorem \0Ipsum \aLorem "
                "Lorem \aIpsum \bLorem \tIpsum \nLorem \rIpsum \0Lorem \\Ipsum \"Lorem !Ipsum @Lorem \0Ipsum \aLorem "
                "Lorem \aIpsum \bLorem \tIpsum \nLorem \rIpsum \0Lorem \\Ipsum \"Lorem !Ipsum @Lorem \0Ipsum \aLorem "
                "Lorem \aIpsum \bLorem \tIpsum \nLorem \rIpsum \0Lorem \\Ipsum \"Lorem !Ipsum @Lorem \0Ipsum \aLorem "
                "Lorem \aIpsum \bLorem \tIpsum \nLorem \rIpsum \0Lorem \\Ipsum \"Lorem !Ipsum @Lorem \0Ipsum \aLorem "
                "Lorem \aIpsum \bLorem \tIpsum \nLorem \rIpsum \0Lorem \\Ipsum \"Lorem !Ipsum @Lorem \0Ipsum \aLorem "
                "Lorem \aIpsum \bLorem \tIpsum \nLorem \rIpsum \0Lorem \\Ipsum \"Lorem !Ipsum @Lorem \0Ipsum \aLorem "
                "Lorem \aIpsum \bLorem \tIpsum \nLorem \rIpsum \0Lorem \\Ipsum \"Lorem !Ipsum @Lorem \0Ipsum \aLorem "
                "Lorem \aIpsum \bLorem \tIpsum \nLorem \rIpsum \0Lorem \\Ipsum \"Lorem !Ipsum @Lorem \0Ipsum \aLorem "
                "Lorem \aIpsum \bLorem \tIpsum \nLorem \rIpsum \0Lorem \\Ipsum \"Lorem !Ipsum @Lorem \0Ipsum \aLorem "
                "Lorem \aIpsum \bLorem \tIpsum \nLorem \rIpsum \0Lorem \\Ipsum \"Lorem !Ipsum @Lorem \0Ipsum \aLorem ";
        const size_t BYTES_SIZE = sizeof(BYTES) - 1;

        kit_String string = u(kit_String_fromBytes(BYTES, BYTES_SIZE));
        sut = u(kit_String_duplicate(string));

        assert_not_equal(sut, string);
        assert_string_equal(sut, string);
        assert_equal(BYTES_SIZE, kit_String_size(string));
        assert_equal(kit_String_size(sut), kit_String_size(string));
        assert_less_equal(kit_String_capacity(sut), kit_String_capacity(string));
        assert_greater_equal(kit_String_capacity(sut), kit_String_size(sut));

        kit_String_delete(string);
    }

    kit_String_delete(sut);
}
