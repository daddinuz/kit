/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 21, 2017 
 */

#ifndef KIT_RESULT_INCLUDED
#define KIT_RESULT_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

enum kit_Result {
    KIT_RESULT_OK,
    KIT_RESULT_OUT_OF_RANGE_ERROR,
    KIT_RESULT_OUT_OF_MEMORY_ERROR,
    KIT_RESULT_ILLEGAL_STATE_ERROR,
    KIT_RESULT_CONCURRENT_MODIFICATION_ERROR,
};

extern const char *
kit_Result_explain(enum kit_Result result);

#ifdef __cplusplus
}
#endif

#endif /* KIT_RESULT_INCLUDED */
