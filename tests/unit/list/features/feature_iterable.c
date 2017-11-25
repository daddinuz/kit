/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 25, 2017 
 */

#include <seeds.h>
#include <traits/traits.h>
#include <features/feature_iterable.h>
#include <fixtures/fixture_list_context.h>

FeatureDefine(ListIteratorFromEmptyListBoundaries) {
    void *e;
    struct kit_List *list = traits_context;
    assert_not_null(list);
    struct kit_List_Iterator *sut = Option_unwrap(kit_List_Iterator_fromBegin(list));

    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_Iterator_next(sut, &e));
    assert_null(e);
    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_Iterator_previous(sut, &e));
    assert_null(e);
    assert_equal(KIT_RESULT_ILLEGAL_STATE_ERROR, kit_List_Iterator_setLast(sut, "x"));
    kit_List_Iterator_delete(sut);

    sut = Option_unwrap(kit_List_Iterator_fromEnd(list));
    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_Iterator_next(sut, &e));
    assert_null(e);
    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_Iterator_previous(sut, &e));
    assert_null(e);
    assert_equal(KIT_RESULT_ILLEGAL_STATE_ERROR, kit_List_Iterator_setLast(sut, "x"));
    kit_List_Iterator_delete(sut);
}

FeatureDefine(ListIteratorFromSeededListBoundaries) {
    void *e;
    struct kit_List *list = traits_context;
    assert_not_null(list);
    struct kit_List_Iterator *sut = Option_unwrap(kit_List_Iterator_fromBegin(list));

    assert_equal(KIT_RESULT_ILLEGAL_STATE_ERROR, kit_List_Iterator_setLast(sut, "x"));
    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_Iterator_previous(sut, &e));
    assert_null(e);
    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_List_Iterator_next(sut, &e));
    assert_string_equal(SEEDS[0], e);
    kit_List_Iterator_delete(sut);

    sut = Option_unwrap(kit_List_Iterator_fromEnd(list));
    assert_equal(KIT_RESULT_ILLEGAL_STATE_ERROR, kit_List_Iterator_setLast(sut, "x"));
    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_Iterator_next(sut, &e));
    assert_null(e);
    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_List_Iterator_previous(sut, &e));
    assert_string_equal(SEEDS[SEEDS_SIZE - 1], e);
    kit_List_Iterator_delete(sut);
}

FeatureDefine(ListIteratorRewindFromEmptyList) {
    void *e;
    struct kit_Traits_ListIteratorContext *context = traits_context;
    struct kit_List *list = context->list;
    assert_not_null(list);
    struct kit_List_Iterator *sut = context->sut;
    assert_not_null(sut);

    kit_List_Iterator_rewindToBegin(sut);
    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_Iterator_next(sut, &e));
    assert_null(e);
    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_Iterator_previous(sut, &e));
    assert_null(e);
    assert_equal(KIT_RESULT_ILLEGAL_STATE_ERROR, kit_List_Iterator_setLast(sut, "x"));

    kit_List_Iterator_rewindToEnd(sut);
    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_Iterator_next(sut, &e));
    assert_null(e);
    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_Iterator_previous(sut, &e));
    assert_null(e);
    assert_equal(KIT_RESULT_ILLEGAL_STATE_ERROR, kit_List_Iterator_setLast(sut, "x"));
}

FeatureDefine(ListIteratorRewindFromSeededList) {
    void *e;
    struct kit_Traits_ListIteratorContext *context = traits_context;
    struct kit_List *list = context->list;
    assert_not_null(list);
    struct kit_List_Iterator *sut = context->sut;
    assert_not_null(sut);

    kit_List_Iterator_rewindToBegin(sut);
    assert_equal(KIT_RESULT_ILLEGAL_STATE_ERROR, kit_List_Iterator_setLast(sut, "x"));
    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_Iterator_previous(sut, &e));
    assert_null(e);
    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_List_Iterator_next(sut, &e));
    assert_string_equal(SEEDS[0], e);

    kit_List_Iterator_rewindToEnd(sut);
    assert_equal(KIT_RESULT_ILLEGAL_STATE_ERROR, kit_List_Iterator_setLast(sut, "x"));
    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_Iterator_next(sut, &e));
    assert_null(e);
    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_List_Iterator_previous(sut, &e));
    assert_string_equal(SEEDS[SEEDS_SIZE - 1], e);
}

