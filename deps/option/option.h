/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   January 10, 2018
 */

#ifndef OPTION_INCLUDED
#define OPTION_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#define OPTION_VERSION          "0.10.0"
#define OPTION_VERSION_MAJOR    0
#define OPTION_VERSION_MINOR    10
#define OPTION_VERSION_PATCH    0

#include <stddef.h>
#include <stdbool.h>

#if !(defined(__GNUC__) || defined(__clang__))
#define __attribute__(...)
#endif

/**
 * Option represents encapsulation of an optional value; it is used as the return type of functions which may or may
 * not return a meaningful value when they are applied.
 *
 * @attention
 *  Option type must be treated as opaque therefore should be used only through the functions exported by this interface,
 *  its members should never be accessed directly.
 */
typedef struct {
    void *__data;
} Option;

/**
 * An helper macro used for type hinting, useful when writing interfaces.
 * By convention the annotated type is the wrapped data type.
 */
#define OptionOf(xType) \
    Option

/**
 * The None Option instance used instead of NULL to represent the absence of a value.
 */
extern const Option None;

/**
 * Creates an Option.
 *
 * @param data The optional value.
 * @return None if data is NULL else a new Option instance wrapping data.
 */
extern Option
Option_new(void *data);

/**
 * Tests if Option is None
 *
 * @param self The Option instance.
 * @return false if Option is None else true.
 */
extern bool
Option_isSome(Option self);

/**
 * Tests if Option is None
 *
 * @param self The Option instance.
 * @return true if Option is None else false.
 */
extern bool
Option_isNone(Option self);

/**
 * Unwraps an Option, yielding its wrapped value if it's not None.
 * Aborts execution if Option is None with a custom panic message.
 *
 * @attention
 *  This function should never be used directly, used the exported macro instead.
 *
 * @param __file The file name.
 * @param __line The line number.
 * @param self The Option instance.
 * @param format The custom panic message.
 * @param ... The format params.
 * @return The unwrapped value or terminates the execution.
 */
extern void *
__Option_expect(const char *__file, size_t __line, Option self, const char *format, ...)
__attribute__((__nonnull__(1, 4), __format__(__printf__, 4, 5)));

/**
 * @see __Option_expect(const char *__file, size_t __line, Option self, const char *format, ...)
 */
#define Option_expect(xSelf, ...) \
  __Option_expect(__FILE__, __LINE__, (xSelf), __VA_ARGS__)

/**
 * Unwraps an Option, yielding its wrapped value if it's not None.
 * Aborts execution if Option is None with a pre-defined panic message.
 *
 * @attention
 *  This function should never be used directly, used the exported macro instead.
 *
 * @param __file The file name.
 * @param __line The line number.
 * @param self The Option instance.
 * @return The unwrapped value or terminates the execution.
 */
extern void *
__Option_unwrap(const char *__file, size_t __line, Option self)
__attribute__((__nonnull__(1)));

/**
 * @see __Option_unwrap(const char *__file, size_t __line, Option self)
 */
#define Option_unwrap(xSelf) \
  __Option_unwrap(__FILE__, __LINE__, (xSelf))

/**
 * Maps self applying mapFn.
 *
 * @param self The Option instance.
 * @param mapFn The map function [<b>must not be NULL</b>].
 * @return The mapped Option instance.
 */
extern Option
Option_map(Option self, Option mapFn(Option))
__attribute__((__nonnull__));

/**
 * Maps self applying mapFn if self is not None, otherwise returns a default Option.
 *
 * @param self The Option instance.
 * @param def The default option.
 * @param mapFn The map function [<b>must not be NULL</b>].
 * @return The mapped Option instance.
 */
extern Option
Option_mapOr(Option self, Option def, Option mapFn(Option))
__attribute__((__nonnull__));

/**
 * Maps self applying mapFn if self is not None, otherwise compute a default Option applying defFn.
 *
 * @param self The Option instance.
 * @param defFn The default function to compute if self is None [<b>must not be NULL</b>].
 * @param mapFn The map function to apply if self is not None [<b>must not be NULL</b>].
 * @return The mapped Option instance.
 */
