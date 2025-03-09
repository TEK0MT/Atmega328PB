/* LinkerScript.ld */
MEMORY {
    FLASH (rx)  : ORIGIN = 0x0000, LENGTH = 32K
    SRAM (rwx)  : ORIGIN = 0x0100, LENGTH = 2K
}

SECTIONS {
    /* Vector Table */
    .vectors : {
        KEEP(*(.vectors))
    } > FLASH

    /* Initialized Data (to be copied from Flash to RAM) */
    _sidata = LOADADDR(.data);
    .data : {
        _sdata = .;
        *(.data)
        *(.data*)
        _edata = .;
    } > RAM AT > FLASH

    /* Uninitialized Data (zeroed in RAM) */
    .bss (NOLOAD) : {
        _sbss = .;
        *(.bss)
        *(.bss*)
        _ebss = .;
    } > RAM

    /* Read-Only Data */
    .rodata : {
        *(.rodata)
        *(.rodata*)
    } > FLASH
}
