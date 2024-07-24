#include "system.h"
#include "../libc/stdio.h"
#include "../libc/string.h"

#define BUFFER_SIZE 256

void shell_install()
{
  while (1) // Bad!!
  {
    char input_buffer[BUFFER_SIZE];
    colorputs("blankos> ", 9);
    get_input(input_buffer, BUFFER_SIZE);
    printf("\n");
    
    // Childish shell
    if (strcmp(input_buffer, "") == 0)
    {
	continue;
    }
    else if (strcmp(input_buffer, "help") == 0)
    {
        printf("This is the Blank Operating System\ndesigned for fun by xamidev\n\nCommand help:\n\n\thelp - shows this message\n\tpanic - makes the kernel panic\n");
    }
    else if (strcmp(input_buffer, "panic") == 0)
    {
	printf("%d", 4/0);
    }
    else {
	puts("Unknown command\n");
    }
  }
}
