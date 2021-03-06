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
#include <fixtures/fixture_stack.h>
#include <kit/collections/stack.h>

/*
 * kit_StackType
 */
enum kit_StackType {
    KIT_STACK_TYPE_DOUBLY_LIST,
    KIT_STACK_TYPE_SINGLY_LIST,
    KIT_STACK_TYPE_XOR_LIST,
    KIT_STACK_TYPE_VECTOR,
};

/*
 * Helpers declarations
 */
static struct kit_Stack *setup_helper(enum kit_StackType type, const char *const seeds[], size_t seeds_size);

/*
 * Setups implementations
 */
SetupDefine(EmptyStackSinglyListSetup) {
    return setup_helper(KIT_STACK_TYPE_SINGLY_LIST, NULL, 0);
}

SetupDefine(SeededStackSinglyListSetup) {
    return setup_helper(KIT_STACK_TYPE_SINGLY_LIST, SEEDS, SEEDS_SIZE);
}

SetupDefine(EmptyStackDoublyListSetup) {
    return setup_helper(KIT_STACK_TYPE_DOUBLY_LIST, NULL, 0);
}

SetupDefine(SeededStackDoublyListSetup) {
    return setup_helper(KIT_STACK_TYPE_DOUBLY_LIST, SEEDS, SEEDS_SIZE);
}

SetupDefine(EmptyStackXorListSetup) {
    return setup_helper(KIT_STACK_TYPE_XOR_LIST, NULL, 0);
}

SetupDefine(SeededStackXorListSetup) {
    return setup_helper(KIT_STACK_TYPE_XOR_LIST, SEEDS, SEEDS_SIZE);
}

SetupDefine(EmptyStackVectorSetup) {
    return setup_helper(KIT_STACK_TYPE_VECTOR, NULL, 0);
}

SetupDefine(SeededStackVectorSetup) {
    return setup_helper(KIT_STACK_TYPE_VECTOR, SEEDS, SEEDS_SIZE);
}

/*
 * Teardowns implementations
 */
TeardownDefine(StackTeardown) {
    struct kit_Stack *sut = traits_unit_get_context();
    assert_not_null(sut);
    kit_Stack_delete(sut);
}

/*
 * Fixtures implementations
 */
FixtureDefine(EmptyStackSinglyListFixture, EmptyStackSinglyListSetup, StackTeardown);
FixtureDefine(SeededStackSinglyListFixture, SeededStackSinglyListSetup, StackTeardown);

FixtureDefine(EmptyStackDoublyListFixture, EmptyStackDoublyListSetup, StackTeardown);
FixtureDefine(SeededStackDoublyListFixture, SeededStackDoublyListSetup, StackTeardown);

FixtureDefine(EmptyStackXorListFixture, EmptyStackXorListSetup, StackTeardown);
FixtureDefine(SeededStackXorListFixture, SeededStackXorListSetup, StackTeardown);

FixtureDefine(EmptyStackVectorFixture, EmptyStackVectorSetup, StackTeardown);
FixtureDefine(SeededStackVectorFixture, SeededStackVectorSetup, StackTeardown);

/*
 * Helpers implementations
 */
struct kit_Stack *setup_helper(enum kit_StackType type, const char *const seeds[], const size_t seeds_size) {
    struct kit_Stack *sut = NULL;

    switch (type) {
        case KIT_STACK_TYPE_DOUBLY_LIST:
            sut = Option_unwrap(kit_Stack_fromDoublyList());
            break;
        case KIT_STACK_TYPE_SINGLY_LIST:
            sut = Option_unwrap(kit_Stack_fromSinglyList());
            break;
        case KIT_STACK_TYPE_XOR_LIST:
            sut = Option_unwrap(kit_Stack_fromXorList());
            break;
        case KIT_STACK_TYPE_VECTOR:
            sut = Option_unwrap(kit_Stack_fromVector(0));
            break;
        default:
            traits_assert(false);
    }

    assert_not_null(sut);

    if (seeds) {
        for (size_t i = 0; i < seeds_size; i++) {
            assert_equal(Ok, kit_Stack_push(sut, (void *) seeds[i]));
        }
    }

    return sut;
}
