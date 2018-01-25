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
#include <kit/collections/atom.h>

#define u(xOption) \
    Option_unwrap(xOption)

/*
 *
 */
int main() {
    kit_Atom literal = u(kit_Atom_fromLiteral("Hello World!"));
    kit_Atom integer = u(kit_Atom_fromInteger(-865765909809282));
    kit_Atom floating = u(kit_Atom_fromFloating(86576583.986764));

    printf(
            "Atom[%zu]: `%s` (%s)\n",
            kit_Atom_length(literal), literal, kit_truth(u(kit_Atom_fromLiteral("Hello World!")) == literal)
    );

    printf(
            "Atom[%zu]: `%s` (%s)\n",
            kit_Atom_length(integer), integer, kit_truth(u(kit_Atom_fromInteger(-865765909809282)) == integer)
    );

    printf(
            "Atom[%zu]: `%s` (%s)\n",
            kit_Atom_length(floating), floating, kit_truth(u(kit_Atom_fromFloating(86576583.986764)) == floating)
    );

    return 0;
}
