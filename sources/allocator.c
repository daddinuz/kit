/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 21, 2017 
 */

#include <kit/allocator/allocator.h>
#include <kit/allocator/allocator_config.h>

MutableOption __kit_Allocator_malloc(const char *file, const int line, const size_t size) {
    (void) file;
    (void) line;
    return __kit_Allocator_mallocFn(file, line, size);
}

MutableOption __kit_Allocator_calloc(const char *file, const int line, const size_t numberOfMembers, const size_t memberSize) {
    (void) file;
    (void) line;
    return __kit_Allocator_callocFn(file, line, numberOfMembers, memberSize);
}

MutableOption __kit_Allocator_ralloc(const char *file, const int line, void *ptr, const size_t newSize) {
    (void) file;
    (void) line;
    return __kit_Allocator_rallocFn(file, line, ptr, newSize);
}

MutableOption __kit_Allocator_copy(const char *file, const int line, void *dst, const void *src, const size_t size) {
    (void) file;
    (void) line;
    return __kit_Allocator_copyFn(file, line, dst, src, size);
}

MutableOption __kit_Allocator_move(const char *file, const int line, void *dst, const void *src, size_t size) {
    (void) file;
    (void) line;
    return __kit_Allocator_moveFn(file, line, dst, src, size);
}

MutableOption __kit_Allocator_set(const char *file, const int line, void *ptr, int value, const size_t size) {
    (void) file;
    (void) line;
    return __kit_Allocator_setFn(file, line, ptr, value, size);
}

void __kit_Allocator_free(const char *file, const int line, void *ptr) {
    (void) file;
    (void) line;
    __kit_Allocator_freeFn(file, line, ptr);
}
