#include "../libc/stdio.h"
#include "../drivers/serial.h"
#include "gdt.h"
#include "idt.h"
#include "system.h"
#include "paging.h"
#include "../drivers/ata.h"
#include "../libc/stdint.h" 
#include "../drivers/framebuffer.h"

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

char* ascii_title =
"\n"
"*******************************\n"
"| Blank OS version 0.3.68-dev |\n"
"*******************************\n"
"\n";

unsigned int g_multiboot_info_address;

uint32_t* framebuffer;
int scanline;

// in characters, not pixels
uint32_t VGA_WIDTH;
uint32_t VGA_HEIGHT;


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

    serial_printf(3, "Framebuffer Address: 0x%x\r\n", fb_info->framebuffer_addr);
serial_printf(3, "Framebuffer Width: %u\r\n", fb_info->framebuffer_width);
serial_printf(3, "Framebuffer Height: %u\r\n", fb_info->framebuffer_height);
serial_printf(3, "Framebuffer Pitch: %u\r\n", fb_info->framebuffer_pitch);
serial_printf(3, "Framebuffer BPP: %u\r\n", fb_info->framebuffer_bpp);


    if (fb_info) {
	log("Entered fb_info\r\n", 3);
        framebuffer = (uint32_t *)(uintptr_t) fb_info->framebuffer_addr;

        uint32_t width = fb_info->framebuffer_width;
        uint32_t height = fb_info->framebuffer_height;
        uint32_t pitch = fb_info->framebuffer_pitch;
        uint32_t bpp = fb_info->framebuffer_bpp;

	//8x16 font, not padded 
	VGA_WIDTH = width/8;
	VGA_HEIGHT = height/16;

	scanline = width * (bpp/8);	

	
	/* TEST print charset
	int y_offset = 2;
	for (int i=0; i<512; i++)
	{
		if (i%(width/9)==0) y_offset++;
		draw_char(0+i, 0+i, y_offset, white, black);
	}
	*/
	
	/* TEST print red square	
        for (uint32_t y = 0; y < 10; y++) {
            for (uint32_t x = 0; x < 10; x++) {
                putpixel(framebuffer, (int)pitch, (int)bpp, x, y, red);
		//framebuffer[y * (pitch / 4) + x] = 0xFF0000; // Rouge
            }
        }
	*/
	
	log("Drew to framebuffer.\r\n", 3);
    }
    /*
    puts("This should work by now! Enter Graphics Mode.");
    printf("\nMy name is %s, and I'm %d. 0x%x", "Alan", 34, 0xdeadbeef);

    for (int i=0; i<512; i++)
    {
	printf("%d ", i);
    } 
    */

    for (int i=0; i<100; i++)
    {
	printf("%d\n", i);
    }

    //colorputs("Wow, such colorful output!", green, blue);

    colorputs(ascii_title, green, black);

    while (1);


  /*
  init_serial();
  log("serial connection established\n", 3);
  gdt_install();
  log("initialized GDT entries\n", 2);
  idt_install();
  log("initialized IDT\n", 2);
  isr_install();
  log("initialized ISRs\n", 2);
  irq_install();
  __asm__ __volatile__("sti");
  log("initialized IRQs\n", 2),
 
  clear();
  colorputs(ascii_title, 10);
  colorputs("   by @xamidev - star the repo for a cookie!\n\n", 14);

  init_paging();
  printf("Hello, paging world!\n");

  //test_read_sector();

  uint32_t *ptr = (uint32_t*)0xA0000000;
  uint32_t do_page_fault = *ptr;

  timer_install();
  serial_printf(2, "%d\tinitialized timer handler", global_ticks); 
  keyboard_install(); 
  serial_printf(2, "%d\tinitialized keyboard handler", global_ticks); 
  shell_install();
  serial_printf(2, "%d\tstarted system shell", global_ticks); 
  */
}
