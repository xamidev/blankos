// Kernel entry point
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#include "../libc/stdio.h"
#include "../drivers/serial.h"
#include "gdt.h"
#include "idt.h"
#include "system.h"
#include "paging.h"
#include "../drivers/ata.h"
#include <stdint.h>
#include "../drivers/framebuffer.h"
#include "kmain.h"

void kmain(multiboot2_info *mb_info)
{
	multiboot2_tag_framebuffer *fb_info = NULL;

    uint8_t *tags = mb_info->tags;
    while (1) {
        uint32_t tag_type = *((uint32_t*) tags);
        uint32_t tag_size = *((uint32_t*) (tags + 4));

        if (tag_type == 0) break;
        if (tag_type == 8) {
            fb_info = (multiboot2_tag_framebuffer*) tags;
        }

        tags += ((tag_size + 7) & ~7);
    }

    serial_printf(3, "Framebuffer Address: 0x%x\r", fb_info->framebuffer_addr);
	serial_printf(3, "Framebuffer Width: %u\r\n", fb_info->framebuffer_width);
	serial_printf(3, "Framebuffer Height: %u\r\n", fb_info->framebuffer_height);
	serial_printf(3, "Framebuffer Pitch: %u\r\n", fb_info->framebuffer_pitch);
	serial_printf(3, "Framebuffer BPP: %u\r\n", fb_info->framebuffer_bpp);

    if (fb_info) {
        framebuffer = (uint32_t *)(uintptr_t) fb_info->framebuffer_addr;

        uint32_t width = fb_info->framebuffer_width;
        uint32_t height = fb_info->framebuffer_height;
        uint32_t bpp = fb_info->framebuffer_bpp;

        //8x16 font, not padded 
        VGA_WIDTH = width/8;
        VGA_HEIGHT = height/16;
        scanline = width * (bpp/8);	
    }

    printf("[kernel] multiboot2 info at 0x%x, size=%u\n", mb_info, mb_info->total_size);
    printf("[kernel] framebuffer discovered at 0x%x\n", fb_info->framebuffer_addr);
    printf("[kernel] fb0: width=%u, height=%u, pitch=%u, bpp=%u\n", fb_info->framebuffer_width, fb_info->framebuffer_height, fb_info->framebuffer_pitch, fb_info->framebuffer_bpp);

    init_serial();
    gdt_install();
    idt_install();
    isr_install();
    irq_install();
    __asm__ __volatile__("sti");
 
    //init_paging();
    //test_read_sector();
    //uint32_t *ptr = (uint32_t*)0xA0000000;
    //uint32_t do_page_fault = *ptr;

    timer_install();
    keyboard_install();
    printf("[kernel] spawning shell...\n"); 
    shell_install();
}
