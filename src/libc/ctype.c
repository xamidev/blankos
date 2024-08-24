// Ctype implementation for blankos/libc
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https//github.com/xamidev/blankos

#include <stdint.h>
#include <stdbool.h>

bool isdigit(char c)
{
	return c >= '0' && c <= '9';
}

bool isspace(char c)
{
	return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r';
}
