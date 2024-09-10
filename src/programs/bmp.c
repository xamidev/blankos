// Bitmap image renderer
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#include "../kernel/kmain.h"
#include <stdint.h>
#include "../kernel/initrd.h"
#include "../drivers/framebuffer.h"
#include "../libc/stdio.h"
#include "../drivers/serial.h"
#include "../kernel/kheap.h"

#pragma pack(push, 1)
typedef struct
{
	uint16_t bfType;
	uint32_t bfSize;
	uint16_t bfReserved1;
	uint16_t bfReserved2;
	uint32_t bfOffBits;
} BMPHeader;

typedef struct
{
	uint32_t biSize;
	int32_t  biWidth;
	int32_t  biHeight;
	uint16_t biPlanes;
	uint16_t biBitCount;
	uint32_t biCompression;
	uint32_t biSizeImage;
	int32_t  biXPelsPerMeter;
	int32_t  biYPelsPerMeter;
	uint32_t biClrUsed;
	uint32_t biClrImportant;
} BMPInfoHeader;
#pragma pack(pop)

void display_bmp(uint32_t* fb, int pitch, int bpp, uint8_t* initrd, const char* filename)
{
	uint32_t buf_size = tar_get_file_size(initrd, filename);
	char* buffer = (char*)malloc(buf_size);
	int file_status = tar_file_to_buffer(initrd, filename, buffer);

	if (file_status != 0)
	{
		printf("Error loading file '%s'\n", filename);
		return;
	}

	BMPHeader* bmp_header = (BMPHeader*)buffer;
	BMPInfoHeader* bmp_info = (BMPInfoHeader*) (buffer+sizeof(BMPHeader));

	if (bmp_header->bfType != 0x4D42)
	{
		printf("'%s' is not a valid BMP file\n", filename);
		return;
	}

	int width = bmp_info->biWidth;
	int height = bmp_info->biHeight;
	int pixel_offset = bmp_header->bfOffBits;

	printf("%d-bit BMP, width: %d, height: %d, pixel offset: %d\n", bmp_info->biBitCount, bmp_info->biWidth, bmp_info->biHeight, (int)bmp_header->bfOffBits);	
	erase_cursor();
	uint8_t* pixel_data = (uint8_t*)(buffer + pixel_offset);

	int cursor_y = (get_cursor_y()+1)*16;
	serial_printf(3, "cursor_y=%d\n", cursor_y);

	for (int y=cursor_y; y<height+cursor_y; y++)
	{
		for (int x=0; x<width; x++)
		{
			int index = (x+(height-y-1+cursor_y)*width)*3;
			uint8_t blue = pixel_data[index];
			uint8_t green = pixel_data[index+1];
			uint8_t red = pixel_data[index+2];

			uint32_t color = (0xFF << 24) | (red << 16) | (green << 8) | blue;
			putpixel(fb, pitch, bpp, x, y, color);
		}
	}

	// Update cursor pos after image drawing
	move_cursor(get_cursor_x(), get_cursor_y()+(height/16)+2);
	free(buffer);
}

void program_bmp(int argc, char* argv[])
{
	if (argc < 2)
	{
		puts("Usage: bmp <file>\n"); 
		return;
	}
	display_bmp(framebuffer, pitch, bpp, (uint8_t*)initrd_addr, argv[1]);
}
