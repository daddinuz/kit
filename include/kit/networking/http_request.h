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

#ifndef kIT_HTTP_REQUEST_INCLUDED
#define kIT_HTTP_REQUEST_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <option/option.h>
#include <kit/errors.h>
#include <kit/compiler_steroids.h>
#include <kit/collections/atom.h>
#include <kit/collections/string.h>
#include <kit/networking/http_method.h>
#include <kit/networking/http_response.h>

/**
 * kit_HttpRequest interface.
 */
struct kit_HttpRequest;

extern enum kit_HttpMethod
kit_HttpRequest_getMethod(const struct kit_HttpRequest *self)
__attribute__((__warn_unused_result__, __nonnull__));

extern kit_Atom
kit_HttpRequest_getUrl(const struct kit_HttpRequest *self)
__attribute__((__warn_unused_result__, __nonnull__));

extern OptionOf(kit_String)
kit_HttpRequest_getHeaders(const struct kit_HttpRequest *self)
__attribute__((__warn_unused_result__, __nonnull__));

extern OptionOf(kit_String)
kit_HttpRequest_getBody(const struct kit_HttpRequest *self)
__attribute__((__warn_unused_result__, __nonnull__));

extern size_t
kit_HttpRequest_getTimeout(const struct kit_HttpRequest *self)
__attribute__((__warn_unused_result__, __nonnull__));

extern bool
kit_HttpRequest_getFollowLocation(const struct kit_HttpRequest *self)
__attribute__((__warn_unused_result__, __nonnull__));

extern bool
kit_HttpRequest_getPeerVerification(const struct kit_HttpRequest *self)
__attribute__((__warn_unused_result__, __nonnull__));

extern bool
kit_HttpRequest_getHostVerification(const struct kit_HttpRequest *self)
__attribute__((__warn_unused_result__, __nonnull__));

// *************************************

// takes ownership
extern ResultOf(const struct kit_HttpResponse *, OutOfMemoryError)
kit_HttpRequest_fire(const struct kit_HttpRequest **ref)
__attribute__((__warn_unused_result__, __nonnull__));

// *************************************

extern void
kit_HttpRequest_delete(const struct kit_HttpRequest *self);

/**
 * kit_HttpRequestBuilder interface.
 */
struct kit_HttpRequestBuilder;

extern OptionOf(struct kit_HttpRequestBuilder *)
kit_HttpRequestBuilder_new(enum kit_HttpMethod method, kit_Atom url)
__attribute__((__warn_unused_result__, __nonnull__));

// *************************************

// takes ownership
extern struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_setHeaders(struct kit_HttpRequestBuilder *self, kit_String *ref)
__attribute__((__nonnull__));

// takes ownership
extern struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_setBody(struct kit_HttpRequestBuilder *self, kit_String *ref)
__attribute__((__nonnull__));

// *************************************

extern struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_setTimeout(struct kit_HttpRequestBuilder *self, size_t timeout)
__attribute__((__nonnull__));

extern struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_setFollowLocation(struct kit_HttpRequestBuilder *self, bool followLocation)
__attribute__((__nonnull__));

extern struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_setPeerVerification(struct kit_HttpRequestBuilder *self, bool peerVerification)
__attribute__((__nonnull__));

extern struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_setHostVerification(struct kit_HttpRequestBuilder *self, bool hostVerification)
__attribute__((__nonnull__));

// *************************************

// takes ownership
extern const struct kit_HttpRequest *
kit_HttpRequestBuilder_build(struct kit_HttpRequestBuilder **ref)
__attribute__((__warn_unused_result__, __nonnull__));

// *************************************

extern void
kit_HttpRequestBuilder_delete(struct kit_HttpRequestBuilder *self);

#ifdef __cplusplus
}
#endif

#endif /* kIT_HTTP_REQUEST_INCLUDED */
