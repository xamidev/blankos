// uhex (microhex) port for BlankOS; read-only version
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

// This version is the port of a hex viewer which already was not great,
// and now by being here it is even worse because it is RO and will have
// hardcoded stuff in it (no ioctl, STDOUT, or other stuff here...)

#define BYTES 1024
#define round(x) (int)(x < 0 ? (x -0.5) : x + 0.5)

#include "../libc/stdio.h"
#include "../kernel/kmain.h"
#include "../kernel/initrd.h"
#include "../libc/string.h"
#include "../kernel/kheap.h"

int isprint(int c)
{
	return (c >= 32 && c <= 126);
}

void print_hex(unsigned char* buf, int byteno, int pos, int BYTES_PER_LINE)
{
	for (int i=0; i<byteno; i++)
	{
		if (i%BYTES_PER_LINE == 0)
		{
			if (i != 0)
			{
				printf(" ");
				for (int j=i-BYTES_PER_LINE; j<i; j++)
				{
					if (isprint(buf[j])) colorprintf(salmon, black, "%c", buf[j]);
					else printf(".");
				}
			}
			puts("\n");

			if (pos == 0) printf("%06d:   ", i);
			else printf("%06d:   ", pos);
		}
	printf("%2x ", buf[i]);
	}

	int padding = BYTES_PER_LINE - (byteno % BYTES_PER_LINE);
	if (padding < BYTES_PER_LINE)
	{
		for (int i=0; i<padding; i++) printf("   ");
		printf("  ");
	}
	int start = byteno-(byteno%BYTES_PER_LINE);
	for (int j=start; j<byteno; j++)
	{
		if (isprint(buf[j])) {
			colorprintf(salmon, black, "%c", buf[j]);
		} else {
			printf(".");
		}
	}
	puts("\n");
}

void program_uhex(int argc, char* argv[])
{
	if (argc < 2)
	{
		puts("Usage: uhex <file>\n");
		return;
	}

	int BYTES_PER_LINE = 20;
	
	//unsigned char buf[BYTES]; // malloc with file_size next?
	uint32_t file_size = tar_get_file_size((uint8_t*)initrd_addr, argv[1]);
	unsigned char* buf = (unsigned char*)malloc(file_size);
	tar_file_to_buffer((uint8_t*)initrd_addr, argv[1], (char*)buf);
	print_hex(buf, file_size, 0, BYTES_PER_LINE);

	free(buf);
}
