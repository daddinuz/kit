/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   January 02, 2018 
 */

#include <seeds.h>
#include <traits/traits.h>
#include <features/feature_remove.h>
#include <kit/collections/map.h>
#include <kit/collections/atom.h>

#define EXPECTED_SIZE   (SEEDS_SIZE / 2)
#define COUPLES         (EXPECTED_SIZE * 2)

FeatureDefine(MapPop) {
    Result result;
    struct kit_Map *sut = traits_context;
    assert_not_null(sut);

    assert_false(kit_Map_isEmpty(sut));
    assert_equal(EXPECTED_SIZE, kit_Map_size(sut));

    for (size_t i = 0, s = EXPECTED_SIZE - 1; i < COUPLES; s--) {
        kit_Atom key = Option_unwrap(kit_Atom_fromLiteral(SEEDS[i++]));
        char *value = (char *) SEEDS[i++];

        assert_true(kit_Map_has(sut, key));

        assert_string_equal(value, Result_unwrap(kit_Map_get(sut, key)));
        assert_string_equal(value, Result_unwrap(kit_Map_pop(sut, key)));

        assert_false(kit_Map_has(sut, key));

        result = kit_Map_get(sut, key);
        assert_true(Result_isError(result));
        assert_equal(&OutOfRangeError, Result_inspect(result));

        result = kit_Map_pop(sut, key);
        assert_true(Result_isError(result));
        assert_equal(&OutOfRangeError, Result_inspect(result));

        if (s == 0) {
            assert_true(kit_Map_isEmpty(sut));
        } else {
            assert_false(kit_Map_isEmpty(sut));
        }
        assert_equal(s, kit_Map_size(sut));
    }
    assert_true(kit_Map_isEmpty(sut));
    assert_equal(0, kit_Map_size(sut));
}

FeatureDefine(MapClear) {
    Result result;
    struct kit_Map *sut = traits_context;

    assert_false(kit_Map_isEmpty(sut));
    assert_equal(EXPECTED_SIZE, kit_Map_size(sut));

    kit_Map_clear(sut);

    assert_true(kit_Map_isEmpty(sut));
    assert_equal(0, kit_Map_size(sut));

    for (size_t i = 0; i < COUPLES;) {
        kit_Atom key = Option_unwrap(kit_Atom_fromLiteral(SEEDS[i++]));

        assert_false(kit_Map_has(sut, key));

        result = kit_Map_pop(sut, key);
        assert_true(Result_isError(result));
        assert_equal(&OutOfRangeError, Result_inspect(result));

        result = kit_Map_get(sut, key);
        assert_true(Result_isError(result));
        assert_equal(&OutOfRangeError, Result_inspect(result));
    }
}
