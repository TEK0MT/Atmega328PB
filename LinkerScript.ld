/* Linker script for ATmega328PB */

/* Define memory regions:
   - FLASH: Program memory (read/execute). Adjust LENGTH if needed.
   - SRAM: Data memory (read/write). Datasheet shows SRAM starting at 0x0100.
*/
MEMORY
{
  FLASH (rx) : ORIGIN = 0x0000, LENGTH = 32K
  SRAM  (rwx): ORIGIN = 0x800100, LENGTH = 2K
}


/* Define the sections */
SECTIONS
{
  /* .text section:
     Place vector table, startup routines, code and read-only data in FLASH.
  */
  .text :
  {
    *(.vectors)      /* Interrupt vectors */
    *(.init)         /* Initialization code */
    *(.text)         /* Program code */
    *(.text.*)
    *(.rodata)       /* Read-only data */
    *(.rodata.*)
  } > FLASH

  /* .data section:
     Although this section is allocated in SRAM (for run-time),
     its initial load image is stored in FLASH.
  */
  _sidata = LOADADDR(.data);
.data :
{
    _sdata = .;
    *(.data)
    _edata = .;
} > SRAM AT> FLASH


  /* .bss section:
     Uninitialized data is allocated in SRAM.
  */
  .bss :
  {
    _sbss = .;       /* Start symbol for .bss */
    *(.bss)
    *(COMMON)
    _ebss = .;       /* End symbol for .bss */
  } > SRAM

  /* .stack section (optional):
     This example defines a NOLOAD section for the stack.
     Here the stack is defined between _stack_bottom and _stack_top.
     Adjust the addresses as needed for your application.
  */
  .stack (NOLOAD) :
  {
    _stack_top = 0x08FF;      /* Typically, the top of SRAM */
    _stack_bottom = _ebss + 1;  /* Stack starts just after .bss */
  } > SRAM
  /* Provide symbols required by libgcc startup code */
__data_load_start = _sidata;
__data_start      = _sdata;
__data_end        = _edata;
__bss_start       = _sbss;
__bss_end         = _ebss;

}
