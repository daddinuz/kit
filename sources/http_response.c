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
#include <kit/networking/http_response.h>

struct kit_HttpResponse {
    const struct kit_HttpRequest *request;
    kit_Atom url;
    kit_String headers;
    kit_String body;
    enum kit_HttpStatus status;
};

const struct kit_HttpRequest *kit_HttpResponse_getRequest(const struct kit_HttpResponse *self) {
    assert(self);
    return self->request;
}

kit_Atom kit_HttpResponse_getUrl(const struct kit_HttpResponse *self) {
    assert(self);
    return self->url;
}

ImmutableOption kit_HttpResponse_getHeaders(const struct kit_HttpResponse *self) {
    assert(self);
    return ImmutableOption_new(self->headers);
}

ImmutableOption kit_HttpResponse_getBody(const struct kit_HttpResponse *self) {
    assert(self);
    return ImmutableOption_new(self->body);
}

enum kit_HttpStatus kit_HttpResponse_getStatus(const struct kit_HttpResponse *self) {
    assert(self);
    return self->status;
}

void kit_HttpResponse_delete(const struct kit_HttpResponse *self) {
    if (self) {
        kit_HttpRequest_delete(self->request);
        kit_String_delete(self->body);
        kit_String_delete(self->headers);
        kit_Allocator_free((void *) self);
    }
}

struct kit_HttpResponseBuilder {
    struct kit_HttpResponse *response;
};

MutableOption kit_HttpResponseBuilder_new(const struct kit_HttpRequest *request) {
    assert(request);
    bool teardownRequired = false;
    struct kit_HttpResponse *response = NULL;
    struct kit_HttpResponseBuilder *self = NULL;
    MutableOption selfOption, responseOption;

    do {
        selfOption = kit_Allocator_malloc(sizeof(*self));
        if (MutableOption_isNone(selfOption)) {
            teardownRequired = true;
            break;
        }
        self = MutableOption_unwrap(selfOption);

        responseOption = kit_Allocator_malloc(sizeof(*response));
        if (MutableOption_isNone(responseOption)) {
            teardownRequired = true;
            break;
        }
        response = MutableOption_unwrap(responseOption);

        response->request = request;
        response->url = kit_HttpRequest_getUrl(request);
        response->headers = NULL;
        response->body = NULL;
        response->status = KIT_HTTP_STATUS_OK;
        self->response = response;
    } while (false);

    if (teardownRequired) {
        kit_Allocator_free(response);
        kit_Allocator_free(self);
        selfOption = MutableOption_None;
    }

    return selfOption;
}

struct kit_HttpResponseBuilder *
kit_HttpResponseBuilder_setStatus(struct kit_HttpResponseBuilder *self, enum kit_HttpStatus status) {
    assert(self);
    self->response->status = status;
    return self;
}

struct kit_HttpResponseBuilder *
kit_HttpResponseBuilder_setUrl(struct kit_HttpResponseBuilder *self, kit_Atom url) {
    assert(self);
    assert(url);
    self->response->url = url;
    return self;
}

struct kit_HttpResponseBuilder *
kit_HttpResponseBuilder_setHeaders(struct kit_HttpResponseBuilder *self, kit_String *ref) {
    assert(self);
    assert(ref);
    assert(*ref);
    self->response->headers = ImmutableOption_unwrap(kit_String_shrink(ref));
    *ref = NULL;
    return self;
}

struct kit_HttpResponseBuilder *
kit_HttpResponseBuilder_setBody(struct kit_HttpResponseBuilder *self, kit_String *ref) {
    assert(self);
    assert(ref);
    assert(*ref);
    self->response->body = ImmutableOption_unwrap(kit_String_shrink(ref));
    *ref = NULL;
    return self;
}

const struct kit_HttpResponse *
kit_HttpResponseBuilder_build(struct kit_HttpResponseBuilder **ref) {
    assert(ref);
    assert(*ref);
    const struct kit_HttpResponse *response = (*ref)->response;
    kit_HttpResponseBuilder_delete(*ref);
    *ref = NULL;
    return response;
}

void kit_HttpResponseBuilder_delete(struct kit_HttpResponseBuilder *self) {
    if (self) {
        kit_Allocator_free(self);
    }
}
