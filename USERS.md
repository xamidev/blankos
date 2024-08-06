# Blank OS User's Manual

## Getting started

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

Prints ten random words using an arbitrary dictionary that you can expand in `src/programs/words.c`.

#### `primes`

Computes prime numbers up to `PRIMES_MAX`, defined in `src/programs/primes.c`.

#### `rainbow`

Asks for text and then outputs it with different vibrant colors.

#### `clear`

Clears the screen by scrolling (screen height) times.

#### `math`

**This program is not working!**
The lexer and parser should be okay, but I can't figure out the `%f` floating point format specifier in the freestanding printf implementation; it triggers weird exceptions that I don't understand. So no math interpreter for now.

#### `bf`

A brainfuck interpreter with every instruction and default tape size (30k cells).

#### `uptime`

Gets system uptime from the timer in ticks. Ticks are incremented at a rate of 18.222Hz (18.222 ticks per second).
