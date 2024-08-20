// Miscellaneous small programs

#include "../libc/stdio.h"
#include "../kernel/system.h"
#include "../libc/string.h"

// Print a rainbow colorful text for testing

#define BUF_SIZE 256
#define COLORS 20

void program_rainbow()
{
	char input_buffer[BUF_SIZE];
	puts("What to print? ");
	get_input(input_buffer, BUF_SIZE);	
	puts("\n");

	for (int i=0; i<COLORS; i++)
	{
		//colorputs(input_buffer, i);
		puts("\n");
	}	
}

// Clear the terminal

#define ROWS 25

void program_clear()
{	
	for (int i=0; i<ROWS; i++) scroll(1);
}

// Get uptime in ticks

void program_uptime()
{
	int ticks = uptime();
	double seconds = ticks/18.2065; // PIC channel 0 freq
	printf("%d ticks\t%f seconds\n", ticks, seconds);
}

// Get help

void program_help()
{
	printf("help\tpanic\twords\tprimes\trainbow\tclear\nmath\tbf\t   uptime   echo\t  sysinfo\tconway\nrot13   morse\n");
}

// Panic

void program_panic()
{
	asm volatile("int $0x13");
}

// Output input

void program_echo(int argc, char* argv[])
{
	for (int i=1; i<argc; i++)
	{
		puts(argv[i]);
		if (i < argc-1) {
			putc(' ');
		}
	}
	puts("\n");
}
