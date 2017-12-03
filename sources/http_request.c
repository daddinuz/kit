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
    kit_Atom *url;
    struct kit_Map *headers;
    ImmutableOptional(const struct kit_Text *) body;
    long timeout;
    bool followLocation;
    bool peerVerification;
    bool hostVerification;
};

enum kit_HttpMethod kit_HttpRequest_getMethod(const struct kit_HttpRequest *self) {
    assert(self);
    return self->method;
}

kit_Atom *kit_HttpRequest_getUrl(const struct kit_HttpRequest *self) {
    assert(self);
    return self->url;
}

const struct kit_Map *kit_HttpRequest_getHeaders(const struct kit_HttpRequest *self) {
    assert(self);
    return self->headers;
}

ImmutableOption kit_HttpRequest_getBody(const struct kit_HttpRequest *self) {
    assert(self);
    return self->body;
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
    *ref = NULL;
    // TODO make response
    return ImmutableOption_None;
}

void kit_HttpRequest_delete(const struct kit_HttpRequest *self) {
    if (self) {
        kit_Map_delete(self->headers);
        kit_Allocator_free((void *) self);
    }
}

struct kit_HttpRequestBuilder {
    struct kit_HttpRequest request;
};

MutableOption kit_HttpRequestBuilder_new(enum kit_HttpMethod method, kit_Atom *url) {
    assert(url);
    struct kit_HttpRequestBuilder *self;
    MutableOption selfOption = kit_Allocator_calloc(1, sizeof(*self)), headersOption;

    if (MutableOption_isSome(selfOption)) {
        self = MutableOption_unwrap(selfOption);
        headersOption = kit_Map_fromHashMap(0, kit_compareFn, kit_hashFn);
        if (MutableOption_isSome(headersOption)) {
            self->request.method = method;
            self->request.url = url;
            self->request.headers = MutableOption_unwrap(headersOption);
            self->request.body = ImmutableOption_None;
            self->request.timeout = -1;
            self->request.followLocation = true;
            self->request.peerVerification = true;
            self->request.hostVerification = true;
        } else {
            kit_Allocator_free(self);
            selfOption = MutableOption_None;
        }
    }

    return selfOption;
}

struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_putHeader(struct kit_HttpRequestBuilder *self, kit_Atom *key, kit_Atom *value) {
    assert(self);
    assert(key);
    assert(value);
    kit_Map_put(self->request.headers, key, (void *) value);
    return self;
}

struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_setBody(struct kit_HttpRequestBuilder *self, const struct kit_Text *body) {
    assert(self);
    assert(body);
    self->request.body = ImmutableOption_new((void *) body);
    return self;
}

struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_setTimeout(struct kit_HttpRequestBuilder *self, long timeout) {
    assert(self);
    self->request.timeout = timeout;
    return self;
}

struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_setFollowLocation(struct kit_HttpRequestBuilder *self, bool followLocation) {
    assert(self);
    self->request.followLocation = followLocation;
    return self;
}

struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_setPeerVerification(struct kit_HttpRequestBuilder *self, bool peerVerification) {
    assert(self);
    self->request.peerVerification = peerVerification;
    return self;
}

struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_setHostVerification(struct kit_HttpRequestBuilder *self, bool hostVerification) {
    assert(self);
    self->request.hostVerification = hostVerification;
    return self;
}

ImmutableOption kit_HttpRequestBuilder_build(struct kit_HttpRequestBuilder **ref) {
    assert(ref);
    assert(*ref);
    ImmutableOption option;
    struct kit_HttpRequest *newRequest = NULL;
    struct kit_HttpRequest builderRequest = (*ref)->request;
    MutableOption requestOption = kit_Allocator_malloc(sizeof(*newRequest));

    if (MutableOption_isSome(requestOption)) {
        newRequest = MutableOption_unwrap(requestOption);
        newRequest->method = builderRequest.method;
        newRequest->url = builderRequest.url;
        newRequest->headers = builderRequest.headers;
        newRequest->body = builderRequest.body;
        newRequest->timeout = builderRequest.timeout;
        newRequest->followLocation = builderRequest.followLocation;
        newRequest->peerVerification = builderRequest.peerVerification;
        newRequest->hostVerification = builderRequest.hostVerification;
    }

    option = ImmutableOption_new(newRequest);
    if (ImmutableOption_isSome(option)) {
        kit_HttpRequestBuilder_delete(*ref);
        *ref = NULL;
    }
    return option;
}

void kit_HttpRequestBuilder_delete(struct kit_HttpRequestBuilder *self) {
    if (self) {
        kit_Allocator_free(self);
    }
}
