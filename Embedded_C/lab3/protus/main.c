#include <stdint.h>

#define RCC_BASE       0x40021000
#define PORTA_BASE     0x40010800

#define RCC_APB2ENR    (*((volatile uint32_t *)(RCC_BASE + 0x18)))
#define GPIOA_CRH      (*((volatile uint32_t *)(PORTA_BASE + 0x04)))
#define GPIOA_ODR      (*((volatile uint32_t *)(PORTA_BASE + 0x0C)))

extern void NMI_Handler(void);
extern void H_fault_Handler(void);

int main(void) {
    RCC_APB2ENR |= 1 << 2;
    GPIOA_CRH &= 0xff0fffff;
    GPIOA_CRH |= 0x00200000;

    volatile int i;  // Declare loop counter outside the loop

    while (1) {
        GPIOA_ODR |= 1 << 13;   //set bit 13
        for (i = 0; i < 5000; i++);  // Initialize loop counter here
        GPIOA_ODR &= ~(1 << 13);  //reset bit 13
        for (i = 0; i < 5000; i++);  // Reuse loop counter here
    }
    return 0;
}
