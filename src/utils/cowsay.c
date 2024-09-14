// Cowsay-like program
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#include "../libc/stdio.h"
#include "../libc/string.h"

#define MAX_MSG_LEN 128

const char* cow =
"        \\   ^__^\n"
"         \\  (oo)\\_______\n"
"            (__)\\       )\\/\\\n"
"                ||----w |\n"
"                ||     ||\n";

void print_bubble(const char* message)
{
	int len = strlen(message);
	puts(" ");
	for (int i=0; i<len+2; i++)
	{
		puts("_");
	}
	puts("\n");

	printf("< %s >\n", message);

	puts(" ");
	for (int i=0; i<len+2; i++)
	{
		puts("-");
	}
	puts("\n");
}

void cowsay(char* msg, uint32_t fg, uint32_t bg)
{
	print_bubble(msg);
	colorputs(cow, fg, bg);
}

void program_cowsay(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("Usage: %s <message>\n", argv[0]);
		return;
	}

	char message[MAX_MSG_LEN];
	message[0] = '\0';

	for (int i=1; i<argc; i++)
	{
		if (strlen(message) + strlen(argv[i]) + 1 < MAX_MSG_LEN)
		{
			strcat(message, argv[i]);
			if (i < argc-1)
			{
				strcat(message, " ");
			}
		} else {
			puts("Too long message.\n");
			return;
		}
	}

	print_bubble(message);
	printf("%s", cow);
}
