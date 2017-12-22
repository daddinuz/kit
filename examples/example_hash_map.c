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
#include <kit/collections/hash_map.h>

#define I(x)    ImmutableOption_unwrap((x))
#define M(x)    MutableOption_unwrap((x))

void report(struct kit_HashMap *map);

/*
 *
 */
int main() {
    kit_Atom accept = I(kit_Atom_fromLiteral("Accept"));
    kit_Atom contentType = I(kit_Atom_fromLiteral("ContentType"));
    kit_Atom authorization = I(kit_Atom_fromLiteral("Authorization"));
    struct kit_HashMap *map = M(kit_HashMap_new(0, kit_compareFn, kit_hashFn));

    report(map);

    kit_HashMap_put(map, accept, (void *) I(kit_Atom_fromLiteral("text/plain")));
    kit_HashMap_put(map, contentType, (void *) I(kit_Atom_fromLiteral("application/json")));
    kit_HashMap_put(map, authorization, (void *) I(kit_Atom_fromLiteral("Basic QWxhZGRpbc2FtZQ==")));

    report(map);

    kit_invalidate((void **) &map, kit_HashMap_delete);
    return 0;
}

void report(struct kit_HashMap *map) {
    static const char S[] = "-----------------------------------------------------------------------------------------";
    struct kit_HashMap_Iterator *iterator = M(kit_HashMap_Iterator_new(map));
    const void *key = NULL;
    void *value = NULL;

    printf("\n%.*s\n{\n", (int) sizeof(S), S);
    while (KIT_RESULT_OK == kit_HashMap_Iterator_next(iterator, &key, &value)) {
        printf("\t'%s': '%s',\n", (const char *) key, (const char *) value);
    }
    printf("}\n%.*s\n", (int) sizeof(S), S);

    kit_HashMap_Iterator_delete(iterator);
}
