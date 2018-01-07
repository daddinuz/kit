/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   December 08, 2017 
 */

#include <stdio.h>
#include <kit/utils.h>
#include <kit/collections/string.h>

#define I(x)    ImmutableOption_unwrap((x))

/*
 *
 */
int main() {
    kit_String string = I(kit_String_fromFormat("%s %s!", "Hello", "World"));
    printf("(%3zu)[%3zu]`%s`\n", kit_String_size(string), kit_String_capacity(string), string);

    string = I(kit_String_appendFormat(&string, " %s %s!", "I'm evil!", "MuahUahUah"));
    printf("(%3zu)[%3zu]`%s`\n", kit_String_size(string), kit_String_capacity(string), string);

    string = I(kit_String_setBytes(&string, "abc\"\0\t\n\r\b\a123", 13));
    printf("(%3zu)[%3zu]`%s`\n", kit_String_size(string), kit_String_capacity(string), string);

    string = I(kit_String_quote(&string));
    printf("(%3zu)[%3zu]`%s`\n", kit_String_size(string), kit_String_capacity(string), string);

    kit_String_delete(kit_move((void **) &string));
    return 0;
}
