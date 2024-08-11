# Blank OS Developer's Manual

## Getting Started

### System description

Blank OS runs on a monolithic kernel booted by a 3rd party bootloader; GRUB (whose executable is named `stage2_eltorito`). The kernel is compiled in ELF format. The target processor architecture is 32-bit x86. Blank OS is BIOS-independent which means it does not use Real mode BIOS functions as its routines. It rather uses in and out port communication to communicate with hardware directly (such as the keyboard) and it uses specific memory locations (for example the framebuffer to manage the screen in text mode).

### Code structure

The source code is available in folder `src`. You will find subfolders corresponding to appropriate system parts, such as the kernel, the C library (including drivers) and programs.

### System calls

No system calls are available, as the OS runs in kernel-space.

## Making programs for the OS

### Step 1 - Making the program and the entry point

To make a program for the OS, first create the appropriate C source file and header file in the `src/programs` subfolder. Name it appropriately, for example `myprogram.c`.

In this file, you will put the functions your program will use. The entry point for the program should be a void function named `program_<PROGRAM_NAME>`. The entry point can either take no arguments, or use the classic argc/argv structure. 

Valid examples for entry points include:

```
void program_myprogram()
void program_myprogram(void)
void program_myprogram(int argc, char* argv[])
```

Then, code your stuff freely. The entry point function will basically be the "main" function of your program, like in a regular C file. You can make your own header file too, for example `myprogram.h`.
Keep in mind that the standard C library is not available here, so you'll have to use functions from the BlankOS C library, which is located in `src/libc`. Also feel free to look at the header files in `src/drivers` and `src/kernel`, there might be interesting functions in there too (managing input/output devices, the timer, etc..)

### Step 2 - Registering the program

Now that your program is done, you will need to make it a part of the OS. 

#### General program header file registering

To make the entry point function reachable from the shell, you first have to include it in the general programs header file located in `src/programs/programs.h`.

Put the entry point function prototype in that file. A valid example might be:

```
void program_myprogram(int argc, char* argv[]);
```

#### Shell command registering

Now that your entry point is reachable from the shell source file, you'll have to register it as a command. To do that, locate the section in `src/kernel/shell.c`, in the very beginning of the `shell_install()` function that has a lot of similar lines to the one below:

```
register_command("myprogram", program_myprogram);
```

Add one of these lines for your entry point and the command name you'd like. (like the line above). First argument is the desired command name, and second argument is the entry point for your program. 

Don't make your command name too long, preferably a few characters, like the other ones.

#### Help utility registering (optional)

Finally, you can add your command to the list of available commands by adding it to the `printf` call in the `src/programs/misc.c` source file, in the function `program_help()`.

If possible make sure that the new command name is aligned with the other ones.

### Step 3 - Compiling and linking

The linking process should be taken care by the appropriate Linker script `link.ld` and the Makefile instructions and targets. Nothing should be changed in those files, and your source files should be added automatically.

### Step 4 - Contributing to the project (optional)

If you're proud of what you've made, you can clone the repo, make your changes, open a pull request and maybe your program will be added to the main BlankOS repo, and later distributed in the new ISOs!


