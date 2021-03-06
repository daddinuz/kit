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
#include <fixtures/fixture_list.h>
#include <fixtures/fixture_list_context.h>

/*
 * kit_ListType
 */
enum kit_ListType {
    KIT_LIST_TYPE_DOUBLY_LIST,
    KIT_LIST_TYPE_XOR_LIST,
    KIT_LIST_TYPE_VECTOR,
};

/*
 * Helpers declarations
 */
static struct kit_List *
setup_list_helper(enum kit_ListType type, const char *const *seeds, size_t seeds_size);

static struct kit_Traits_ListIteratorContext *
setup_list_iterator_helper(enum kit_ListType type, const char *const *seeds, size_t seeds_size);

/*
 * Setups implementations
 */
SetupDefine(EmptyListDoublyListSetup) {
    return setup_list_helper(KIT_LIST_TYPE_DOUBLY_LIST, NULL, 0);
}

SetupDefine(SeededListDoublyListSetup) {
    return setup_list_helper(KIT_LIST_TYPE_DOUBLY_LIST, SEEDS, SEEDS_SIZE);
}

SetupDefine(EmptyListXorListSetup) {
    return setup_list_helper(KIT_LIST_TYPE_XOR_LIST, NULL, 0);
}

SetupDefine(SeededListXorListSetup) {
    return setup_list_helper(KIT_LIST_TYPE_XOR_LIST, SEEDS, SEEDS_SIZE);
}

SetupDefine(EmptyListVectorSetup) {
    return setup_list_helper(KIT_LIST_TYPE_VECTOR, NULL, 0);
}

SetupDefine(SeededListVectorSetup) {
    return setup_list_helper(KIT_LIST_TYPE_VECTOR, SEEDS, SEEDS_SIZE);
}

SetupDefine(ListIteratorFromEmptyListDoublyListSetup) {
    return setup_list_iterator_helper(KIT_LIST_TYPE_DOUBLY_LIST, NULL, 0);
}

SetupDefine(ListIteratorFromSeededListDoublyListSetup) {
    return setup_list_iterator_helper(KIT_LIST_TYPE_DOUBLY_LIST, SEEDS, SEEDS_SIZE);
}

SetupDefine(ListIteratorFromEmptyListXorListSetup) {
    return setup_list_iterator_helper(KIT_LIST_TYPE_XOR_LIST, NULL, 0);
}

SetupDefine(ListIteratorFromSeededListXorListSetup) {
    return setup_list_iterator_helper(KIT_LIST_TYPE_XOR_LIST, SEEDS, SEEDS_SIZE);
}

SetupDefine(ListIteratorFromEmptyListVectorSetup) {
    return setup_list_iterator_helper(KIT_LIST_TYPE_VECTOR, NULL, 0);
}

SetupDefine(ListIteratorFromSeededListVectorSetup) {
    return setup_list_iterator_helper(KIT_LIST_TYPE_VECTOR, SEEDS, SEEDS_SIZE);
}

/*
 * Teardowns implementations
 */
TeardownDefine(ListTeardown) {
    struct kit_List *sut = traits_unit_get_context();
    assert_not_null(sut);
    kit_List_delete(sut);
}

TeardownDefine(ListIteratorTeardown) {
    struct kit_Traits_ListIteratorContext *context = traits_unit_get_context();
    assert_not_null(context);
    assert_not_null(context->list);
    assert_not_null(context->sut);
    kit_List_delete(context->list);
    kit_List_Iterator_delete(context->sut);
    free(context);
}

/*
 * Fixtures implementations
 */
FixtureDefine(EmptyListDoublyListFixture, EmptyListDoublyListSetup, ListTeardown);
FixtureDefine(SeededListDoublyListFixture, SeededListDoublyListSetup, ListTeardown);

FixtureDefine(EmptyListXorListFixture, EmptyListXorListSetup, ListTeardown);
FixtureDefine(SeededListXorListFixture, SeededListXorListSetup, ListTeardown);

FixtureDefine(EmptyListVectorFixture, EmptyListVectorSetup, ListTeardown);
FixtureDefine(SeededListVectorFixture, SeededListVectorSetup, ListTeardown);

FixtureDefine(ListIteratorFromEmptyListDoublyListFixture, ListIteratorFromEmptyListDoublyListSetup,
              ListIteratorTeardown);
FixtureDefine(ListIteratorFromSeededListDoublyListFixture, ListIteratorFromSeededListDoublyListSetup,
              ListIteratorTeardown);

FixtureDefine(ListIteratorFromEmptyListXorListFixture, ListIteratorFromEmptyListXorListSetup, ListIteratorTeardown);
FixtureDefine(ListIteratorFromSeededListXorListFixture, ListIteratorFromSeededListXorListSetup, ListIteratorTeardown);

FixtureDefine(ListIteratorFromEmptyListVectorFixture, ListIteratorFromEmptyListVectorSetup, ListIteratorTeardown);
FixtureDefine(ListIteratorFromSeededListVectorFixture, ListIteratorFromSeededListVectorSetup, ListIteratorTeardown);

/*
 * Helpers implementations
 */
struct kit_List *
setup_list_helper(enum kit_ListType type, const char *const seeds[], const size_t seeds_size) {
    assert_true((seeds && seeds_size) > 0 || (NULL == seeds && seeds_size == 0));
    struct kit_List *sut = NULL;

    switch (type) {
        case KIT_LIST_TYPE_DOUBLY_LIST:
            sut = Option_unwrap(kit_List_fromDoublyList());
            break;
        case KIT_LIST_TYPE_XOR_LIST:
            sut = Option_unwrap(kit_List_fromXorList());
            break;
        case KIT_LIST_TYPE_VECTOR:
            sut = Option_unwrap(kit_List_fromVector(0));
            break;
        default:
            traits_assert(false);
    }

    assert_not_null(sut);

    if (seeds) {
        for (size_t i = 0; i < seeds_size; i++) {
            assert_equal(Ok, kit_List_pushBack(sut, (void *) seeds[i]));
        }
    }

    return sut;
}

struct kit_Traits_ListIteratorContext *
setup_list_iterator_helper(enum kit_ListType type, const char *const *seeds, size_t seeds_size) {
    assert_true((seeds && seeds_size) > 0 || (NULL == seeds && seeds_size == 0));

    struct kit_Traits_ListIteratorContext *context = calloc(1, sizeof(*context));
    assert_not_null(context);

    context->list = setup_list_helper(type, seeds, seeds_size);
    assert_not_null(context->list);

    context->sut = Option_unwrap(kit_List_Iterator_fromBegin(context->list));
    assert_not_null(context->sut);

    return context;
}
