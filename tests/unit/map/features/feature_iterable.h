/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   January 04, 2018 
 */

#ifndef KIT_FEATURE_ITERABLE_INCLUDED
#define KIT_FEATURE_ITERABLE_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <traits-unit/traits-unit.h>

FeatureDeclare(MapIteratorFromEmptyMap);
FeatureDeclare(MapIteratorRetrieveElements);
FeatureDeclare(MapIteratorUpdateElements);
FeatureDeclare(MapIteratorDetectModifications);

#ifdef __cplusplus
}
#endif

#endif /* KIT_FEATURE_ITERABLE_INCLUDED */
