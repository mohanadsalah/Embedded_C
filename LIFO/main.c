#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "LIFO.h"
#include "LIFO.c" // Including source files directly is generally not recommended

unsigned int buffer1[5]; // 5*4=20 bytes in data memory in uart_lifo

int main() {
    unsigned int i , temp=0;
    LIFO_BUF_t uart_lifo, I2C_lifo;

    // Static allocation
    LIFO_init_item(&uart_lifo, buffer1, 5);

    // Dynamic allocation
    unsigned int *buffer2 = (unsigned int*) malloc(5 * sizeof(unsigned int)); // 5*4=20 bytes in heap in I2C_lifo
    LIFO_init_item(&I2C_lifo, buffer2, 5);

    // Add items to uart_lifo
    for(i = 0; i < 5; i++) {
        if (LIFO_Add_item(&uart_lifo, i) == LIFO_no_error)
            printf("UART_LIFO add : %d \n", i);
    }

    // Retrieve items from uart_lifo
    for(i = 0; i < 5; i++) {
        if (LIFO_get_item(&uart_lifo, &temp) == LIFO_no_error)
            printf("UART_LIFO get : %d \n", temp);
    }

    return 0;
}
