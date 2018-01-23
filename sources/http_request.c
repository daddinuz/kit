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

#include <assert.h>
#include <kit/allocator/allocator.h>
#include <kit/networking/http_request.h>

struct kit_HttpRequest {
    enum kit_HttpMethod method;
    kit_Atom url;
    kit_String headers;
    kit_String body;
    size_t timeout;
    bool followLocation;
    bool peerVerification;
    bool hostVerification;
};

enum kit_HttpMethod
kit_HttpRequest_getMethod(const struct kit_HttpRequest *self) {
    assert(self);
    return self->method;
}

kit_Atom
kit_HttpRequest_getUrl(const struct kit_HttpRequest *self) {
    assert(self);
    return self->url;
}

OptionOf(kit_String)
kit_HttpRequest_getHeaders(const struct kit_HttpRequest *self) {
    assert(self);
    return Option_new((void *) self->headers);
}

OptionOf(kit_String)
kit_HttpRequest_getBody(const struct kit_HttpRequest *self) {
    assert(self);
    return Option_new((void *) self->body);
}

size_t
kit_HttpRequest_getTimeout(const struct kit_HttpRequest *self) {
    assert(self);
    return self->timeout;
}

bool
kit_HttpRequest_getFollowLocation(const struct kit_HttpRequest *self) {
    assert(self);
    return self->followLocation;
}

bool
kit_HttpRequest_getPeerVerification(const struct kit_HttpRequest *self) {
    assert(self);
    return self->peerVerification;
}

bool
kit_HttpRequest_getHostVerification(const struct kit_HttpRequest *self) {
    assert(self);
    return self->hostVerification;
}

void
kit_HttpRequest_delete(const struct kit_HttpRequest *self) {
    if (self) {
        kit_String_delete(self->body);
        kit_String_delete(self->headers);
        kit_Allocator_free((void *) self);
    }
}

struct kit_HttpRequestBuilder {
    struct kit_HttpRequest *request;
};

OptionOf(struct kit_HttpResponseBuilder *)
kit_HttpRequestBuilder_new(enum kit_HttpMethod method, kit_Atom url) {
    assert(url);
    bool teardownRequired = false;
    struct kit_HttpRequest *request = NULL;
    struct kit_HttpRequestBuilder *self = NULL;
    Option selfOption, requestOption;

    do {
        selfOption = kit_Allocator_malloc(sizeof(*self));
        if (Option_isNone(selfOption)) {
            teardownRequired = true;
            break;
        }
        self = Option_unwrap(selfOption);

        requestOption = kit_Allocator_malloc(sizeof(*request));
        if (Option_isNone(requestOption)) {
            teardownRequired = true;
            break;
        }
        request = Option_unwrap(requestOption);

        request->method = method;
        request->url = url;
        request->headers = NULL;
        request->body = NULL;
        request->timeout = 0;
        request->followLocation = true;
        request->peerVerification = true;
        request->hostVerification = true;
        self->request = request;
    } while (false);

    if (teardownRequired) {
        kit_Allocator_free(request);
        kit_Allocator_free(self);
        selfOption = None;
    }

    return selfOption;
}

enum kit_HttpMethod
kit_HttpRequestBuilder_setMethod(struct kit_HttpRequestBuilder *self, enum kit_HttpMethod method) {
    assert(self);
    const enum kit_HttpMethod previousMethod = self->request->method;
    self->request->method = method;
    return previousMethod;
}

kit_Atom
kit_HttpRequestBuilder_setUrl(struct kit_HttpRequestBuilder *self, kit_Atom url) {
    assert(self);
    kit_Atom previousUrl = self->request->url;
    self->request->url = url;
    return previousUrl;
}

OptionOf(kit_String)
kit_HttpRequestBuilder_setHeaders(struct kit_HttpRequestBuilder *self, kit_String *ref) {
    assert(self);
    assert(ref);
    assert(*ref);
    Option previousHeaders = Option_new((void *) self->request->headers);
    self->request->headers = Option_unwrap(kit_String_shrink(ref));
    *ref = NULL;
    return previousHeaders;
}

OptionOf(kit_String)
kit_HttpRequestBuilder_clearHeaders(struct kit_HttpRequestBuilder *self) {
    assert(self);
    Option previousHeaders = Option_new((void *) self->request->headers);
    self->request->headers = NULL;
    return previousHeaders;
}

OptionOf(kit_String)
kit_HttpRequestBuilder_setBody(struct kit_HttpRequestBuilder *self, kit_String *ref) {
    assert(self);
    assert(ref);
    assert(*ref);
    Option previousBody = Option_new((void *) self->request->body);
    self->request->body = Option_unwrap(kit_String_shrink(ref));
    *ref = NULL;
    return previousBody;
}

OptionOf(kit_String)
kit_HttpRequestBuilder_clearBody(struct kit_HttpRequestBuilder *self) {
    assert(self);
    Option previousBody = Option_new((void *) self->request->body);
    self->request->body = NULL;
    return previousBody;
}

size_t
kit_HttpRequestBuilder_setTimeout(struct kit_HttpRequestBuilder *self, size_t timeout) {
    assert(self);
    const size_t previousTimeout = self->request->timeout;
    self->request->timeout = timeout;
    return previousTimeout;
}

bool
kit_HttpRequestBuilder_setFollowLocation(struct kit_HttpRequestBuilder *self, bool enable) {
    assert(self);
    const bool previousFollowLocation = self->request->followLocation;
    self->request->followLocation = enable;
    return previousFollowLocation;
}

bool
kit_HttpRequestBuilder_setPeerVerification(struct kit_HttpRequestBuilder *self, bool enable) {
    assert(self);
    const bool previousPeerVerification = self->request->peerVerification;
    self->request->peerVerification = enable;
    return previousPeerVerification;
}

bool
kit_HttpRequestBuilder_setHostVerification(struct kit_HttpRequestBuilder *self, bool enable) {
    assert(self);
    const bool previousHostVerification = self->request->hostVerification;
    self->request->hostVerification = enable;
    return previousHostVerification;
}

const struct kit_HttpRequest *
kit_HttpRequestBuilder_build(struct kit_HttpRequestBuilder **ref) {
    assert(ref);
    assert(*ref);
    const struct kit_HttpRequest *request = (*ref)->request;
    kit_HttpRequestBuilder_delete(*ref);
    *ref = NULL;
    return request;
}

void
kit_HttpRequestBuilder_delete(struct kit_HttpRequestBuilder *self) {
    if (self) {
        kit_Allocator_free(self);
    }
}
