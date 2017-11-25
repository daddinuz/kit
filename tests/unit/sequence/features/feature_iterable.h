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
FeatureDeclare(SequenceIteratorFromEmptySequenceBoundaries);
FeatureDeclare(SequenceIteratorFromSeededSequenceBoundaries);

/*
 * Rewind
 */
FeatureDeclare(SequenceIteratorRewindFromEmptySequence);
FeatureDeclare(SequenceIteratorRewindFromSeededSequence);

/*
 * Traverse
 */
FeatureDeclare(SequenceIteratorReachTheBoundariesOfSequence);
FeatureDeclare(SequenceIteratorUpdateRetrievedElements);

/*
 * DetectModifications
 */
FeatureDeclare(SequenceIteratorDetectModifications);

#ifdef __cplusplus
}
#endif

#endif /* KIT_FEATURE_ITERABLE_INCLUDED */
