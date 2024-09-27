// Kernel heap management
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#include "kheap.h"
#include <stdint.h>
#include "system.h"
#include "../libc/stdio.h"

// Free list allocator

static uint8_t heap[HEAP_SIZE];
static block_t* free_list = NULL;

void init_alloc()
{
	free_list = (block_t*)heap;
	free_list->size = HEAP_SIZE-sizeof(block_t);
	free_list->next = NULL;
	printf("[kernel] initialized heap and allocator, start=0x%x\n", heap);
}

void* malloc(size_t size)
{
	block_t* prev = NULL;
	block_t* curr = free_list;

	while (curr != NULL)
	{
		if (curr->size >= size)
		{
			if (curr->size > (size_t)(size + sizeof(block_t)))
			{
				block_t* new_block = (block_t*)((uint8_t*)curr + sizeof(block_t) + size);
				new_block->size = curr->size - size - sizeof(block_t);
				new_block->next = curr->next;
				curr->size = size;
				curr->next = new_block;
			}

			if (prev == NULL)
			{
				free_list = curr->next;
			} else {
				prev->next = curr->next;
			}

			return (void*)((uint8_t*)curr + sizeof(block_t));
		}

		prev = curr;
		curr = curr->next;
	}

	return NULL;
}

void* calloc(size_t num, size_t size)
{
	size_t total_size = num*size;
	void* ptr = malloc(total_size);

	if (ptr != NULL)
	{
		uint8_t* byte_ptr = (uint8_t*)ptr;
		for (size_t i=0; i<total_size; i++)
		{
			byte_ptr[i] = 0;
		}
	}

	return ptr;
}

void free(void* ptr)
{
	if (ptr == NULL) return;

	block_t* block_to_free = (block_t*)((uint8_t*)ptr - sizeof(block_t));
	block_to_free->next = free_list;
	free_list = block_to_free;
}
