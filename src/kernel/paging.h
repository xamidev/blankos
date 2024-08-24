// Paging kernel module header
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#ifndef PAGING_H
#define PAGING_H

#include "system.h"
#include <stdint.h>

#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a%(8*4))

typedef struct
{
	uint32_t present	: 1;
	uint32_t rw			: 1;
	uint32_t user		: 1;
	uint32_t accessed	: 1;
	uint32_t dirty		: 1;
	uint32_t unused		: 7;
	uint32_t frame		: 20;
} page_t;

typedef struct
{
	page_t pages[1024];
} page_table_t;

typedef struct
{
	page_table_t *tables[1024];
	uint32_t tablesPhysical[1024];
	uint32_t physicalAsddr;
} page_directory_t;

void init_paging();
void switch_page_directory(page_directory_t *new);
page_t *get_page(uint32_t address, int make, page_directory_t *dir);
void page_fault();

#endif
