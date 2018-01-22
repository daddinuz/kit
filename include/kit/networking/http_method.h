/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 22, 2017
 */

#ifndef kIT_HTTP_METHOD_INCLUDED
#define kIT_HTTP_METHOD_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <kit/compiler_steroids.h>

enum kit_HttpMethod {
    KIT_HTTP_METHOD_DELETE,
    KIT_HTTP_METHOD_GET,
    KIT_HTTP_METHOD_HEAD,
    KIT_HTTP_METHOD_POST,
    KIT_HTTP_METHOD_PUT,
    KIT_HTTP_METHOD_CONNECT,
    KIT_HTTP_METHOD_OPTIONS,
    KIT_HTTP_METHOD_TRACE,
    KIT_HTTP_METHOD_COPY,
    KIT_HTTP_METHOD_LOCK,
    KIT_HTTP_METHOD_MOVE,
    KIT_HTTP_METHOD_SEARCH,
    KIT_HTTP_METHOD_UNLOCK,
    KIT_HTTP_METHOD_BIND,
    KIT_HTTP_METHOD_REBIND,
    KIT_HTTP_METHOD_UNBIND,
    KIT_HTTP_METHOD_REPORT,
    KIT_HTTP_METHOD_CHECKOUT,
    KIT_HTTP_METHOD_MERGE,
    KIT_HTTP_METHOD_NOTIFY,
    KIT_HTTP_METHOD_SUBSCRIBE,
    KIT_HTTP_METHOD_UNSUBSCRIBE,
    KIT_HTTP_METHOD_PATCH,
    KIT_HTTP_METHOD_PURGE,
    KIT_HTTP_METHOD_LINK,
    KIT_HTTP_METHOD_UNLINK
};

extern const char *
kit_HttpMethod_explain(enum kit_HttpMethod method)
__attribute__((__warn_unused_result__));

#ifdef __cplusplus
}
#endif

#endif /* kIT_HTTP_METHOD_INCLUDED */
