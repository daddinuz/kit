/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   December 03, 2017 
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <kit/utils.h>
#include <kit/networking/http.h>

#define M(x)   MutableOption_unwrap((x))
#define I(x)   ImmutableOption_unwrap((x))

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
    kit_Atom url = I(kit_Atom_fromLiteral("https://api.github.com/repos/daddinuz/kit/issues"));
    kit_String requestHeaders = I(
            kit_String_fromFormat(
                    "Authorization: token %s\n"
                            "Accept: application/vnd.github.VERSION.raw+json\n"
                            "Content-Type: application/json\n"
                            "User-Agent: daddinuz/kit\n",
                    getenv("GITHUB_AUTH_TOKEN")
            )
    );

    struct kit_HttpRequestBuilder *requestBuilder = M(kit_HttpRequestBuilder_new(KIT_HTTP_METHOD_GET, url));
    kit_HttpRequestBuilder_setTimeout(requestBuilder, 25);
    kit_HttpRequestBuilder_setHeaders(requestBuilder, &requestHeaders); // takes ownership invalidating requestHeaders
    assert(NULL == requestHeaders);

    const struct kit_HttpRequest *request = kit_HttpRequestBuilder_build(&requestBuilder); // takes ownership deleting and invalidating requestBuilder.
    assert(NULL == requestBuilder);
    printRequest(request);

    const struct kit_HttpResponse *response = I(kit_HttpRequest_fire(&request)); // takes ownership invalidating request.
    assert(NULL == request);
    printResponse(response);

    kit_invalidate((void **) &response, kit_HttpResponse_delete); // deletes and invalidates response and associated request
    return 0;
}

/*
 * 
 */
void printRequest(const struct kit_HttpRequest *request) {
    assert(request);
    const char *buffer;
    ImmutableOption immutableOption;

    puts("");
    printf("method: %s\n", kit_HttpMethod_explain(kit_HttpRequest_getMethod(request)));
    printf("url: %s\n", kit_HttpRequest_getUrl(request));

    immutableOption = kit_HttpRequest_getHeaders(request);
    buffer = I(ImmutableOption_isSome(immutableOption) ? immutableOption : kit_Atom_fromLiteral(""));
    printf("headers:\n%s\n", buffer);

    immutableOption = kit_HttpRequest_getBody(request);
    buffer = I(ImmutableOption_isSome(immutableOption) ? immutableOption : kit_Atom_fromLiteral(""));
    printf("body:\n%s\n", buffer);

    printf("timeout: %ld\n", kit_HttpRequest_getTimeout(request));
    printf("followLocation: %s\n", kit_truth(kit_HttpRequest_getFollowLocation(request)));
    printf("peerVerification: %s\n", kit_truth(kit_HttpRequest_getPeerVerification(request)));
    printf("hostVerification: %s\n", kit_truth(kit_HttpRequest_getHostVerification(request)));
    puts("");
}

void printResponse(const struct kit_HttpResponse *response) {
    assert(response);
    const char *buffer;
    ImmutableOption immutableOption;
    const enum kit_HttpStatus status = kit_HttpResponse_getStatus(response);

    puts("");
    printf("effectiveUrl: %s\n", kit_HttpResponse_getUrl(response));

    immutableOption = kit_HttpResponse_getHeaders(response);
    buffer = I(ImmutableOption_isSome(immutableOption) ? immutableOption : kit_Atom_fromLiteral(""));
    printf("headers:\n%s\n", buffer);

    immutableOption = kit_HttpResponse_getBody(response);
    buffer = I(ImmutableOption_isSome(immutableOption) ? immutableOption : kit_Atom_fromLiteral(""));
    printf("body:\n%s\n", buffer);

    printf("status: %d (%s)\n", status, kit_HttpStatus_explain(status));
    puts("");
}
