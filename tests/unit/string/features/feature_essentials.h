/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   December 12, 2017 
 */

#ifndef KIT_FEATURE_ESSENTIALS_INCLUDED
#define KIT_FEATURE_ESSENTIALS_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <traits-unit/traits-unit.h>

FeatureDeclare(StringNew);
FeatureDeclare(StringQuoted);
FeatureDeclare(StringFromBytes);
FeatureDeclare(StringFromFormat);
FeatureDeclare(StringFromLiteral);
FeatureDeclare(StringDuplicate);

#ifdef __cplusplus
}
#endif

#endif /* KIT_FEATURE_ESSENTIALS_INCLUDED */
