/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   December 03, 2017 
 */

#include <assert.h>
#include <kit/utils.h>
#include <kit/allocator/allocator.h>
#include <kit/networking/http_request.h>

struct kit_HttpRequest {
    enum kit_HttpMethod method;
    kit_Atom url;
    const struct kit_Map *headers;
    kit_String body;
    long timeout;
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

ImmutableOption kit_HttpRequest_getHeaders(const struct kit_HttpRequest *self) {
    assert(self);
    return ImmutableOption_new(self->headers);
}

ImmutableOption kit_HttpRequest_getBody(const struct kit_HttpRequest *self) {
    assert(self);
    return ImmutableOption_new(self->body);
}

long kit_HttpRequest_getTimeout(const struct kit_HttpRequest *self) {
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

ImmutableOption kit_HttpRequest_fire(const struct kit_HttpRequest **ref) {
    assert(ref);
    assert(*ref);
    bool teardownRequired = false;
    struct kit_Map *responseHeaders = NULL;
    const struct kit_HttpRequest *request = *ref;
    struct kit_HttpResponseBuilder *responseBuilder = NULL;
    MutableOption responseBuilderOption, responseHeadersOption;

    do {
        // TODO perform the real request and handle oom (1)

        responseHeadersOption = kit_Map_fromHashMap(0, kit_compareFn, kit_hashFn);
        if (MutableOption_isNone(responseHeadersOption)) {
            teardownRequired = true;
            break;
        }
        responseHeaders = MutableOption_unwrap(responseHeadersOption);

        // TODO add responseHeaders here and handle oom

        responseBuilderOption = kit_HttpResponseBuilder_new(request);
        if (MutableOption_isNone(responseBuilderOption)) {
            teardownRequired = true;
            break;
        }
        responseBuilder = MutableOption_unwrap(responseBuilderOption);

        // TODO set response effective url
        kit_HttpResponseBuilder_setHeaders(responseBuilder, &responseHeaders);
        // TODO set response body
        // TODO set response status
    } while (false);

    if (teardownRequired) {
        // TODO free what was needed in (1)
        kit_Map_delete(responseHeaders);
        kit_HttpResponseBuilder_delete(responseBuilder);
        return ImmutableOption_None;
    } else {
        *ref = NULL;
        return ImmutableOption_new(kit_HttpResponseBuilder_build(&responseBuilder));
    }
}

void kit_HttpRequest_delete(const struct kit_HttpRequest *self) {
    if (self) {
        kit_Map_delete((void *) self->headers);
        kit_Allocator_free((void *) self);
    }
}

struct kit_HttpRequestBuilder {
    struct kit_HttpRequest *request;
};

MutableOption kit_HttpRequestBuilder_new(enum kit_HttpMethod method, kit_Atom url) {
    assert(url);
    bool teardownRequired = false;
    struct kit_HttpRequest *request = NULL;
    struct kit_HttpRequestBuilder *self = NULL;
    MutableOption selfOption, requestOption;

    do {
        selfOption = kit_Allocator_malloc(sizeof(*self));
        if (MutableOption_isNone(selfOption)) {
            teardownRequired = true;
            break;
        }
        self = MutableOption_unwrap(selfOption);

        requestOption = kit_Allocator_malloc(sizeof(*request));
        if (MutableOption_isNone(requestOption)) {
            teardownRequired = true;
            break;
        }
        request = MutableOption_unwrap(requestOption);

        request->method = method;
        request->url = url;
        request->headers = NULL;
        request->body = NULL;
        request->timeout = -1;
        request->followLocation = true;
        request->peerVerification = true;
        request->hostVerification = true;
        self->request = request;
    } while (false);

    if (teardownRequired) {
        kit_Allocator_free(request);
        kit_Allocator_free(self);
        selfOption = MutableOption_None;
    }

    return selfOption;
}

struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_setHeaders(struct kit_HttpRequestBuilder *self, struct kit_Map **ref) {
    assert(self);
    assert(ref);
    assert(*ref);
    self->request->headers = *ref;
    *ref = NULL;
    return self;
}

struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_setBody(struct kit_HttpRequestBuilder *self, kit_String *ref) {
    assert(self);
    assert(ref);
    assert(*ref);
    self->request->body = *ref;
    *ref = NULL;
    return self;
}

struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_setTimeout(struct kit_HttpRequestBuilder *self, long timeout) {
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