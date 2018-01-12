/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   December 30, 2017 
 */

#include <seeds.h>
#include <traits/traits.h>
#include <features/feature_insert.h>
#include <kit/collections/map.h>
#include <kit/collections/atom.h>

#define EXPECTED_SIZE   (SEEDS_SIZE / 2)
#define COUPLES         (EXPECTED_SIZE * 2)

FeatureDefine(MapAdd) {
    Result result;
    struct kit_Map *sut = traits_context;
    assert_not_null(sut);

    assert_true(kit_Map_isEmpty(sut));
    assert_equal(0, kit_Map_size(sut));

    for (size_t i = 0, s = 1; i < COUPLES; s++) {
        kit_Atom key = Option_unwrap(kit_Atom_fromLiteral(SEEDS[i++]));
        char *value = (char *) SEEDS[i++];

        assert_false(kit_Map_has(sut, key));

        result = kit_Map_get(sut, key);
        assert_true(Result_isError(result));
        assert_equal(&OutOfRangeError, Result_inspect(result));

        result = kit_Map_add(sut, kit_Pair_make(key, value));
        assert_true(Result_isOk(result));
        assert_null(Result_unwrap(result));

        assert_true(kit_Map_has(sut, key));

        result = kit_Map_get(sut, key);
        assert_true(Result_isOk(result));
        assert_string_equal(value, Result_unwrap(result));

        assert_false(kit_Map_isEmpty(sut));
        assert_equal(s, kit_Map_size(sut));
    }
    assert_false(kit_Map_isEmpty(sut));
    assert_equal(EXPECTED_SIZE, kit_Map_size(sut));

    for (size_t i = 0; i < COUPLES;) {
        kit_Atom key = Option_unwrap(kit_Atom_fromLiteral(SEEDS[i++]));
        char *value = (char *) SEEDS[i++];
        char newValue[] = "x";

        assert_true(kit_Map_has(sut, key));
        assert_false(kit_Map_isEmpty(sut));
        assert_equal(EXPECTED_SIZE, kit_Map_size(sut));

        result = kit_Map_get(sut, key);
        assert_true(Result_isOk(result));
        assert_string_equal(value, Result_unwrap(result));

        result = kit_Map_add(sut, kit_Pair_make(key, newValue));
        assert_true(Result_isOk(result));
        assert_string_equal(value, Result_unwrap(result));

        assert_true(kit_Map_has(sut, key));
        assert_false(kit_Map_isEmpty(sut));
        assert_equal(EXPECTED_SIZE, kit_Map_size(sut));

        result = kit_Map_get(sut, key);
        assert_true(Result_isOk(result));
        assert_string_equal(newValue, Result_unwrap(result));
    }
}

FeatureDefine(MapPut) {
    Result result;
    struct kit_Map *sut = traits_context;
    assert_not_null(sut);

    assert_true(kit_Map_isEmpty(sut));
    assert_equal(0, kit_Map_size(sut));

    for (size_t i = 0, s = 1; i < COUPLES; s++) {
        kit_Atom key = Option_unwrap(kit_Atom_fromLiteral(SEEDS[i++]));
        char *value = (char *) SEEDS[i++];

        assert_false(kit_Map_has(sut, key));

        result = kit_Map_get(sut, key);
        assert_true(Result_isError(result));
        assert_equal(&OutOfRangeError, Result_inspect(result));

        result = kit_Map_put(sut, key, value);
        assert_true(Result_isOk(result));
        assert_null(Result_unwrap(result));

        assert_true(kit_Map_has(sut, key));

        result = kit_Map_get(sut, key);
        assert_true(Result_isOk(result));
        assert_string_equal(value, Result_unwrap(result));

        assert_false(kit_Map_isEmpty(sut));
        assert_equal(s, kit_Map_size(sut));
    }

    assert_false(kit_Map_isEmpty(sut));
    assert_equal(EXPECTED_SIZE, kit_Map_size(sut));

    for (size_t i = 0; i < COUPLES;) {
        kit_Atom key = Option_unwrap(kit_Atom_fromLiteral(SEEDS[i++]));
        char *value = (char *) SEEDS[i++];
        char newValue[] = "x";

        assert_true(kit_Map_has(sut, key));
        assert_false(kit_Map_isEmpty(sut));
        assert_equal(EXPECTED_SIZE, kit_Map_size(sut));

        result = kit_Map_get(sut, key);
        assert_true(Result_isOk(result));
        assert_string_equal(value, Result_unwrap(result));

        result = kit_Map_put(sut, key, newValue);
        assert_true(Result_isOk(result));
        assert_string_equal(value, Result_unwrap(result));

        assert_false(kit_Map_isEmpty(sut));
        assert_true(kit_Map_has(sut, key));
        assert_equal(EXPECTED_SIZE, kit_Map_size(sut));

        result = kit_Map_get(sut, key);
        assert_true(Result_isOk(result));
        assert_string_equal(newValue, Result_unwrap(result));
    }

    assert_false(kit_Map_isEmpty(sut));
    assert_equal(EXPECTED_SIZE, kit_Map_size(sut));
}
