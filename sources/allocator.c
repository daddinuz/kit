/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 21, 2017 
 */

#include <kit/allocator/allocator.h>
#include <kit/allocator/allocator_selector.h>

void *__kit_Allocator_malloc(const char *file, const int line, const size_t size) {
    (void) file;
    (void) line;
    return __kit_Allocator_mallocFn(file, line, size);
}

void *__kit_Allocator_calloc(const char *file, const int line, const size_t memberSize, const size_t numberOfMembers) {
    (void) file;
    (void) line;
    return __kit_Allocator_callocFn(file, line, memberSize, numberOfMembers);
}

void *__kit_Allocator_ralloc(const char *file, const int line, void *ptr, const size_t newSize) {
    (void) file;
    (void) line;
    return __kit_Allocator_rallocFn(file, line, ptr, newSize);
}

void *__kit_Allocator_copy(const char *file, const int line, void *dst, const void *src, const size_t size) {
    (void) file;
    (void) line;
    return __kit_Allocator_copyFn(file, line, dst, src, size);
}

void *__kit_Allocator_move(const char *file, const int line, void *dst, const void *src, size_t size) {
    (void) file;
    (void) line;
    return __kit_Allocator_moveFn(file, line, dst, src, size);
}

void *__kit_Allocator_write(const char *file, const int line, void *ptr, int value, const size_t size) {
    (void) file;
    (void) line;
    return __kit_Allocator_writeFn(file, line, ptr, value, size);
}

void __kit_Allocator_free(const char *file, const int line, void *ptr) {
    (void) file;
    (void) line;
    __kit_Allocator_freeFn(file, line, ptr);
}
