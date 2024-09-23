# Blank OS User's Manual

## Getting started

First, let me introduce you some features of this project.

## Features

- Serial port driver (output & debug)
- Framebuffer driver (output)
- PS/2 Keyboard and PIC driver (input)
- PIT (system clock/timer) driver
- Working IDT, GDT, ISRs, and IRQs
- Kernel panicking (exception handling)
- A kernel-space shell
- Cool color output!!
- Some small working kernel-space programs, such as...
- A brainfuck interpreter
- An arithmetic calculator
- ROT13 and Morse cipher programs
- Conway's Game of Life
- And some more...

### Installation and emulation/execution

Please refer to the relevant sections in the project `README.md` available in the root folder.

### First steps

Once you have launched the OS for the first time, you should first see the welcome banner with the system version. Then, the kernel shell will spawn and you will be able to execute commands.

To get the list of available commands on the system, type `help`.

### Commands

#### `help`

Shows all of the available commands, which are explained here.

#### `panic`

Triggers a kernel panic by reserved exception.

#### `words`

Prints random words using an arbitrary dictionary that you can expand in `src/programs/words.c`.

Options:
- `<nothing>` will default amount of words to 10
- `<integer>` will set the amount of words to that number 

#### `primes`

Computes prime numbers.

Options:
- `<nothing>` will default to `PRIMES_MAX` (a million)
- `<integer>` will compute primes up to that number

#### `rainbow <string>`

Asks for text and then outputs it with different vibrant colors.

#### `clear`

Clears the screen by scrolling (screen height) times.

#### `math`

A math lexer & parser that can calculate simple arithmetic operations. Adding, subtracting, multiplying, dividing, and factoring are supported. (I plan to get support for trigonometric functions maybe)

#### `bf <optional: file>`

A brainfuck interpreter with every instruction and default tape size (30k cells). Takes an optional argument, the filename for a Brainfuck source file.

#### `uptime`

Gets system uptime from the timer in ticks. Ticks are incremented at a rate of 18.222Hz (18.222 ticks per second).

#### `echo <string>`

The classic echo command, that outputs your input.

#### `sysinfo [option]`

Outputs information about the current system (CPU and RAM).
 
Options:
- `<nothing>` will show basic info about the CPUid and lower/upper memory.
- `-v` will output the CPUID, lower/upper memory, and the memory map.

#### `conway [option]`

A classic Game of Life implementation with standard rules and 100 generations.

Options:
- `<nothing>` will spawn a random soup of cells
- `-g` will spawn a classic glider
- `-l` will spawn a lightweight spaceship

#### `rot13 <string>`

Encode a string using the rot13 cipher.

#### `morse <string>`

Convert a string to its morse equivalent.

#### `cowsay <string>`

Makes a cow speak!

#### `pi <terms>`

Computes Pi up to a couple of digits using the Leibniz series; takes one integer argument, the number of terms of the series to compute.

#### `bmp <file>`

Shows information about a 24-bit BMP image and renders it in the terminal.

### Initrd utilities

You can browse the (really) simple TAR filesystem with the following commands:

#### `ls`

Lists all files present in `initrd.tar`.

#### `cat <file>`

Prints file content to terminal. Filename must be specified the same way as it is outputted when using `ls`.

### Games

#### `naval`

Starts a simplified naval battle game with 5 ships, one position each.

#### `snake <ticks>`

Starts a simplified and buggy snake game. You can choose the speed by setting the `ticks` argument, or let it default to a normal speed.

Controls:
- `q` to quit
- `wasd` to move

#### `exec <binary>`

Executes a binary file. Warning: this is highly broken and syscalls aren't working. It's written in a childish manner. Help is always appreciated (lol).

#### `uhex <file>`

Prints the hex and ASCII contents of a file.
