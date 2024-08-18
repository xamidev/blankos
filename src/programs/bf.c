
#include "../kernel/system.h"
#include "../libc/stdio.h"

#define BUF_SIZE 256

void brainfuck(char* input)
{
	unsigned char tape[30000] = {0};
	unsigned char* ptr = tape;
	char current_char;
	size_t i;
	size_t loop;

	for (i=0; input[i] != 0; i++)
	{
		current_char = input[i];
		if (current_char == '>') {
			++ptr;
		} else if (current_char == '<') {
			--ptr;
		} else if (current_char == '+') {
			++*ptr;
		} else if (current_char == '-') {
			--*ptr;
		} else if (current_char == '.') {
			putc(*ptr);
		} else if (current_char == ',') {
			*ptr = keyboard_getchar();
		} else if (current_char == '[') {
			continue;
		} else if (current_char == ']' && *ptr) {
			loop = 1;
			while (loop > 0)
			{
				current_char = input[--i];
				if (current_char == '[') {
					loop--;
				} else if (current_char == ']') {
					loop++;
				}
			}
		}
	}
}

void program_bf()
{
	char input_buffer[BUF_SIZE];
	puts("Brainfuck code? ");
	get_input(input_buffer, BUF_SIZE);
	brainfuck(input_buffer);
	//brainfuck(",[.[-],]");
	puts("\n");
}