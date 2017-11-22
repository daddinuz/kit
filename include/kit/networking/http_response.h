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
 * kit_http_Response interface.
 */
extern struct kit_http_Response;

extern const struct kit_http_Request *
kit_http_Response_getRequest(const struct kit_http_Response *self);

extern kit_Atom
kit_http_Response_getUrl(const struct kit_http_Response *self);

extern const struct kit_Map *
kit_http_Response_getHeaders(const struct kit_http_Response *self);

extern const struct kit_Text *
kit_http_Response_getBody(const struct kit_http_Response *self);

extern enum kit_http_Status
kit_http_Response_getStatus(const struct kit_http_Response *self);

extern void
kit_http_Response_delete(const struct kit_http_Response *self);

/**
 * kit_http_ResponseBuilder interface.
 */
extern struct kit_http_ResponseBuilder;

extern struct kit_http_ResponseBuilder *
kit_http_ResponseBuilder_new(const struct kit_http_Request *request);

extern struct kit_http_ResponseBuilder *
kit_http_ResponseBuilder_setRequest(struct kit_http_ResponseBuilder *self, const struct kit_http_Request *request);

extern struct kit_http_ResponseBuilder *
kit_http_ResponseBuilder_setUrl(struct kit_http_ResponseBuilder *self, kit_Atom url);

extern struct kit_http_ResponseBuilder *
kit_http_ResponseBuilder_setHeaders(struct kit_http_ResponseBuilder *self, const struct kit_Map *headers);

extern struct kit_http_ResponseBuilder *
kit_http_ResponseBuilder_setBody(struct kit_http_ResponseBuilder *self, const struct kit_Text *body);

extern struct kit_http_ResponseBuilder *
kit_http_ResponseBuilder_setStatus(struct kit_http_ResponseBuilder *self, enum kit_http_Status status);

extern const struct kit_http_Response *
kit_http_ResponseBuilder_build(struct kit_http_ResponseBuilder *self);

extern void
kit_http_ResponseBuilder_delete(struct kit_http_ResponseBuilder *self);

#ifdef __cplusplus
}
#endif

#endif /* kIT_HTTP_RESPONSE_INCLUDED */
