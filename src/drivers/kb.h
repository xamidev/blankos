// Keyboard driver header
// Author: xamidev
// Licensed under the Unlicense. See the repo below.
// https://github.com/xamidev/blankos

#ifndef KB_H
#define KB_H

#define KEYBOARD_BUFFER_SIZE    256

#define LEFT_SHIFT_PRESSED      0x2A
#define RIGHT_SHIFT_PRESSED     0x36
#define LEFT_SHIFT_RELEASED     0xAA
#define RIGHT_SHIFT_RELEASED    0xB6

char keyboard_getchar();

#endif
