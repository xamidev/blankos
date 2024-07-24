# Blank OS Developer's Manual

## Getting Started

### System description

Blank OS runs on a monolithic kernel booted by a 3rd party bootloader; GRUB (whose executable is named `stage2_eltorito`). The kernel is compiled in ELF format. The target processor architecture is 32-bit x86. Blank OS is BIOS-independent which means it does not use Real mode BIOS functions as its routines. It rather uses in and out port communication to communicate with hardware directly (such as the keyboard) and it uses specific memory locations (for example the framebuffer to manage the screen in text mode).

### Code structure

The source code is available in folder `src`. You will find subfolders corresponding to appropriate system parts, such as the kernel, the C library (including drivers) and programs.

## Making programs for the OS

### Programming

Basically you can use the kernel C library functions available in `src/libc/` and make programs out of those functions. Then you can set up the shell for your program to be launchable.

More on that soon.

### Compiling and linking

The linking process should be taken care by the appropriate Linker script `link.ld` and the Makefile instructions and targets.
