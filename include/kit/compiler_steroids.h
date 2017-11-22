/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 21, 2017 
 */

#ifndef KIT_COMPILER_STEROIDS_INCLUDED
#define KIT_COMPILER_STEROIDS_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#if !(defined(__GNUC__) || defined(__clang__))
#define __attribute__(...)
#endif

#ifdef __cplusplus
}
#endif

#endif /* KIT_COMPILER_STEROIDS_INCLUDED */
