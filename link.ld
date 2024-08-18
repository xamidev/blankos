ENTRY(loader)

SECTIONS {
  /* Address to load at; 2MB */

  /*. = 2M;*/

  .multiboot_header ALIGN(4K) : {
  	*(.multiboot_header)
  }
  /* Align relevant sections at 4KB  */

  .text ALIGN (4K) :
  {
    *(.text)
    *(.rodata)
  }

  .data ALIGN (4K) :
  {
    *(.data)
  }

  .bss ALIGN (4K) :
  {
    *(COMMON)
    *(.bss)
  }

  end = .; _end = .; __end = .;
}
