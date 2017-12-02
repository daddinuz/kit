/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 21, 2017 
 */

/*
 * Hats (hashed array tree) are containers representing arrays that can change in size.
 * Its primary objective is to reduce the amount of element copying due to automatic array resizing operations,
 * and to improve memory usage patterns.
 *
 * Unlike arrays, their size can change dynamically, with their storage being handled automatically by the container.
 * Internally, a hashed array tree has a top-level directory containing a power of two number of leaf arrays.
 * All leaf arrays are the same size as the top-level directory.
 * This structure superficially resembles a hash table with array-based collision chains, which is the basis
 * for the name hashed array tree.
 */

// TODO

#ifndef KIT_HAT_INCLUDED
#define KIT_HAT_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdbool.h>
#include <option/option.h>
#include <kit/compiler_steroids.h>
#include <kit/collections/bound.h>
#include <kit/collections/result.h>

/**
 * kit_Hat interface.
 */
struct kit_Hat;

/**
 * Creates a new instance of kit_Hat.
 * In case of out of memory this function returns Option_None.
 *
 * @return A new instance of kit_Hat or Option_None.
 */
extern Optional(struct kit_Hat *)
kit_Hat_new(void);

/**
 * Creates a new instance of kit_Hat giving hits about initial capacity.
 * In case of out of memory this function returns Option_None.
 *
 * @param capacityHint The hint about the initial capacity.
 * @return A new instance of kit_Hat or Option_None.
 */
extern Optional(struct kit_Hat *)
kit_Hat_from(size_t capacityHint);

/**
 * Deletes an instance of kit_Hat.
 * If @param self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_Hat_delete(struct kit_Hat *self);

/**
 * Removes all elements from the container, leaving it with a size of 0.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The container instance.
 */
extern void
kit_Hat_clear(struct kit_Hat *self)
__attribute__((__nonnull__));

/**
 * Inserts elements at the given index of the container.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The container instance.
 * @param e The element to be inserted.
 * @param index The index where the element has to be placed.
 * @return
 *      - KIT_RESULT_OK            :   The operation was performed successfully.
 *      - KIT_RESULT_OUT_OF_RANGE  :   The given index is out of range, nothing has been done.
 *      - KIT_RESULT_OUT_OF_MEMORY :   There's no more space left, nothing has been done.
 */
extern enum kit_Result
kit_Hat_insert(struct kit_Hat *self, void *e, size_t index)
__attribute__((__nonnull__(1)));

/**
 * Inserts elements at the back of the container.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The container instance.
 * @param e The element to be inserted.
 * @return
 *      - KIT_RESULT_OK            :   The operation was performed successfully.
 *      - KIT_RESULT_OUT_OF_MEMORY :   There's no more space left, nothing has been done.
 */
extern enum kit_Result
kit_Hat_pushBack(struct kit_Hat *self, void *e)
__attribute__((__nonnull__(1)));

/**
 * Inserts elements at the front of the container.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The container instance.
 * @param e The element to be inserted.
 * @return
 *      - KIT_RESULT_OK            :   The operation was performed successfully.
 *      - KIT_RESULT_OUT_OF_MEMORY :   There's no more space left, nothing has been done.
 */
extern enum kit_Result
kit_Hat_pushFront(struct kit_Hat *self, void *e)
__attribute__((__nonnull__(1)));

/**
 * Removes elements at the back of the container.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *      - @param out must not be NULL.
 *
 * @param self The container instance.
 * @param out The removed element.
 * @return
 *      - KIT_RESULT_OK            :   The operation was performed successfully.
 *      - KIT_RESULT_OUT_OF_RANGE  :   No such element in the container, nothing has been done.
 */
extern enum kit_Result
kit_Hat_popBack(struct kit_Hat *self, void **out)
__attribute__((__nonnull__));

/**
 * Removes elements at the front of the container.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *      - @param out must not be NULL.
 *
 * @param self The container instance.
 * @param out The removed element.
 * @return
 *      - KIT_RESULT_OK            :   The operation was performed successfully.
 *      - KIT_RESULT_OUT_OF_RANGE  :   No such element in the container, nothing has been done.
 */
extern enum kit_Result
kit_Hat_popFront(struct kit_Hat *self, void **out)
__attribute__((__nonnull__));

/**
 * Removes elements at the given index of the container.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *      - @param out must not be NULL.
 *
 * @param self The container instance.
 * @param out The removed element.
 * @param index The index of the element to remove.
 * @return
 *      - KIT_RESULT_OK            :   The operation was performed successfully.
 *      - KIT_RESULT_OUT_OF_RANGE  :   No such element in the container, nothing has been done.
 */
