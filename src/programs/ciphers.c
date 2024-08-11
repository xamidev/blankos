#include "../libc/stdio.h"
#include "ciphers.h"

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

void program_rot13()
{
	char input_buffer[BUFFER_SIZE];
	char output[BUFFER_SIZE];
	puts("String? ");
	get_input(input_buffer, BUFFER_SIZE);
	rot13(input_buffer, output);
	printf("\n%s\n", output);
}

#include "../libc/string.h"
#include "../libc/stdint.h"

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

void program_morse() {
    char output[512]; 
    char input_buffer[BUFFER_SIZE];
    puts("String? ");
    get_input(input_buffer, BUFFER_SIZE);
    to_morse(input_buffer, output);
    printf("\n%s\n", output);
}

