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
    const struct kit_HttpRequest *request;
    const struct kit_HttpResponse *response;
    struct kit_HttpRequestBuilder *builder = M(kit_HttpRequestBuilder_new(KIT_HTTP_METHOD_GET, I(kit_Atom_fromLiteral("https://github.com"))));

    kit_HttpRequestBuilder_setTimeout(builder, 60);
    kit_HttpRequestBuilder_putHeader(builder, I(kit_Atom_fromLiteral("Accept")), I(kit_Atom_fromLiteral("application/json")));    kit_HttpRequestBuilder_putHeader(builder, I(kit_Atom_fromLiteral("Accept")), I(kit_Atom_fromLiteral("application/json")));

    request = I(kit_HttpRequestBuilder_build(&builder)); // moves ownership deleting and invalidating builder.
    assert(NULL == builder);
    printRequest(request);

    response = I(kit_HttpRequest_fire(&request)); // moves ownership invalidating request.
    assert(NULL == request);
    printResponse(response);

    kit_invalidate((void **) &response, kit_HttpResponse_delete); // deletes and invalidate response and associated request
    return 0;
}

void printRequest(const struct kit_HttpRequest *request) {
    assert(request);
    puts("");
    printf("method: %s\n", kit_HttpMethod_explanin(kit_HttpRequest_getMethod(request)));
    printf("url: %s\n", kit_HttpRequest_getUrl(request));

    // --- TODO -----------------------------------------------------------
    void *value;
    kit_Atom *accept = I(kit_Atom_fromLiteral("Accept"));
    const struct kit_Map *headers = kit_HttpRequest_getHeaders(request);
    kit_Map_get((void *) headers, accept, &value);
    printf("headers:\n");
    printf("\t%s: %s\n", accept, (const char *) value);
    printf("body: %s\n", ""); // kit_HttpRequest_getBody(request));
    // --------------------------------------------------------------------

    printf("timeout: %ld\n", kit_HttpRequest_getTimeout(request));
    printf("followLocation: %s\n", kit_truth(kit_HttpRequest_getFollowLocation(request)));
    printf("peerVerification: %s\n", kit_truth(kit_HttpRequest_getPeerVerification(request)));
    printf("hostVerification: %s\n", kit_truth(kit_HttpRequest_getHostVerification(request)));
    puts("");
}

void printResponse(const struct kit_HttpResponse *response) {
    assert(response);
    // TODO
}
