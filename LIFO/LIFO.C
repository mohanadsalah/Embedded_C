#include "LIFO.h"

// APIs

// Function to add an item to the LIFO buffer
LIFO_Status LIFO_Add_item(LIFO_BUF_t* lifo_buf, unsigned int item)
{
    // Check if lifo buffer is valid
    if (!lifo_buf->base || !lifo_buf->head)
        return LIFO_NULL;

    // Check if lifo is full
    if (lifo_buf->count == lifo_buf->length)
        return LIFO_Full;

    // Add value to the lifo buffer
    *(lifo_buf->head) = item;
    lifo_buf->head++;
    lifo_buf->count++;

    return LIFO_no_error;
}

// Function to get an item from the LIFO buffer
LIFO_Status LIFO_get_item(LIFO_BUF_t* lifo_buf, unsigned int* item)
{
    // Check if lifo buffer is valid
    if (!lifo_buf->base || !lifo_buf->head)
        return LIFO_NULL;

    // Check if lifo is empty
    if (lifo_buf->count == 0)
        return LIFO_empty;

    // Retrieve value from the lifo buffer
    lifo_buf->head--;
    *item = *(lifo_buf->head);
    lifo_buf->count--;

    return LIFO_no_error;
}

// Function to initialize the LIFO buffer
LIFO_Status LIFO_init_item(LIFO_BUF_t* lifo_buf, unsigned int* buf, unsigned int length)
{
    // Check if buffer is NULL
    if (buf == 0)
        return LIFO_NULL;

    // Initialize lifo buffer properties
    lifo_buf->base = buf;
    lifo_buf->head = buf;
    lifo_buf->length = length;
    lifo_buf->count = 0;

    return LIFO_no_error;
}
