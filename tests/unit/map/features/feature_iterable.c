/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   January 04, 2018 
 */

#include <seeds.h>
#include <traits/traits.h>
#include <features/feature_iterable.h>
#include <fixtures/fixture_map_context.h>
#include <kit/collections/atom.h>

#define EXPECTED_SIZE   (SEEDS_SIZE / 2)
#define COUPLES         (EXPECTED_SIZE * 2)

FeatureDefine(MapIteratorFromEmptyMap) {
    struct kit_Traits_MapIteratorContext *context = traits_context;;
    struct kit_Map_Iterator *sut = context->sut;
    struct kit_Pair e;

    assert_false(kit_Map_Iterator_isModified(sut));
    assert_equal(KIT_RESULT_ILLEGAL_STATE_ERROR, kit_Map_Iterator_setLast(sut, "x"));
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Map_Iterator_next(sut, &e));

    assert_false(kit_Map_Iterator_isModified(sut));
    assert_equal(KIT_RESULT_ILLEGAL_STATE_ERROR, kit_Map_Iterator_setLast(sut, "x"));
}

FeatureDefine(MapIteratorRetrieveElements) {
    struct kit_Traits_MapIteratorContext *context = traits_context;;
    struct kit_Map_Iterator *sut = context->sut;
    struct kit_Map *map = context->map;
    struct kit_Pair e;

    assert_equal(EXPECTED_SIZE, kit_Map_size(map));

    size_t i;
    for (i = 0; KIT_RESULT_OK == kit_Map_Iterator_next(sut, &e); i++) {
        struct kit_Pair tmp;
        assert_true(kit_Map_has(map, e.key));
        assert_equal(KIT_RESULT_OK, kit_Map_get(map, e.key, &tmp));
        assert_string_equal(e.value, tmp.value);
    }
    assert_equal(EXPECTED_SIZE, i);
    assert_false(kit_Map_Iterator_isModified(sut));
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Map_Iterator_next(sut, &e));
}

FeatureDefine(MapIteratorUpdateElements) {
    struct kit_Traits_MapIteratorContext *context = traits_context;;
    struct kit_Map_Iterator *sut = context->sut;
    struct kit_Map *map = context->map;
    struct kit_Pair e;

    assert_equal(EXPECTED_SIZE, kit_Map_size(map));
    assert_false(kit_Map_Iterator_isModified(sut));
    assert_equal(KIT_RESULT_ILLEGAL_STATE_ERROR, kit_Map_Iterator_setLast(sut, "x"));

    size_t i;
    for (i = 0; KIT_RESULT_OK == kit_Map_Iterator_next(sut, &e); i++) {
        assert_equal(KIT_RESULT_OK, kit_Map_Iterator_setLast(sut, "x"));
    }
    assert_equal(EXPECTED_SIZE, i);
    assert_false(kit_Map_Iterator_isModified(sut));
    assert_equal(KIT_RESULT_OK, kit_Map_Iterator_setLast(sut, "x"));
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Map_Iterator_next(sut, &e));

    kit_Map_Iterator_rewind(sut);

    for (i = 0; KIT_RESULT_OK == kit_Map_Iterator_next(sut, &e); i++) {
        assert_string_equal("x", e.value);
    }
    assert_equal(EXPECTED_SIZE, i);

    for (i = 0; i < COUPLES;) {
        kit_Atom key = ImmutableOption_unwrap(kit_Atom_fromLiteral(SEEDS[i++]));

        assert_true(kit_Map_has(map, key));
        assert_false(kit_Map_has(map, ImmutableOption_unwrap(kit_Atom_fromLiteral(SEEDS[i++]))));

        assert_equal(KIT_RESULT_OK, kit_Map_get(map, key, &e));
        assert_string_equal("x", e.value);
    }
}

FeatureDefine(MapIteratorDetectModifications) {
    struct kit_Traits_MapIteratorContext *context = traits_context;;
    struct kit_Map_Iterator *sut = context->sut;
    struct kit_Map *map = context->map;
    struct kit_Pair e;
    char *value;
    kit_Atom key;

    assert_false(kit_Map_Iterator_isModified(sut));
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_Map_Iterator_next(sut, &e));
    assert_equal(KIT_RESULT_ILLEGAL_STATE_ERROR, kit_Map_Iterator_setLast(sut, "x"));

    assert_false(kit_Map_Iterator_isModified(sut));
    assert_equal(KIT_RESULT_ILLEGAL_STATE_ERROR, kit_Map_Iterator_setLast(sut, "x"));

    key = ImmutableOption_unwrap(kit_Atom_fromLiteral(SEEDS[0]));
    value = (char *) SEEDS[1];

    assert_equal(KIT_RESULT_OK, kit_Map_put(map, key, value));

    assert_true(kit_Map_Iterator_isModified(sut));
    assert_equal(KIT_RESULT_CONCURRENT_MODIFICATION_ERROR, kit_Map_Iterator_next(sut, &e));
    assert_equal(KIT_RESULT_CONCURRENT_MODIFICATION_ERROR, kit_Map_Iterator_setLast(sut, "x"));

    kit_Map_Iterator_rewind(sut);
    assert_false(kit_Map_Iterator_isModified(sut));
    assert_equal(KIT_RESULT_OK, kit_Map_Iterator_next(sut, &e));
    assert_string_equal(key, e.key);
    assert_string_equal(value, e.value);
    assert_equal(KIT_RESULT_OK, kit_Map_Iterator_setLast(sut, "x"));
    assert_equal(KIT_RESULT_OK, kit_Map_get(map, key, &e));
    assert_string_equal("x", e.value);
}
