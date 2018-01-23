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

struct kit_HttpResponse;

extern const struct kit_HttpRequest *
kit_HttpResponse_getRequest(const struct kit_HttpResponse *self)
__attribute__((__warn_unused_result__, __nonnull__));

extern kit_Atom
kit_HttpResponse_getUrl(const struct kit_HttpResponse *self)
__attribute__((__warn_unused_result__, __nonnull__));

extern OptionOf(kit_String)
kit_HttpResponse_getHeaders(const struct kit_HttpResponse *self)
__attribute__((__warn_unused_result__, __nonnull__));

extern OptionOf(kit_String)
kit_HttpResponse_getBody(const struct kit_HttpResponse *self)
__attribute__((__warn_unused_result__, __nonnull__));

extern enum kit_HttpStatus
kit_HttpResponse_getStatus(const struct kit_HttpResponse *self)
__attribute__((__warn_unused_result__, __nonnull__));

extern void
kit_HttpResponse_delete(const struct kit_HttpResponse *self);

/**
 * kit_HttpResponseBuilder interface.
 */
struct kit_HttpResponseBuilder;

extern OptionOf(struct kit_HttpResponseBuilder *)
kit_HttpResponseBuilder_new(const struct kit_HttpRequest *request)
__attribute__((__warn_unused_result__, __nonnull__));

extern struct kit_HttpResponseBuilder *
kit_HttpResponseBuilder_setStatus(struct kit_HttpResponseBuilder *self, enum kit_HttpStatus status)
__attribute__((__nonnull__));

extern struct kit_HttpResponseBuilder *
kit_HttpResponseBuilder_setUrl(struct kit_HttpResponseBuilder *self, kit_Atom url)
__attribute__((__nonnull__));

// *************************************

// takes ownership
extern struct kit_HttpResponseBuilder *
kit_HttpResponseBuilder_setHeaders(struct kit_HttpResponseBuilder *self, kit_String *ref)
__attribute__((__nonnull__));

// takes ownership
extern struct kit_HttpResponseBuilder *
kit_HttpResponseBuilder_setBody(struct kit_HttpResponseBuilder *self, kit_String *ref)
__attribute__((__nonnull__));

// takes ownership
extern const struct kit_HttpResponse *
kit_HttpResponseBuilder_build(struct kit_HttpResponseBuilder **ref)
__attribute__((__warn_unused_result__, __nonnull__));

// *************************************

extern void
kit_HttpResponseBuilder_delete(struct kit_HttpResponseBuilder *self);

#ifdef __cplusplus
}
#endif

#endif /* kIT_HTTP_RESPONSE_INCLUDED */
