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

#ifndef KIT_ATOM_INCLUDED
#define KIT_ATOM_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdbool.h>
#include <option/option.h>
#include <kit/compiler_steroids.h>

/**
 * Atoms are pointers to a unique, immutable, sequence of zero or more arbitrary bytes.
 * There is only a single occurrence of any atom, which is why it’s called an atom.
 * Two atoms are identical if they point to the same location.
 * One of the advantages of atoms is that comparing two byte sequences for equality is performed by simply comparing pointers.
 * Another advantage is that using atoms saves space because there’s only one occurrence of each sequence.
 * Atoms are often used as keys in data structures that are indexed by sequences of arbitrary bytes instead of by integers.
 */
typedef const char *kit_Atom;

/**
 * Gets the kit_Atom instance or creates a new one if not exists from a sequence of bytes.
 *
 * @param bytes The sequence of bytes [<b>must not be NULL</b>].
 * @param length The length of the sequence.
 * @return A new instance of kit_Atom or None.
 */
extern OptionOf(kit_Atom)
kit_Atom_put(const void *bytes, size_t length)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Behaves like kit_Atom_put but takes a string literal and converts it to an atom.
 *
 * @param literal The string literal [<b>must not be NULL</b>].
 * @return A new instance of kit_Atom or None.
 */
extern OptionOf(kit_Atom)
kit_Atom_fromLiteral(const char *literal)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Behaves like kit_Atom_put but takes an integer number and converts it to an atom.
 *
 * @param n The number to be converted.
 * @return A new instance of kit_Atom or None.
 */
extern OptionOf(kit_Atom)
kit_Atom_fromInteger(long long n)
__attribute__((__warn_unused_result__));

/**
 * Behaves like kit_Atom_put but takes an floating number and converts it to an atom.
 *
 * @param n The number to be converted.
 * @return A new instance of kit_Atom or None.
 */
extern OptionOf(kit_Atom)
kit_Atom_fromFloating(long double n)
__attribute__((__warn_unused_result__));

/**
 * Gets the length of the atom.
 *
 * @attention
 *  This function requires a kit_Atom instance (not just any string!).
 *
 * @param atom The kit_Atom instance [<b>must not be NULL</b>].
 * @return The length of the atom.
 */
extern size_t
kit_Atom_length(kit_Atom atom)
__attribute__((__warn_unused_result__, __nonnull__));

#ifdef __cplusplus
}
#endif

#endif /* KIT_ATOM_INCLUDED */
