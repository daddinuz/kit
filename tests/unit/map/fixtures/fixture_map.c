/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   December 30, 2017 
 */

#include <seeds.h>
#include <traits/traits.h>
#include <fixtures/fixture_map.h>
#include <kit/utils.h>
#include <kit/collections/map.h>
#include <kit/collections/atom.h>

/*
 * kit_MapType
 */
enum kit_MapType {
    KIT_MAP_TYPE_HASH_MAP,
};

/*
 * Helpers declarations
 */
static struct kit_Map *
setup_map_helper(enum kit_MapType type, const char *const *seeds, size_t seeds_size);

/*
 * Setups implementations
 */
SetupDefine(EmptyMapHashMapSetup) {
    return setup_map_helper(KIT_MAP_TYPE_HASH_MAP, NULL, 0);
}

SetupDefine(SeededMapHashMapSetup) {
    return setup_map_helper(KIT_MAP_TYPE_HASH_MAP, SEEDS, SEEDS_SIZE);
}

/*
 * Teardowns implementations
 */
TeardownDefine(MapTeardown) {
    struct kit_Map *sut = traits_context;
    assert_not_null(sut);
    kit_Map_delete(sut);
}

/*
 * Fixtures implementations
 */
FixtureDefine(EmptyMapHashMapFixture, EmptyMapHashMapSetup, MapTeardown);
FixtureDefine(SeededMapHashMapFixture, SeededMapHashMapSetup, MapTeardown);

/*
 * Helpers implementations
 */
struct kit_Map *
setup_map_helper(enum kit_MapType type, const char *const seeds[], const size_t seeds_size) {
    assert_true((seeds && seeds_size) > 0 || (NULL == seeds && seeds_size == 0));
    struct kit_Map *sut = NULL;

    switch (type) {
        case KIT_MAP_TYPE_HASH_MAP:
            sut = MutableOption_unwrap(kit_Map_fromHashMap(0, kit_compareFn, kit_hashFn));
            break;
        default:
            traits_assert(false);
    }

    assert_not_null(sut);

    if (seeds) {
        const size_t SIZE = seeds_size / 2;
        const size_t COUPLES = SIZE * 2;
        for (size_t i = 0; i < COUPLES;) {
            kit_Atom key = ImmutableOption_unwrap(kit_Atom_fromLiteral(seeds[i++]));
            char *value = (void *) seeds[i++];
            assert_equal(KIT_RESULT_OK, kit_Map_put(sut, key, value));
        }
        assert_equal(SIZE, kit_Map_size(sut));
    }

    return sut;
}
