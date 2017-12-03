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
#include <option/option.h>
#include <kit/compiler_steroids.h>
#include <kit/collections/map.h>
#include <kit/collections/atom.h>
#include <kit/collections/text.h>
#include <kit/networking/http_method.h>
#include <kit/networking/http_response.h>

/**
 * kit_HttpRequest interface.
 */
struct kit_HttpRequest;

extern enum kit_HttpMethod
kit_HttpRequest_getMethod(const struct kit_HttpRequest *self)
__attribute__((__nonnull__));

extern kit_Atom
kit_HttpRequest_getUrl(const struct kit_HttpRequest *self)
__attribute__((__nonnull__));

extern const struct kit_Map *
kit_HttpRequest_getHeaders(const struct kit_HttpRequest *self)
__attribute__((__nonnull__));

extern ImmutableOptional(const struct kit_Text *)
kit_HttpRequest_getBody(const struct kit_HttpRequest *self)
__attribute__((__nonnull__));

extern long
kit_HttpRequest_getTimeout(const struct kit_HttpRequest *self)
__attribute__((__nonnull__));

extern bool
kit_HttpRequest_getFollowLocation(const struct kit_HttpRequest *self)
__attribute__((__nonnull__));

extern bool
kit_HttpRequest_getPeerVerification(const struct kit_HttpRequest *self)
__attribute__((__nonnull__));

extern bool
kit_HttpRequest_getHostVerification(const struct kit_HttpRequest *self)
__attribute__((__nonnull__));

// TODO
// moves ownership invalidating ref.
extern ImmutableOptional(const struct kit_HttpResponse *)
kit_HttpRequest_fire(const struct kit_HttpRequest **ref)
__attribute__((__nonnull__));

extern void
kit_HttpRequest_delete(const struct kit_HttpRequest *self);

/**
 * kit_HttpRequestBuilder interface.
 */
struct kit_HttpRequestBuilder;

extern MutableOptional(struct kit_HttpRequestBuilder *)
kit_HttpRequestBuilder_new(enum kit_HttpMethod method, kit_Atom url)
__attribute__((__nonnull__));

extern struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_putHeader(struct kit_HttpRequestBuilder *self, kit_Atom key, kit_Atom value)
__attribute__((__nonnull__));

extern struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_setBody(struct kit_HttpRequestBuilder *self, const struct kit_Text *body)
__attribute__((__nonnull__));

extern struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_setTimeout(struct kit_HttpRequestBuilder *self, long timeout)
__attribute__((__nonnull__));

extern struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_setFollowLocation(struct kit_HttpRequestBuilder *self, bool followLocation)
__attribute__((__nonnull__));

extern struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_setPeerVerification(struct kit_HttpRequestBuilder *self, bool peerVerification)
__attribute__((__nonnull__));

extern struct kit_HttpRequestBuilder *
kit_HttpRequestBuilder_setHostVerification(struct kit_HttpRequestBuilder *self, bool hostVerification)
__attribute__((__nonnull__));

// moves ownership invalidating ref.
extern ImmutableOptional(const struct kit_HttpRequest *)
kit_HttpRequestBuilder_build(struct kit_HttpRequestBuilder **ref)
__attribute__((__nonnull__));

extern void
kit_HttpRequestBuilder_delete(struct kit_HttpRequestBuilder *self);

#ifdef __cplusplus
}
#endif

#endif /* kIT_HTTP_REQUEST_INCLUDED */
