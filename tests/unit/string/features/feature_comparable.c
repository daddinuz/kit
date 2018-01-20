/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   December 15, 2017 
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

        kit_String other = u(kit_String_new(0));
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
