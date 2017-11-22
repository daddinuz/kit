/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 22, 2017
 */

#ifndef kIT_HTTP_REQUEST_INCLUDED
#define kIT_HTTP_REQUEST_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <kit/collections/map.h>
#include <kit/collections/atom.h>
#include <kit/collections/text.h>
#include <kit/networking/http_method.h>
#include <kit/networking/http_response.h>

/**
 * kit_http_Request interface.
 */
extern struct kit_http_Request;

extern enum kit_http_Method
kit_http_Request_getMethod(const struct kit_http_Request *self);

extern kit_Atom
kit_http_Request_getUrl(const struct kit_http_Request *self);

extern const struct kit_Map *
kit_http_Request_getHeaders(const struct kit_http_Request *self);

extern const struct kit_Text *
kit_http_Request_getBody(const struct kit_http_Request *self);

extern long
kit_http_Request_getTimeout(const struct kit_http_Request *self);

extern bool
kit_http_Request_getFollowLocation(const struct kit_http_Request *self);

extern bool
kit_http_Request_getPeerVerification(const struct kit_http_Request *self);

extern bool
kit_http_Request_getHostVerification(const struct kit_http_Request *self);

extern const struct kit_http_Response *
kit_http_Request_fire(const struct kit_http_Request *self);

extern void
kit_http_Request_delete(const struct kit_http_Request *self);

/**
 * kit_http_RequestBuilder interface.
 */
extern struct kit_http_RequestBuilder;

extern struct kit_http_RequestBuilder *
kit_http_RequestBuilder_new(enum kit_http_Method method, kit_Atom url);

extern struct kit_http_RequestBuilder *
kit_http_RequestBuilder_setMethod(struct kit_http_RequestBuilder *self, enum kit_http_Method method);

extern struct kit_http_RequestBuilder *
kit_http_RequestBuilder_setUrl(struct kit_http_RequestBuilder *self, kit_Atom url);

extern struct kit_http_RequestBuilder *
kit_http_RequestBuilder_setHeaders(struct kit_http_RequestBuilder *self, const struct kit_Map *headers);

extern struct kit_http_RequestBuilder *
kit_http_RequestBuilder_setBody(struct kit_http_RequestBuilder *self, const struct kit_Text *body);

extern struct kit_http_RequestBuilder *
kit_http_RequestBuilder_setTimeout(struct kit_http_RequestBuilder *self, long timeout);

extern struct kit_http_RequestBuilder *
kit_http_RequestBuilder_setFollowLocation(struct kit_http_RequestBuilder *self, bool followLocation);

extern struct kit_http_RequestBuilder *
kit_http_RequestBuilder_setPeerVerification(struct kit_http_RequestBuilder *self, bool peerVerification);

extern struct kit_http_RequestBuilder *
kit_http_RequestBuilder_setHostVerification(struct kit_http_RequestBuilder *self, bool hostVerification);

extern const struct kit_http_Request *
kit_http_RequestBuilder_build(struct kit_http_RequestBuilder *self);

extern void
kit_http_RequestBuilder_delete(struct kit_http_RequestBuilder *self);

#ifdef __cplusplus
}
#endif

#endif /* kIT_HTTP_REQUEST_INCLUDED */
