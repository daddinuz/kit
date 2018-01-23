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

#ifndef kIT_HTTP_STATUS_INCLUDED
#define kIT_HTTP_STATUS_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <kit/compiler_steroids.h>

enum kit_HttpStatus {
    KIT_HTTP_STATUS_CONTINUE = 100,                         /* Continue                        */
    KIT_HTTP_STATUS_SWITCHING_PROTOCOLS = 101,              /* Switching Protocols             */
    KIT_HTTP_STATUS_PROCESSING = 102,                       /* Processing                      */
    KIT_HTTP_STATUS_OK = 200,                               /* OK                              */
    KIT_HTTP_STATUS_CREATED = 201,                          /* Created                         */
    KIT_HTTP_STATUS_ACCEPTED = 202,                         /* Accepted                        */
    KIT_HTTP_STATUS_NON_AUTHORITATIVE_INFORMATION = 203,    /* Non-Authoritative Information   */
    KIT_HTTP_STATUS_NO_CONTENT = 204,                       /* No Content                      */
    KIT_HTTP_STATUS_RESET_CONTENT = 205,                    /* Reset Content                   */
    KIT_HTTP_STATUS_PARTIAL_CONTENT = 206,                  /* Partial Content                 */
    KIT_HTTP_STATUS_MULTI_STATUS = 207,                     /* Multi-Status                    */
    KIT_HTTP_STATUS_ALREADY_REPORTED = 208,                 /* Already Reported                */
    KIT_HTTP_STATUS_IM_USED = 226,                          /* IM Used                         */
    KIT_HTTP_STATUS_MULTIPLE_CHOICES = 300,                 /* Multiple Choices                */
    KIT_HTTP_STATUS_MOVED_PERMANENTLY = 301,                /* Moved Permanently               */
    KIT_HTTP_STATUS_FOUND = 302,                            /* Found                           */
    KIT_HTTP_STATUS_SEE_OTHER = 303,                        /* See Other                       */
    KIT_HTTP_STATUS_NOT_MODIFIED = 304,                     /* Not Modified                    */
    KIT_HTTP_STATUS_USE_PROXY = 305,                        /* Use Proxy                       */
    KIT_HTTP_STATUS_TEMPORARY_REDIRECT = 307,               /* Temporary Redirect              */
    KIT_HTTP_STATUS_PERMANENT_REDIRECT = 308,               /* Permanent Redirect              */
    KIT_HTTP_STATUS_BAD_REQUEST = 400,                      /* Bad Request                     */
    KIT_HTTP_STATUS_UNAUTHORIZED = 401,                     /* Unauthorized                    */
    KIT_HTTP_STATUS_PAYMENT_REQUIRED = 402,                 /* Payment Required                */
    KIT_HTTP_STATUS_FORBIDDEN = 403,                        /* Forbidden                       */
    KIT_HTTP_STATUS_NOT_FOUND = 404,                        /* Not Found                       */
    KIT_HTTP_STATUS_METHOD_NOT_ALLOWED = 405,               /* Method Not Allowed              */
    KIT_HTTP_STATUS_NOT_ACCEPTABLE = 406,                   /* Not Acceptable                  */
    KIT_HTTP_STATUS_PROXY_AUTHENTICATION_REQUIRED = 407,    /* Proxy Authentication Required   */
    KIT_HTTP_STATUS_REQUEST_TIMEOUT = 408,                  /* Request Timeout                 */
    KIT_HTTP_STATUS_CONFLICT = 409,                         /* Conflict                        */
    KIT_HTTP_STATUS_GONE = 410,                             /* Gone                            */
    KIT_HTTP_STATUS_LENGTH_REQUIRED = 411,                  /* Length Required                 */
    KIT_HTTP_STATUS_PRECONDITION_FAILED = 412,              /* Precondition Failed             */
    KIT_HTTP_STATUS_PAYLOAD_TOO_LARGE = 413,                /* Payload Too Large               */
    KIT_HTTP_STATUS_URI_TOO_LONG = 414,                     /* URI Too Long                    */
    KIT_HTTP_STATUS_UNSUPPORTED_MEDIA_TYPE = 415,           /* Unsupported Media Type          */
    KIT_HTTP_STATUS_RANGE_NOT_SATISFIABLE = 416,            /* Range Not Satisfiable           */
    KIT_HTTP_STATUS_EXPECTATION_FAILED = 417,               /* Expectation Failed              */
    KIT_HTTP_STATUS_MISDIRECTED_REQUEST = 421,              /* Misdirected Request             */
    KIT_HTTP_STATUS_UNPROCESSABLE_ENTITY = 422,             /* Unprocessable Entity            */
    KIT_HTTP_STATUS_LOCKED = 423,                           /* Locked                          */
    KIT_HTTP_STATUS_FAILED_DEPENDENCY = 424,                /* Failed Dependency               */
    KIT_HTTP_STATUS_UPGRADE_REQUIRED = 426,                 /* Upgrade Required                */
    KIT_HTTP_STATUS_PRECONDITION_REQUIRED = 428,            /* Precondition Required           */
    KIT_HTTP_STATUS_TOO_MANY_REQUESTS = 429,                /* Too Many Requests               */
    KIT_HTTP_STATUS_REQUEST_HEADER_FIELDS_TOO_LARGE = 431,  /* Request Header Fields Too Large */
    KIT_HTTP_STATUS_UNAVAILABLE_FOR_LEGAL_REASONS = 451,    /* Unavailable For Legal Reasons   */
    KIT_HTTP_STATUS_INTERNAL_SERVER_ERROR = 500,            /* Internal Server Error           */
    KIT_HTTP_STATUS_NOT_IMPLEMENTED = 501,                  /* Not Implemented                 */
    KIT_HTTP_STATUS_BAD_GATEWAY = 502,                      /* Bad Gateway                     */
    KIT_HTTP_STATUS_SERVICE_UNAVAILABLE = 503,              /* Service Unavailable             */
    KIT_HTTP_STATUS_GATEWAY_TIMEOUT = 504,                  /* Gateway Timeout                 */
    KIT_HTTP_STATUS_VERSION_NOT_SUPPORTED = 505,            /* HTTP Version Not Supported      */
    KIT_HTTP_STATUS_VARIANT_ALSO_NEGOTIATES = 506,          /* Variant Also Negotiates         */
    KIT_HTTP_STATUS_INSUFFICIENT_STORAGE = 507,             /* Insufficient Storage            */
    KIT_HTTP_STATUS_LOOP_DETECTED = 508,                    /* Loop Detected                   */
    KIT_HTTP_STATUS_NOT_EXTENDED = 510,                     /* Not Extended                    */
    KIT_HTTP_STATUS_NETWORK_AUTHENTICATION_REQUIRED = 511   /* Network Authentication Required */
};

extern const char *
kit_HttpStatus_explain(enum kit_HttpStatus status)
__attribute__((__warn_unused_result__));

#ifdef __cplusplus
}
#endif

#endif /* kIT_HTTP_STATUS_INCLUDED */
