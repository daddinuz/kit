/// @file

#pragma once

#include <stdalign.h>
#include <kit/types.h>

typedef struct MemoryLayout {
    const usize align;
    const usize size;
} MemoryLayout;

#define layoutof(type)                                                         \
    ((MemoryLayout) { .align = alignof(type), .size = sizeof(type) })
