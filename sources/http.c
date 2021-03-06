/*
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 *
 * Copyright (c) 2018 Davide Di Carlo
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <curl/curl.h>
#include <kit/errors.h>
#include <kit/networking/http.h>

static bool
kit_HttpRequest_initialize(void);

static size_t
kit_HttpRequest_writeFn(void *content, size_t memberSize, size_t membersCount, void *userData);

ResultOf(const struct kit_HttpResponse *, NetworkingError, OutOfMemoryError)
kit_HttpRequest_fire(const struct kit_HttpRequest **ref) {
    assert(ref);
    assert(*ref);

    if (!kit_HttpRequest_initialize()) {
        return Result_error(OutOfMemoryError);
    }

    Option option;
    Result result = Result_ok(NULL);
    bool teardownRequired = true;
    const struct kit_HttpRequest *request = *ref;
    struct kit_HttpResponseBuilder *responseBuilder = NULL;
    kit_String responseBody = NULL, responseHeaders = NULL;
    struct curl_slist *curlHeaders = NULL;
    CURL *curlHandler = NULL;

    do {
        option = kit_HttpResponseBuilder_new(&request);
        assert(*ref);
        if (Option_isNone(option)) {
            assert(request);
            result = Result_error(OutOfMemoryError);
            break;
        }
        assert(NULL == request);
        request = *ref;
        responseBuilder = Option_unwrap(option);

        option = kit_String_new(0);
        if (Option_isNone(option)) {
            result = Result_error(OutOfMemoryError);
            break;
        }
        responseBody = Option_unwrap(option);

        option = kit_String_new(0);
        if (Option_isNone(option)) {
            result = Result_error(OutOfMemoryError);
            break;
        }
        responseHeaders = Option_unwrap(option);

        if (Option_isSome(kit_HttpRequest_getHeaders(request))) {
            curlHeaders = curl_slist_append(curlHeaders, Option_unwrap(kit_HttpRequest_getHeaders(request)));
            if (NULL == curlHeaders) {
                result = Result_error(OutOfMemoryError);
                break;
            }
        }

        curlHandler = curl_easy_init();
        if (NULL == curlHandler) {
            result = Result_error(OutOfMemoryError);
            break;
        }

        // Set request url and method
        curl_easy_setopt(curlHandler, CURLOPT_URL, kit_HttpRequest_getUrl(request));
        curl_easy_setopt(curlHandler, CURLOPT_CUSTOMREQUEST,
                         kit_HttpMethod_explain(kit_HttpRequest_getMethod(request)));

        // Set request headers
        curl_easy_setopt(curlHandler, CURLOPT_HTTPHEADER, curlHeaders);

        // Set request body
        if (Option_isSome(kit_HttpRequest_getBody(request))) {
            kit_String body = Option_unwrap(kit_HttpRequest_getBody(request));
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
            if (CURLE_OUT_OF_MEMORY == curlError) {
                result = Result_error(OutOfMemoryError);
            } else {
                result = Result_errorWithDetails(NetworkingError, curl_easy_strerror(curlError));
            }
            break;
        }

        // Get response's info
        {
            // set response effective url
            if (kit_HttpRequest_getFollowLocation(request)) {
                char *tmp = NULL;
                curl_easy_getinfo(curlHandler, CURLINFO_EFFECTIVE_URL, &tmp);
                option = kit_Atom_fromLiteral(tmp);
            } else {
                option = kit_Atom_fromLiteral(kit_HttpRequest_getUrl(request));
            }
            if (Option_isNone(option)) {
                result = Result_error(OutOfMemoryError);
                break;
            }
            kit_HttpResponseBuilder_setUrl(responseBuilder, Option_unwrap(option));

            // set response status
            enum kit_HttpStatus responseStatus;
            curl_easy_getinfo(curlHandler, CURLINFO_RESPONSE_CODE, &responseStatus);
            kit_HttpResponseBuilder_setStatus(responseBuilder, responseStatus);

            // set response headers
            option = kit_HttpResponseBuilder_setHeaders(responseBuilder, &responseHeaders);
            assert(Option_isNone(option));
            assert(NULL == responseHeaders);

            // set response body
            option = kit_HttpResponseBuilder_setBody(responseBuilder, &responseBody);
            assert(Option_isNone(option));
            assert(NULL == responseBody);
        }

        teardownRequired = false;
    } while (false);

    curl_easy_cleanup(curlHandler);
    curl_slist_free_all(curlHeaders);

    if (teardownRequired) {
        assert(OutOfMemoryError == Result_inspect(result) || NetworkingError == Result_inspect(result));
        kit_HttpResponseBuilder_delete(responseBuilder);
        kit_String_delete(responseBody);
        kit_String_delete(responseHeaders);
        return result;
    } else {
        assert(Result_isOk(result));
        *ref = NULL;
        return Result_ok((void *) kit_HttpResponseBuilder_build(&responseBuilder));
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
    Option option = kit_String_appendBytes(buffer, content, contentSize);

    if (Option_isSome(option)) {
        *buffer = Option_unwrap(option);
        return contentSize;
    } else {
        return CURL_MAX_WRITE_SIZE;
    }
}
