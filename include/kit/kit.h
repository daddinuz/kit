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

#ifndef KIT_INCLUDED
#define KIT_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Versioning
 */
#define KIT_VERSION_MAJOR       0
#define KIT_VERSION_MINOR       1
#define KIT_VERSION_PATCH       0
#define KIT_VERSION_SUFFIX      ""
#define KIT_VERSION_IS_RELEASE  0
#define KIT_VERSION_HEX         0x000100

// miscellaneous
#include <kit/compiler_steroids.h>
#include <kit/errors.h>
#include <kit/utils.h>

// allocator
#include <kit/allocator/allocator.h>

// collections
#include <kit/collections/array.h>
#include <kit/collections/atom.h>
#include <kit/collections/bound.h>
#include <kit/collections/doubly_list.h>
#include <kit/collections/hash_map.h>
#include <kit/collections/list.h>
#include <kit/collections/map.h>
#include <kit/collections/pair.h>
#include <kit/collections/queue.h>
#include <kit/collections/sequence.h>
#include <kit/collections/singly_list.h>
#include <kit/collections/stack.h>
#include <kit/collections/string.h>
#include <kit/collections/vector.h>
#include <kit/collections/xor_list.h>

// networking
#include <kit/networking/http.h>


/**
 * Gets the kit package version.
 *
 * @return the semantic versioning string of the package.
 */
extern const char *
kit_version(void);

#ifdef __cplusplus
}
#endif

#endif /* KIT_INCLUDED */
