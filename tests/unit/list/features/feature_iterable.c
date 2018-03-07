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

#include <seeds.h>
#include <traits/traits.h>
#include <features/feature_iterable.h>
#include <fixtures/fixture_list_context.h>

FeatureDefine(ListIteratorFromEmptyListBoundaries) {
    struct kit_List *list = traits_unit_get_context();
    assert_not_null(list);

    struct kit_List_Iterator *sut = Option_unwrap(kit_List_Iterator_fromBegin(list));

    assert_equal(OutOfRangeError, Result_inspect(kit_List_Iterator_next(sut)));
    assert_equal(OutOfRangeError, Result_inspect(kit_List_Iterator_previous(sut)));
    assert_equal(IllegalStateError, Result_inspect(kit_List_Iterator_setLast(sut, "x")));

    kit_List_Iterator_delete(sut);
    sut = Option_unwrap(kit_List_Iterator_fromEnd(list));

    assert_equal(OutOfRangeError, Result_inspect(kit_List_Iterator_next(sut)));
    assert_equal(OutOfRangeError, Result_inspect(kit_List_Iterator_previous(sut)));
    assert_equal(IllegalStateError, Result_inspect(kit_List_Iterator_setLast(sut, "x")));

    kit_List_Iterator_delete(sut);
}

FeatureDefine(ListIteratorFromSeededListBoundaries) {
    struct kit_List *list = traits_unit_get_context();
    assert_not_null(list);

    struct kit_List_Iterator *sut = Option_unwrap(kit_List_Iterator_fromBegin(list));

    assert_equal(IllegalStateError, Result_inspect(kit_List_Iterator_setLast(sut, "x")));
    assert_equal(OutOfRangeError, Result_inspect(kit_List_Iterator_previous(sut)));
    assert_string_equal(SEEDS[0], Result_unwrap(kit_List_Iterator_next(sut)));

    kit_List_Iterator_delete(sut);
    sut = Option_unwrap(kit_List_Iterator_fromEnd(list));

    assert_equal(IllegalStateError, Result_inspect(kit_List_Iterator_setLast(sut, "x")));
    assert_equal(OutOfRangeError, Result_inspect(kit_List_Iterator_next(sut)));
    assert_string_equal(SEEDS[SEEDS_SIZE - 1], Result_unwrap(kit_List_Iterator_previous(sut)));

    kit_List_Iterator_delete(sut);
}

FeatureDefine(ListIteratorRewindFromEmptyList) {
    struct kit_Traits_ListIteratorContext *context = traits_unit_get_context();
    assert_not_null(context);

    struct kit_List *list = context->list;
    assert_not_null(list);

    struct kit_List_Iterator *sut = context->sut;
    assert_not_null(sut);

    kit_List_Iterator_rewindToBegin(sut);

    assert_equal(OutOfRangeError, Result_inspect(kit_List_Iterator_next(sut)));
    assert_equal(OutOfRangeError, Result_inspect(kit_List_Iterator_previous(sut)));
    assert_equal(IllegalStateError, Result_inspect(kit_List_Iterator_setLast(sut, "x")));

    kit_List_Iterator_rewindToEnd(sut);

    assert_equal(OutOfRangeError, Result_inspect(kit_List_Iterator_next(sut)));
    assert_equal(OutOfRangeError, Result_inspect(kit_List_Iterator_previous(sut)));
    assert_equal(IllegalStateError, Result_inspect(kit_List_Iterator_setLast(sut, "x")));
}

