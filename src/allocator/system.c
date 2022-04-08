#include <assert.h>
#include <stdlib.h>
#include <memory.h>

#include <kit/cta.h>
#include <kit/dbg.h>
#include <kit/types.h>
#include <kit/allocator/system.h>

cta(MUST_USE)
static AllocResult
systemAllocate(const MemoryLayout layout, const Trace trace) {
    (void)trace;

    void *const ptr = aligned_alloc(layout.align, layout.size);
    dbg("\n\tAt %s@%s:%d\n\t- allocate(align=%zu, size=%zu) -> %p\n",
        trace.func,
        trace.file,
        trace.line,
        layout.align,
        layout.size,
        ptr);

    return ptr ? AllocResult_ok(ptr) : AllocResult_err(OutOfMemory);
}

cta(MUST_USE, DENY_NULL(1))
static AllocResult systemReallocate(void *const ptr,
                                    const MemoryLayout oldLayout,
                                    const MemoryLayout newLayout,
                                    const Trace trace) {
    (void)trace;
    assert(ptr);

    if (newLayout.align <= alignof(max_align_t)) {
        void *const newPtr = realloc(ptr, newLayout.size);
        dbg("\n\tAt %s@%s:%d\n\t- reallocate(ptr=%p, oldAlign=%zu, "
            "oldSize=%zu, "
            "newAlign=%zu, newSize=%zu) -> %p\n",
            trace.func,
            trace.file,
            trace.line,
            ptr,
            oldLayout.align,
            oldLayout.size,
            newLayout.align,
            newLayout.size,
            newPtr);

        return newPtr ? AllocResult_ok(newPtr) : AllocResult_err(OutOfMemory);
    }

    void *const newPtr = aligned_alloc(newLayout.align, newLayout.size);
    dbg("\n\tAt %s@%s:%d\n\t- reallocate(ptr=%p, oldAlign=%zu, oldSize=%zu, "
        "newAlign=%zu, newSize=%zu) -> %p\n",
        trace.func,
        trace.file,
        trace.line,
        ptr,
        oldLayout.align,
        oldLayout.size,
        newLayout.align,
        newLayout.size,
        newPtr);

    if (newPtr) {
        memcpy(newPtr, ptr, usize_min(oldLayout.size, newLayout.size));
        free(ptr);
        return AllocResult_ok(newPtr);
    }

    return AllocResult_err(OutOfMemory);
}

cta(DENY_NULL(1))
static void systemDeallocate(void *const ptr,
                             const MemoryLayout layout,
                             const Trace trace) {
    (void)layout;
    (void)trace;
    assert(ptr);

    dbg("\n\tAt %s@%s:%d\n\t- deallocate(ptr=%p, align=%zu, size=%zu)\n",
        trace.func,
        trace.file,
        trace.line,
        ptr,
        layout.align,
        layout.size);

    free(ptr);
}

static const Allocator instance = {
    .allocate = systemAllocate,
    .reallocate = systemReallocate,
    .deallocate = systemDeallocate,
};

const Allocator *const SystemAllocator = &instance;
