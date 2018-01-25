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
 * Read-only struct which holds http request data.
 */
struct kit_HttpRequest;

/**
 * Returns the http method associated to the specified request.
 *
 * @param self The kit_HttpRequest instance [<b>must not be NULL</b>].
 * @return The http method of the specified request.
 */
extern enum kit_HttpMethod
kit_HttpRequest_getMethod(const struct kit_HttpRequest *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns the url associated to the specified request.
 *
 * @param self The kit_HttpRequest instance [<b>must not be NULL</b>].
 * @return The url associated to the specified request.
 */
extern kit_Atom
kit_HttpRequest_getUrl(const struct kit_HttpRequest *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns an option wrapping the headers associated to the specified request if any.
 *
 * @attention
 *  The current request is the owner of these headers and therefore the user should not keep any references to the headers
 *  and must not modify or free the headers, they must be considered read-only.
 *
 * @param self The kit_HttpRequest instance [<b>must not be NULL</b>].
 * @return The headers associated to the specified request.
 */
extern OptionOf(kit_String)
kit_HttpRequest_getHeaders(const struct kit_HttpRequest *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns an option wrapping the body associated to the specified request if any.
 *
 * @attention
 *  The current request is the owner of the body and therefore the user should not keep any references to the body
 *  and must not modify or free the body, it must be considered read-only.
 *
 * @param self The kit_HttpRequest instance [<b>must not be NULL</b>].
 * @return The body associated to the specified request.
 */
extern OptionOf(kit_String)
kit_HttpRequest_getBody(const struct kit_HttpRequest *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns the timeout associated to the specified request.
 *
 * @param self The kit_HttpRequest instance [<b>must not be NULL</b>].
 * @return The timeout associated to the specified request.
 */
extern size_t
kit_HttpRequest_getTimeout(const struct kit_HttpRequest *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns true if follow location is enabled for the specified request else false.
 *
 * @param self The kit_HttpRequest instance [<b>must not be NULL</b>].
 * @return true if follow location is enabled for the specified request else false.
 */
extern bool
kit_HttpRequest_getFollowLocation(const struct kit_HttpRequest *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns true if peer verification is enabled for the specified request else false.
 *
 * @param self The kit_HttpRequest instance [<b>must not be NULL</b>].
 * @return true if peer verification is enabled for the specified request else false.
 */
extern bool
kit_HttpRequest_getPeerVerification(const struct kit_HttpRequest *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns true if host verification is enabled for the specified request else false.
 *
 * @param self The kit_HttpRequest instance [<b>must not be NULL</b>].
 * @return true if host verification is enabled for the specified request else false.
 */
extern bool
kit_HttpRequest_getHostVerification(const struct kit_HttpRequest *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Performs the http request returning the server response.
 *
 * @attention
 *  This function moves the ownership of the request to the resulting response invalidating it in case of success.
 *
 * @param ref The reference to the request instance [<b>must not be NULL</b>].
 * @return
 * - Ok => Wraps the http response, *ref has been invalidated.
 * - NetworkingError => There were something wrong with the connection, *ref has not been invalidated.
 * - OutOfMemoryError => There's no more space left, *ref has not been invalidated.
 */
extern ResultOf(const struct kit_HttpResponse *, NetworkingError, OutOfMemoryError)
kit_HttpRequest_fire(const struct kit_HttpRequest **ref)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Deletes this instance of kit_HttpRequest.
 * If self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_HttpRequest_delete(const struct kit_HttpRequest *self);

/**
 * Request builder opaque struct.
 */
struct kit_HttpRequestBuilder;

/**
 * Creates a new request builder.
 * In case of out of memory this function returns None.
 *
 * @param method The http method for the request.
 * @param url The url for the request.
 * @return A new kit_HttpRequestBuilder instance or None.
 */
extern OptionOf(struct kit_HttpRequestBuilder *)
kit_HttpRequestBuilder_new(enum kit_HttpMethod method, kit_Atom url)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Sets the method for the request.
 *
 * @param self The request builder instance [<b>must not be NULL</b>].
 * @param method Self explaining.
 * @return The replaced method.
 */
extern enum kit_HttpMethod
kit_HttpRequestBuilder_setMethod(struct kit_HttpRequestBuilder *self, enum kit_HttpMethod method)
__attribute__((__nonnull__));

/**
 * Sets the url for the request.
 *
 * @param self The request builder instance [<b>must not be NULL</b>].
 * @param url Self explaining.
 * @return The replaced url.
 */
extern kit_Atom
kit_HttpRequestBuilder_setUrl(struct kit_HttpRequestBuilder *self, kit_Atom url)
__attribute__((__nonnull__));

/**
 * Sets the headers for the request.
 *
 * @attention
 *  This function moves the ownership of the headers to the resulting request invalidating it in case of success.
 *  The user is responsible to free the replaced headers if any.
 *
 * @param self The request builder instance [<b>must not be NULL</b>].
 * @param ref The reference to the headers instance [<b>must not be NULL</b>].
 * @return The replaced headers.
 */
extern OptionOf(kit_String)
kit_HttpRequestBuilder_setHeaders(struct kit_HttpRequestBuilder *self, kit_String *ref)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Clears the headers of the request.
 *
 * @attention
 *  The user is responsible to free the replaced headers if any.
 *
 * @param self The request builder instance [<b>must not be NULL</b>].
 * @return The replaced headers.
 */
extern OptionOf(kit_String)
kit_HttpRequestBuilder_clearHeaders(struct kit_HttpRequestBuilder *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Sets the body for the request.
 *
 * @attention
 *  This function moves the ownership of the body to the resulting request invalidating it in case of success.
 *  The user is responsible to free the replaced body if any.
 *
 * @param self The request builder instance [<b>must not be NULL</b>].
 * @param ref The reference to the body instance [<b>must not be NULL</b>].
 * @return The replaced body.
 */
extern OptionOf(kit_String)
kit_HttpRequestBuilder_setBody(struct kit_HttpRequestBuilder *self, kit_String *ref)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Clears the body of the request.
 *
 * @attention
 *  The user is responsible to free the replaced body if any.
 *
 * @param self The request builder instance [<b>must not be NULL</b>].
 * @return The replaced body.
 */
extern OptionOf(kit_String)
kit_HttpRequestBuilder_clearBody(struct kit_HttpRequestBuilder *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Sets the timeout for the request.
 *
 * @param self The request builder instance [<b>must not be NULL</b>].
 * @param timeout The specified timeout.
 * @return The replaced value for timeout.
 */
extern size_t
kit_HttpRequestBuilder_setTimeout(struct kit_HttpRequestBuilder *self, size_t timeout)
__attribute__((__nonnull__));

/**
 * Enables or disables follow location for the request.
 *
 * @param self The request builder instance [<b>must not be NULL</b>].
 * @param enable Self explaining.
 * @return The previous value for follow location.
 */
extern bool
kit_HttpRequestBuilder_setFollowLocation(struct kit_HttpRequestBuilder *self, bool enable)
__attribute__((__nonnull__));

/**
 * Enables or disables peer verification for the request.
 *
 * @param self The request builder instance [<b>must not be NULL</b>].
 * @param enable Self explaining.
 * @return The previous value for peer verification.
 */
extern bool
kit_HttpRequestBuilder_setPeerVerification(struct kit_HttpRequestBuilder *self, bool enable)
__attribute__((__nonnull__));

/**
 * Enables or disables host verification for the request.
 *
 * @param self The request builder instance [<b>must not be NULL</b>].
 * @param enable Self explaining.
 * @return The previous value for host verification.
 */
extern bool
kit_HttpRequestBuilder_setHostVerification(struct kit_HttpRequestBuilder *self, bool enable)
__attribute__((__nonnull__));

/**
 * Constructs the http request.
 *
 * @attention
 *  This function takes the ownership of the request builder invalidating it in case of success.
 *
 * @param ref The reference to the request builder instance [<b>must not be NULL</b>].
 * @return The http request instance.
 */
extern const struct kit_HttpRequest *
kit_HttpRequestBuilder_build(struct kit_HttpRequestBuilder **ref)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Deletes this instance of kit_HttpRequestBuilder.
 * If self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_HttpRequestBuilder_delete(struct kit_HttpRequestBuilder *self);

#ifdef __cplusplus
}
#endif

#endif /* kIT_HTTP_REQUEST_INCLUDED */
