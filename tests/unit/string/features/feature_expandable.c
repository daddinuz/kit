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

#include <traits/traits.h>
#include <features/feature_expandable.h>
#include <kit/collections/string.h>

#define u(x)    Option_unwrap((x))

FeatureDefine(StringExpand) {
    (void) traits_context;

    kit_String sut;

    {
        const char LITERAL[] = "";
        const size_t LITERAL_SIZE = sizeof(LITERAL) - 1;

        sut = u(kit_String_fromLiteral(LITERAL));
        assert_not_null(sut);
        assert_string_equal(sut, LITERAL);
        assert_true(kit_String_isEmpty(sut));
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);

        Option option = kit_String_expand(
                &sut, KIT_STRING_DEFAULT_CAPACITY - 1
        );
        assert_true(Option_isSome(option));
        assert_null(sut);

        sut = Option_unwrap(option);
        assert_string_equal(sut, LITERAL);
        assert_true(kit_String_isEmpty(sut));
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);
    }

    kit_String_delete(sut);

    {
        const char LITERAL[] = "";
        const size_t LITERAL_SIZE = sizeof(LITERAL) - 1;

        sut = u(kit_String_fromLiteral(LITERAL));
        assert_not_null(sut);
        assert_string_equal(sut, LITERAL);
        assert_true(kit_String_isEmpty(sut));
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);

        Option option = kit_String_expand(
                &sut, KIT_STRING_DEFAULT_CAPACITY + KIT_STRING_MINIMUM_RESERVATION - 1
        );
        assert_true(Option_isSome(option));
        assert_null(sut);

        sut = Option_unwrap(option);
        assert_string_equal(sut, LITERAL);
        assert_true(kit_String_isEmpty(sut));
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY + KIT_STRING_MINIMUM_RESERVATION);
    }

    kit_String_delete(sut);

    {
        const char LITERAL[] = "";
        const size_t LITERAL_SIZE = sizeof(LITERAL) - 1;

        sut = u(kit_String_fromLiteral(LITERAL));
        assert_not_null(sut);
        assert_string_equal(sut, LITERAL);
        assert_true(kit_String_isEmpty(sut));
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);

        Option option = kit_String_expand(
                &sut, KIT_STRING_DEFAULT_CAPACITY + KIT_STRING_MINIMUM_RESERVATION + 1
        );
        assert_true(Option_isSome(option));
        assert_null(sut);

        sut = Option_unwrap(option);
        assert_string_equal(sut, LITERAL);
        assert_true(kit_String_isEmpty(sut));
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY + KIT_STRING_MINIMUM_RESERVATION + 1);
    }

    kit_String_delete(sut);

    {
        const char LITERAL[] = "Hello World!\n";
        const size_t LITERAL_SIZE = sizeof(LITERAL) - 1;

        sut = u(kit_String_fromLiteral(LITERAL));
        assert_not_null(sut);
        assert_string_equal(sut, LITERAL);
        assert_false(kit_String_isEmpty(sut));
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);

        Option option = kit_String_expand(
                &sut, KIT_STRING_DEFAULT_CAPACITY + KIT_STRING_MINIMUM_RESERVATION - 1
        );
        assert_true(Option_isSome(option));
        assert_null(sut);

        sut = Option_unwrap(option);
        assert_string_equal(sut, LITERAL);
        assert_false(kit_String_isEmpty(sut));
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY + KIT_STRING_MINIMUM_RESERVATION);
    }

    kit_String_delete(sut);

    {
        const char LITERAL[] = "Hello World!\n";
        const size_t LITERAL_SIZE = sizeof(LITERAL) - 1;

        sut = u(kit_String_fromLiteral(LITERAL));
        assert_not_null(sut);
        assert_string_equal(sut, LITERAL);
        assert_false(kit_String_isEmpty(sut));
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);

        Option option = kit_String_expand(
                &sut, KIT_STRING_DEFAULT_CAPACITY + KIT_STRING_MINIMUM_RESERVATION + 1
        );
        assert_true(Option_isSome(option));
        assert_null(sut);

        sut = Option_unwrap(option);
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

        sut = u(kit_String_fromLiteral(LITERAL));
        assert_not_null(sut);
        assert_string_equal(sut, LITERAL);
        assert_true(kit_String_isEmpty(sut));
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);

        Option option = kit_String_shrink(&sut);
        assert_true(Option_isSome(option));
        assert_null(sut);

        sut = Option_unwrap(option);
        assert_string_equal(sut, LITERAL);
        assert_true(kit_String_isEmpty(sut));
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);
    }

    kit_String_delete(sut);

    {
        const char LITERAL[] = "Hello Wold!\n";
        const size_t LITERAL_SIZE = sizeof(LITERAL) - 1;

        sut = u(kit_String_fromLiteral(LITERAL));
        assert_not_null(sut);
        assert_string_equal(sut, LITERAL);
        assert_false(kit_String_isEmpty(sut));
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);

        Option option = kit_String_shrink(&sut);
        assert_true(Option_isSome(option));
        assert_null(sut);

        sut = Option_unwrap(option);
        assert_string_equal(sut, LITERAL);
        assert_false(kit_String_isEmpty(sut));
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);
    }

    kit_String_delete(sut);

    {
        const char LITERAL[] = "Hello Wold!\n";
        const size_t LITERAL_SIZE = sizeof(LITERAL) - 1;

        sut = u(kit_String_fromLiteral(LITERAL));
        assert_not_null(sut);
        assert_string_equal(sut, LITERAL);
        assert_false(kit_String_isEmpty(sut));
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);

        Option option = kit_String_expand(
                &sut, KIT_STRING_DEFAULT_CAPACITY + KIT_STRING_MINIMUM_RESERVATION + 1
        );
        assert_true(Option_isSome(option));
        assert_null(sut);

        sut = Option_unwrap(option);
        assert_string_equal(sut, LITERAL);
        assert_false(kit_String_isEmpty(sut));
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY + KIT_STRING_MINIMUM_RESERVATION + 1);

        option = kit_String_shrink(&sut);
        assert_true(Option_isSome(option));
        assert_null(sut);

        sut = Option_unwrap(option);
        assert_string_equal(sut, LITERAL);
        assert_false(kit_String_isEmpty(sut));
        assert_equal(kit_String_size(sut), LITERAL_SIZE);
        assert_equal(kit_String_capacity(sut), KIT_STRING_DEFAULT_CAPACITY);
    }

    kit_String_delete(sut);
}
