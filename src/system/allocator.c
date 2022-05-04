#include <stdlib.h>
#include <kit/alloc/errors.h>
#include <kit/system/allocator.h>

#define NULL_PTR  2
#define ZERO_SIZE 1

static int DUMMY = 0;

AllocResult SystemAllocator(void *ptr, const usize size, const Trace trace) {
    (void)trace;
    const int selector = ((NULL == ptr) << 1) | (0 == size);
    ptr = (&DUMMY == ptr) ? NULL : ptr;

    switch (selector) {
        case NULL_PTR | ZERO_SIZE: {  // NULL == ptr && 0 == size
            return AllocResult_fromError(UnsupportedLayout);
        }
        case NULL_PTR: {  // NULL == ptr && 0 < size
            void *const newPtr = calloc(1, size);
            return AllocResult_fromNullable(newPtr, OutOfMemory);
        }
        case ZERO_SIZE: {  // NULL != ptr && 0 == size
            free(ptr);
            return AllocResult_new(&DUMMY);
        }
        default: {  // NULL != ptr && 0 < size
            void *const newPtr = realloc(ptr, size);
            return AllocResult_fromNullable(newPtr, OutOfMemory);
        }
    }
}
