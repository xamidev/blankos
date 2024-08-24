// Kernel entry point header
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https//github.com/xamidev/blankos

#ifndef KMAIN_H
#define KMAIN_H

typedef struct {
    uint32_t type;
    uint32_t size;
    uint64_t framebuffer_addr;
    uint32_t framebuffer_pitch;
    uint32_t framebuffer_width;
    uint32_t framebuffer_height;
    uint8_t framebuffer_bpp;
    uint8_t framebuffer_type;
    uint16_t reserved;
} multiboot2_tag_framebuffer;

typedef struct {
    uint32_t total_size;
    uint32_t reserved;
    uint8_t tags[0];
} multiboot2_info;

unsigned int g_multiboot_info_address;

uint32_t* framebuffer;
int scanline;

// in characters, not pixels
uint32_t VGA_WIDTH;
uint32_t VGA_HEIGHT;

#endif