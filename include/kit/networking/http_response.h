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

#ifndef kIT_HTTP_RESPONSE_INCLUDED
#define kIT_HTTP_RESPONSE_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <option/option.h>
#include <kit/compiler_steroids.h>
#include <kit/collections/atom.h>
#include <kit/collections/string.h>
#include <kit/networking/http_status.h>
#include <kit/networking/http_request.h>

/**
 * Read-only struct which holds http response data.
 */
struct kit_HttpResponse;

/**
 * Returns the http request that generated this response.
 *
 * @param self The kit_HttpResponse instance [<b>must not be NULL</b>].
 * @return The request that generated this response.
 */
extern const struct kit_HttpRequest *
kit_HttpResponse_getRequest(const struct kit_HttpResponse *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns the effective url of the response.
 * If follow location was enabled this url may be different from request's url.
 *
 * @param self The kit_HttpResponse instance [<b>must not be NULL</b>].
 * @return The effective url of the response.
 */
extern kit_Atom
kit_HttpResponse_getUrl(const struct kit_HttpResponse *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns an option wrapping the headers associated to the specified response if any.
 *
 * @attention
 *  The current response is the owner of these headers and therefore the user should not keep any references to the headers
 *  and must not modify or free the headers, they must be considered read-only.
 *
 * @param self The kit_HttpResponse instance [<b>must not be NULL</b>].
 * @return The headers associated to the specified response.
 */
extern OptionOf(kit_String)
kit_HttpResponse_getHeaders(const struct kit_HttpResponse *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns an option wrapping the body associated to the specified response if any.
 *
 * @attention
 *  The current response is the owner of the body and therefore the user should not keep any references to the body
 *  and must not modify or free the body, it must be considered read-only.
 *
 * @param self The kit_HttpResponse instance [<b>must not be NULL</b>].
 * @return The body associated to the specified response.
 */
extern OptionOf(kit_String)
kit_HttpResponse_getBody(const struct kit_HttpResponse *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Returns the http status code associated to the specified response.
 * 
 * @param self The kit_HttpResponse instance [<b>must not be NULL</b>].
 * @return The http status code associated to the specified response.
 */
extern enum kit_HttpStatus
kit_HttpResponse_getStatus(const struct kit_HttpResponse *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Deletes this instance of kit_HttpResponse.
 * If self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_HttpResponse_delete(const struct kit_HttpResponse *self);

/**
 * Response builder opaque struct.
 */
struct kit_HttpResponseBuilder;

/**
 * Creates a new response builder.
 * In case of out of memory this function returns None.
 *
 * @attention
 *  This function moves the ownership of the request to the resulting response invalidating it in case of success.
 *
 * @param ref The reference to the http request that generated this response [<b>must not be NULL</b>].
 * @return A new kit_HttpResponseBuilder instance or None.
 */
extern OptionOf(struct kit_HttpResponseBuilder *)
kit_HttpResponseBuilder_new(const struct kit_HttpRequest **ref)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Sets the request for the response.
 *
 * @attention
 *  This function moves the ownership of the request to the resulting response invalidating it in case of success.
 *  The user is responsible to free the replaced request.
 *
 * @param self The response builder instance [<b>must not be NULL</b>].
 * @param ref The reference to the request instance [<b>must not be NULL</b>].
 * @return The replaced request.
 */
extern const struct kit_HttpRequest *
kit_HttpResponseBuilder_setRequest(struct kit_HttpResponseBuilder *self, const struct kit_HttpRequest **ref)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Sets the status for the response.
 *
 * @param self The response builder instance [<b>must not be NULL</b>].
 * @param status The http status code.
 * @return The replaced status code.
 */
extern enum kit_HttpStatus
kit_HttpResponseBuilder_setStatus(struct kit_HttpResponseBuilder *self, enum kit_HttpStatus status)
__attribute__((__nonnull__));

/**
 * Sets the effective url for the response.
 *
 * @param self The response builder instance [<b>must not be NULL</b>].
 * @param url The effective url.
 * @return The replaced url.
 */
extern kit_Atom
kit_HttpResponseBuilder_setUrl(struct kit_HttpResponseBuilder *self, kit_Atom url)
__attribute__((__nonnull__));

/**
 * Sets the headers for the response.
 *
 * @attention
 *  This function moves the ownership of the headers to the resulting response invalidating it in case of success.
 *  The user is responsible to free the replaced headers if any.
 *
 * @param self The response builder instance [<b>must not be NULL</b>].
 * @param ref The reference to the headers instance [<b>must not be NULL</b>].
 * @return The replaced headers.
 */
extern OptionOf(kit_String)
kit_HttpResponseBuilder_setHeaders(struct kit_HttpResponseBuilder *self, kit_String *ref)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Clears the headers of the response.
 *
 * @attention
 *  The user is responsible to free the replaced headers if any.
 *
 * @param self The response builder instance [<b>must not be NULL</b>].
 * @return The replaced headers.
 */
extern OptionOf(kit_String)
kit_HttpResponseBuilder_clearHeaders(struct kit_HttpResponseBuilder *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Sets the body for the response.
 *
 * @attention
 *  This function moves the ownership of the body to the resulting response invalidating it in case of success.
 *  The user is responsible to free the replaced body if any.
 *
 * @param self The response builder instance [<b>must not be NULL</b>].
 * @param ref The reference to the body instance [<b>must not be NULL</b>].
 * @return The replaced body.
 */
extern OptionOf(kit_String)
kit_HttpResponseBuilder_setBody(struct kit_HttpResponseBuilder *self, kit_String *ref)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Clears the body of the response.
 *
 * @attention
 *  The user is responsible to free the replaced body if any.
 *
 * @param self The response builder instance [<b>must not be NULL</b>].
 * @return The replaced body.
 */
extern OptionOf(kit_String)
kit_HttpResponseBuilder_clearBody(struct kit_HttpResponseBuilder *self)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Constructs the http response.
 *
 * @attention
 *  This function takes the ownership of the response builder invalidating it in case of success.
 *
 * @param ref The reference to the response builder instance [<b>must not be NULL</b>].
 * @return The http response instance.
 */
extern const struct kit_HttpResponse *
kit_HttpResponseBuilder_build(struct kit_HttpResponseBuilder **ref)
__attribute__((__warn_unused_result__, __nonnull__));

/**
 * Deletes this instance of kit_HttpResponseBuilder.
 * If self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_HttpResponseBuilder_delete(struct kit_HttpResponseBuilder *self);

#ifdef __cplusplus
}
#endif

#endif /* kIT_HTTP_RESPONSE_INCLUDED */
