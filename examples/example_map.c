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

#include <stdio.h>
#include <kit/utils.h>
#include <kit/collections/map.h>
#include <kit/collections/atom.h>

#define _(x)            ((void) ((x) ? 1 : 0));

static void
report(struct kit_Map *map)
__attribute__((__nonnull__));

/*
 *
 */
int main() {
    kit_Atom accept = Option_unwrap(kit_Atom_fromLiteral("Accept"));
    kit_Atom contentType = Option_unwrap(kit_Atom_fromLiteral("ContentType"));
    kit_Atom authorization = Option_unwrap(kit_Atom_fromLiteral("Authorization"));
    struct kit_Map *map = Option_unwrap(kit_Map_fromHashMap(0, kit_compareFn, kit_hashFn));

    _(Result_unwrap(kit_Map_put(map, accept, Option_unwrap(kit_Atom_fromLiteral("text/plain")))));
    _(Result_unwrap(kit_Map_put(map, contentType, Option_unwrap(kit_Atom_fromLiteral("application/json")))));
    _(Result_unwrap(kit_Map_put(map, authorization, Option_unwrap(kit_Atom_fromLiteral("Basic QWxhZGRpbc2FtZQ==")))));

    report(map);

    _(Result_unwrap(kit_Map_put(map, accept, Option_unwrap(kit_Atom_fromLiteral("text/csv")))));

    kit_Map_delete(kit_move((void **) &map));
    return 0;
}

void report(struct kit_Map *map) {
    Result result;
    struct kit_Pair *pair = Option_unwrap(kit_Pair_new("", NULL));
    struct kit_Map_Iterator *iterator = Option_unwrap(kit_Map_Iterator_new(map));

    printf("{\n");
    for (const char *key, *value; Result_isOk(result = kit_Map_Iterator_next(iterator, &pair)); /* _._ */) {
        pair = Result_unwrap(result);
        key = kit_Pair_getKey(pair);
        value = kit_Pair_getValue(pair);
        printf("  '%s': '%s',\n", key, value);
    }
    printf("}\n");

    kit_Pair_delete(kit_move((void **) &pair));
    kit_Map_Iterator_delete(kit_move((void **) &iterator));
}
