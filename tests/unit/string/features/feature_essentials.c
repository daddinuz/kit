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

#define I(x)    ImmutableOption_unwrap((x))

FeatureDefine(StringNew) {
    (void) traits_context;

    kit_String sut = NULL;

    {
        sut = I(kit_String_new(KIT_STRING_DEFAULT_CAPACITY - 1));
        assert_not_null(sut);
        assert_string_equal("", sut);
        assert_equal(0, kit_String_size(sut));
        assert_equal(KIT_STRING_DEFAULT_CAPACITY, kit_String_capacity(sut));
    }

    kit_String_delete(sut);

    {
        sut = I(kit_String_new(KIT_STRING_DEFAULT_CAPACITY));
        assert_not_null(sut);
        assert_string_equal("", sut);
        assert_equal(0, kit_String_size(sut));
        assert_equal(KIT_STRING_DEFAULT_CAPACITY, kit_String_capacity(sut));
    }

    kit_String_delete(sut);

    {
        sut = I(kit_String_new(KIT_STRING_DEFAULT_CAPACITY + 1));
        assert_not_null(sut);
        assert_string_equal("", sut);
        assert_equal(0, kit_String_size(sut));
        assert_equal(KIT_STRING_DEFAULT_CAPACITY + 1, kit_String_capacity(sut));
    }

    kit_String_delete(sut);
}

FeatureDefine(StringQuoted) {
    (void) traits_context;

    kit_String sut = NULL;

    {
        const char BYTES[] = "\a\b\n\r\t\\\"\0abc123!";
        const char EXPECTED[] = "\"\\a\\b\\n\\r\\t\\\\\\\"\\x00abc123!\"";
        const size_t BYTES_SIZE = sizeof(BYTES) - 1;
        const size_t EXPECTED_SIZE = sizeof(EXPECTED) - 1;
        const size_t EXPECTED_CAPACITY = (EXPECTED_SIZE > KIT_STRING_DEFAULT_CAPACITY) ? EXPECTED_SIZE
                                                                                       : KIT_STRING_DEFAULT_CAPACITY;

        sut = I(kit_String_quoted(BYTES, BYTES_SIZE));
        assert_not_null(sut);
        assert_string_equal(EXPECTED, sut);
        assert_equal(EXPECTED_SIZE, kit_String_size(sut));
        assert_equal(EXPECTED_CAPACITY, kit_String_capacity(sut));
    }

    kit_String_delete(sut);

    {
        const char BYTES[] = "\0\a\b\n\r\t\\\"\0abc123!\0";
        const char EXPECTED[] = "\"\\x00\\a\\b\\n\\r\\t\\\\\\\"\\x00abc123!\\x00\"";
        const size_t BYTES_SIZE = sizeof(BYTES) - 1;
        const size_t EXPECTED_SIZE = sizeof(EXPECTED) - 1;
        const size_t EXPECTED_CAPACITY = (EXPECTED_SIZE > KIT_STRING_DEFAULT_CAPACITY) ? EXPECTED_SIZE
                                                                                       : KIT_STRING_DEFAULT_CAPACITY;

        sut = I(kit_String_quoted(BYTES, BYTES_SIZE));
        assert_not_null(sut);
        assert_string_equal(EXPECTED, sut);
        assert_equal(EXPECTED_SIZE, kit_String_size(sut));
        assert_equal(EXPECTED_CAPACITY, kit_String_capacity(sut));
    }

    kit_String_delete(sut);

    {
        const char BYTES[] = "\0\\\"\a\b\n\r\t\t\r\n\b\a\"\\\0ABC\0\\\"\a\b\n\r\t\t\r\n\b\a\"\\\0DEF\0\\\"\a\b\n\r\t\t\r\n\b\a\"\\\0GHI\0\\\"\a\b\n\r\t\t\r\n\b\a\"\\\0LMN\0\\\"\a\b\n\r\t\t\r\n\b\a\"\\\0OPQ\0\\\"\a\b\n\r\t\t\r\n\b\a\"\\\0RST\0\\\"\a\b\n\r\t\t\r\n\b\a\"\\\0UVZ\0\\\"\a\b\n\r\t\t\r\n\b\a\"\\\0";
        const char EXPECTED[] = "\"\\x00\\\\\\\"\\a\\b\\n\\r\\t\\t\\r\\n\\b\\a\\\"\\\\\\x00ABC\\x00\\\\\\\"\\a\\b\\n\\r\\t\\t\\r\\n\\b\\a\\\"\\\\\\x00DEF\\x00\\\\\\\"\\a\\b\\n\\r\\t\\t\\r\\n\\b\\a\\\"\\\\\\x00GHI\\x00\\\\\\\"\\a\\b\\n\\r\\t\\t\\r\\n\\b\\a\\\"\\\\\\x00LMN\\x00\\\\\\\"\\a\\b\\n\\r\\t\\t\\r\\n\\b\\a\\\"\\\\\\x00OPQ\\x00\\\\\\\"\\a\\b\\n\\r\\t\\t\\r\\n\\b\\a\\\"\\\\\\x00RST\\x00\\\\\\\"\\a\\b\\n\\r\\t\\t\\r\\n\\b\\a\\\"\\\\\\x00UVZ\\x00\\\\\\\"\\a\\b\\n\\r\\t\\t\\r\\n\\b\\a\\\"\\\\\\x00\"";
        const size_t BYTES_SIZE = sizeof(BYTES) - 1;
        const size_t EXPECTED_SIZE = sizeof(EXPECTED) - 1;
        const size_t EXPECTED_CAPACITY = (EXPECTED_SIZE > KIT_STRING_DEFAULT_CAPACITY) ? EXPECTED_SIZE
                                                                                       : KIT_STRING_DEFAULT_CAPACITY;

        sut = I(kit_String_quoted(BYTES, BYTES_SIZE));
        assert_not_null(sut);
        assert_string_equal(EXPECTED, sut);
        assert_equal(EXPECTED_SIZE, kit_String_size(sut));
        assert_equal(EXPECTED_CAPACITY, kit_String_capacity(sut));
    }

    kit_String_delete(sut);
}
