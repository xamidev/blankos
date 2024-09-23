// Cipher programs
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#include "../libc/stdio.h"
#include "ciphers.h"
#include "../libc/string.h"
#include <stdint.h>

void rot13(char* input, char* output)
{
	int i = 0;

	while (input[i] != '\0')
	{
		char c = input[i];

		if (c >= 'a' && c <= 'z') {
			output[i] = ((c - 'a' + 13) % 26) + 'a';
		} else if (c >= 'A' && c <= 'Z') {
			output[i] = ((c - 'A' + 13) % 26) + 'A';
		} else {
			output[i] = c;
		}

		i++;
	}
	output[i] = '\0';
}

void program_rot13(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("Usage: %s <string>\n", argv[0]);
		return;
	}

	char input_buffer[BUFFER_SIZE] = {0};
	char output[BUFFER_SIZE] = {0};

	for (int i=1; i<argc; i++)
	{
		strcat(input_buffer, argv[i]);
		if (i<argc-1)
		{
			strcat(input_buffer, " ");
		}
	}
	rot13(input_buffer, output);
	printf("%s\n", output);
}

const char* morse_alphabet[] = {
    ".-",   // A
    "-...", // B
    "-.-.", // C
    "-..",  // D
    ".",    // E
    "..-.", // F
    "--.",  // G
    "....", // H
    "..",   // I
    ".---", // J
    "-.-",  // K
    ".-..", // L
    "--",   // M
    "-.",   // N
    "---",  // O
    ".--.", // P
    "--.-", // Q
    ".-.",  // R
    "...",  // S
    "-",    // T
    "..-",  // U
    "...-", // V
    ".--",  // W
    "-..-", // X
    "-.--", // Y
    "--.."  // Z
};

const char* morse_digits[] = {
    "-----", // 0
    ".----", // 1
    "..---", // 2
    "...--", // 3
    "....-", // 4
    ".....", // 5
    "-....", // 6
    "--...", // 7
    "---..", // 8
    "----."  // 9
};

void to_morse(const char* input, char* output) {
    int i = 0;
    int pos = 0;
    
    while (input[i] != '\0') {
        char c = input[i];
        
        if (c >= 'a' && c <= 'z') {
            const char* morse_code = morse_alphabet[c - 'a'];
            int j = 0;
            while (morse_code[j] != '\0') {
                output[pos++] = morse_code[j++];
            }
        } else if (c >= 'A' && c <= 'Z') {
            const char* morse_code = morse_alphabet[c - 'A'];
            int j = 0;
            while (morse_code[j] != '\0') {
                output[pos++] = morse_code[j++];
            }
        } else if (c >= '0' && c <= '9') {
            const char* morse_code = morse_digits[c - '0'];
            int j = 0;
            while (morse_code[j] != '\0') {
                output[pos++] = morse_code[j++];
            }
        } else if (c == ' ') {
            output[pos++] = ' ';
        }

        output[pos++] = ' ';
        i++;
    }
    
    if (pos > 0) {
        output[pos - 1] = '\0';
    } else {
        output[pos] = '\0'; 
    }
}

void program_morse(int argc, char* argv[]) {
    
    if (argc < 2)
    {
	printf("Usage: %s <string>\n", argv[0]);
	return;
    }
	
    char output[512]; 
    char message[BUFFER_SIZE];

    for (int i=1; i<argc; i++)
    {
	strcat(message, argv[i]);
	if (i < argc-1)
	{
		strcat(message, " ");
	}
    }

    to_morse(message, output);
    printf("%s\n", output);
}

