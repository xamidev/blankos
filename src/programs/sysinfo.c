// System information program
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https//github.com/xamidev/blankos

#include "../kernel/sysinfo.h"
#include "../libc/stdio.h"
#include "../kernel/system.h"
#include "../libc/string.h"

extern unsigned int multiboot_info_address;

typedef struct multiboot_memory_map
{
	unsigned int size;
	unsigned int base_addr_low;
	unsigned int base_addr_high;
	unsigned int length_low;
	unsigned int length_high;
	unsigned int type;
} multiboot_memory_map_t;

void get_cpuid()
{
	// CPUid

	unsigned int eax, edx;
	char vendor[13];
	unsigned int* v = (unsigned int*)vendor;

	asm volatile("cpuid"
			: "=b"(v[0]), "=d"(v[1]), "=c"(v[2])
			: "a"(0));
	vendor[12] = '\0';

	cpuid(1, &eax, &edx);
	unsigned int model = (eax >> 4) & 0xF;
	unsigned int family = (eax >> 8) & 0xF;

	printf("CPU information\n\tvendor:   %s\n\tfamily:   %u\n\tmodel:    %u\n\tfeatures: 0x%x\n", vendor, family, model, edx);
}

void get_meminfo(unsigned int multiboot_info_address, int verbose)
{
	// RAM
	
	unsigned int mem_lower = *((unsigned int*)(multiboot_info_address + 4));
	unsigned int mem_upper = *((unsigned int*)(multiboot_info_address + 8));

	printf("RAM information\n\tLower memory: %u KB\n\tUpper memory: %u KB\n", mem_lower, mem_upper);

	if (verbose)
	{
		multiboot_memory_map_t* mmap = (multiboot_memory_map_t*)*((unsigned int*)(multiboot_info_address + 44));
		printf("Memory map:\nBase addr          | Length             | Type\n----------------------------------------------------\n");

		while ((unsigned int)mmap < multiboot_info_address + *((unsigned int*)(multiboot_info_address + 40)))
		{
			if (mmap->length_high != 0 && mmap->length_low != 0)
			{
				printf("0x%x%x | 0x%x%x | %u\n",
					mmap->base_addr_high, mmap->base_addr_low,
					mmap->length_high, mmap->length_low,
					mmap->type);
			}
			mmap = (multiboot_memory_map_t*)((unsigned int)mmap + mmap->size + sizeof(unsigned int));
		}
	}
}

void program_sysinfo(int argc, char* argv[])
{
	if (argc == 1)
	{
		get_cpuid();
		get_meminfo(g_multiboot_info_address, 0);
	} else if (argc == 2 && strcmp(argv[1], "-v") == 0)
	{	
		get_cpuid();
		get_meminfo(g_multiboot_info_address, 1);
	}
}
