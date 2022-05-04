/// @file

#pragma once

/**
 * Pre-Processor utils.
 */

#define VA_HEAD_IMPL(x, ...) x
#define VA_HEAD(...)         VA_HEAD_IMPL(__VA_ARGS__, 0)

#define VA_TAIL_IMPL(_, ...) __VA_ARGS__
#define VA_TAIL(...)         VA_TAIL_IMPL(__VA_ARGS__, 0)

#define STRINGIZE(x) #x
#define STRINGIFY(x) STRINGIZE(x)
