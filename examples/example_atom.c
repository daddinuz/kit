/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 22, 2017 
 */

#include <stdio.h>
#include <kit/collections/atom.h>

#define bool2string(x)  (((x)) ? "true" : "false")

/*
 *
 */
int main() {
    kit_Atom literal = Option_unwrap(kit_Atom_fromLiteral("Hello World!"));
    kit_Atom integer = Option_unwrap(kit_Atom_fromInteger(-865765909809282));
    kit_Atom floating = Option_unwrap(kit_Atom_fromFloating(86576583.986764));

    printf(
            "Atom[%zu]: `%s` (%s)\n",
            kit_Atom_length(literal), literal, bool2string(
                    Option_unwrap(kit_Atom_fromLiteral("Hello World!")) == literal)
    );

    printf(
            "Atom[%zu]: `%s` (%s)\n",
            kit_Atom_length(integer), integer, bool2string(
                    Option_unwrap(kit_Atom_fromInteger(-865765909809282)) == integer)
    );

    printf(
            "Atom[%zu]: `%s` (%s)\n",
            kit_Atom_length(floating), floating, bool2string(
                    Option_unwrap(kit_Atom_fromFloating(86576583.986764)) == floating)
    );

    return 0;
}