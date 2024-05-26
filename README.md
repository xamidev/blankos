# Blank OS

Rewritten 32-bit Protected Mode monolithic version of Blank OS for the x86 processor architecture. Features a framebuffer and serial port driver. The OS relies on an old, legacy version of GRUB as the bootloader. This *should* be GRUB 2 compatible.

Long-term goal of this OS is to be capable of running user programs and having its own complete kernel C library so that users can write their own C programs to be ran using the kernel.

Next steps for this project will be:
- a working formatted printing function
- Segmentation and a GDT implementation
- IDT implementation
- User programs
- Shell
- Kernel libc
- Filesystem support

## Usage

First, install dependencies:
```
sudo apt install gcc nasm make bochs
```

Then, clone the repository and run these commands:
```
make
make run
```
This will start a new Bochs debugger instance. To proceed with the kernel execution, you will have to type `c` in the shell spawning Bochs. Serial output will be saved under the `com1.out` file, this way you can debug the kernel by viewing its log messages. 

Feel free to open issues or pull requests.
