/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   January 11, 2018 
 */

#ifndef KIT_ERRORS_INCLUDED
#define KIT_ERRORS_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <option/option.h>

extern Error OutOfRangeError;
extern Error OutOfMemoryError;
extern Error IllegalStateError;
extern Error ConcurrentModificationError;

#ifdef __cplusplus
}
#endif

#endif /* KIT_ERRORS_INCLUDED */
