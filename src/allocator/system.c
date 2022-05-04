#include <assert.h>
#include <stdlib.h>
#include <memory.h>

#include <kit/cta.h>
#include <kit/types.h>
#include <kit/allocator/system.h>

cta(MUST_USE)
static AllocResult
systemAllocate(const MemoryLayout layout, const Trace trace) {
    (void)trace;

    void *const ptr = aligned_alloc(layout.align, layout.size);
    return AllocResult_fromNullable(ptr, OutOfMemory);
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
        return AllocResult_fromNullable(newPtr, OutOfMemory);
    }

    void *const newPtr = aligned_alloc(newLayout.align, newLayout.size);
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
    free(ptr);
}

static const Allocator instance = {
    .allocate = systemAllocate,
    .reallocate = systemReallocate,
    .deallocate = systemDeallocate,
};

const Allocator *const SystemAllocator = &instance;
