/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   December 03, 2017 
 */

#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <kit/networking/http_method.h>

static const char KIT_HTTP_METHOD_DELETE_EXPLANATION[] = "DELETE";
static const char KIT_HTTP_METHOD_GET_EXPLANATION[] = "GET";
static const char KIT_HTTP_METHOD_HEAD_EXPLANATION[] = "HEAD";
static const char KIT_HTTP_METHOD_POST_EXPLANATION[] = "POST";
static const char KIT_HTTP_METHOD_PUT_EXPLANATION[] = "PUT";
static const char KIT_HTTP_METHOD_CONNECT_EXPLANATION[] = "CONNECT";
static const char KIT_HTTP_METHOD_OPTIONS_EXPLANATION[] = "OPTIONS";
static const char KIT_HTTP_METHOD_TRACE_EXPLANATION[] = "TRACE";
static const char KIT_HTTP_METHOD_COPY_EXPLANATION[] = "COPY";
static const char KIT_HTTP_METHOD_LOCK_EXPLANATION[] = "LOCK";
static const char KIT_HTTP_METHOD_MOVE_EXPLANATION[] = "MOVE";
static const char KIT_HTTP_METHOD_SEARCH_EXPLANATION[] = "SEARCH";
static const char KIT_HTTP_METHOD_UNLOCK_EXPLANATION[] = "UNLOCK";
static const char KIT_HTTP_METHOD_BIND_EXPLANATION[] = "BIND";
static const char KIT_HTTP_METHOD_REBIND_EXPLANATION[] = "REBIND";
static const char KIT_HTTP_METHOD_UNBIND_EXPLANATION[] = "UNBIND";
static const char KIT_HTTP_METHOD_REPORT_EXPLANATION[] = "REPORT";
static const char KIT_HTTP_METHOD_CHECKOUT_EXPLANATION[] = "CHECKOUT";
static const char KIT_HTTP_METHOD_MERGE_EXPLANATION[] = "MERGE";
static const char KIT_HTTP_METHOD_NOTIFY_EXPLANATION[] = "NOTIFY";
static const char KIT_HTTP_METHOD_SUBSCRIBE_EXPLANATION[] = "SUBSCRIBE";
static const char KIT_HTTP_METHOD_UNSUBSCRIBE_EXPLANATION[] = "UNSUBSCRIBE";
static const char KIT_HTTP_METHOD_PATCH_EXPLANATION[] = "PATCH";
static const char KIT_HTTP_METHOD_PURGE_EXPLANATION[] = "PURGE";
static const char KIT_HTTP_METHOD_LINK_EXPLANATION[] = "LINK";
static const char KIT_HTTP_METHOD_UNLINK_EXPLANATION[] = "UNLINK";

const char *kit_HttpMethod_explain(enum kit_HttpMethod method) {
    switch (method) {
        case KIT_HTTP_METHOD_DELETE:
            return KIT_HTTP_METHOD_DELETE_EXPLANATION;
        case KIT_HTTP_METHOD_GET:
            return KIT_HTTP_METHOD_GET_EXPLANATION;
        case KIT_HTTP_METHOD_HEAD:
            return KIT_HTTP_METHOD_HEAD_EXPLANATION;
        case KIT_HTTP_METHOD_POST:
            return KIT_HTTP_METHOD_POST_EXPLANATION;
        case KIT_HTTP_METHOD_PUT:
            return KIT_HTTP_METHOD_PUT_EXPLANATION;
        case KIT_HTTP_METHOD_CONNECT:
            return KIT_HTTP_METHOD_CONNECT_EXPLANATION;
        case KIT_HTTP_METHOD_OPTIONS:
            return KIT_HTTP_METHOD_OPTIONS_EXPLANATION;
        case KIT_HTTP_METHOD_TRACE:
            return KIT_HTTP_METHOD_TRACE_EXPLANATION;
        case KIT_HTTP_METHOD_COPY:
            return KIT_HTTP_METHOD_COPY_EXPLANATION;
        case KIT_HTTP_METHOD_LOCK:
            return KIT_HTTP_METHOD_LOCK_EXPLANATION;
        case KIT_HTTP_METHOD_MOVE:
            return KIT_HTTP_METHOD_MOVE_EXPLANATION;
        case KIT_HTTP_METHOD_SEARCH:
            return KIT_HTTP_METHOD_SEARCH_EXPLANATION;
        case KIT_HTTP_METHOD_UNLOCK:
            return KIT_HTTP_METHOD_UNLOCK_EXPLANATION;
        case KIT_HTTP_METHOD_BIND:
            return KIT_HTTP_METHOD_BIND_EXPLANATION;
        case KIT_HTTP_METHOD_REBIND:
            return KIT_HTTP_METHOD_REBIND_EXPLANATION;
        case KIT_HTTP_METHOD_UNBIND:
            return KIT_HTTP_METHOD_UNBIND_EXPLANATION;
        case KIT_HTTP_METHOD_REPORT:
            return KIT_HTTP_METHOD_REPORT_EXPLANATION;
        case KIT_HTTP_METHOD_CHECKOUT:
            return KIT_HTTP_METHOD_CHECKOUT_EXPLANATION;
        case KIT_HTTP_METHOD_MERGE:
            return KIT_HTTP_METHOD_MERGE_EXPLANATION;
        case KIT_HTTP_METHOD_NOTIFY:
            return KIT_HTTP_METHOD_NOTIFY_EXPLANATION;
        case KIT_HTTP_METHOD_SUBSCRIBE:
            return KIT_HTTP_METHOD_SUBSCRIBE_EXPLANATION;
        case KIT_HTTP_METHOD_UNSUBSCRIBE:
            return KIT_HTTP_METHOD_UNSUBSCRIBE_EXPLANATION;
        case KIT_HTTP_METHOD_PATCH:
            return KIT_HTTP_METHOD_PATCH_EXPLANATION;
        case KIT_HTTP_METHOD_PURGE:
            return KIT_HTTP_METHOD_PURGE_EXPLANATION;
        case KIT_HTTP_METHOD_LINK:
            return KIT_HTTP_METHOD_LINK_EXPLANATION;
        case KIT_HTTP_METHOD_UNLINK:
            return KIT_HTTP_METHOD_UNLINK_EXPLANATION;
        default:
            assert(false);
            abort();
    }
}
