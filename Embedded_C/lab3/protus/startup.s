/* startup_cortexM3.s 
ENG\ Mohanad
*/
/* SRAM 0x20000000 */
.section .vectors
.word 0x20001000              /* stack top address */
.word _reset                  /* 1 Reset */
.word Vector_handler         /* 2 NMI */
.word Vector_handler         /* 3 HARD FAULT */
.word Vector_handler         /* 4 MM FAULT */
.word Vector_handler         /* 5 Bus FAULT */
.word Vector_handler         /* 6 Usage FAULT */
.word Vector_handler         /* 7 Reversed */
.word Vector_handler         /* 8 Reversed */
.word Vector_handler         /* 9 Reversed */
.word Vector_handler         /* 10 Reversed */
.word Vector_handler         /* 11 SV call */
.word Vector_handler         /* 12 Debug Reversed */
.word Vector_handler         /* 13 Reversed */
.word Vector_handler         /* 14 Pend SV */
.word Vector_handler         /* 15 Systick */
.word Vector_handler         /* 16 IRQ0 */
.word Vector_handler         /* 17 IRQ1 */
.word Vector_handler         /* 18 IRQ2 */
.word Vector_handler         /* 19 IRQ3 */
/* ... */
                     /* On to IRQ67 */
.section .text
_reset:
    bl main
    b .
.thumb_func
Vector_handler:
    b _reset
