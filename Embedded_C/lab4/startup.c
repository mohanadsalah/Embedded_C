/* startup.c - ENG.Mohanad */
#include <stdint.h>

/* Extern declaration of main function */
extern int main(void);

// Booking 1024 bytes located by .bss through uninitialized array of long 256 elements (256*4) = 1024 bytes
static unsigned long stack_top[256];

/* Function prototypes for exception handlers */
void Reset_Handler(void);
void Default_Handler(void);

void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((weak, alias("Default_Handler")));

/* Vector table */
void (*const g_p_fn_Vectors[])() __attribute__((section(".vectors"))) = {
    (void (*)())((unsigned long)stack_top + sizeof(stack_top)), /* Stack Pointer */
    &Reset_Handler,         /* Reset Handler */
    &NMI_Handler,           /* NMI Handler */
    &HardFault_Handler      /* Hard Fault Handler */
};

extern unsigned int _E_text;
extern unsigned int _S_data;
extern unsigned int _E_data;
extern unsigned int _S_bss;
extern unsigned int _E_bss;

/* Function definitions for exception handlers */

void Reset_Handler(void) {
    /* Copy data section from flash to SRAM */
    unsigned int DATA_size = (unsigned char *)&_E_data - (unsigned char *)&_S_data;
    unsigned char *P_src = (unsigned char *)&_E_text;
    unsigned char *P_dst = (unsigned char *)&_S_data;

    int i; // Declare 'i' outside of the loop to adhere to C90 standard
    for (i = 0; i < DATA_size; i++) {
        *P_dst++ = *P_src++;
    }

    /* Initialize .bss section in SRAM = 0 */
    unsigned int bss_size = (unsigned char *)&_E_bss - (unsigned char *)&_S_bss;
    P_dst = (unsigned char *)&_S_bss;
    for (i = 0; i < bss_size; i++) {
        *P_dst++ = (unsigned char)0;
    }

    /* Call main function */
    main();
}

void Default_Handler(void) {
    Reset_Handler();
}
