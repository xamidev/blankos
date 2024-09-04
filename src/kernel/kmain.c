// Kernel entry point
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#include "../libc/stdio.h"
#include "../drivers/serial.h"
#include "gdt.h"
#include "idt.h"
#include "system.h"
#include "../drivers/ata.h"
#include <stdint.h>
#include "../drivers/framebuffer.h"
#include "kmain.h"
#include "multiboot2.h"
#include "kheap.h"

void kmain(multiboot2_info *mb_info)
{
	multiboot2_tag_framebuffer *fb_info = NULL;
	struct multiboot_tag_mmap *mmap_tag = NULL;

    uint8_t *tags = mb_info->tags;
    while (1) {
        uint32_t tag_type = *((uint32_t*) tags);
        uint32_t tag_size = *((uint32_t*) (tags + 4));

        if (tag_type == 0) break;
        if (tag_type == MULTIBOOT_TAG_TYPE_FRAMEBUFFER) {
            fb_info = (multiboot2_tag_framebuffer*) tags;
        }
	if (tag_type == MULTIBOOT_TAG_TYPE_MMAP) {
		mmap_tag = (struct multiboot_tag_mmap*) tags;
	}

        tags += ((tag_size + 7) & ~7);
    }

    serial_printf(3, "Framebuffer Address: 0x%x", fb_info->framebuffer_addr);
	serial_printf(3, "Framebuffer Width: %u", fb_info->framebuffer_width);
	serial_printf(3, "Framebuffer Height: %u", fb_info->framebuffer_height);
	serial_printf(3, "Framebuffer Pitch: %u", fb_info->framebuffer_pitch);
	serial_printf(3, "Framebuffer BPP: %u", fb_info->framebuffer_bpp);

    if (fb_info) {
        framebuffer = (uint32_t *)(uintptr_t) fb_info->framebuffer_addr;

        uint32_t width = fb_info->framebuffer_width;
        uint32_t height = fb_info->framebuffer_height;
        uint32_t bpp = fb_info->framebuffer_bpp;

        //8x16 font, not padded 
        VGA_WIDTH = width/8;
        VGA_HEIGHT = height/16;
        serial_printf(3, "VGA_WIDTH=%d, VGA_HEIGHT=%d", VGA_WIDTH, VGA_HEIGHT);
        scanline = width * (bpp/8);	
    }

    printf("[kernel] multiboot2 info at 0x%x, size=%u\n", mb_info, mb_info->total_size);
    printf("[kernel] framebuffer discovered at 0x%x\n", fb_info->framebuffer_addr);
    printf("[kernel] fb0: width=%u, height=%u, pitch=%u, bpp=%u\n", fb_info->framebuffer_width, fb_info->framebuffer_height, fb_info->framebuffer_pitch, fb_info->framebuffer_bpp);

    if (mmap_tag)
    {
	printf("[kernel] found memory map tag by multiboot2\n");
	struct multiboot_mmap_entry *mmap = mmap_tag->entries;

	while ((uint8_t*) mmap < tags + mmap_tag->size)
	{
		
		if (mmap->addr != 0)
		{
			/*
			printf("[debug] base addr=0x%x%x, length=0x%x%x, type=%u\n",
				(uint32_t) (mmap->addr >> 32),
				(uint32_t) (mmap->addr & 0xFFFFFFFF),
				(uint32_t) (mmap->len >> 32),
				(uint32_t) (mmap->len & 0xFFFFFFFF),
				mmap->type);
			*/
		}

		mmap = (struct multiboot_mmap_entry*) ((uint8_t*)mmap + mmap_tag->entry_size);
	}
    }

    init_serial();
    gdt_install();
    idt_install();
    isr_install();
    irq_install();
    __asm__ __volatile__("sti");

    init_alloc();
    void* ptr1 = malloc(256);
    void* ptr2 = malloc(512);
    free(ptr2); 

    timer_install();
    keyboard_install();
    printf("[kernel] spawning shell...\n"); 
    shell_install();
}
