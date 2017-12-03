/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   December 01, 2017 
 */

#include <stdio.h>
#include <kit/utils.h>
#include <kit/collections/map.h>
#include <kit/collections/atom.h>
#include <kit/collections/array.h>

void report(struct kit_Map *map, struct kit_Array *keys);

/*
 *
 */
int main() {
#define I(x)    ImmutableOption_unwrap((x))
#define M(x)    MutableOption_unwrap((x))

    void *e = NULL;
    kit_Atom *accept = I(kit_Atom_fromLiteral("Accept"));
    kit_Atom *contentType = I(kit_Atom_fromLiteral("ContentType"));
    kit_Atom *authorization = I(kit_Atom_fromLiteral("Authorization"));
    struct kit_Map *map = M(kit_Map_fromHashMap(0, kit_compareFn, kit_hashFn));
    struct kit_Array *keys = M(kit_Array_from((void *) accept, (void *) contentType, (void *) authorization));

    report(map, keys);

    kit_Map_put(map, accept, (void *) I(kit_Atom_fromLiteral("text/plain")));
    kit_Map_put(map, contentType, (void *) I(kit_Atom_fromLiteral("application/json")));
    kit_Map_put(map, authorization, (void *) I(kit_Atom_fromLiteral("Basic QWxhZGRpbc2FtZQ==")));

    report(map, keys);

    printf("\nUpdating: `%s` ...\n", accept);
    kit_Map_put(map, accept, (void *) I(kit_Atom_fromLiteral("application/json")));

    report(map, keys);

    printf("\nRemoving: `%s` ...\n", authorization);
    kit_Map_pop(map, authorization, &e);

    report(map, keys);

    kit_invalidate((void **) &keys, kit_Array_delete);
    kit_invalidate((void **) &map, kit_Map_delete);
    return 0;

#undef M
#undef I
}

void report(struct kit_Map *map, struct kit_Array *keys) {
#define s(x)    ((const char *) (x))

    void *e;
    kit_Atom *atom1;
    kit_Atom *atom2;
    const char sep[] = "----------------------------------------------------------------------------------------------";

    printf("\n%.*s\n", (int) sizeof(sep), sep);
    printf("size: %zu\n", kit_Map_size(map));
    printf("isEmpty: %s", kit_truth(kit_Map_isEmpty(map)));
    for (size_t i = 0; i < kit_Array_capacity(keys); i++) {
        e = NULL;
        kit_Array_get(keys, &e, i);
        atom1 = e;
        e = NULL;
        kit_Map_get(map, atom1, &e);
        atom2 = e;
        printf("\n%s:\n\tpresent: %s\n\tvalue: %s", s(atom1), kit_truth(kit_Map_has(map, atom1)), s(atom2));
    }
    printf("\n%.*s\n", (int) sizeof(sep), sep);

#undef s
}
