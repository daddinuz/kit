/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 21, 2017 
 */

#ifndef KIT_UTILS_INCLUDED
#define KIT_UTILS_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <kit/compiler_steroids.h>

extern void
kit_swap(void **a, void **b) __attribute__((__nonnull__));

extern void
kit_invalidate(void **ref, void (*destructor)()) __attribute__((__nonnull__));

#ifdef __cplusplus
}
#endif

#endif /* KIT_UTILS_INCLUDED */
