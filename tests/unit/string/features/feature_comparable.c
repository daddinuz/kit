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
#include <features/feature_comparable.h>
#include <kit/collections/string.h>

#define u(x)    Option_unwrap((x))

FeatureDefine(StringIsEqual) {
    (void) traits_context;

    kit_String sut;

    {
        const char BYTES[] = "abc\0\t123\n\r!=?";
        const size_t BYTES_SIZE = sizeof(BYTES) - 1;

        sut = u(kit_String_fromBytes(BYTES, BYTES_SIZE));
        assert_true(kit_String_isEqual(sut, sut));

        kit_String other = u(kit_String_new());
        assert_true(kit_String_isEqual(sut, sut));
        assert_true(kit_String_isEqual(other, other));
        assert_false(kit_String_isEqual(sut, other));

        other = u(kit_String_setLiteral(&other, "Hello World!\n"));
        assert_true(kit_String_isEqual(sut, sut));
        assert_true(kit_String_isEqual(other, other));
        assert_false(kit_String_isEqual(sut, other));

        other = u(kit_String_setLiteral(&other, BYTES));
        assert_true(kit_String_isEqual(sut, sut));
        assert_true(kit_String_isEqual(other, other));
        assert_false(kit_String_isEqual(sut, other));

        other = u(kit_String_setBytes(&other, BYTES, BYTES_SIZE));
        assert_true(kit_String_isEqual(sut, sut));
        assert_true(kit_String_isEqual(other, other));
        assert_true(kit_String_isEqual(sut, other));

        sut = u(kit_String_setLiteral(&sut, ""));
        other = u(kit_String_setLiteral(&other, ""));
        assert_true(kit_String_isEqual(sut, sut));
        assert_true(kit_String_isEqual(other, other));
        assert_true(kit_String_isEqual(sut, other));

        kit_String_delete(other);
    }

    kit_String_delete(sut);
}