extern enum kit_Result
kit_Hat_remove(struct kit_Hat *self, void **out, size_t index)
__attribute__((__nonnull__));

/**
 * Replaces the element at the given index.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The container instance.
 * @param e The new element.
 * @param index The index of the element to be replaced.
 * @return
 *      - KIT_RESULT_OK            :   The operation was performed successfully.
 *      - KIT_RESULT_OUT_OF_RANGE  :   The given index is out of range, nothing has been done.
 */
extern enum kit_Result
kit_Hat_set(struct kit_Hat *self, void *e, size_t index)
__attribute__((__nonnull__(1)));

/**
 * Gets the element stored at the given index.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *      - @param out must not be NULL.
 *
 * @param self The container instance.
 * @param out The element requested.
 * @param index The index of the element requested.
 * @return
 *      - KIT_RESULT_OK            :   The operation was performed successfully.
 *      - KIT_RESULT_OUT_OF_RANGE  :   The given index is out of range, nothing has been done.
 */
extern enum kit_Result
kit_Hat_get(struct kit_Hat *self, void **out, size_t index)
__attribute__((__nonnull__));

/**
 * Gets the element stored at the back of the container.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *      - @param out must not be NULL.
 *
 * @param self The container instance.
 * @param out The element requested.
 * @return
 *      - KIT_RESULT_OK            :   The operation was performed successfully.
 *      - KIT_RESULT_OUT_OF_RANGE  :   No such element in the container, nothing has been done.
 */
extern enum kit_Result
kit_Hat_back(struct kit_Hat *self, void **out)
__attribute__((__nonnull__));

/**
 * Gets the element stored at the front of the container.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *      - @param out must not be NULL.
 *
 * @param self The container instance.
 * @param out The element requested.
 * @return
 *      - KIT_RESULT_OK            :   The operation was performed successfully.
 *      - KIT_RESULT_OUT_OF_RANGE  :   No such element in the container, nothing has been done.
 */
extern enum kit_Result
kit_Hat_front(struct kit_Hat *self, void **out)
__attribute__((__nonnull__));

/**
 * Gets the number of elements currently stored in the container.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The container instance.
 * @return The numbers of elements in the container.
 */
extern size_t
kit_Hat_size(struct kit_Hat *self)
__attribute__((__nonnull__));

/**
 * Checks if the container is empty.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The container instance.
 * @return true if the container is empty false otherwise.
 */
extern bool
kit_Hat_isEmpty(struct kit_Hat *self)
__attribute__((__nonnull__));

/**
 * Gets the number of elements the container can store before expansion.
 * (When size is equal to capacity the container will expand).
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The container instance.
 * @return The numbers of elements that can be stored before expansion.
 */
extern size_t
kit_Hat_capacity(struct kit_Hat *self)
__attribute__((__nonnull__));

/**
 * Explicitly request an expansion to hold at least size elements.
 * If requested size is less than hat capacity nothing will be done.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The container instance.
 * @return
 *      - KIT_RESULT_OK            :   The operation was performed successfully.
 *      - KIT_RESULT_OUT_OF_MEMORY :   There's no more space left, nothing has been done.
 */
extern enum kit_Result
kit_Hat_reserve(struct kit_Hat *self, size_t size)
__attribute__((__nonnull__));

/**
 * Requests the container to shrink in order to fit at least the stored elements freeing resources not used.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The container instance.
 * @return
 *      - KIT_RESULT_OK            :   The operation was performed successfully.
 *      - KIT_RESULT_OUT_OF_MEMORY :   Unable to relocate memory, nothing has been done.
 */
extern enum kit_Result
kit_Hat_shrink(struct kit_Hat *self)
__attribute__((__nonnull__));

/**
 * [Unsafe method]
 * Gets the raw data of the container.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The container instance.
 * @return The low level array of elements.
 */
extern void **
kit_Hat_raw(struct kit_Hat *self)
__attribute__((__nonnull__));    /* unsafe */

/**
 * kit_Hat_Iterator interface.
 */
struct kit_Hat_Iterator;

/**
 * Creates a new instance of kit_Hat_Iterator.
 * In case of out of memory this function returns Option_None.
 *
 * Checked runtime errors:
 *      - @param container must not be NULL.
 *      - @param bound must be KIT_BOUND_BEGIN or KIT_BOUND_END.
 *
 * @param container The instance of the container to iterate.
 * @param bound The start bound.
 * @return A new instance of kit_Hat_Iterator or Option_None.
 */