FeatureDefine(ListIteratorRewindFromSeededList) {
    struct kit_Traits_ListIteratorContext *context = traits_unit_get_context();
    assert_not_null(context);

    struct kit_List *list = context->list;
    assert_not_null(list);

    struct kit_List_Iterator *sut = context->sut;
    assert_not_null(sut);

    kit_List_Iterator_rewindToBegin(sut);

    assert_equal(IllegalStateError, Result_inspect(kit_List_Iterator_setLast(sut, "x")));
    assert_equal(OutOfRangeError, Result_inspect(kit_List_Iterator_previous(sut)));
    assert_string_equal(SEEDS[0], Result_unwrap(kit_List_Iterator_next(sut)));

    kit_List_Iterator_rewindToEnd(sut);

    assert_equal(IllegalStateError, Result_inspect(kit_List_Iterator_setLast(sut, "x")));
    assert_equal(OutOfRangeError, Result_inspect(kit_List_Iterator_next(sut)));
    assert_string_equal(SEEDS[SEEDS_SIZE - 1], Result_unwrap(kit_List_Iterator_previous(sut)));
}

FeatureDefine(ListIteratorReachTheBoundariesOfList) {
    struct kit_Traits_ListIteratorContext *context = traits_unit_get_context();
    assert_not_null(context);

    struct kit_List *list = context->list;
    assert_not_null(list);

    struct kit_List_Iterator *sut = context->sut;
    assert_not_null(sut);

    kit_List_Iterator_rewindToBegin(sut);

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_string_equal(SEEDS[i], Result_unwrap(kit_List_Iterator_next(sut)));
    }
    assert_equal(OutOfRangeError, Result_inspect(kit_List_Iterator_next(sut)));

    for (size_t i = SEEDS_SIZE; i > 0; i--) {
        assert_string_equal(SEEDS[i - 1], Result_unwrap(kit_List_Iterator_previous(sut)));
    }
    assert_equal(OutOfRangeError, Result_inspect(kit_List_Iterator_previous(sut)));

    kit_List_Iterator_rewindToEnd(sut);

    for (size_t i = SEEDS_SIZE; i > 0; i--) {
        assert_string_equal(SEEDS[i - 1], Result_unwrap(kit_List_Iterator_previous(sut)));
    }
    assert_equal(OutOfRangeError, Result_inspect(kit_List_Iterator_previous(sut)));

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_string_equal(SEEDS[i], Result_unwrap(kit_List_Iterator_next(sut)));
    }
    assert_equal(OutOfRangeError, Result_inspect(kit_List_Iterator_next(sut)));
}

FeatureDefine(ListIteratorUpdateRetrievedElements) {
    struct kit_Traits_ListIteratorContext *context = traits_unit_get_context();
    assert_not_null(context);

    struct kit_List *list = context->list;
    assert_not_null(list);

    struct kit_List_Iterator *sut = context->sut;
    assert_not_null(sut);

    kit_List_Iterator_rewindToBegin(sut);

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_string_equal(SEEDS[i], Result_unwrap(kit_List_Iterator_next(sut)));
        assert_string_equal(SEEDS[i], Result_unwrap(kit_List_Iterator_setLast(sut, "x")));
    }
    assert_equal(OutOfRangeError, Result_inspect(kit_List_Iterator_next(sut)));

    for (size_t i = SEEDS_SIZE; i > 0; i--) {
        assert_string_equal("x", Result_unwrap(kit_List_Iterator_previous(sut)));
        assert_string_equal("x", Result_unwrap(kit_List_Iterator_setLast(sut, "y")));
    }
    assert_equal(OutOfRangeError, Result_inspect(kit_List_Iterator_previous(sut)));

    kit_List_Iterator_rewindToEnd(sut);

    for (size_t i = SEEDS_SIZE; i > 0; i--) {
        assert_string_equal("y", Result_unwrap(kit_List_Iterator_previous(sut)));
        assert_string_equal("y", Result_unwrap(kit_List_Iterator_setLast(sut, "z")));
    }
    assert_equal(OutOfRangeError, Result_inspect(kit_List_Iterator_previous(sut)));

    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_string_equal("z", Result_unwrap(kit_List_Iterator_next(sut)));
        assert_string_equal("z", Result_unwrap(kit_List_Iterator_setLast(sut, "x")));
    }
    assert_equal(OutOfRangeError, Result_inspect(kit_List_Iterator_next(sut)));
}

