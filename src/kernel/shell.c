// Basic shell and commands kernel module
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#include "system.h"
#include "../libc/stdio.h"
#include "../libc/string.h"
#include "../programs/programs.h"
#include "../libc/crypto.h"
#include <stdint.h>
#include "../drivers/rtc.h"

#define BUFFER_SIZE 256
#define MAX_COMMANDS 64
#define MAX_ARGS     64

// Splash screen: esthetic stuff.

char* motd[] = 
{
	"Now in 2D!",
	"Supercalifragilisticexpialidocious!",
	"Tylko jedno w glowie mam!",
};
int motd_size = sizeof(motd)/sizeof(motd[0]);

bool do_splash = true;

void splash()
{ 
	int random = randint(time_seed());
	char* motd_pick = motd[random%motd_size];
	cowsay(motd_pick, red, black);
	colorputs("        blankOS 0.3.86-alpha", red, black);
	puts("\n");
	

	puts("        Time: ");
	rtc_time_t time;
	rtc_read_time(&time);
	print_time(&time);
	puts("\n");
}

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
  if (do_splash == true)
  {
	do_splash = false;
  	splash();
  }
  
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
  register_command("cowsay", program_cowsay);
  register_command("time", program_time);
  register_command("read", program_read);
  register_command("reboot", program_reboot);

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
