#include <assert.h>
#include <kit/alloc/result.h>

AllocResult AllocResult_new(void *const ptr) {
    assert(ptr);
    return (AllocResult) { .ptr = ptr, .ok = true };
}

AllocResult AllocResult_fromError(const Error *const error) {
    assert(error);
    return (AllocResult) { .error = error, .ok = false };
}

AllocResult
AllocResult_fromNullable(void *const ptr, const Error *const error) {
    assert(error);
    return (ptr) ? AllocResult_new(ptr) : AllocResult_fromError(error);
}
