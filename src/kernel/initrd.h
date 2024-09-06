// Initial TAR ramdisk kernel module header 
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#ifndef INITRD_H
#define INITRD_H

#define TAR_BLOCK_SIZE 512

#include "system.h"

typedef struct
{
	char filename[100];
	char mode[8];
	char owner[8];
	char group[8];
	char size[12];
	char mtime[12];
	char checksum[8];
	char typeflag;
	char linkname[100];
	char magic[6];
	char version[2];
	char uname[32];
	char gname[32];
	char devmajor[8];
	char devminor[8];
	char prefix[155];
} tar_header_t;

void tar_find_file(uint8_t *tar_start, const char* filename);
void ls_initrd(uint8_t* initrd, int verbose);
void cat_initrd(uint8_t* initrd, const char* filename);
int tar_file_to_buffer(uint8_t* initrd, const char* filename, char* buffer);

#endif
