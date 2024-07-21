#include "io.h"
#include "../libc/stdio.h"
#include "system.h"

#define KEYBOARD_BUFFER_SIZE 256

unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
    '9', '0', '-', '=', '\b',	/* Backspace */
    '\t',			/* Tab */
    'q', 'w', 'e', 'r',	/* 19 */
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
    '\'', '`',   0,		/* Left shift */
    '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
    'm', ',', '.', '/',   0,				/* Right shift */
    '*',
    0,	/* Alt */
    ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
    '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
    '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

static char keyboard_buffer[KEYBOARD_BUFFER_SIZE];
static unsigned int keyboard_buffer_start = 0;
static unsigned int keyboard_buffer_end = 0;

void keyboard_handler()
{
	unsigned char scancode;

	scancode = inb(0x60);

	if (scancode & 0x80)
	{
	}
	else 
	{
		char c = kbdus[scancode];
		if (c)
		{
			keyboard_buffer[keyboard_buffer_end] = c;
			keyboard_buffer_end = (keyboard_buffer_end+1) % KEYBOARD_BUFFER_SIZE;
		}
	}
}

void keyboard_install()
{
	irq_install_handler(1, keyboard_handler);
}

char keyboard_getchar()
{
	while (keyboard_buffer_start == keyboard_buffer_end);

	char c = keyboard_buffer[keyboard_buffer_start];
	keyboard_buffer_start = (keyboard_buffer_start+1) % KEYBOARD_BUFFER_SIZE;
	return c;
}
