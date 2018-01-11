/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 22, 2017 
 */

#include <seeds.h>
#include <traits/traits.h>
#include <fixtures/fixture_array.h>
#include <kit/collections/array.h>

/*
 * Setups implementations
 */
SetupDefine(SeededArraySetup) {
    struct kit_Array *sut = Option_unwrap(kit_Array_new(SEEDS_SIZE));

    assert_equal(SEEDS_SIZE, kit_Array_capacity(sut));
    for (size_t i = 0; i < SEEDS_SIZE; i++) {
        assert_null(Result_unwrap(kit_Array_set(sut, (void *) SEEDS[i], i)));
    }

    return sut;
}

/*
 * Teardowns implementations
 */
TeardownDefine(ArrayTeardown) {
    struct kit_Array *sut = traits_context;
    assert_not_null(sut);
    kit_Array_delete(sut);
}

/*
 * Fixtures implementations
 */
FixtureDefine(SeededArrayFixture, SeededArraySetup, ArrayTeardown);
