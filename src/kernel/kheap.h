// Kernel heap management header
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#ifndef KHEAP_H
#define KHEAP_H

#include <stdint.h>
#include "system.h"

typedef struct block
{
	size_t size;
	struct block* next;
} block_t;

#define HEAP_SIZE 1024*1024	// 1MB malloc-able

void init_alloc();
void* malloc(size_t size);
void free(void* ptr);
void* calloc(size_t num, size_t size);

#endif
