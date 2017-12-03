/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 21, 2017 
 */

/*
 * Vectors are containers representing arrays that can change in size.
 * Just like arrays, vectors use contiguous storage locations for their elements, which means
 * that their elements can be accessed just as efficiently as in arrays.
 *
 * But unlike arrays, their size can change dynamically, with their storage being handled automatically by the container.
 * Internally, vectors use a dynamically allocated array to store their elements.
 * This array may need to be reallocated in order to grow in size when new elements are inserted, which implies
 * allocating a new array and moving all elements to it.
 * This is a relatively expensive task in terms of processing time, and thus, vectors do not reallocate
 * each time an element is added to the container.
 */

#ifndef KIT_VECTOR_INCLUDED
#define KIT_VECTOR_INCLUDED

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
 * kit_Vector interface.
 */
struct kit_Vector;

/**
 * Creates a new instance of kit_Vector.
 * In case of out of memory this function returns MutableOption_None.
 *
 * @return A new instance of kit_Vector or MutableOption_None.
 */
extern MutableOptional(struct kit_Vector *)
kit_Vector_new(void);

/**
 * Creates a new instance of kit_Vector giving hits about initial capacity.
 * In case of out of memory this function returns MutableOption_None.
 *
 * @param capacityHint The hint about the initial capacity.
 * @return A new instance of kit_Vector or MutableOption_None.
 */
extern MutableOptional(struct kit_Vector *)
kit_Vector_from(size_t capacityHint);

/**
 * Deletes an instance of kit_Vector.
 * If @param self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_Vector_delete(struct kit_Vector *self);

/**
 * Removes all elements from the container, leaving it with a size of 0.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The container instance.
 */
extern void
kit_Vector_clear(struct kit_Vector *self)
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
kit_Vector_insert(struct kit_Vector *self, void *e, size_t index)
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
kit_Vector_pushBack(struct kit_Vector *self, void *e)
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
kit_Vector_pushFront(struct kit_Vector *self, void *e)
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
kit_Vector_popBack(struct kit_Vector *self, void **out)
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
kit_Vector_popFront(struct kit_Vector *self, void **out)
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
kit_Vector_remove(struct kit_Vector *self, void **out, size_t index)
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
kit_Vector_set(struct kit_Vector *self, void *e, size_t index)
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
kit_Vector_get(struct kit_Vector *self, void **out, size_t index)
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
kit_Vector_back(struct kit_Vector *self, void **out)
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
kit_Vector_front(struct kit_Vector *self, void **out)
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
kit_Vector_size(struct kit_Vector *self)
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
kit_Vector_isEmpty(struct kit_Vector *self)
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
kit_Vector_capacity(struct kit_Vector *self)
__attribute__((__nonnull__));

/**
 * Explicitly request an expansion to hold at least size elements.
 * If requested size is less than vector capacity nothing will be done.
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
kit_Vector_reserve(struct kit_Vector *self, size_t size)
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
kit_Vector_shrink(struct kit_Vector *self)
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
kit_Vector_raw(struct kit_Vector *self)
__attribute__((__nonnull__));    /* unsafe */

/**
 * kit_Vector_Iterator interface.
 */
struct kit_Vector_Iterator;

/**
 * Creates a new instance of kit_Vector_Iterator.
 * In case of out of memory this function returns MutableOption_None.
 *
 * Checked runtime errors:
 *      - @param container must not be NULL.
 *      - @param bound must be KIT_BOUND_BEGIN or KIT_BOUND_END.
 *
 * @param container The instance of the container to iterate.
 * @param bound The start bound.
 * @return A new instance of kit_Vector_Iterator or MutableOption_None.
 */
extern MutableOptional(struct kit_Vector_Iterator *)
kit_Vector_Iterator_new(struct kit_Vector *container, enum kit_Bound bound)
__attribute__((__nonnull__));

/**
 * Creates a new instance of kit_Vector_Iterator from begin of container.
 * In case of out of memory this function returns MutableOption_None.
 *
 * Checked runtime errors:
 *      - @param container must not be NULL.
 *
 * @param container The instance of the container to iterate.
 * @return A new instance of kit_Vector_Iterator or MutableOption_None.
 */
extern MutableOptional(struct kit_Vector_Iterator *)
kit_Vector_Iterator_fromBegin(struct kit_Vector *container)
__attribute__((__nonnull__));

/**
 * Creates a new instance of kit_Vector_Iterator from end of container.
 * In case of out of memory this function returns MutableOption_None.
 *
 * Checked runtime errors:
 *      - @param container must not be NULL.
 *
 * @param container The instance of the container to iterate.
 * @return A new instance of kit_Vector_Iterator or MutableOption_None.
 */
extern MutableOptional(struct kit_Vector_Iterator *)
kit_Vector_Iterator_fromEnd(struct kit_Vector *container)
__attribute__((__nonnull__));

/**
 * Deletes an instance of kit_Vector_Iterator.
 * If @param self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_Vector_Iterator_delete(struct kit_Vector_Iterator *self);

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
kit_Vector_Iterator_rewind(struct kit_Vector_Iterator *self, enum kit_Bound bound)
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
kit_Vector_Iterator_rewindToBegin(struct kit_Vector_Iterator *self)
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
kit_Vector_Iterator_rewindToEnd(struct kit_Vector_Iterator *self)
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
kit_Vector_Iterator_next(struct kit_Vector_Iterator *self, void **out)
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
kit_Vector_Iterator_previous(struct kit_Vector_Iterator *self, void **out)
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
kit_Vector_Iterator_setLast(struct kit_Vector_Iterator *self, void *e)
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
kit_Vector_Iterator_isModified(struct kit_Vector_Iterator *self)
__attribute__((__nonnull__));

#ifdef __cplusplus
}
#endif

#endif /* KIT_VECTOR_INCLUDED */
