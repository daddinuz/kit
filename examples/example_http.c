/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   December 03, 2017 
 */

#include <stdio.h>
#include <assert.h>
#include <kit/utils.h>
#include <kit/networking/http.h>

#define M(x)   MutableOption_unwrap((x))
#define I(x)   ImmutableOption_unwrap((x))

static void
printMap(const struct kit_Map *map)
__attribute__((__nonnull__));

static void
printRequest(const struct kit_HttpRequest *request)
__attribute__((__nonnull__));

static void
printResponse(const struct kit_HttpResponse *response)
__attribute__((__nonnull__));

/*
 *
 */
int main() {
    struct kit_Map *requestHeaders;
    const struct kit_HttpRequest *request;
    const struct kit_HttpResponse *response;
    struct kit_HttpRequestBuilder *requestBuilder;

    requestHeaders = M(kit_Map_fromHashMap(0, kit_compareFn, kit_hashFn));
    kit_Map_put(requestHeaders, I(kit_Atom_fromLiteral("Accept")), (void *) I(kit_Atom_fromLiteral("application/json")));
    kit_Map_put(requestHeaders, I(kit_Atom_fromLiteral("Authorization")), (void *) I(kit_Atom_fromLiteral("Basic QWxhZGRpbc2FtZQ==")));

    requestBuilder = M(kit_HttpRequestBuilder_new(KIT_HTTP_METHOD_GET, I(kit_Atom_fromLiteral("https://github.com"))));
    kit_HttpRequestBuilder_setTimeout(requestBuilder, 60);
    kit_HttpRequestBuilder_setHeaders(requestBuilder, &requestHeaders); // takes ownership invalidating headers
    assert(NULL == requestHeaders);

    request = kit_HttpRequestBuilder_build(&requestBuilder); // takes ownership deleting and invalidating requestBuilder.
    assert(NULL == requestBuilder);
    printRequest(request);

    response = I(kit_HttpRequest_fire(&request)); // takes ownership invalidating request.
    assert(NULL == request);
    printResponse(response);

    kit_invalidate((void **) &response, kit_HttpResponse_delete); // deletes and invalidate response and associated request
    return 0;
}

/*
 * 
 */
void printMap(const struct kit_Map *map) {
    struct kit_Pair pair;
    struct kit_Map_Iterator *iterator = M(kit_Map_Iterator_new((struct kit_Map *) map));

    while (KIT_RESULT_OK == kit_Map_Iterator_next(iterator, &pair)) {
        printf("  %s: %s\n", (const char *) pair.key, (const char *) pair.value);
    }

    kit_Map_Iterator_delete(iterator);
}

void printRequest(const struct kit_HttpRequest *request) {
    assert(request);
    puts("");
    printf("method: %s\n", kit_HttpMethod_explain(kit_HttpRequest_getMethod(request)));
    printf("url: %s\n", kit_HttpRequest_getUrl(request));
    printf("headers:\n");
    if (ImmutableOption_isSome(kit_HttpRequest_getHeaders(request))) {
        printMap(ImmutableOption_unwrap(kit_HttpRequest_getHeaders(request)));
    }
    printf("body:\n");
    if (ImmutableOption_isSome(kit_HttpRequest_getBody(request))) {
        printMap(ImmutableOption_unwrap(kit_HttpRequest_getBody(request)));
    }
    printf("timeout: %ld\n", kit_HttpRequest_getTimeout(request));
    printf("followLocation: %s\n", kit_truth(kit_HttpRequest_getFollowLocation(request)));
    printf("peerVerification: %s\n", kit_truth(kit_HttpRequest_getPeerVerification(request)));
    printf("hostVerification: %s\n", kit_truth(kit_HttpRequest_getHostVerification(request)));
    puts("");
}

void printResponse(const struct kit_HttpResponse *response) {
    assert(response);
    puts("");
    printf("effective_url: %s\n", kit_HttpResponse_getUrl(response));
    printf("headers:\n");
    if (ImmutableOption_isSome(kit_HttpResponse_getHeaders(response))) {
        printMap(ImmutableOption_unwrap(kit_HttpResponse_getHeaders(response)));
    }
    printf("body:\n");
    if (ImmutableOption_isSome(kit_HttpResponse_getBody(response))) {
        printMap(ImmutableOption_unwrap(kit_HttpResponse_getBody(response)));
    }
    printf("status: %d (%s)\n", kit_HttpResponse_getStatus(response), kit_HttpStatus_explanin(kit_HttpResponse_getStatus(response)));
    puts("");
}
