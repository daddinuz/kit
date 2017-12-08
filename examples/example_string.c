/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   December 08, 2017 
 */

#include <stdio.h>
#include <kit/collections/string.h>

#define I(x)    ImmutableOption_unwrap((x))
#define M(x)    MutableOption_unwrap((x))

/*
 *
 */
int main() {
    kit_String string = I(kit_String_fromLiteral("Hello World!"));
    printf("(%3zu)[%3zu]`%s`\n", kit_String_size(string), kit_String_capacity(string), string);

    string = I(kit_String_appendLiteral(&string, " How Are You?"));
    printf("(%3zu)[%3zu]`%s`\n", kit_String_size(string), kit_String_capacity(string), string);

    kit_String formatted = I(kit_String_format("%s %s %zu %d", "lorem", "ipsum", 3453534LU, -356));
    printf("(%3zu)[%3zu]`%s`\n", kit_String_size(formatted), kit_String_capacity(formatted), formatted);

    formatted = I(kit_String_append(&formatted, string));
    printf("(%3zu)[%3zu]`%s`\n", kit_String_size(formatted), kit_String_capacity(formatted), formatted);

    kit_String_clear(formatted);
    formatted = I(kit_String_shrink(&formatted));
    printf("(%3zu)[%3zu]`%s`\n", kit_String_size(formatted), kit_String_capacity(formatted), formatted);

    kit_String_delete(formatted);
    kit_String_delete(string);
    return 0;
}
