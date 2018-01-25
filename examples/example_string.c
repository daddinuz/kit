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

/*
 *
 */
int main() {
    kit_String string = u(kit_String_fromFormat("%s %s!", "Hello", "World"));
    printf("(%3zu)[%3zu]`%s`\n", kit_String_size(string), kit_String_capacity(string), string);

    string = u(kit_String_appendFormat(&string, " %s %s!", "I'm evil!", "MuahUahUah"));
    printf("(%3zu)[%3zu]`%s`\n", kit_String_size(string), kit_String_capacity(string), string);

    string = u(kit_String_setBytes(&string, "abc\"\0\t\n\r\b\a123", 13));
    printf("(%3zu)[%3zu]`%s`\n", kit_String_size(string), kit_String_capacity(string), string);

    string = u(kit_String_quote(&string));
    printf("(%3zu)[%3zu]`%s`\n", kit_String_size(string), kit_String_capacity(string), string);

    kit_String_delete(kit_move((void **) &string));
    return 0;
}
