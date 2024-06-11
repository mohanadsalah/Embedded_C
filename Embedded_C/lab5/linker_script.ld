/* linker_script_cortexM3.ld 
ENG\ Mohanad
*/
MEMORY
{
    flash (RX) : ORIGIN = 0x08000000, LENGTH = 128k
    sram (RWX) : ORIGIN = 0x20000000, LENGTH = 20k
}

SECTIONS 
{
    /* .text section: contains code */
    .text :
    {
        *(.vectors*)
        *(.text*)
        *(.rodata*)
        _E_text = .; // Symbol for the end of the text section
    } > flash

    /* .data section: contains initialized data */
    .data :
    {
        _S_data = .; // Symbol for the start of the data section
        *(.data)
        *(.data.*)
        . = ALIGN(4); // Align to 4-byte boundary
        _E_data = .; // Symbol for the end of the data section
    } > sram AT > flash

    /* .bss section: contains uninitialized data */
    .bss :
    {
        _S_bss = .; // Symbol for the start of the BSS section
        *(.bss*)
        _E_bss = .; // Symbol for the end of the BSS section
        . = ALIGN(4); // Align to 4-byte boundary
        . += 0x1000; // Reserve additional memory
        _heap_End = .; // Symbol for the end of the heap
        . = ALIGN(4); // Align to 4-byte boundary
        . += 0x1000; // Reserve additional memory
        _stack_top = .; // Symbol for the top of the stack
    } > sram
}
