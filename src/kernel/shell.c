#include "system.h"
#include "../libc/stdio.h"
#include "../libc/string.h"
#include "../programs/programs.h"

#define BUFFER_SIZE 256
#define MAX_COMMANDS 16

typedef void (*command_func_t)();

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

void shell_install()
{
  register_command("help", program_help);
  register_command("panic", program_panic);
  register_command("words", program_words);
  register_command("primes", program_primes);
  register_command("rainbow", program_rainbow);
  register_command("clear", program_clear);
  register_command("math", program_math);
  register_command("bf", program_bf);
  register_command("uptime", program_uptime);
  
  for (;;)
  {
    char input_buffer[BUFFER_SIZE];
    colorputs("blankos> ", 9);
    get_input(input_buffer, BUFFER_SIZE);
    puts("\n");

    if (strcmp(input_buffer, "") == 0) {
    	continue;
    }

    command_func_t command = find_command(input_buffer);
    if (command)
    {
	    command();
    } else {
	    printf("Unknown command %s\n", input_buffer);
    }
  }
}
