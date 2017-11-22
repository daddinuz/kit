/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 21, 2017 
 */

#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <kit/collections/result.h>

const char *KIT_RESULT_OK_EXPLANATION = "Success";
const char *KIT_RESULT_OUT_OF_RANGE_ERROR_EXPLANATION = "Out of range";
const char *KIT_RESULT_OUT_OF_MEMORY_ERROR_EXPLANATION = "Out of memory";
const char *KIT_RESULT_ILLEGAL_STATE_ERROR_EXPLANATION = "Illegal state";
const char *KIT_RESULT_CONCURRENT_MODIFICATION_ERROR_EXPLANATION = "Concurrent modification";

const char *kit_Result_explain(enum kit_Result result) {
    switch (result) {
        case KIT_RESULT_OK:
            return KIT_RESULT_OK_EXPLANATION;
        case KIT_RESULT_OUT_OF_RANGE_ERROR:
            return KIT_RESULT_OUT_OF_RANGE_ERROR_EXPLANATION;
        case KIT_RESULT_OUT_OF_MEMORY_ERROR:
            return KIT_RESULT_OUT_OF_MEMORY_ERROR_EXPLANATION;
        case KIT_RESULT_ILLEGAL_STATE_ERROR:
            return KIT_RESULT_ILLEGAL_STATE_ERROR_EXPLANATION;
        case KIT_RESULT_CONCURRENT_MODIFICATION_ERROR:
            return KIT_RESULT_CONCURRENT_MODIFICATION_ERROR_EXPLANATION;
        default:
            assert(false);
            abort();
    }
}
