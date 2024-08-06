#include "system.h"
#include "../libc/stdio.h"
#include "../libc/string.h"
#include "../programs/programs.h"

#define BUFFER_SIZE 256

void shell_install()
{
  while (1) // Bad!!
  {
    char input_buffer[BUFFER_SIZE];
    colorputs("blankos> ", 9);
    get_input(input_buffer, BUFFER_SIZE);
    puts("\n");
    
    // Childish shell
    if (strcmp(input_buffer, "") == 0)
    {
	continue;
    }
    else if (strcmp(input_buffer, "help") == 0)
    {
        printf("help\tpanic\twords\tprimes\trainbow\tclear\nmath\tbf\tuptime\n");
    }
    else if (strcmp(input_buffer, "panic") == 0)
    {
	printf("%d", 4/0);
    }
    else if (strcmp(input_buffer, "words") == 0)
    {
	    program_words();
    }
    else if (strcmp(input_buffer, "primes") == 0)
    {
	    program_primes();
    }
    else if (strcmp(input_buffer, "rainbow") == 0)
    {
	program_rainbow();
    }
    else if (strcmp(input_buffer, "clear") == 0)
    {
	program_clear();
    }
    else if (strcmp(input_buffer, "math") == 0)
    {
	    program_math();
    }
    else if (strcmp(input_buffer, "bf") == 0)
    {
	    program_bf();
    }
    else if (strcmp(input_buffer, "uptime") == 0)
    {
	    program_uptime();
    }
    else {
	printf("Unknown command %s\n", input_buffer);
    }
  }
}
