/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   January 11, 2018 
 */

#include <kit/errors.h>

Error OutOfRangeError = Error_new("Out of range");
Error OutOfMemoryError = Error_new("Out of memory");
Error IllegalStateError = Error_new("Illegal state");
Error ConcurrentModificationError = Error_new("Concurrent modification");
