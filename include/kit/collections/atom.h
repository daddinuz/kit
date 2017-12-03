/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 21, 2017 
 */

/*
 * Atoms are pointers to a unique, immutable, sequence of zero or more arbitrary bytes.
 * There is only a single occurrence of any atom, which is why it’s called an atom.
 * Two atoms are identical if they point to the same location.
 * One of the advantages of atoms is that comparing two byte sequences for equality is performed by simply comparing pointers.
 * Another advantage is that using atoms saves space because there’s only one occurrence of each sequence.
 * Atoms are often used as keys in data structures that are indexed by sequences of arbitrary bytes instead of by integers.
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
 * kit_Atom interface.
 */
typedef const char *kit_Atom;

/**
 * Gets the kit_Atom instance or creates if not exists from a pointer
 * to a sequence of bytes and the number of bytes in that sequence.
 *
 * If the atom already exists, increments the hits of the atom,
 * otherwise adds a new atom to the table of atoms, and returns the new atom instance.
 *
 * An atom is always terminated with a null character, which kit_Atom_new adds when necessary.
 *
 * Checked runtime errors:
 *      - @param s must not be NULL.
 *
 * @param s The sequence of bytes.
 * @param length The length of the sequence.
 * @return An MutableOption containing a kit_Atom instance or MutableOption_None in case of out of memory.
 */
extern MutableOptional(kit_Atom)
kit_Atom_put(const char *s, size_t length)
__attribute__((__nonnull__));

/**
 * Behaves like kit_Atom_put but takes a string literal and converts it to an atom.
 *
 * Checked runtime errors:
 *      - @param s must not be NULL.
 *
 * @param s The string literal to be converted.
 * @return An MutableOption containing a kit_Atom instance or MutableOption_None in case of out of memory.
 */
extern MutableOptional(kit_Atom)
kit_Atom_fromLiteral(const char *s)
__attribute__((__nonnull__));

/**
 * Behaves like kit_Atom_put but takes an integer number and converts it to an atom.
 *
 * Checked runtime errors:
 *      - @param s must not be NULL.
 *
 * @param n The integer number to be converted.
 * @return An MutableOption containing a kit_Atom instance or MutableOption_None in case of out of memory.
 */
extern MutableOptional(kit_Atom)
kit_Atom_fromInteger(long long n);

/**
 * Behaves like kit_Atom_put but takes an floating number and converts it to an atom.
 *
 * Checked runtime errors:
 *      - @param s must not be NULL.
 *
 * @param n The floating number to be converted.
 * @return An MutableOption containing a kit_Atom instance or MutableOption_None in case of out of memory.
 */
extern MutableOptional(kit_Atom)
kit_Atom_fromFloating(long double n);

/**
 * Gets the length of the atom.
 *
 * Checked runtime errors:
 *      - @param atom must not be NULL and must be a valid atom instance (not just a common string!)
 *
 * @param atom The atom instance.
 * @return The length of the atom.
 */
extern size_t
kit_Atom_length(kit_Atom atom)
__attribute__((__nonnull__));

#ifdef __cplusplus
}
#endif

#endif /* KIT_ATOM_INCLUDED */
