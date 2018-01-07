/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   December 01, 2017 
 */

#include <stdio.h>
#include <kit/utils.h>
#include <kit/collections/atom.h>
#include <kit/collections/map.h>

#define I(x)    ImmutableOption_unwrap((x))
#define M(x)    MutableOption_unwrap((x))

void report(struct kit_Map *map);

/*
 *
 */
int main() {
    kit_Atom accept = I(kit_Atom_fromLiteral("Accept"));
    kit_Atom contentType = I(kit_Atom_fromLiteral("ContentType"));
    kit_Atom authorization = I(kit_Atom_fromLiteral("Authorization"));
    struct kit_Map *map = M(kit_Map_fromHashMap(0, kit_compareFn, kit_hashFn));

    report(map);

    kit_Map_put(map, accept, (void *) I(kit_Atom_fromLiteral("text/plain")));
    kit_Map_put(map, contentType, (void *) I(kit_Atom_fromLiteral("application/json")));
    kit_Map_put(map, authorization, (void *) I(kit_Atom_fromLiteral("Basic QWxhZGRpbc2FtZQ==")));

    report(map);

    kit_Map_delete(kit_move((void **) &map));
    return 0;
}

void report(struct kit_Map *map) {
    struct kit_Pair pair;
    static const char S[] = "-----------------------------------------------------------------------------------------";
    struct kit_Map_Iterator *iterator = M(kit_Map_Iterator_new(map));

    printf("\n%s\n{\n", S);
    while (KIT_RESULT_OK == kit_Map_Iterator_next(iterator, &pair)) {
        printf("\t'%s': '%s',\n", (const char *) pair.key, (const char *) pair.value);
    }
    printf("}\n%s\n", S);

    kit_Map_Iterator_delete(kit_move((void **) &iterator));
}
