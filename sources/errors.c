/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   January 11, 2018 
 */

#include <kit/errors.h>

const Error OutOfRangeError = Error_new("Out of range");
const Error OutOfMemoryError = Error_new("Out of memory");
const Error IllegalStateError = Error_new("Illegal state");
const Error ConcurrentModificationError = Error_new("Concurrent modification");
const Error NetworkingError = Error_new("Networking error");
