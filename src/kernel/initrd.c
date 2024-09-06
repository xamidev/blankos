// Initial TAR ramdisk kernel module 
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#include "../libc/stdio.h"
#include <stdint.h>
#include "../libc/string.h"
#include "initrd.h"
#include "system.h"

static unsigned int octal_to_int(const char* str, size_t size)
{
	unsigned int result = 0;
	while (*str && size-- > 0)
	{
		result = (result << 3) | (*str - '0');
		str++;
	}
	return result;
}

uint32_t tar_parse_size(const char* in)
{
	uint32_t size = 0;
	while (*in >= '0' && *in <= '7')
	{
		size = (size*8) + (*in - '0');
		in++;
	}
	return size;
}

void tar_find_file(uint8_t *tar_start, const char* filename)
{
	uint8_t *ptr = tar_start;

	while (1)
	{
		tar_header_t *header = (tar_header_t*)ptr;

		if (header->filename[0] == '\0')
		{
			puts("[tar] EOF\n");
			break;
		}

		unsigned int filesize = octal_to_int(header->size, 11);

		if (strcmp(header->filename, filename) == 0)
		{
			printf("[tar] found file '%s', size=%u bytes\n", header->filename, filesize);

			uint8_t *file_data = ptr+TAR_BLOCK_SIZE;
			printf("[tar] content of '%s':\n", filename);
			for (unsigned int i=0; i<filesize; i++)
			{
				putc(file_data[i]);
			}
			puts("\n");
			return;
		}

		ptr += TAR_BLOCK_SIZE + ((filesize + TAR_BLOCK_SIZE-1) / TAR_BLOCK_SIZE) * TAR_BLOCK_SIZE;
	}

	printf("[tar] file '%s' not found\n", filename);
}

void ls_initrd(uint8_t* initrd, int verbose)
{
	tar_header_t *header = (tar_header_t*)initrd;
	
	if (verbose)
	{
		puts("Size       Type  Filename\n");
	}

	while (header->filename[0] != '\0')
	{
		if (!verbose)
		{
			printf("%s\n", header->filename);
		} else {
			printf("%7d\t%c\t %s\n", header->size, header->typeflag, header->filename);
		}

		uint32_t size = tar_parse_size(header->size);
		uint32_t next_file_offset = ((size+TAR_BLOCK_SIZE-1)/TAR_BLOCK_SIZE)*TAR_BLOCK_SIZE;
		header = (tar_header_t*)((uint8_t*)header + next_file_offset + TAR_BLOCK_SIZE);
	}
}

void cat_initrd(uint8_t* initrd, const char* filename)
{
	tar_header_t *header = (tar_header_t*)initrd;

	while (header->filename[0] != '\0')
	{
		if (strcmp(header->filename, filename) == 0)
		{
			uint32_t size = tar_parse_size(header->size);
			uint8_t* file_content = (uint8_t*)header + 512;

			for (uint32_t i=0; i<size; i++) putc(file_content[i]);
			return;
		}

		uint32_t next_file_offset = ((tar_parse_size(header->size)+TAR_BLOCK_SIZE-1)/TAR_BLOCK_SIZE)*TAR_BLOCK_SIZE;
		header = (tar_header_t*)((uint8_t*)header + next_file_offset + TAR_BLOCK_SIZE);
	}

	printf("File '%s' not found\n", filename);
}

int tar_file_to_buffer(uint8_t* initrd, const char* filename, char* buffer)
{
	uint8_t* current_block = initrd;

	while (1)
	{
		if (current_block[0] == '\0')
		{
			//puts("[tar] EOF\n");
			return -1;
		}

		const char* file_name = (const char*)current_block;
		uint32_t file_size = tar_parse_size((const char*)(current_block+124));

		if (strcmp(file_name, filename) == 0)
		{
			uint8_t* file_data = current_block + TAR_BLOCK_SIZE;
			memcpy(buffer, file_data, file_size);
			buffer[file_size] = '\0';
			return 0;
		}

		uint32_t total_size = ((file_size + TAR_BLOCK_SIZE - 1) / TAR_BLOCK_SIZE) * TAR_BLOCK_SIZE;
		current_block += TAR_BLOCK_SIZE + total_size;
	}
	printf("[tar] file '%s' not found\n", filename);
	return -1;
}
