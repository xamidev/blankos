// Filesystem utilities (for initrd)
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#include "../kernel/initrd.h"
#include "../kernel/kmain.h"
#include "../libc/stdio.h"
#include "../libc/string.h"

void program_ls(int argc, char* argv[])
{
	if (argc == 1)
	{
		ls_initrd((uint8_t*)initrd_addr, 0);
	} else if (argc == 2 && strcmp(argv[1], "-l") == 0) {
		ls_initrd((uint8_t*)initrd_addr, 1);
	}
}

// Basic cat just to read, no concatenation here
void program_cat(int argc, char* argv[]) 
{
	if (argc != 2)
	{
		puts("Usage: cat <file>\n");
		return;
	}
	cat_initrd((uint8_t*)initrd_addr, argv[1]);
}
