/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   January 07, 2018 
 */

#include <assert.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <kit/networking/http.h>

static bool
kit_HttpRequest_initialize(void);

static size_t
kit_HttpRequest_writeFn(void *content, size_t memberSize, size_t membersCount, void *userData);

ImmutableOption kit_HttpRequest_fire(const struct kit_HttpRequest **ref) {
    assert(ref);
    assert(*ref);

    if (!kit_HttpRequest_initialize()) {
        // TODO error handling
        // Out of memory
        return ImmutableOption_None;
    }

    bool teardownRequired = true;
    const struct kit_HttpRequest *request = *ref;
    struct kit_HttpResponseBuilder *responseBuilder = NULL;
    kit_String responseBody = NULL, responseHeaders = NULL;
    struct curl_slist *curlHeaders = NULL;
    CURL *curlHandler = NULL;

    MutableOption mutableOption;
    ImmutableOption immutableOption;

    do {
        mutableOption = kit_HttpResponseBuilder_new(request);
        if (MutableOption_isNone(mutableOption)) {
            // TODO error handling
            // Out of memory
            break;
        }
        responseBuilder = MutableOption_unwrap(mutableOption);

        immutableOption = kit_String_new(0);
        if (ImmutableOption_isNone(immutableOption)) {
            // TODO error handling
            // Out of memory
            break;
        }
        responseBody = ImmutableOption_unwrap(immutableOption);

        immutableOption = kit_String_new(0);
        if (ImmutableOption_isNone(immutableOption)) {
            // TODO error handling
            // Out of memory
            break;
        }
        responseHeaders = ImmutableOption_unwrap(immutableOption);

        if (ImmutableOption_isSome(kit_HttpRequest_getHeaders(request))) {
            curlHeaders = curl_slist_append(curlHeaders, ImmutableOption_unwrap(kit_HttpRequest_getHeaders(request)));
            if (NULL == curlHeaders) {
                // TODO error handling
                // Out of memory
                break;
            }
        }

        curlHandler = curl_easy_init();
        if (NULL == curlHandler) {
            // TODO error handling
            // Out of memory
            break;
        }

        // Set request url and method
        curl_easy_setopt(curlHandler, CURLOPT_URL, kit_HttpRequest_getUrl(request));
        curl_easy_setopt(curlHandler, CURLOPT_CUSTOMREQUEST, kit_HttpMethod_explain(kit_HttpRequest_getMethod(request)));

        // Set request headers
        curl_easy_setopt(curlHandler, CURLOPT_HTTPHEADER, curlHeaders);

        // Set request body
        if (ImmutableOption_isSome(kit_HttpRequest_getBody(request))) {
            kit_String body = ImmutableOption_unwrap(kit_HttpRequest_getBody(request));
            curl_easy_setopt(curlHandler, CURLOPT_POSTFIELDS, body);
            curl_easy_setopt(curlHandler, CURLOPT_POSTFIELDSIZE, kit_String_size(body));
        }

        // Set request parameters
        curl_easy_setopt(curlHandler, CURLOPT_FOLLOWLOCATION, kit_HttpRequest_getFollowLocation(request));
        curl_easy_setopt(curlHandler, CURLOPT_SSL_VERIFYPEER, kit_HttpRequest_getPeerVerification(request));
        curl_easy_setopt(curlHandler, CURLOPT_SSL_VERIFYHOST, kit_HttpRequest_getHostVerification(request));
        curl_easy_setopt(curlHandler, CURLOPT_TIMEOUT, kit_HttpRequest_getTimeout(request));

        // Set request callbacks in order to store the response data
        curl_easy_setopt(curlHandler, CURLOPT_HEADERFUNCTION, kit_HttpRequest_writeFn);
        curl_easy_setopt(curlHandler, CURLOPT_HEADERDATA, &responseHeaders);
        curl_easy_setopt(curlHandler, CURLOPT_WRITEFUNCTION, kit_HttpRequest_writeFn);
        curl_easy_setopt(curlHandler, CURLOPT_WRITEDATA, &responseBody);

#ifndef NDEBUG
        // Set verbose debug output
        curl_easy_setopt(curlHandler, CURLOPT_VERBOSE, 1L);
#endif

        // Perform the request
        CURLcode curlError = curl_easy_perform(curlHandler);
        if (CURLE_OK != curlError) {
            // TODO error handling
            // curl_easy_strerror(curlError);
            break;
        }

        // Get response's info
        {
            // set response effective url
            if (kit_HttpRequest_getFollowLocation(request)) {
                char *tmp = NULL;
                curl_easy_getinfo(curlHandler, CURLINFO_EFFECTIVE_URL, &tmp);
                immutableOption = kit_Atom_fromLiteral(tmp);
            } else {
                immutableOption = kit_Atom_fromLiteral(kit_HttpRequest_getUrl(request));
            }
            if (ImmutableOption_isNone(immutableOption)) {
                // TODO error handling
                // Out of memory
                break;
            }
            kit_HttpResponseBuilder_setUrl(responseBuilder, ImmutableOption_unwrap(immutableOption));

            // set response status
            enum kit_HttpStatus responseStatus;
            curl_easy_getinfo(curlHandler, CURLINFO_RESPONSE_CODE, &responseStatus);
            kit_HttpResponseBuilder_setStatus(responseBuilder, responseStatus);

            // set response headers
            kit_HttpResponseBuilder_setHeaders(responseBuilder, &responseHeaders);
            assert(NULL == responseHeaders);

            // set response body
            kit_HttpResponseBuilder_setBody(responseBuilder, &responseBody);
            assert(NULL == responseBody);
        }

        teardownRequired = false;
    } while (false);

    curl_easy_cleanup(curlHandler);
    curl_slist_free_all(curlHeaders);

    if (teardownRequired) {
        kit_HttpResponseBuilder_delete(responseBuilder);
        kit_String_delete(responseBody);
        kit_String_delete(responseHeaders);
        return ImmutableOption_None;
    } else {
        *ref = NULL;
        return ImmutableOption_new(kit_HttpResponseBuilder_build(&responseBuilder));
    }
}

bool kit_HttpRequest_initialize(void) {
    static bool initializationRequired = true;
    if (initializationRequired) {
        if (CURLE_OK != curl_global_init(CURL_GLOBAL_DEFAULT)) {
            return false;
        }
        atexit(curl_global_cleanup);
        initializationRequired = false;
    }
    return true;
}

size_t kit_HttpRequest_writeFn(void *content, size_t memberSize, size_t membersCount, void *userData) {
    kit_String *buffer = userData;
    const size_t contentSize = memberSize * membersCount;
    ImmutableOption option = kit_String_appendBytes(buffer, content, contentSize);

    if (ImmutableOption_isSome(option)) {
        *buffer = ImmutableOption_unwrap(option);
        return contentSize;
    } else {
        return CURL_MAX_WRITE_SIZE;
    }
}
