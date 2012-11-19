MEMORY {    /* memory map of LPC2148 */
    ROM (rx)  : ORIGIN = 0x00000000, LENGTH = 512k
    RAM (rwx) : ORIGIN = 0x40000000, LENGTH = 32k
}
IRQ_STACK_SIZE = 0;
FIQ_STACK_SIZE = 0;
SVC_STACK_SIZE = 0;
ABT_STACK_SIZE = 0;
UND_STACK_SIZE = 0;
SECTIONS {
        . = 0x00000000;
        .text : {
              * (vectors);
              * (.text);
              . = ALIGN(4);
        }
        .rodata : {
              * (.rodata);
              *(.rodata*)      /* all .rodata* sections (constants, strings, etc.)              */
	      *(.glue_7)       /* all .glue_7 sections  (no idea what these are)                */
	      *(.glue_7t) 
	      *(.eh_frame)
	      . = ALIGN(4);
        }
        flash_sdata = .;

        . = 0x40000000;
        ram_sdata = .;
        .data : AT (flash_sdata) {
              * (.data);
              . = ALIGN(4);
        }
        ram_edata = .;
        data_size = ram_edata - ram_sdata;

        sbss = .;
        .bss : {
             * (.bss);
             . = ALIGN(4);
        }
        ebss = .;
        bss_size = ebss - sbss;
            _end = . ;
    __end = . ;
	 PROVIDE(end = .);
         heap_low = .; /* for _sbrk */
	 . = . + 0x100; /* 64kB of heap memory */
	 heap_top = .; /* for _sbrk */
}