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
 * kit_HttpRequest interface.
 */
extern struct kit_HttpRequest;

extern enum kit_HttpMethod
kit_HttpRequest_getMethod(const struct kit_HttpRequest *self);

extern kit_Atom
kit_HttpRequest_getUrl(const struct kit_HttpRequest *self);

extern const struct kit_Map *
kit_HttpRequest_getHeaders(const struct kit_HttpRequest *self);

extern const struct kit_Text *
kit_HttpRequest_getBody(const struct kit_HttpRequest *self);

extern long
kit_HttpRequest_getTimeout(const struct kit_HttpRequest *self);

extern bool
kit_HttpRequest_getFollowLocation(const struct kit_HttpRequest *self);

extern bool
kit_HttpRequest_getPeerVerification(const struct kit_HttpRequest *self);

extern bool
kit_HttpRequest_getHostVerification(const struct kit_HttpRequest *self);

extern const struct kit_HttpResponse *
kit_HttpRequest_fire(const struct kit_HttpRequest *self);

extern void
kit_HttpRequest_delete(const struct kit_HttpRequest *self);

/**
 * kit_HttpRequestBuilder interface.
 */
extern struct kit_HttpRequestBuilder;

extern struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_new(enum kit_HttpMethod method, kit_Atom url);

extern struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_setMethod(struct kit_HttpRequestBuilder *self, enum kit_HttpMethod method);

extern struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_setUrl(struct kit_HttpRequestBuilder *self, kit_Atom url);

extern struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_setHeaders(struct kit_HttpRequestBuilder *self, const struct kit_Map *headers);

extern struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_setBody(struct kit_HttpRequestBuilder *self, const struct kit_Text *body);

extern struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_setTimeout(struct kit_HttpRequestBuilder *self, long timeout);

extern struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_setFollowLocation(struct kit_HttpRequestBuilder *self, bool followLocation);

extern struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_setPeerVerification(struct kit_HttpRequestBuilder *self, bool peerVerification);

extern struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_setHostVerification(struct kit_HttpRequestBuilder *self, bool hostVerification);

extern const struct kit_HttpRequest *
kit_HttpRequestBuilder_build(struct kit_HttpRequestBuilder *self);

extern void
kit_HttpRequestBuilder_delete(struct kit_HttpRequestBuilder *self);

#ifdef __cplusplus
}
#endif

#endif /* kIT_HTTP_REQUEST_INCLUDED */
