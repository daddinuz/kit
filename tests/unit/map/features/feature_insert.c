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

FeatureDefine(MapAdd) {
    struct kit_Map *sut = traits_context;
    assert_not_null(sut);

    assert_true(kit_Map_isEmpty(sut));
    assert_equal(0, kit_Map_size(sut));

    struct kit_Pair e;
    const size_t EXPECTED_SIZE = SEEDS_SIZE / 2;
    const size_t COUPLES = EXPECTED_SIZE * 2;

    for (size_t i = 0, s = 1; i < COUPLES; s++) {
        kit_Atom key = ImmutableOption_unwrap(kit_Atom_fromLiteral(SEEDS[i++]));
        char *value = (char *) SEEDS[i++];

        assert_equal(KIT_RESULT_OK, kit_Map_add(sut, kit_Pair_make(key, value)));
        assert_false(kit_Map_isEmpty(sut));
        assert_equal(s, kit_Map_size(sut));
        assert_equal(KIT_RESULT_OK, kit_Map_get(sut, key, &e));
        assert_string_equal(key, e.key);
        assert_string_equal(value, e.value);
    }
    assert_false(kit_Map_isEmpty(sut));
    assert_equal(EXPECTED_SIZE, kit_Map_size(sut));

    for (size_t i = 0; i < COUPLES;) {
        kit_Atom key = ImmutableOption_unwrap(kit_Atom_fromLiteral(SEEDS[i++]));
        char *value = (char *) SEEDS[i++];

        assert_equal(KIT_RESULT_OK, kit_Map_get(sut, key, &e));
        assert_string_equal(key, e.key);
        assert_string_equal(value, e.value);
    }
}

FeatureDefine(MapPut) {
    struct kit_Map *sut = traits_context;
    assert_not_null(sut);

    assert_true(kit_Map_isEmpty(sut));
    assert_equal(0, kit_Map_size(sut));

    struct kit_Pair e;
    const size_t EXPECTED_SIZE = SEEDS_SIZE / 2;
    const size_t COUPLES = EXPECTED_SIZE * 2;

    for (size_t i = 0, s = 1; i < COUPLES; s++) {
        kit_Atom key = ImmutableOption_unwrap(kit_Atom_fromLiteral(SEEDS[i++]));
        char *value = (char *) SEEDS[i++];

        assert_equal(KIT_RESULT_OK, kit_Map_put(sut, key, value));
        assert_false(kit_Map_isEmpty(sut));
        assert_equal(s, kit_Map_size(sut));
        assert_equal(KIT_RESULT_OK, kit_Map_get(sut, key, &e));
        assert_string_equal(key, e.key);
        assert_string_equal(value, e.value);
    }
    assert_false(kit_Map_isEmpty(sut));
    assert_equal(EXPECTED_SIZE, kit_Map_size(sut));

    for (size_t i = 0; i < COUPLES;) {
        kit_Atom key = ImmutableOption_unwrap(kit_Atom_fromLiteral(SEEDS[i++]));
        char *value = (char *) SEEDS[i++];

        assert_equal(KIT_RESULT_OK, kit_Map_get(sut, key, &e));
        assert_string_equal(key, e.key);
        assert_string_equal(value, e.value);
    }
}
