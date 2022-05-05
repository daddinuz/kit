#include <errno.h>
#include <assert.h>
#include <stdlib.h>
#include <memory.h>

#include <kit/cta.h>
#include <kit/types.h>
#include <kit/alloc/errors.h>
#include <kit/alloc/result.h>
#include <kit/__experimental__/system/allocator/ext.h>

#define CHECK_LAYOUT(layout)                                                   \
    do {                                                                       \
        const MemoryLayout l = (layout);                                       \
        if (0 == l.align || 0 == l.size) {                                     \
            return AllocResult_fromError(UnsupportedLayout);                   \
        }                                                                      \
    } while (0)

cta(MUST_USE)
static AllocResult allocate(const MemoryLayout layout, const Trace trace) {
    (void)trace;

    CHECK_LAYOUT(layout);

    errno = 0;
    void *const ptr = aligned_alloc(layout.align, layout.size);
    return AllocResult_fromNullable(ptr,
                                    (ENOMEM == errno) ? OutOfMemory
                                                      : UnsupportedLayout);
}

cta(MUST_USE, DENY_NULL(1))
static AllocResult reallocate(void *const ptr,
                              const MemoryLayout oldLayout,
                              const MemoryLayout newLayout,
                              const Trace trace) {
    (void)trace;

    assert(ptr);
    CHECK_LAYOUT(oldLayout);
    CHECK_LAYOUT(newLayout);

    if (newLayout.align <= alignof(max_align_t)) {
        void *const newPtr = realloc(ptr, newLayout.size);
        return AllocResult_fromNullable(newPtr, OutOfMemory);
    }

    errno = 0;
    void *const newPtr = aligned_alloc(newLayout.align, newLayout.size);
    if (newPtr) {
        memcpy(newPtr, ptr, usize_min(oldLayout.size, newLayout.size));
        free(ptr);
        return AllocResult_new(newPtr);
    }

    return AllocResult_fromError((ENOMEM == errno) ? OutOfMemory
                                                   : UnsupportedLayout);
}

cta(DENY_NULL(1))
static void
deallocate(void *const ptr, const MemoryLayout layout, const Trace trace) {
    (void)trace;

    assert(ptr);
    assert(layout.size > 0);
    assert(layout.align > 0);

    free(ptr);
}

static const AllocatorExt instance = {
    .allocate = allocate,
    .reallocate = reallocate,
    .deallocate = deallocate,
};

const AllocatorExt *const SystemAllocatorExt = &instance;
