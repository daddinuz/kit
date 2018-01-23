/*
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 *
 * Copyright (c) 2018 Davide Di Carlo
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
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

/**
 * Returns the string representation of the http method.
 *
 * @param method The http method.
 * @return The string representation of the http method.
 */
extern const char *
kit_HttpMethod_explain(enum kit_HttpMethod method)
__attribute__((__warn_unused_result__));

#ifdef __cplusplus
}
#endif

#endif /* kIT_HTTP_METHOD_INCLUDED */
