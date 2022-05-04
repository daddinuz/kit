#include <assert.h>
#include <memory.h>
#include <kit/allocator.h>

#undef emplace
#undef allocate
#undef duplicate
#undef reallocate
#undef deallocate

static const Error OutOfMemoryInstance = { "Out of memory" };
const Error *const OutOfMemory = &OutOfMemoryInstance;

static const Error UnsupportedLayoutInstance = { "Unsupported layout" };
const Error *const UnsupportedLayout = &UnsupportedLayoutInstance;

AllocResult AllocResult_ok(void *const ptr) {
    assert(ptr);
    return (AllocResult) { .ptr = ptr, .ok = true };
}

AllocResult AllocResult_err(const Error *const error) {
    assert(error);
    return (AllocResult) { .error = error, .ok = false };
}

AllocResult allocate(const Allocator *const allocator,
                     const MemoryLayout layout,
                     const Trace trace) {
    assert(allocator);
    assert(allocator->allocate);
    return allocator->allocate(layout, trace);
}

AllocResult duplicate(const Allocator *const allocator,
                      const void *const ptr,
                      const MemoryLayout layout,
                      const Trace trace) {
    assert(allocator);
    assert(allocator->allocate);
    assert(ptr);

    const AllocResult alloc = allocate(allocator, layout, trace);
    if (alloc.ok) { memcpy(alloc.ptr, ptr, layout.size); }

    return alloc;
}

AllocResult reallocate(const Allocator *const allocator,
                       void *const ptr,
                       const MemoryLayout oldLayout,
                       const MemoryLayout newLayout,
                       const Trace trace) {
    assert(allocator);
    assert(allocator->reallocate);
    assert(ptr);
    return allocator->reallocate(ptr, oldLayout, newLayout, trace);
}

void deallocate(const Allocator *const allocator,
                void *const ptr,
                const MemoryLayout layout,
                const Trace trace) {
    assert(allocator);
    assert(allocator->deallocate);
    assert(ptr);
    allocator->deallocate(ptr, layout, trace);
}
