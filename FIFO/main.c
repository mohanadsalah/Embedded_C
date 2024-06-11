#include "FIFO.h"
#include <stdio.h>

int main()
{
    element_type i, temp;
    FIFO_BUFFER_TYPE FIFO_UART;

    // Initialize FIFO buffer
    if (FIFO_init_item(&FIFO_UART, UART_buffer, 5) == FIFO_no_error)
        printf("Fifo init is done\n");

    // Enqueue elements into FIFO buffer
    for (i = 0; i < 7; i++)
    {
        printf("FIFO Enqueue(%x)\n", i);
        if (FIFO_enqueue_item(&FIFO_UART, i) == FIFO_no_error)
            printf("\tFifo Enqueue %x is done\n", i);
        else
            printf("\tFifo Enqueue %x is failed\n", i);
    }
    FIFO_PRINT(&FIFO_UART);
    for (i = 0; i < 3; i++)
    {
        printf("FIFO Dequeue\n");
        if (FIFO_dequeue_item(&FIFO_UART, &temp) == FIFO_no_error)
            printf("\tFifo dequeue %x is done\n", temp);
        else
            printf("\tFifo dequeue is failed\n");
    }
    FIFO_PRINT(&FIFO_UART);
    printf("FIFO Dequeue\n");
    if (FIFO_dequeue_item(&FIFO_UART, &temp) == FIFO_no_error)
        printf("\tFifo Dequeue %x is done\n", temp);
    else
        printf("\tFifo Dequeue is failed\n");

    printf("FIFO Dequeue\n");
    if (FIFO_dequeue_item(&FIFO_UART, &temp) == FIFO_no_error)
        printf("\tFifo Dequeue %x is done\n", temp);
    else
        printf("\tFifo Dequeue is failed\n");

    FIFO_PRINT(&FIFO_UART);
    return 0;
}
