#ifndef _FIFO_H_
#define _FIFO_H_

#include "stdio.h"
#include "stdint.h"

// User configuration
// Select element_type (element width) [uint8_t , uint16_t , uint32_t , ...]
#define element_type uint8_t

// Create buffer
#define width 5
element_type UART_buffer[width];

// FIFO data types
typedef struct {
    unsigned int length;    // Length of the FIFO buffer
    unsigned int count;     // Number of elements currently in the FIFO buffer
    element_type *base;     // Pointer to the base of the FIFO buffer
    element_type *head;     // Pointer to the head of the FIFO buffer
    element_type *tail;     // Pointer to the tail of the FIFO buffer
} FIFO_BUFFER_TYPE;

typedef enum {
    FIFO_no_error,   // No error occurred
    FIFO_Full,       // FIFO buffer is full
    FIFO_empty,      // FIFO buffer is empty
    FIFO_NULL        // NULL pointer encountered
} FIFO_BUFFER_STATUS;

// FIFO APIs
FIFO_BUFFER_STATUS FIFO_init_item(FIFO_BUFFER_TYPE* Fifo_buf, element_type* buf, uint32_t length);
FIFO_BUFFER_STATUS FIFO_enqueue_item(FIFO_BUFFER_TYPE* Fifo_buf, element_type item);
FIFO_BUFFER_STATUS FIFO_dequeue_item(FIFO_BUFFER_TYPE* Fifo_buf, element_type* item);
FIFO_BUFFER_STATUS FIFO_is_full(FIFO_BUFFER_TYPE* Fifo_buf);
void FIFO_PRINT(FIFO_BUFFER_TYPE* Fifo_buf);

#endif // _FIFO_H_
