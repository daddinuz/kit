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
#include <kit/networking/http_request.h>

/*
 * Features declarations
 */
FeatureDeclare(RequestEssentials);

/*
 * Describe our test case
 */
Describe("Request",
         Trait(
                 "Essentials",
                 Run(RequestEssentials),
         )
)

/*
 * Features declarations
 */
FeatureDefine(RequestEssentials) {
    (void) traits_context;

    struct kit_HttpRequestBuilder *builder = Option_unwrap(
            kit_HttpRequestBuilder_new(KIT_HTTP_METHOD_GET, Option_unwrap(kit_Atom_fromLiteral("url")))
    );

    assert_equal(KIT_HTTP_METHOD_GET, kit_HttpRequestBuilder_setMethod(builder, KIT_HTTP_METHOD_POST));
    assert_equal(KIT_HTTP_METHOD_POST, kit_HttpRequestBuilder_setMethod(builder, KIT_HTTP_METHOD_PUT));

    assert_string_equal(
            "url",
            kit_HttpRequestBuilder_setUrl(builder, Option_unwrap(kit_Atom_fromLiteral("newer url")))
    );
    assert_string_equal(
            "newer url",
            kit_HttpRequestBuilder_setUrl(builder, Option_unwrap(kit_Atom_fromLiteral("newest url")))
    );

    {
        kit_String s = Option_unwrap(kit_String_fromLiteral("headers"));
        assert_true(Option_isNone(kit_HttpRequestBuilder_setHeaders(builder, &s)));
        s = Option_unwrap(kit_HttpRequestBuilder_clearHeaders(builder));
        assert_string_equal("headers", s);
        assert_true(Option_isNone(kit_HttpRequestBuilder_setHeaders(builder, &s)));
    }

    {
        kit_String s = Option_unwrap(kit_String_fromLiteral("body"));
        assert_true(
                Option_isNone(kit_HttpRequestBuilder_setBody(builder, &s))
        );
        s = Option_unwrap(kit_HttpRequestBuilder_clearBody(builder));
        assert_string_equal("body", s);
        assert_true(Option_isNone(kit_HttpRequestBuilder_setBody(builder, &s)));
    }

    assert_equal(0, kit_HttpRequestBuilder_setTimeout(builder, 25));
    assert_equal(25, kit_HttpRequestBuilder_setTimeout(builder, 30));

    assert_true(kit_HttpRequestBuilder_setFollowLocation(builder, false));
    assert_false(kit_HttpRequestBuilder_setFollowLocation(builder, true));

    assert_true(kit_HttpRequestBuilder_setPeerVerification(builder, false));
    assert_false(kit_HttpRequestBuilder_setPeerVerification(builder, true));

    assert_true(kit_HttpRequestBuilder_setHostVerification(builder, false));
    assert_false(kit_HttpRequestBuilder_setHostVerification(builder, true));

    const struct kit_HttpRequest *request = kit_HttpRequestBuilder_build(&builder);
    assert_null(builder);

    assert_equal(KIT_HTTP_METHOD_PUT, kit_HttpRequest_getMethod(request));
    assert_string_equal("newest url", kit_HttpRequest_getUrl(request));
    assert_string_equal("headers", Option_unwrap(kit_HttpRequest_getHeaders(request)));
    assert_string_equal("body", Option_unwrap(kit_HttpRequest_getBody(request)));
    assert_equal(30, kit_HttpRequest_getTimeout(request));
    assert_true(kit_HttpRequest_getFollowLocation(request));
    assert_true(kit_HttpRequest_getPeerVerification(request));
    assert_true(kit_HttpRequest_getHostVerification(request));

    kit_HttpRequest_delete(request);
}
