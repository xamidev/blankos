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

Triggers a kernel panic by trying to divide four by zero.

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

#### `rainbow`

Asks for text and then outputs it with different vibrant colors.

#### `clear`

Clears the screen by scrolling (screen height) times.

#### `math`

A math lexer & parser that can calculate simple arithmetic operations. Adding, subtracting, multiplying, dividing, and factoring are supported. (I plan to get support for trigonometric functions maybe)

#### `bf`

A brainfuck interpreter with every instruction and default tape size (30k cells).

#### `uptime`

Gets system uptime from the timer in ticks. Ticks are incremented at a rate of 18.222Hz (18.222 ticks per second).

#### `echo`

The classic echo command, that outputs your input.

#### `sysinfo`

Outputs information about the current system (CPU and RAM).
 
Options:
- `<nothing>` will show basic info about the CPUid and lower/upper memory.
- `-v` will output the CPUID, lower/upper memory, and the memory map.

#### `conway`

A classic Game of Life implementation with standard rules and 100 generations.

Options:
- `<nothing>` will spawn a random soup of cells
- `-g` will spawn a classic glider
- `-l` will spawn a lightweight spaceship

#### `rot13`

Encode a string using the rot13 cipher.

#### `morse`

Convert a string to its morse equivalent.
