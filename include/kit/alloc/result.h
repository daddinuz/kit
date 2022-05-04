/// @file

/**
 * An allocation may result in either a valid memory area pointed by ptr or an
 * error. It's user reposibility to uphold the following invariants:
 * - ok is true and ptr points to a still allocated valid memory area
 * - ok is false and error is set to the cause of the failure
 * (neither ptr nor error are allowed to be null)
 */

#pragma once

#include <kit/cta.h>
#include <kit/types.h>
#include <kit/error.h>

typedef struct AllocResult {
    union {
        void *const ptr;
        const Error *const error;
    };
    const bool ok;
} AllocResult;

cta(MUST_USE, DENY_NULL(1))
extern AllocResult AllocResult_new(void *ptr);

cta(MUST_USE, DENY_NULL(1))
extern AllocResult AllocResult_fromError(const Error *error);

cta(MUST_USE, DENY_NULL(2))
extern AllocResult AllocResult_fromNullable(void *ptr, const Error *error);
