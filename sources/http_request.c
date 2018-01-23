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

enum kit_HttpMethod kit_HttpRequest_getMethod(const struct kit_HttpRequest *self) {
    assert(self);
    return self->method;
}

kit_Atom kit_HttpRequest_getUrl(const struct kit_HttpRequest *self) {
    assert(self);
    return self->url;
}

Option kit_HttpRequest_getHeaders(const struct kit_HttpRequest *self) {
    assert(self);
    // FIXME
    return Option_new((void *) self->headers);
}

Option kit_HttpRequest_getBody(const struct kit_HttpRequest *self) {
    assert(self);
    // FIXME
    return Option_new((void *) self->body);
}

size_t kit_HttpRequest_getTimeout(const struct kit_HttpRequest *self) {
    assert(self);
    return self->timeout;
}

bool kit_HttpRequest_getFollowLocation(const struct kit_HttpRequest *self) {
    assert(self);
    return self->followLocation;
}

bool kit_HttpRequest_getPeerVerification(const struct kit_HttpRequest *self) {
    assert(self);
    return self->peerVerification;
}

bool kit_HttpRequest_getHostVerification(const struct kit_HttpRequest *self) {
    assert(self);
    return self->hostVerification;
}

void kit_HttpRequest_delete(const struct kit_HttpRequest *self) {
    if (self) {
        kit_String_delete(self->body);
        kit_String_delete(self->headers);
        kit_Allocator_free((void *) self);
    }
}

struct kit_HttpRequestBuilder {
    struct kit_HttpRequest *request;
};

Option kit_HttpRequestBuilder_new(enum kit_HttpMethod method, kit_Atom url) {
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

struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_setHeaders(struct kit_HttpRequestBuilder *self, kit_String *ref) {
    assert(self);
    assert(ref);
    assert(*ref);
    self->request->headers = Option_unwrap(kit_String_shrink(ref));
    *ref = NULL;
    return self;
}

struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_setBody(struct kit_HttpRequestBuilder *self, kit_String *ref) {
    assert(self);
    assert(ref);
    assert(*ref);
    self->request->body = Option_unwrap(kit_String_shrink(ref));
    *ref = NULL;
    return self;
}

struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_setTimeout(struct kit_HttpRequestBuilder *self, size_t timeout) {
    assert(self);
    self->request->timeout = timeout;
    return self;
}

struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_setFollowLocation(struct kit_HttpRequestBuilder *self, bool followLocation) {
    assert(self);
    self->request->followLocation = followLocation;
    return self;
}

struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_setPeerVerification(struct kit_HttpRequestBuilder *self, bool peerVerification) {
    assert(self);
    self->request->peerVerification = peerVerification;
    return self;
}

struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_setHostVerification(struct kit_HttpRequestBuilder *self, bool hostVerification) {
    assert(self);
    self->request->hostVerification = hostVerification;
    return self;
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

void kit_HttpRequestBuilder_delete(struct kit_HttpRequestBuilder *self) {
    if (self) {
        kit_Allocator_free(self);
    }
}
