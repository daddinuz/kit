/*
 * C Header File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   November 21, 2017 
 */

/*
 * Sequence provides a common interface for mono-directional iterable containers with dynamic sizes
 * that can be expanded or contracted on both ends (either its front or its back).
 */

#ifndef KIT_SEQUENCE_INCLUDED
#define KIT_SEQUENCE_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdbool.h>
#include <option/option.h>
#include <kit/compiler_steroids.h>
#include <kit/collections/result.h>

/**
 * kit_Sequence interface.
 */
struct kit_Sequence;

/**
 * Creates a new instance of kit_Sequence using DoublyList as underlying container.
 * In case of out of memory this function returns Option_None.
 *
 * @return A new instance of kit_Sequence or Option_None.
 */
extern Optional(struct kit_Sequence *)
kit_Sequence_fromDoublyList(void);

/**
 * Creates a new instance of kit_Sequence using SinglyList as underlying container.
 * In case of out of memory this function returns Option_None.
 *
 * @return A new instance of kit_Sequence or Option_None.
 */
extern Optional(struct kit_Sequence *)
kit_Sequence_fromSinglyList(void);

/**
 * Creates a new instance of kit_Sequence using XorList as underlying container.
 * In case of out of memory this function returns Option_None.
 *
 * @return A new instance of kit_Sequence or Option_None.
 */
extern Optional(struct kit_Sequence *)
kit_Sequence_fromXorList(void);

/**
 * Creates a new instance of kit_Sequence using Vector as underlying container.
 * In case of out of memory this function returns Option_None.
 *
 * @return A new instance of kit_Sequence or Option_None.
 */
extern Optional(struct kit_Sequence *)
kit_Sequence_fromVector(size_t capacityHint);

/**
 * Deletes an instance of kit_Sequence.
 * If @param self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_Sequence_delete(struct kit_Sequence *self);

/**
 * Removes all elements from the container, leaving it with a size of 0.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The container instance.
 */
extern void
kit_Sequence_clear(struct kit_Sequence *self) __attribute__((__nonnull__));

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
kit_Sequence_insert(struct kit_Sequence *self, void *e, size_t index) __attribute__((__nonnull__(1)));

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
kit_Sequence_pushBack(struct kit_Sequence *self, void *e) __attribute__((__nonnull__(1)));

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
kit_Sequence_pushFront(struct kit_Sequence *self, void *e) __attribute__((__nonnull__(1)));

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
kit_Sequence_popBack(struct kit_Sequence *self, void **out) __attribute__((__nonnull__));

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
kit_Sequence_popFront(struct kit_Sequence *self, void **out) __attribute__((__nonnull__));

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
kit_Sequence_remove(struct kit_Sequence *self, void **out, size_t index) __attribute__((__nonnull__));

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
kit_Sequence_set(struct kit_Sequence *self, void *e, size_t index) __attribute__((__nonnull__(1)));

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
kit_Sequence_get(struct kit_Sequence *self, void **out, size_t index) __attribute__((__nonnull__));

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
kit_Sequence_back(struct kit_Sequence *self, void **out) __attribute__((__nonnull__));

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
kit_Sequence_front(struct kit_Sequence *self, void **out) __attribute__((__nonnull__));

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
kit_Sequence_size(struct kit_Sequence *self) __attribute__((__nonnull__));

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
kit_Sequence_isEmpty(struct kit_Sequence *self) __attribute__((__nonnull__));

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
kit_Sequence_capacity(struct kit_Sequence *self) __attribute__((__nonnull__));

/**
 * Requests an expansion to hold at least @param size elements.
 * (This method may ignore the request if the container does not support reserve)
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
kit_Sequence_reserve(struct kit_Sequence *self, size_t size) __attribute__((__nonnull__));

/**
 * Requests the container to shrink in order to fit the stored elements freeing resources not used.
 * (This method may ignore the request if the container does not support shrink)
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
kit_Sequence_shrink(struct kit_Sequence *self) __attribute__((__nonnull__));

/**
 * kit_Sequence_Iterator interface.
 */
struct kit_Sequence_Iterator;

/**
 * Creates a new instance of kit_Sequence_Iterator from begin of container.
 * In case of out of memory this function returns Option_None.
 *
 * Checked runtime errors:
 *      - @param container must not be NULL.
 *
 * @param container The instance of the container to iterate.
 * @return A new instance of kit_Sequence_Iterator or Option_None.
 */
extern Optional(struct kit_Sequence_Iterator *)
kit_Sequence_Iterator_new(struct kit_Sequence *container) __attribute__((__nonnull__));

/**
 * Deletes an instance of kit_Sequence_Iterator.
 * If @param self is NULL no action will be performed.
 *
 * @param self The instance to be deleted.
 */
extern void
kit_Sequence_Iterator_delete(struct kit_Sequence_Iterator *self);

/**
 * Rewinds the iterator to begin of container.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The iterator instance.
 */
extern void
kit_Sequence_Iterator_rewind(struct kit_Sequence_Iterator *self) __attribute__((__nonnull__));

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
kit_Sequence_Iterator_next(struct kit_Sequence_Iterator *self, void **out) __attribute__((__nonnull__));

/**
 * Replaces the last retrieved element.
 *
 * Checked runtime errors:
 *      - @param self must not be NULL.
 *
 * @param self The iterator instance.
 * @param e The new element.
 * @return
 *      - KIT_RESULT_OK                         :   The operation was performed successfully.
 *      - KIT_RESULT_ILLEGAL_STATE              :   next() has not been called, nothing has been done.
 *      - KIT_RESULT_CONCURRENT_MODIFICATION    :   The container has been modified, nothing has been done.
 */
extern enum kit_Result
kit_Sequence_Iterator_setLast(struct kit_Sequence_Iterator *self, void *e) __attribute__((__nonnull__(1)));

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
kit_Sequence_Iterator_isModified(struct kit_Sequence_Iterator *self) __attribute__((__nonnull__));

#ifdef __cplusplus
}
#endif

#endif /* KIT_SEQUENCE_INCLUDED */
