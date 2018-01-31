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
#include <kit/collections/string.h>

#define u(x) \
    Option_unwrap((x))

#define _s(x) \
        #x

#define s(x) \
        _s(x)

/*
 *
 */
int main() {
    kit_String string3 = u(kit_String_fromLiteral(" [> data field 3 <] "));
    string3 = u(kit_String_prependBytes(&string3, "\0\a\t\r\b\n\b\r\t\a\0", 11));
    string3 = u(kit_String_appendBytes(&string3, "\0\a\t\r\b\n\b\r\t\a\0", 11));
    string3 = u(kit_String_quote(&string3));
    printf("%s: (%3zu)[%3zu]`%s`\n", s(string3), kit_String_size(string3), kit_String_capacity(string3), string3);

    kit_String string2 = u(kit_String_fromLiteral(" [> data field 2 <] "));
    string2 = u(kit_String_prependBytes(&string2, "\0\a\t\r\b\n\b\r\t\a\0", 11));
    string2 = u(kit_String_appendBytes(&string2, "\0\a\t\r\b\n\b\r\t\a\0", 11));
    string2 = u(kit_String_quote(&string2));
    printf("%s: (%3zu)[%3zu]`%s`\n", s(string2), kit_String_size(string2), kit_String_capacity(string2), string2);

    kit_String string1 = u(kit_String_fromLiteral(" [> data field 1 <] "));
    string1 = u(kit_String_prependBytes(&string1, "\0\a\t\r\b\n\b\r\t\a\0", 11));
    string1 = u(kit_String_appendBytes(&string1, "\0\a\t\r\b\n\b\r\t\a\0", 11));
    string1 = u(kit_String_quote(&string1));
    printf("%s: (%3zu)[%3zu]`%s`\n", s(string1), kit_String_size(string1), kit_String_capacity(string1), string1);

    kit_String string = u(kit_String_new());
    printf("%s: (%3zu)[%3zu]`%s`\n", s(string), kit_String_size(string), kit_String_capacity(string), string);

    string = u(kit_String_prepend(&string, string3));
    printf("%s: (%3zu)[%3zu]`%s`\n", s(string), kit_String_size(string), kit_String_capacity(string), string);

    string = u(kit_String_prependLiteral(&string, "\n"));
    printf("%s: (%3zu)[%3zu]`%s`\n", s(string), kit_String_size(string), kit_String_capacity(string), string);

    string = u(kit_String_prependBytes(&string, string2, kit_String_size(string2)));
    printf("%s: (%3zu)[%3zu]`%s`\n", s(string), kit_String_size(string), kit_String_capacity(string), string);

    string = u(kit_String_prependFormat(&string, "\n%s\n", string1));
    printf("%s: (%3zu)[%3zu]`%s`\n", s(string), kit_String_size(string), kit_String_capacity(string), string);

    string = u(kit_String_appendLiteral(&string, "\n"));
    printf("%s: (%3zu)[%3zu]`%s`\n", s(string), kit_String_size(string), kit_String_capacity(string), string);

    kit_String_delete(kit_move((void **) &string3));
    kit_String_delete(kit_move((void **) &string2));
    kit_String_delete(kit_move((void **) &string1));
    kit_String_delete(kit_move((void **) &string));
    return 0;
}
