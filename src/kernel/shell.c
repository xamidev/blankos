#include "system.h"
#include "../libc/stdio.h"
#include "../libc/string.h"
#include "../programs/programs.h"
#include <stdint.h>

#define BUFFER_SIZE 256
#define MAX_COMMANDS 16
#define MAX_ARGS 64


char* ascii_title =
"\n"
"----------------------------------------------\n"
"Blank OS version 0.3.71-dev\n"
"Author: @xamidev - star the repo for a cookie!\n"
"----------------------------------------------\n"
"\n";


typedef void (*command_func_t)(int argc, char *argv[]);

typedef struct
{
	const char* name;
	command_func_t function;
} shell_command_t;

shell_command_t shell_commands[MAX_COMMANDS];
int command_count = 0;

void register_command(const char* name, command_func_t function)
{
	if (command_count < MAX_COMMANDS)
	{
		shell_commands[command_count].name = name;
		shell_commands[command_count].function = function;
		command_count++;
	}
}

command_func_t find_command(const char* name)
{
	for (int i=0; i < command_count; i++)
	{
		if (strcmp(name, shell_commands[i].name) == 0) 
			return shell_commands[i].function;
	}
	return 0;
}

int parse_input(char* input, char* argv[], int max_args)
{
	int argc = 0;
	char* token = strtok(input, " ");
	while (token != NULL && argc < max_args - 1)
	{
		argv[argc++] = token;
		token = strtok(NULL, " ");
	}
	argv[argc] = NULL;
	return argc;
}

void shell_install()
{ 
  colorputs(ascii_title, yellow, black);
  
  register_command("help", program_help);
  register_command("panic", program_panic);
  register_command("words", program_words);
  register_command("primes", program_primes);
  register_command("rainbow", program_rainbow);
  register_command("clear", program_clear);
  register_command("math", program_math);
  register_command("bf", program_bf);
  register_command("uptime", program_uptime);
  register_command("echo", program_echo);
  register_command("sysinfo", program_sysinfo);
  register_command("conway", program_conway);
  register_command("rot13", program_rot13);
  register_command("morse", program_morse);

  for (;;)
  {
    char input_buffer[BUFFER_SIZE];
    char* argv[MAX_ARGS];

    // Prompt
    colorputs("root", blue, black);
    colorputs("@", white, black);
    colorputs("blankos", green, black);
    colorputs("~$ ", white, black);

    get_input(input_buffer, BUFFER_SIZE);
    puts("\n");
    
    int argc = parse_input(input_buffer, argv, MAX_ARGS);

    if (argc == 0) continue;

    command_func_t command = find_command(argv[0]);
    if (command)
    {
	    command(argc, argv);
    } else {
	    printf("Unknown command %s\n", argv[0]);
    }
  }
}
