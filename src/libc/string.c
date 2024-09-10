// String operations implementation for blankos/libc
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#include <stdint.h>
#include "../kernel/system.h"

int strlen(const char* str)
{
  int len = 0;
  while (*str++)
  {
    len++;
  }
  return len;
}

int strcmp(const char* str1, const char* str2)
{
  while (*str1 && (*str1 == *str2))
  {
    str1++;
    str2++;
  }
  return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}

char* strchr(const char* str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
		{
			return (char*)str;
		}
		str++;
	}
	if (c == '\0')
	{
		return (char*)str;
	}
	return NULL;
}

char* strtok(char* str, const char* delimiter)
{
	static char* last;
	if (str)
	{
		last = str;
	} else {
		str = last;
	}

	if (!str || *str == '\0')
	{
		return NULL;
	}

	char* token_start = str;
	while (*str && !strchr(delimiter, *str))
	{
		str++;
	}

	if (*str)
	{
		*str = '\0';
		last = str + 1;
	} else {
		last = NULL;
	}

	return token_start;
}

int atoi(char* str)
{
	int result = 0;

	for (int i=0; str[i] != '\0'; i++)
	{
		result = result*10 + str[i] - '0';
	}

	return result;
}

void strcat(char* dest, const char* src)
{
	while (*dest)
	{
		dest++;
	}

	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}

	*dest = '\0';
}

size_t strnlen(const char* str, size_t max_len)
{
	size_t len = 0;
	while (*str && len < max_len)
	{
		len++;
		str++;
	}
	return len;
}

void strncat(char* dest, const char* src, size_t n)
{
	while (*dest)
	{
		dest++;
	}

	while (*src && n > 0)
	{
		*dest = *src;
		dest++;
		src++;
		n--;
	}

	*dest = '\0';
}
