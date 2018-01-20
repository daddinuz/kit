/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   December 16, 2017 
 */

#ifndef KIT_FEATURE_MUTABLE_INCLUDED
#define KIT_FEATURE_MUTABLE_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <traits-unit/traits-unit.h>

FeatureDeclare(StringAppend);
FeatureDeclare(StringAppendBytes);
FeatureDeclare(StringAppendFormat);
FeatureDeclare(StringAppendLiteral);
FeatureDeclare(StringSet);
FeatureDeclare(StringSetBytes);
FeatureDeclare(StringSetFormat);
FeatureDeclare(StringSetLiteral);
FeatureDeclare(StringQuote);
FeatureDeclare(StringClear);

#ifdef __cplusplus
}
#endif

#endif /* KIT_FEATURE_MUTABLE_INCLUDED */