extern Optional(struct kit_Hat_Iterator *)
kit_Hat_Iterator_new(struct kit_Hat *container, enum kit_Bound bound)
__attribute__((__nonnull__));

/**
 * Creates a new instance of kit_Hat_Iterator from begin of container.
 * In case of out of memory this function returns Option_None.
 *
 * Checked runtime errors:
 *      - @param container must not be NULL.
 *
 * @param container The instance of the container to iterate.
 * @return A new instance of kit_Hat_Iterator or Option_None.
 */
extern Optional(struct kit_Hat_Iterator *)
kit_Hat_Iterator_fromBegin(struct kit_Hat *container)
__attribute__((__nonnull__));

/**
 * Creates a new instance of kit_Hat_Iterator from end of container.
 * In case of out of memory this function returns Option_None.
 *
 * Checked runtime errors:
 *      - @param container must not be NULL.
 *
 * @param container The instance of the container to iterate.
 * @return A new instance of kit_Hat_Iterator or Option_None.
 */
extern Optional(struct kit_Hat_Iterator *)
kit_Hat_Iterator_fromEnd(struct kit_Hat *container)
__attribute__((__nonnull__));

/**
 * Deletes an instance of kit_Hat_Iterator.
 * If @param self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_Hat_Iterator_delete(struct kit_Hat_Iterator *self);

/**
 * Rewinds the iterator.
 *
 * Checked runtime errors:
 *      - @param container must not be NULL.
 *      - @param bound must be KIT_BOUND_BEGIN or KIT_BOUND_END.
 *
 * @param container The instance of the container to iterate.
 * @param bound The start bound.
 */
extern void
kit_Hat_Iterator_rewind(struct kit_Hat_Iterator *self, enum kit_Bound bound)
__attribute__((__nonnull__));

/**
 * Rewinds the iterator to begin of container.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The iterator instance.
 */
extern void
kit_Hat_Iterator_rewindToBegin(struct kit_Hat_Iterator *self)
__attribute__((__nonnull__));

/**
 * Rewinds the iterator to end of container.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The iterator instance.
 */
extern void
kit_Hat_Iterator_rewindToEnd(struct kit_Hat_Iterator *self)
__attribute__((__nonnull__));

/**
 * Gets the next element moving forward in the container.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *      - @param out must not be NULL.
 *
 * @param self The iterator instance.
 * @param out The retrieved element.
 * @return
 *      - KIT_RESULT_OK                        :   The operation was performed successfully.
 *      - KIT_RESULT_OUT_OF_RANGE              :   The iterator hit the end of the container, nothing has been done.
 *      - KIT_RESULT_CONCURRENT_MODIFICATION   :   The container has been modified, nothing has been done.
 */
extern enum kit_Result
kit_Hat_Iterator_next(struct kit_Hat_Iterator *self, void **out)
__attribute__((__nonnull__));

/**
 * Gets the previous element moving backward in the container.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *      - @param out must not be NULL.
 *
 * @param self The iterator instance.
 * @param out The retrieved element.
 * @return
 *      - KIT_RESULT_OK                        :   The operation was performed successfully.
 *      - KIT_RESULT_OUT_OF_RANGE              :   The iterator hit the begin of the container, nothing has been done.
 *      - KIT_RESULT_CONCURRENT_MODIFICATION   :   The container has been modified, nothing has been done.
 */
extern enum kit_Result
kit_Hat_Iterator_previous(struct kit_Hat_Iterator *self, void **out)
__attribute__((__nonnull__));

/**
 * Replaces the last retrieved element.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The iterator instance.
 * @param e The new element.
 * @return
 *      - KIT_RESULT_OK                        :   The operation was performed successfully.
 *      - KIT_RESULT_ILLEGAL_STATE             :   Neither next() or previous() has been called, nothing has been done.
 *      - KIT_RESULT_CONCURRENT_MODIFICATION   :   The container has been modified, nothing has been done.
 */
extern enum kit_Result
kit_Hat_Iterator_setLast(struct kit_Hat_Iterator *self, void *e)
__attribute__((__nonnull__(1)));

/**
 * Checks for associated container modifications.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The iterator instance.
 * @return true if the container has been modified else false
 */
extern bool
kit_Hat_Iterator_isModified(struct kit_Hat_Iterator *self)
__attribute__((__nonnull__));

#ifdef __cplusplus
}
#endif

#endif /* KIT_HAT_INCLUDED */
