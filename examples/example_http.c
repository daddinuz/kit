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

void printRequest(const struct kit_HttpRequest *request) __attribute__((__nonnull__));
void printResponse(const struct kit_HttpResponse *response) __attribute__((__nonnull__));

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

    requestBuilder = M(kit_HttpRequestBuilder_new(KIT_HTTP_METHOD_GET, I(kit_Atom_fromLiteral("https://github.com"))));
    kit_HttpRequestBuilder_setTimeout(requestBuilder, 60);
    kit_HttpRequestBuilder_setHeaders(requestBuilder, &requestHeaders); // takes ownership invalidating headers
    assert(NULL == requestHeaders);

    request = kit_HttpRequestBuilder_build(&requestBuilder); // takes ownership deleting and invalidating requestBuilder.
    assert(NULL == requestBuilder);
    printRequest(request);

    // TODO perform real call
    response = I(kit_HttpRequest_fire(&request)); // takes ownership invalidating request.
    assert(NULL == request);
    printResponse(response);

    kit_invalidate((void **) &response, kit_HttpResponse_delete); // deletes and invalidate response and associated request
    return 0;
}

void printRequest(const struct kit_HttpRequest *request) {
    assert(request);
    puts("");
    printf("method: %s\n", kit_HttpMethod_explain(kit_HttpRequest_getMethod(request)));
    printf("url: %s\n", kit_HttpRequest_getUrl(request));

    // --- TODO -----------------------------------------------------------
    printf("headers:\n");
    printf("body:\n");
    // --------------------------------------------------------------------

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

    // --- TODO -----------------------------------------------------------
    printf("headers:\n");
    printf("body:\n");
    // --------------------------------------------------------------------

    printf("status: %d (%s)\n", kit_HttpResponse_getStatus(response), kit_HttpStatus_explanin(kit_HttpResponse_getStatus(response)));
    puts("");
}
