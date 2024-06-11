# include "FIFO.h"

FIFO_BUFFER_STATUS FIFO_init_item(FIFO_BUFFER_TYPE* Fifo_buf, element_type* buf, uint32_t length)
{
    // Check if buffer pointer is NULL
    if (buf == NULL)
        return FIFO_NULL;

    // Initialize FIFO buffer
    Fifo_buf->base = buf;
    Fifo_buf->head = buf;
    Fifo_buf->tail = buf;
    Fifo_buf->length = length;
    Fifo_buf->count = 0;

    return FIFO_no_error;
}

FIFO_BUFFER_STATUS FIFO_enqueue_item(FIFO_BUFFER_TYPE* Fifo_buf, element_type item)
{
    // Check if any buffer pointers are NULL
    if (!Fifo_buf->base || !Fifo_buf->head || !Fifo_buf->tail)
        return FIFO_NULL;

    // Check if FIFO is full
    if (FIFO_is_full(Fifo_buf) == FIFO_Full)
        return FIFO_Full;

    // Enqueue item
    *(Fifo_buf->head) = item;
    Fifo_buf->count++;

    // Update head pointer, wrap around if necessary
    if (Fifo_buf->head == (Fifo_buf->base + Fifo_buf->length))
        Fifo_buf->head = Fifo_buf->base;
    else
        Fifo_buf->head++;

    return FIFO_no_error;
}

FIFO_BUFFER_STATUS FIFO_dequeue_item(FIFO_BUFFER_TYPE* Fifo_buf, element_type* item)
{
    // Check if any buffer pointers are NULL
    if (!Fifo_buf->base || !Fifo_buf->head || !Fifo_buf->tail)
        return FIFO_NULL;

    // Check if FIFO is empty
    if (Fifo_buf->count == 0)
        return FIFO_empty;

    // Dequeue item
    *item = *(Fifo_buf->tail);
    Fifo_buf->count--;

    // Update tail pointer, wrap around if necessary
    if (Fifo_buf->tail == (Fifo_buf->base + Fifo_buf->length))
        Fifo_buf->tail = Fifo_buf->base;
    else
        Fifo_buf->tail++;

    return FIFO_no_error;
}

FIFO_BUFFER_STATUS FIFO_is_full(FIFO_BUFFER_TYPE* Fifo_buf)
{
    // Check if any buffer pointers are NULL
    if (!Fifo_buf->base || !Fifo_buf->head || !Fifo_buf->tail)
        return FIFO_NULL;

    // Check if FIFO is full
    if (Fifo_buf->count == Fifo_buf->length)
        return FIFO_Full;
    else
        return FIFO_no_error;
}

void FIFO_PRINT(FIFO_BUFFER_TYPE* Fifo_buf)
{
    element_type* temp;
    unsigned int i;

    if (Fifo_buf->count == 0)
    {
        printf("FIFO_empty\n");
    }
    else
    {
        temp = Fifo_buf->tail;
        printf("FIFO elements: ");
        for (i = 0; i < Fifo_buf->count; i++)
        {
            printf("%x ", *temp);
            temp++;
        }
        printf("\n===============================\n");
    }
}
