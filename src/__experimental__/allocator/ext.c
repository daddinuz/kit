#include <assert.h>
#include <memory.h>
#include <kit/__experimental__/allocator/ext.h>

#undef xemplace
#undef xallocate
#undef xduplicate
#undef xreallocate
#undef xdeallocate

AllocResult xallocate(const AllocatorExt *const allocator,
                      const MemoryLayout layout,
                      const Trace trace) {
    assert(allocator);
    assert(allocator->allocate);
    return allocator->allocate(layout, trace);
}

AllocResult xduplicate(const AllocatorExt *const allocator,
                       const void *const ptr,
                       const MemoryLayout layout,
                       const Trace trace) {
    assert(allocator);
    assert(allocator->allocate);
    assert(ptr);

    const AllocResult alloc = xallocate(allocator, layout, trace);
    if (alloc.ok) { memcpy(alloc.ptr, ptr, layout.size); }

    return alloc;
}

AllocResult xreallocate(const AllocatorExt *const allocator,
                        void *const ptr,
                        const MemoryLayout oldLayout,
                        const MemoryLayout newLayout,
                        const Trace trace) {
    assert(allocator);
    assert(allocator->reallocate);
    assert(ptr);
    return allocator->reallocate(ptr, oldLayout, newLayout, trace);
}

void xdeallocate(const AllocatorExt *const allocator,
                 void *const ptr,
                 const MemoryLayout layout,
                 const Trace trace) {
    assert(allocator);
    assert(allocator->deallocate);
    assert(ptr);
    allocator->deallocate(ptr, layout, trace);
}
