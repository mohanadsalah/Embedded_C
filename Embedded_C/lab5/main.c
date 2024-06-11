// Define a type for volatile unsigned 32-bit integers
typedef volatile unsigned int vuint32_t;

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

// Memory addresses for RCC (Reset and Clock Control) and GPIOA (General Purpose I/O port A)
#define RCC_BASE        0x40021000
#define GPIOA_BASE      0x40010800

// RCC_APB2ENR register controls the I/O port A clock
#define RCC_APB2ENR     *((volatile uint32_t *)(RCC_BASE + 0X18))
// GPIOA_CRH register controls the configuration of port A pins
#define GPIOA_CRH       *((volatile uint32_t *)(GPIOA_BASE + 0X04))
// GPIOA_ODR register controls the output data of port A pins
#define GPIOA_ODR       *((volatile uint32_t *)(GPIOA_BASE + 0X0C))

// Bitmask for enabling I/O port A clock in RCC_APB2ENR register
#define RCC_IOPAEN      (1 << 2)
// Bitmask for pin 13 of GPIOA
#define GPIOA13         (1UL << 13)

// Define a union to access individual fields of GPIOA_ODR register
typedef union {
    vuint32_t all_fields;
    struct {
        vuint32_t reversed : 13; // Unused bits
        vuint32_t P_13 : 1;      // Bit representing pin 13 of GPIOA
    } pin;
} R_ODR_T;

// Pointer to GPIOA_ODR register with structured access
volatile R_ODR_T* R_ODR = (volatile R_ODR_T*)(GPIOA_BASE + 0X0C);

// Global array of unsigned char variables
unsigned char g_variables[3] = {1, 2, 3};
// Constant array of unsigned char variables
unsigned char const const_variables[3] = {1, 2, 3};
// Volatile array of unsigned char variables
volatile unsigned char bss_var[3];

// Symbols defined by the linker for memory management
extern unsigned int _E_bss; // End of BSS segment
extern unsigned int _heap_End; // End of heap segment

// Function prototype for _sbrk
void* _sbrk(int incr);

// Main function
int main(void) {
    // Allocate memory for an integer pointer and free it immediately
    int *ptr = (int*) malloc(4);
    free(ptr);   
    
    // Enable clock for I/O port A
    RCC_APB2ENR |= RCC_IOPAEN;
    // Configure pin 13 of port A as output
    GPIOA_CRH &= 0Xff0fffff;
    GPIOA_CRH |= 0x00200000;
    
    // Infinite loop for toggling pin 13
    while(1) {
        // Set pin 13 of port A high
        R_ODR->pin.P_13 = 1;
        // Delay
        for(int i = 0; i < 5000; i++);
        // Clear pin 13 of port A
        R_ODR->pin.P_13 = 0;
        // Delay
        for(int i = 0; i < 5000; i++);
    }
    
    return 0;
}

// Function to manage heap memory allocation
void* _sbrk(int incr) {
    // Static variable to keep track of the heap pointer
    static unsigned char* heap_ptr = NULL;
    // Variable to store the previous heap pointer
    unsigned char* prev_heap_ptr = NULL;

    // Initialize heap pointer if it's NULL
    if (heap_ptr == NULL)
        heap_ptr = (unsigned char*)&_E_bss;

    // Save the current heap pointer
    prev_heap_ptr = heap_ptr;

    // Check if requested memory exceeds the end of heap
    if ((heap_ptr + incr) > ((unsigned char*)&_heap_End))
        return (void*)NULL;

    // Update the heap pointer
    heap_ptr += incr;

    // Return the previous heap pointer
    return (void*)prev_heap_ptr;
}
