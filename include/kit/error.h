/// @file

#pragma once

/**
 * Error interface.
 *
 * Users must ensure that following conditions uphold:
 * - Every Error instance must be immutable.
 * - Every Error instance must have static lifetime (whole program).
 *
 * Those conditions allow to check for Error equality just comparing
 * pointer to Error instances.
 *
 * example:
 * ```C
 * static const Error OutOfMemoryInstance = { "Out of memory" };
 * static const Error *const OutOfMemory = &OutOfMemoryInstance;
 *
 * const Error *something_that_fails(void) {
 *     // ...
 *     return OutOfMemory;
 * }
 *
 * int main(void) {
 *     if (OutOfMemory == something_that_fails()) {
 *         perror(OutOfMemory->description);
 *         // ...
 *     }
 *
 *     // ...
 * }
 * ```
 */

typedef struct Error {
    const char *const description;
} Error;
