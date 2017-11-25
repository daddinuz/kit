/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 25, 2017 
 */

#ifndef KIT_FIXTURE_LIST_CONTEXT_INCLUDED
#define KIT_FIXTURE_LIST_CONTEXT_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <kit/collections/list.h>

struct kit_Traits_ListIteratorContext {
    struct kit_List *list;
    struct kit_List_Iterator *sut;
};

#ifdef __cplusplus
}
#endif

#endif /* KIT_FIXTURE_LIST_CONTEXT_INCLUDED */
