/// @file

#pragma once

#include <kit/cta.h>
#include <kit/allocator.h>

cta(MUST_USE)
extern AllocResult SystemAllocator(void *ptr, usize size, Trace trace);
