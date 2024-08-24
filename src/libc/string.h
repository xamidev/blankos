// String operations implementation for blankos/libc header
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#ifndef STRING_H
#define STRING_H

int strlen(const char* str);
int strcmp(const char* str1, const char* str2);
char* strtok(char* str, const char* delimiter);
int atoi(char* str);
void strcat(char* dest, const char* src);


#endif