extern Option
Option_mapOrElse(Option self, Option defFn(void), Option mapFn(Option))
__attribute__((__nonnull__));

/**
 * Error represents applicative errors that may occur at runtime.
 */
typedef struct {
    const char *message;
} const Error;

/**
 * Helper function to create new errors
 */
#define Error_new(xMessage) \
    {.message=(xMessage)}

/**
 * The Ok Error instance to notify a successful execution.
 */
extern Error Ok;

/**
 * Result holds a returned value or an error code providing a way of handling errors, without resorting to exception
 * handling; when a function that may fail returns a result type, the programmer is forced to consider success or failure
 * paths, before getting access to the expected result; this eliminates the possibility of an erroneous programmer assumption.
 *
  * @attention
 *  Result type must be treated as opaque therefore should be used only through the functions exported by this interface,
 *  its members should never be accessed directly.
 */
typedef struct {
    void *__data;
    Error *__error;
} Result;

/**
 * An helper macro used for type hinting, useful when writing interfaces.
 * By convention the first annotated type is the wrapped data type, every types following are Error types.
 */
#define ResultOf(...) \
    Result

/**
 * Creates a Result notifying a successful execution.
 *
 * @param data The result value.
 * @return A new Result instance wrapping data.
 */
extern Result
Result_ok(void *data);

/**
 * Creates a Result notifying a unsuccessful execution.
 *
 * @param data The result value.
 * @return A new Result instance wrapping an error.
 */
extern Result
Result_error(Error *error)
__attribute__((__nonnull__));

/**
 * Tests if Result is Ok
 *
 * @param self The Result instance.
 * @return true if Result is Ok else false.
 */
extern bool
Result_isOk(Result self);

/**
 * Tests if Result is Error
 *
 * @param self The Result instance.
 * @return true if Result is Error else false.
 */
extern bool
Result_isError(Result self);

/**
 * Unwraps a Result, yielding its wrapped value if it's Ok .
 * Aborts execution if Result is Error with a custom panic message.
 *
 * @attention
 *  This function should never be used directly, used the exported macro instead.
 *
 * @param __file The file name.
 * @param __line The line number.
 * @param self The Result instance.
 * @param format The custom panic message.
 * @param ... The format params.
 * @return The unwrapped value or terminates the execution.
 */
extern void *
__Result_expect(const char *__file, size_t __line, Result self, const char *format, ...)
__attribute__((__nonnull__(1, 4), __format__(__printf__, 4, 5)));

/**
 * @see __Result_expect(const char *__file, size_t __line, Result self, const char *format, ...)
 */
#define Result_expect(xSelf, ...) \
  __Result_expect(__FILE__, __LINE__, (xSelf), __VA_ARGS__)

/**
 * Unwraps a Result, yielding its wrapped value if it's Ok .
 * Aborts execution if Result is Error with a pre-defined panic message.
 *
 * @attention
 *  This function should never be used directly, used the exported macro instead.
 *
 * @param __file The file name.
 * @param __line The line number.
 * @param self The Result instance.
 * @return The unwrapped value or terminates the execution.
 */
extern void *
__Result_unwrap(const char *__file, size_t __line, Result self)
__attribute__((__nonnull__(1)));

/**
 * @see __Result_unwrap(const char *__file, size_t __line, Result self)
 */
#define Result_unwrap(xSelf) \
  __Result_unwrap(__FILE__, __LINE__, (xSelf))

/**
 * Inspects the result error.
 *
 * @param self The Result instance.
 * @return The Error associated to the result.
 */
extern Error *
Result_inspect(Result self);

/**
 * Explains the result error.
 *
 * @param self The Result instance.
 * @return An explanation string.
 */
extern const char *
Result_explain(Result self);

#ifdef __cplusplus
}
#endif

#endif /* OPTION_INCLUDED */
