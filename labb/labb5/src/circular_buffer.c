#include <stdio.h>
#include <limits.h>
#include "circular_buffer.h"

void initCircularBuffer(struct circularBuffer* bufferPtr, u_int32_t* data,
                        int maxLength) {
    bufferPtr->data = data;
    bufferPtr->head = 0;
    bufferPtr->tail = 0;
    bufferPtr->maxLength = maxLength;
    bufferPtr->size = 0;
}

int inc(int maxLength, int val) { return (val + 1) % maxLength; }

int dec(int maxLength, int val) {
    if (val == 0) {
        return maxLength - 1;
    } else {
        return val - 1;
    }
}

/*
 * This function should check if the buffer pointed to by bufferPtr
 * contains one or more elements with the value specified by the
 * 'value' argument.
 *
 * The function should return:
 *  - 'value' if the an element with the argument value was found in the queue.
 *  - INT_MIN (defined in limits.h) if value was not found.
 */
u_int32_t contains(struct circularBuffer* bufferPtr, u_int32_t value) {
    for (int i = bufferPtr->head; i != bufferPtr->tail;
         i = inc(bufferPtr->maxLength, i)) {
        if (bufferPtr->data[i] == value) {
            return value;
        }
    }
    return INT_MIN;
}

/*
 * This function should add the value specified by the 'value'
 * argument at the tail of the buffer.
 *
 * The function should return:
 *  - 'value' if the value was successfully added to the queue.
 *  - INT_MIN (defined in limits.h) if the value was not added.
 */
u_int32_t addElement(struct circularBuffer* bufferPtr, u_int32_t value) {
    if (inc(bufferPtr->maxLength, bufferPtr->tail) == bufferPtr->head) {
        return INT_MIN;
    } else {
        bufferPtr->data[bufferPtr->tail] = value;
        bufferPtr->tail = inc(bufferPtr->maxLength, bufferPtr->tail);
        bufferPtr->size++;
        return value;
    }
}

/*
 * This function should remove all elements in the buffer whose
 * value matches the 'value' argument.
 *
 * The function should return:
 *  The argument value: if at least one element was removed from queue.
 *  INT_MIN (defined in limits.h) if no element was removed.
 */
u_int32_t removeValue(struct circularBuffer* bufferPtr, u_int32_t value) {
    u_int32_t returnval = INT_MIN;
    for (int i = bufferPtr->head; i != bufferPtr->tail;
         i = inc(bufferPtr->maxLength, i)) {
        if (bufferPtr->data[i] == value) {
            returnval = value;
            for (int ii = inc(bufferPtr->maxLength, i); ii != bufferPtr->tail;
                 ii = inc(bufferPtr->maxLength, ii)) {
                bufferPtr->data[dec(bufferPtr->maxLength, ii)] =
                    bufferPtr->data[ii];
            }
            bufferPtr->tail = dec(bufferPtr->maxLength, bufferPtr->tail);
        }
    }
    return returnval;
}

/*
 * Remove the oldest element, which is at the head of the queue.
 *
 * The function should return:
 *   - 'value' if the head element was successfully removed
 *   - INT_MIN (defined in limits.h) if no element was removed (i.e., the
 *     queue was empty when the function was called.
 */
u_int32_t removeHead(struct circularBuffer* bufferPtr) {
    if (bufferPtr->head == bufferPtr->tail) {
        return INT_MIN;
    } else {
        u_int32_t temp = bufferPtr->data[bufferPtr->head];
        bufferPtr->head = inc(bufferPtr->maxLength, bufferPtr->head);
        bufferPtr->size--;
        return temp;
    }
}

u_int32_t getsize(struct circularBuffer* bufferPtr) { return bufferPtr->size; }

/*
 * Print the elements in the buffer from head to tail.
 */
void printBuffer(struct circularBuffer* bufferPtr) { printf("bkuf"); }