FeatureDefine(ListIteratorReachTheBoundariesOfList) {
    void *e;
    struct kit_Traits_ListIteratorContext *context = traits_context;
    struct kit_List *list = context->list;
    assert_not_null(list);
    struct kit_List_Iterator *sut = context->sut;
    assert_not_null(sut);

    kit_List_Iterator_rewindToBegin(sut);
    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        e = NULL;
        assert_equal(KIT_RESULT_OK, kit_List_Iterator_next(sut, &e));
        assert_string_equal(SEEDS[i], e);
    }
    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_Iterator_next(sut, &e));
    assert_null(e);
    for (size_t i = SEEDS_SIZE; i > 0; i--) {
        e = NULL;
        assert_equal(KIT_RESULT_OK, kit_List_Iterator_previous(sut, &e));
        assert_string_equal(SEEDS[i - 1], e);
    }
    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_Iterator_previous(sut, &e));
    assert_null(e);

    kit_List_Iterator_rewindToEnd(sut);
    for (size_t i = SEEDS_SIZE; i > 0; i--) {
        e = NULL;
        assert_equal(KIT_RESULT_OK, kit_List_Iterator_previous(sut, &e));
        assert_string_equal(SEEDS[i - 1], e);
    }
    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_Iterator_previous(sut, &e));
    assert_null(e);
    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        e = NULL;
        assert_equal(KIT_RESULT_OK, kit_List_Iterator_next(sut, &e));
        assert_string_equal(SEEDS[i], e);
    }
    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_Iterator_next(sut, &e));
    assert_null(e);
}

FeatureDefine(ListIteratorUpdateRetrievedElements) {
    void *e;
    struct kit_Traits_ListIteratorContext *context = traits_context;
    struct kit_List *list = context->list;
    assert_not_null(list);
    struct kit_List_Iterator *sut = context->sut;
    assert_not_null(sut);

    kit_List_Iterator_rewindToBegin(sut);
    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        e = NULL;
        assert_equal(KIT_RESULT_OK, kit_List_Iterator_next(sut, &e));
        assert_string_equal(SEEDS[i], e);
        kit_List_Iterator_setLast(sut, "x");
    }
    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_Iterator_next(sut, &e));
    assert_null(e);
    for (size_t i = SEEDS_SIZE; i > 0; i--) {
        e = NULL;
        assert_equal(KIT_RESULT_OK, kit_List_Iterator_previous(sut, &e));
        assert_string_equal("x", e);
        kit_List_Iterator_setLast(sut, "y");
    }
    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_Iterator_previous(sut, &e));
    assert_null(e);


    kit_List_Iterator_rewindToEnd(sut);
    for (size_t i = SEEDS_SIZE; i > 0; i--) {
        e = NULL;
        assert_equal(KIT_RESULT_OK, kit_List_Iterator_previous(sut, &e));
        assert_string_equal("y", e);
        kit_List_Iterator_setLast(sut, "x");
    }
    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_Iterator_previous(sut, &e));
    assert_null(e);
    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        e = NULL;
        assert_equal(KIT_RESULT_OK, kit_List_Iterator_next(sut, &e));
        assert_string_equal("x", e);
    }
    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_Iterator_next(sut, &e));
    assert_null(e);
}

