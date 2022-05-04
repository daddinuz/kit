#include <assert.h>
#include <memory.h>
#include <kit/allocator.h>

#undef emplace
#undef allocate
#undef duplicate
#undef reallocate
#undef deallocate

AllocResult
allocate(const Allocator allocator, const usize size, const Trace trace) {
    assert(allocator);
    assert(size > 0);
    return allocator(NULL, size, trace);
}

AllocResult duplicate(const Allocator allocator,
                      const void *const ptr,
                      const usize size,
                      const Trace trace) {
    assert(allocator);
    assert(ptr);
    assert(size > 0);
    const AllocResult alloc = allocate(allocator, size, trace);
    if (alloc.ok) { memcpy(alloc.ptr, ptr, size); }
    return alloc;
}

AllocResult reallocate(const Allocator allocator,
                       void *const ptr,
                       const usize size,
                       const Trace trace) {
    assert(allocator);
    assert(ptr);
    assert(size > 0);
    return allocator(ptr, size, trace);
}

void deallocate(const Allocator allocator, void *const ptr, const Trace trace) {
    assert(allocator);
    assert(ptr);
    allocator(ptr, 0, trace);
}
