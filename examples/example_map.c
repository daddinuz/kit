/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   December 01, 2017 
 */

#include <stdio.h>
#include <assert.h>
#include <kit/utils.h>
#include <kit/collections/map.h>
#include <kit/collections/atom.h>

#define u(x) \
    Option_unwrap((x))

static void
report(struct kit_Map *map)
__attribute__((__nonnull__));

/*
 *
 */
int main() {
    kit_Atom accept = u(kit_Atom_fromLiteral("Accept"));
    kit_Atom contentType = u(kit_Atom_fromLiteral("ContentType"));
    kit_Atom authorization = u(kit_Atom_fromLiteral("Authorization"));
    struct kit_Map *map = u(kit_Map_fromHashMap(0, kit_compareFn, kit_hashFn));

    assert(NULL == Result_unwrap(kit_Map_put(map, accept, u(kit_Atom_fromLiteral("text/plain")))));
    assert(NULL == Result_unwrap(kit_Map_put(map, contentType, u(kit_Atom_fromLiteral("application/json")))));
    assert(NULL == Result_unwrap(kit_Map_put(map, authorization, u(kit_Atom_fromLiteral("Basic QWxhZGRpbc2FtZQ==")))));

    report(map);

    assert(
            u(kit_Atom_fromLiteral("text/plain"))
            ==
            Result_unwrap(kit_Map_put(map, accept, u(kit_Atom_fromLiteral("text/csv"))))
    );

    kit_Map_delete(kit_move((void **) &map));
    return 0;
}

void report(struct kit_Map *map) {
    assert(map);
    Result result;
    struct kit_Pair *pair = u(kit_Pair_new("", NULL));
    struct kit_Map_Iterator *iterator = u(kit_Map_Iterator_new(map));

    printf("{\n");
    for (const char *key, *value; Result_isOk(result = kit_Map_Iterator_next(iterator, &pair)); /* _._ */) {
        assert(NULL == pair);
        pair = Result_unwrap(result);
        key = kit_Pair_getKey(pair);
        value = kit_Pair_getValue(pair);
        printf("  '%s': '%s',\n", key, value);
    }
    printf("}\n");

    kit_Pair_delete(kit_move((void **) &pair));
    kit_Map_Iterator_delete(kit_move((void **) &iterator));
}