FeatureDefine(ListIteratorDetectModifications) {
    struct kit_Traits_ListIteratorContext *context = traits_unit_get_context();
    assert_not_null(context);

    struct kit_List *list = context->list;
    assert_not_null(list);

    struct kit_List_Iterator *sut = context->sut;
    assert_not_null(sut);

    assert_false(kit_List_Iterator_isModified(sut));

    assert_equal(OutOfRangeError, Result_inspect(kit_List_Iterator_next(sut)));
    assert_equal(OutOfRangeError, Result_inspect(kit_List_Iterator_previous(sut)));
    assert_equal(IllegalStateError, Result_inspect(kit_List_Iterator_setLast(sut, "x")));

    assert_equal(Ok, kit_List_pushFront(list, "x"));
    assert_true(kit_List_Iterator_isModified(sut));

    assert_equal(ConcurrentModificationError, Result_inspect(kit_List_Iterator_next(sut)));
    assert_equal(ConcurrentModificationError, Result_inspect(kit_List_Iterator_previous(sut)));
    assert_equal(ConcurrentModificationError, Result_inspect(kit_List_Iterator_setLast(sut, "x")));

    kit_List_Iterator_rewindToBegin(sut);
    assert_false(kit_List_Iterator_isModified(sut));

    assert_equal(IllegalStateError, Result_inspect(kit_List_Iterator_setLast(sut, "x")));
    assert_equal(OutOfRangeError, Result_inspect(kit_List_Iterator_previous(sut)));
    assert_equal("x", Result_unwrap(kit_List_Iterator_next(sut)));

    assert_equal(OutOfRangeError, Result_inspect(kit_List_Iterator_next(sut)));
    assert_equal("x", Result_unwrap(kit_List_Iterator_setLast(sut, "o")));
    assert_equal("o", Result_unwrap(kit_List_Iterator_previous(sut)));
    assert_equal("o", Result_unwrap(kit_List_Iterator_setLast(sut, "x")));
    assert_equal("x", Result_unwrap(kit_List_Iterator_next(sut)));

    assert_equal(Ok, kit_List_pushBack(list, "z"));
    assert_true(kit_List_Iterator_isModified(sut));

    assert_equal(ConcurrentModificationError, Result_inspect(kit_List_Iterator_next(sut)));
    assert_equal(ConcurrentModificationError, Result_inspect(kit_List_Iterator_previous(sut)));
    assert_equal(ConcurrentModificationError, Result_inspect(kit_List_Iterator_setLast(sut, "x")));

    kit_List_Iterator_rewindToEnd(sut);
    assert_false(kit_List_Iterator_isModified(sut));

    assert_equal(IllegalStateError, Result_inspect(kit_List_Iterator_setLast(sut, "o")));
    assert_equal(OutOfRangeError, Result_inspect(kit_List_Iterator_next(sut)));
    assert_equal("z", Result_unwrap(kit_List_Iterator_previous(sut)));
    assert_equal("z", Result_unwrap(kit_List_Iterator_setLast(sut, "o")));
    assert_equal("o", Result_unwrap(kit_List_Iterator_next(sut)));
    assert_equal("o", Result_unwrap(kit_List_Iterator_setLast(sut, "z")));
    assert_equal("z", Result_unwrap(kit_List_Iterator_previous(sut)));

    assert_equal(Ok, kit_List_insert(list, 1, "y"));
    assert_true(kit_List_Iterator_isModified(sut));

    assert_equal(ConcurrentModificationError, Result_inspect(kit_List_Iterator_next(sut)));
    assert_equal(ConcurrentModificationError, Result_inspect(kit_List_Iterator_previous(sut)));
    assert_equal(ConcurrentModificationError, Result_inspect(kit_List_Iterator_setLast(sut, "x")));
}
