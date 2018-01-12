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
    struct kit_Pair pair;
    Result result;

    assert_false(kit_Map_Iterator_isModified(sut));

    result = kit_Map_Iterator_setLast(sut, "x");
    assert_true(Result_isError(result));
    assert_equal(&IllegalStateError, Result_inspect(result));

    result = kit_Map_Iterator_next(sut, &pair);
    assert_true(Result_isError(result));
    assert_equal(&OutOfRangeError, Result_inspect(result));

    assert_false(kit_Map_Iterator_isModified(sut));

    result = kit_Map_Iterator_setLast(sut, "x");
    assert_true(Result_isError(result));
    assert_equal(&IllegalStateError, Result_inspect(result));
}

FeatureDefine(MapIteratorRetrieveElements) {
    struct kit_Traits_MapIteratorContext *context = traits_context;;
    struct kit_Map_Iterator *sut = context->sut;
    struct kit_Map *map = context->map;
    struct kit_Pair pair;
    Result result;

    assert_equal(EXPECTED_SIZE, kit_Map_size(map));

    size_t i = 0;
    result = kit_Map_Iterator_next(sut, &pair);

    while (Result_isOk(result)) {
        assert_equal(&pair, Result_unwrap(result));
        assert_true(kit_Map_has(map, pair.key));
        assert_string_equal(Result_unwrap(kit_Map_get(map, pair.key)), pair.value);
        result = kit_Map_Iterator_next(sut, &pair);
        i += 1;
    }

    assert_equal(EXPECTED_SIZE, i);
    assert_false(kit_Map_Iterator_isModified(sut));

    result = kit_Map_Iterator_next(sut, &pair);
    assert_true(Result_isError(result));
    assert_equal(&OutOfRangeError, Result_inspect(result));
}

FeatureDefine(MapIteratorUpdateElements) {
    struct kit_Traits_MapIteratorContext *context = traits_context;;
    struct kit_Map_Iterator *sut = context->sut;
    struct kit_Map *map = context->map;
    struct kit_Pair pair;
    Result result;

    assert_equal(EXPECTED_SIZE, kit_Map_size(map));
    assert_false(kit_Map_Iterator_isModified(sut));

    result = kit_Map_Iterator_setLast(sut, "x");
    assert_true(Result_isError(result));
    assert_equal(&IllegalStateError, Result_inspect(result));

    size_t i = 0;
    result = kit_Map_Iterator_next(sut, &pair);

    while (Result_isOk(result)) {
        result = kit_Map_Iterator_setLast(sut, "x");
        assert_true(Result_isOk(result));
        assert_string_equal(Result_unwrap(result), pair.value);
        result = kit_Map_Iterator_next(sut, &pair);
        i += 1;
    }

    assert_equal(EXPECTED_SIZE, i);
    assert_false(kit_Map_Iterator_isModified(sut));

    result = kit_Map_Iterator_setLast(sut, "x");
    assert_true(Result_isOk(result));
    assert_string_equal("x", Result_unwrap(result));

    result = kit_Map_Iterator_next(sut, &pair);
    assert_true(Result_isError(result));
    assert_equal(&OutOfRangeError, Result_inspect(result));

    kit_Map_Iterator_rewind(sut);

    i = 0;
    result = kit_Map_Iterator_next(sut, &pair);
    while (Result_isOk(result)) {
        assert_equal(&pair, Result_unwrap(result));
        assert_true(kit_Map_has(map, pair.key));
        assert_string_equal("x", pair.value);
        result = kit_Map_Iterator_next(sut, &pair);
        i += 1;
    }
    assert_equal(EXPECTED_SIZE, i);

    for (i = 0; i < COUPLES;) {
        kit_Atom key = Option_unwrap(kit_Atom_fromLiteral(SEEDS[i++]));

        assert_true(kit_Map_has(map, key));
        assert_false(kit_Map_has(map, Option_unwrap(kit_Atom_fromLiteral(SEEDS[i++]))));

        assert_string_equal("x", Result_unwrap(kit_Map_get(map, key)));
    }
}

FeatureDefine(MapIteratorDetectModifications) {
    struct kit_Traits_MapIteratorContext *context = traits_context;;
    struct kit_Map_Iterator *sut = context->sut;
    struct kit_Map *map = context->map;
    struct kit_Pair pair;
    Result result;
    kit_Atom key;
    char *value;

    assert_false(kit_Map_Iterator_isModified(sut));

    result = kit_Map_Iterator_next(sut, &pair);
    assert_true(Result_isError(result));
    assert_equal(&OutOfRangeError, Result_inspect(result));

    result = kit_Map_Iterator_setLast(sut, "x");
    assert_true(Result_isError(result));
    assert_equal(&IllegalStateError, Result_inspect(result));

    assert_false(kit_Map_Iterator_isModified(sut));

    result = kit_Map_Iterator_setLast(sut, "x");
    assert_true(Result_isError(result));
    assert_equal(&IllegalStateError, Result_inspect(result));

    key = Option_unwrap(kit_Atom_fromLiteral(SEEDS[0]));
    value = (char *) SEEDS[1];

    Result_unwrap(kit_Map_put(map, key, value));

    assert_true(kit_Map_Iterator_isModified(sut));

    result = kit_Map_Iterator_next(sut, &pair);
    assert_true(Result_isError(result));
    assert_equal(&ConcurrentModificationError, Result_inspect(result));

    result = kit_Map_Iterator_setLast(sut, "x");
    assert_true(Result_isError(result));
    assert_equal(&ConcurrentModificationError, Result_inspect(result));

    kit_Map_Iterator_rewind(sut);

    assert_false(kit_Map_Iterator_isModified(sut));

    Result_unwrap(kit_Map_Iterator_next(sut, &pair));
    assert_string_equal(key, pair.key);
    assert_string_equal(value, pair.value);

    Result_unwrap(kit_Map_Iterator_setLast(sut, "x"));
    assert_string_equal("x", Result_unwrap(kit_Map_get(map, key)));
}
