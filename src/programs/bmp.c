// Bitmap image renderer
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#include "../kernel/kmain.h"
#include <stdint.h>
#include "../kernel/initrd.h"
#include "../drivers/framebuffer.h"
#include "../libc/stdio.h"

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

void display_bmp(uint32_t* fb, int pitch, int bpp, uint8_t* initrd)
{
	char buffer[1024*1024];
	int file_status = tar_file_to_buffer(initrd, "./flower.bmp", buffer);

	if (file_status != 0)
	{
		puts("Error loading BMP\n");
		return;
	}

	BMPHeader* bmp_header = (BMPHeader*)buffer;
	BMPInfoHeader* bmp_info = (BMPInfoHeader*) (buffer+sizeof(BMPHeader));

	if (bmp_header->bfType != 0x4D42)
	{
		puts("Not a valid BMP\n");
		return;
	}

	int width = bmp_info->biWidth;
	int height = bmp_info->biHeight;
	int pixel_offset = bmp_header->bfOffBits;

	if (bmp_info->biBitCount != 24)
	{
		puts("Not a 24-bit BMP\n");
		return;
	}

	uint8_t* pixel_data = (uint8_t*)(buffer + pixel_offset);

	for (int y=0; y<height; y++)
	{
		for (int x=0; x<width; x++)
		{
			int index = (x+(height-y-1)*width)*3;
			uint8_t blue = pixel_data[index];
			uint8_t green = pixel_data[index+1];
			uint8_t red = pixel_data[index+2];

			uint32_t color = (red << 16) | (green << 8) | blue;
			putpixel(fb, pitch, bpp, x, y, color);
		}
	}
}
