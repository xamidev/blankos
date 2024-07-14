ENTRY(loader)

SECTIONS {
  /* Address to load at; 1MB */

  . = 0x00100000;

  .__mbHeader : {
	  *(.__mbHeader)
  }

  /* Align relevant sections at 4KB  */

  .text ALIGN (0x1000) :
  {
    *(.text)
    *(.rodata)
  }

  .data ALIGN (0x1000) :
  {
    *(.data)
  }

  .bss ALIGN (0x1000) :
  {
    *(COMMON)
    *(.bss)
  }
}
