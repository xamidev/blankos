#ifndef PROGRAMS_H
#define PROGRAMS_H

void program_words();
void program_primes();
void program_math();
void program_bf();
void program_sysinfo();

void get_cpuid();
void get_meminfo(unsigned int multiboot_info_address);

// Misc
void program_rainbow();
void program_clear();
void program_uptime();
void program_panic();
void program_help();
void program_echo();
#endif
