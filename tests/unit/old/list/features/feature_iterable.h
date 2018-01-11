/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 25, 2017 
 */

#ifndef KIT_FEATURE_ITERABLE_INCLUDED
#define KIT_FEATURE_ITERABLE_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <traits-unit/traits-unit.h>

/*
 * Constructor/Destructor
 */
FeatureDeclare(ListIteratorFromEmptyListBoundaries);
FeatureDeclare(ListIteratorFromSeededListBoundaries);

/*
 * Rewind
 */
FeatureDeclare(ListIteratorRewindFromEmptyList);
FeatureDeclare(ListIteratorRewindFromSeededList);

/*
 * Traverse
 */
FeatureDeclare(ListIteratorReachTheBoundariesOfList);
FeatureDeclare(ListIteratorUpdateRetrievedElements);

/*
 * DetectModifications
 */
FeatureDeclare(ListIteratorDetectModifications);

#ifdef __cplusplus
}
#endif

#endif /* KIT_FEATURE_ITERABLE_INCLUDED */