FeatureDefine(ListIteratorDetectModifications) {
    void *e;
    struct kit_Traits_ListIteratorContext *context = traits_context;
    struct kit_List *list = context->list;
    assert_not_null(list);
    struct kit_List_Iterator *sut = context->sut;
    assert_not_null(sut);

    assert_false(kit_List_Iterator_isModified(sut));

    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_Iterator_next(sut, &e));
    assert_null(e);
    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_Iterator_previous(sut, &e));
    assert_null(e);
    assert_equal(KIT_RESULT_ILLEGAL_STATE_ERROR, kit_List_Iterator_setLast(sut, "o"));

    kit_List_pushFront(list, "x");
    assert_true(kit_List_Iterator_isModified(sut));
    e = NULL;
    assert_equal(KIT_RESULT_CONCURRENT_MODIFICATION_ERROR, kit_List_Iterator_next(sut, &e));
    assert_null(e);
    e = NULL;
    assert_equal(KIT_RESULT_CONCURRENT_MODIFICATION_ERROR, kit_List_Iterator_previous(sut, &e));
    assert_null(e);
    assert_equal(KIT_RESULT_CONCURRENT_MODIFICATION_ERROR, kit_List_Iterator_setLast(sut, "o"));

    kit_List_Iterator_rewindToBegin(sut);
    assert_false(kit_List_Iterator_isModified(sut));
    assert_equal(KIT_RESULT_ILLEGAL_STATE_ERROR, kit_List_Iterator_setLast(sut, "o"));
    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_Iterator_previous(sut, &e));
    assert_null(e);
    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_List_Iterator_next(sut, &e));
    assert_equal("x", e);
    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_Iterator_next(sut, &e));
    assert_null(e);
    assert_equal(KIT_RESULT_OK, kit_List_Iterator_setLast(sut, "o"));
    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_List_Iterator_previous(sut, &e));
    assert_equal("o", e);
    assert_equal(KIT_RESULT_OK, kit_List_Iterator_setLast(sut, "x"));
    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_List_Iterator_next(sut, &e));
    assert_equal("x", e);

    kit_List_pushBack(list, "z");
    assert_true(kit_List_Iterator_isModified(sut));
    e = NULL;
    assert_equal(KIT_RESULT_CONCURRENT_MODIFICATION_ERROR, kit_List_Iterator_next(sut, &e));
    assert_null(e);
    e = NULL;
    assert_equal(KIT_RESULT_CONCURRENT_MODIFICATION_ERROR, kit_List_Iterator_previous(sut, &e));
    assert_null(e);
    assert_equal(KIT_RESULT_CONCURRENT_MODIFICATION_ERROR, kit_List_Iterator_setLast(sut, "o"));

    kit_List_Iterator_rewindToEnd(sut);
    assert_false(kit_List_Iterator_isModified(sut));
    assert_equal(KIT_RESULT_ILLEGAL_STATE_ERROR, kit_List_Iterator_setLast(sut, "o"));
    e = NULL;
    assert_equal(KIT_RESULT_OUT_OF_RANGE_ERROR, kit_List_Iterator_next(sut, &e));
    assert_null(e);
    assert_equal(KIT_RESULT_OK, kit_List_Iterator_previous(sut, &e));
    assert_equal("z", e);
    assert_equal(KIT_RESULT_OK, kit_List_Iterator_setLast(sut, "o"));
    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_List_Iterator_next(sut, &e));
    assert_equal("o", e);
    assert_equal(KIT_RESULT_OK, kit_List_Iterator_setLast(sut, "z"));
    e = NULL;
    assert_equal(KIT_RESULT_OK, kit_List_Iterator_previous(sut, &e));
    assert_equal("z", e);

    kit_List_insert(list, "y", 1);
    assert_true(kit_List_Iterator_isModified(sut));
    e = NULL;
    assert_equal(KIT_RESULT_CONCURRENT_MODIFICATION_ERROR, kit_List_Iterator_next(sut, &e));
    assert_null(e);
    e = NULL;
    assert_equal(KIT_RESULT_CONCURRENT_MODIFICATION_ERROR, kit_List_Iterator_previous(sut, &e));
    assert_null(e);
    assert_equal(KIT_RESULT_CONCURRENT_MODIFICATION_ERROR, kit_List_Iterator_setLast(sut, "o"));
}
