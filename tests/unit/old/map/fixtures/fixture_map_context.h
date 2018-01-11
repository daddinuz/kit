/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   January 04, 2018 
 */

#ifndef KIT_FIXTURE_MAP_CONTEXT_INCLUDED
#define KIT_FIXTURE_MAP_CONTEXT_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <kit/collections/map.h.old>

struct kit_Traits_MapIteratorContext {
    struct kit_Map *map;
    struct kit_Map_Iterator *sut;
};

#ifdef __cplusplus
}
#endif

#endif /* KIT_FIXTURE_MAP_CONTEXT_INCLUDED */
