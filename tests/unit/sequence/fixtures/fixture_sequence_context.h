/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 25, 2017 
 */

#ifndef KIT_FIXTURE_SEQUENCE_CONTEXT_INCLUDED
#define KIT_FIXTURE_SEQUENCE_CONTEXT_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <kit/collections/sequence.h>

struct kit_Traits_SequenceIteratorContext {
    struct kit_Sequence *sequence;
    struct kit_Sequence_Iterator *sut;
};

#ifdef __cplusplus
}
#endif

#endif /* KIT_FIXTURE_SEQUENCE_CONTEXT_INCLUDED */
