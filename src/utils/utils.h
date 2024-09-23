// Global program entry points header
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#ifndef UTILS_H
#define UTILS_H

void program_words();
void program_primes();
void program_math();
void program_bf();
void program_sysinfo();

void get_cpuid();
void get_meminfo(unsigned int multiboot_info_address); // to be fixed: cannot get full memory map (sysinfo -v)
void program_cowsay();
void cowsay(); // Splash screen
void program_pi();

// Ciphers
void program_rot13();
void program_morse();

// Misc
void program_rainbow();
void program_clear();
void program_uptime();
void program_panic();
void program_help();
void program_echo();
void program_time();
void program_read();
void program_reboot();

// Filesystem (initrd)
void program_ls();
void program_cat();

void program_bmp();
void program_lspci();

// Games
void program_navalbattle();
void program_conway();
void program_snake();

// Binaries loading and execution
void program_exec();

#endif
