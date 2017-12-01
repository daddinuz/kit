/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 22, 2017
 */

#ifndef kIT_HTTP_RESPONSE_INCLUDED
#define kIT_HTTP_RESPONSE_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <kit/collections/map.h>
#include <kit/collections/atom.h>
#include <kit/collections/text.h>
#include <kit/networking/http_status.h>
#include <kit/networking/http_request.h>

/**
 * kit_HttpResponse interface.
 */
extern struct kit_HttpResponse;

extern const struct kit_HttpRequest *
kit_HttpResponse_getRequest(const struct kit_HttpResponse *self);

extern kit_Atom
kit_HttpResponse_getUrl(const struct kit_HttpResponse *self);

extern const struct kit_Map *
kit_HttpResponse_getHeaders(const struct kit_HttpResponse *self);

extern const struct kit_Text *
kit_HttpResponse_getBody(const struct kit_HttpResponse *self);

extern enum kit_HttpStatus
kit_HttpResponse_getStatus(const struct kit_HttpResponse *self);

extern void
kit_HttpResponse_delete(const struct kit_HttpResponse *self);

/**
 * kit_HttpResponseBuilder interface.
 */
extern struct kit_HttpResponseBuilder;

extern struct kit_HttpResponseBuilder *
kit_HttpResponseBuilder_new(const struct kit_HttpRequest *request);

extern struct kit_HttpResponseBuilder *
kit_HttpResponseBuilder_setRequest(struct kit_HttpResponseBuilder *self, const struct kit_HttpRequest *request);

extern struct kit_HttpResponseBuilder *
kit_HttpResponseBuilder_setUrl(struct kit_HttpResponseBuilder *self, kit_Atom url);

extern struct kit_HttpResponseBuilder *
kit_HttpResponseBuilder_setHeaders(struct kit_HttpResponseBuilder *self, const struct kit_Map *headers);

extern struct kit_HttpResponseBuilder *
kit_HttpResponseBuilder_setBody(struct kit_HttpResponseBuilder *self, const struct kit_Text *body);

extern struct kit_HttpResponseBuilder *
kit_HttpResponseBuilder_setStatus(struct kit_HttpResponseBuilder *self, enum kit_HttpStatus status);

extern const struct kit_HttpResponse *
kit_HttpResponseBuilder_build(struct kit_HttpResponseBuilder *self);

extern void
kit_HttpResponseBuilder_delete(struct kit_HttpResponseBuilder *self);

#ifdef __cplusplus
}
#endif

#endif /* kIT_HTTP_RESPONSE_INCLUDED */
