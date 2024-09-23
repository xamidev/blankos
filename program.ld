OUTPUT_FORMAT(binary)
ENTRY(main)

SECTIONS
{
	. = 0x1000;
	.text : { *(.text*) }
	.data : { *(.data*) }
	.bss : { *(.bss*) }
}
