/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 22, 2017 
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
