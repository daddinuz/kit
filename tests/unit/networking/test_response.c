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

#include <traits/traits.h>
#include <traits-unit/traits-unit.h>
#include <kit/networking/http_response.h>

/*
 * Features declarations
 */
FeatureDeclare(ResponseEssentials);

/*
 * Describe our test case
 */
Describe("Response",
         Trait(
                 "Essentials",
                 Run(ResponseEssentials),
         )
)

/*
 * Features declarations
 */
FeatureDefine(ResponseEssentials) {
    (void) traits_context;

    const struct kit_HttpRequest *const REQUEST;

    {
        struct kit_HttpRequestBuilder *requestBuilder = Option_unwrap(
                kit_HttpRequestBuilder_new(KIT_HTTP_METHOD_GET, Option_unwrap(kit_Atom_fromLiteral("url")))
        );

        *((const struct kit_HttpRequest **) &REQUEST) = kit_HttpRequestBuilder_build(&requestBuilder);
        assert_null(requestBuilder);
    }

    struct kit_HttpResponseBuilder *builder = NULL;

    {
        const struct kit_HttpRequest *request = REQUEST;

        builder = Option_unwrap(kit_HttpResponseBuilder_new(&request));
        assert_null(request);
        assert_not_null(REQUEST);
    }

    {
        struct kit_HttpRequestBuilder *requestBuilder = Option_unwrap(
                kit_HttpRequestBuilder_new(KIT_HTTP_METHOD_PUT, Option_unwrap(kit_Atom_fromLiteral("new url")))
        );

        const struct kit_HttpRequest *newRequest = kit_HttpRequestBuilder_build(&requestBuilder);
        const struct kit_HttpRequest *const newRequestCopy = newRequest;
        assert_null(requestBuilder);

        const struct kit_HttpRequest *request = kit_HttpResponseBuilder_setRequest(builder, &newRequest);
        assert_null(newRequest);
        assert_equal(request, REQUEST);

        newRequest = kit_HttpResponseBuilder_setRequest(builder, &request);
        assert_null(request);
        assert_equal(newRequest, newRequestCopy);

        kit_HttpRequest_delete(newRequest);
    }

    assert_equal(
            KIT_HTTP_STATUS_OK,
            kit_HttpResponseBuilder_setStatus(builder, KIT_HTTP_STATUS_METHOD_NOT_ALLOWED)
    );
    assert_equal(
            KIT_HTTP_STATUS_METHOD_NOT_ALLOWED,
            kit_HttpResponseBuilder_setStatus(builder, KIT_HTTP_STATUS_BAD_REQUEST)
    );

    assert_string_equal(
            "url",
            kit_HttpResponseBuilder_setUrl(builder, Option_unwrap(kit_Atom_fromLiteral("new url")))
    );
    assert_string_equal(
            "new url",
            kit_HttpResponseBuilder_setUrl(builder, Option_unwrap(kit_Atom_fromLiteral("effective url")))
    );

    {
        kit_String s = Option_unwrap(kit_String_fromLiteral("headers"));
        assert_true(Option_isNone(kit_HttpResponseBuilder_setHeaders(builder, &s)));
        s = Option_unwrap(kit_HttpResponseBuilder_clearHeaders(builder));
        assert_string_equal("headers", s);
        assert_true(Option_isNone(kit_HttpResponseBuilder_setHeaders(builder, &s)));
    }

    {
        kit_String s = Option_unwrap(kit_String_fromLiteral("body"));
        assert_true(
                Option_isNone(kit_HttpResponseBuilder_setBody(builder, &s))
        );
        s = Option_unwrap(kit_HttpResponseBuilder_clearBody(builder));
        assert_string_equal("body", s);
        assert_true(Option_isNone(kit_HttpResponseBuilder_setBody(builder, &s)));
    }

    const struct kit_HttpResponse *response = kit_HttpResponseBuilder_build(&builder);
    assert_null(builder);

    assert_equal(REQUEST, kit_HttpResponse_getRequest(response));
    assert_string_equal("effective url", kit_HttpResponse_getUrl(response));
    assert_string_equal("headers", Option_unwrap(kit_HttpResponse_getHeaders(response)));
    assert_string_equal("body", Option_unwrap(kit_HttpResponse_getBody(response)));
    assert_equal(KIT_HTTP_STATUS_BAD_REQUEST, kit_HttpResponse_getStatus(response));

    kit_HttpResponse_delete(response);
}
