![showcase](https://github.com/user-attachments/assets/0e3208db-e585-4086-9346-c00414d98646)

# BlankOS

Rewritten monolithic, ring 0, lower-half, singletasking kernel for the x86 processor architecture, using GRUB (eltorito) as bootloader. Emulation was tested on QEMU using Arch Linux 6.9.7-arch1-1, and on real hardware too.
The long-term goal of this OS is to be capable of running user programs and having its own complete kernel C library so that users can write their own C programs and expand the system!

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

## Usage

Download the latest BlankOS disk image from the "Releases" tab, and start it using the QEMU emulator:

```
qemu-system-i386 blankOS-i386-0.3.45.img
```

## Building from source

```
git clone https://github.com/xamidev/blankos
make toolchain
make
make run
```

The `toolchain` target will download the appropriate cross-compiling tools, and the `run` target will make a disk image for emulation or real hardware testing. *Some operations require root access. Always audit the code yourself before running anything as root!*

## Running on real hardware

To run the OS on real hardware, you'll first need to have a BIOS-compatible computer. Some of the new laptops with graphical "BIOSes" only support UEFI now. So make sure to get a computer that can boot into BIOS mode. You'll have to switch the boot mode to "Legacy" in your BIOS/UEFI utility.

Burn your image file onto a USB stick:
```
sudo dd bs=4M if=blankos-fat.img of=/dev/sdX status=progress oflag=sync
```

Replace `sdX` with your USB drive name (you can find it by doing `sudo fdisk -l`).
Tada! You now have a working BlankOS USB stick. Go ahead and try it out!

## Debugging (QEMU w/ GDB)

```
qemu-system-i386 -s -S -drive file=blankos-fat.img,format=raw
```

In another shell:

```
gdb kernel.elf
(gdb) target remote localhost:1234
```

## Documentation

Two other documents are available to help you understand the project better. One is the User's Manual, labelled [USERS.md](USERS.md), and the other one is the Developer's Manual, labelled [DEVELOPERS.md](DEVELOPERS.md). They are full of useful resources around Blank OS. You'll learn how to use the system and how to contribute to it.

### Resources

- the [OSDev.org](https://wiki.osdev.org/Expanded_Main_Page) wiki and forums
- the [Nanobyte](https://www.youtube.com/watch?v=9t-SPC7Tczc&list=PLFjM7v6KGMpiH2G-kT781ByCNC_0pKpPN) YouTube channel
- the [Daedalus Community](https://www.youtube.com/@DaedalusCommunity) YouTube channel
- a great book named *Operating Systems: From 0 to 1*, by Tu, Do Hoang
- the Intel [64 and IA-32 Architectures Software Developer Manuals](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html)
- [Bran's Kernel Development Tutorial](http://www.osdever.net/bkerndev/index.php)
- Ralf Brown's Interrupt List

### ⚠️ Disclaimer

This is a hobbyist operating system kernel and it comes without any warranty whatsoever! It isn't capable of anything really. Feedback and contributions are highly appreciated!

### Roadmap

- [X] Booting with GRUB
- [X] Common basic structures (IDT, GDT, ISRs, IRQs)
- [X] Common drivers (framebuffer, keyboard, serial, timer)
- [X] Kernel-space utilities (shell, simple programs)
- [ ] FAT32 filesystem
- [ ] Paging/Page Frame Allocation
- [ ] TCP/IP Network stack
- [ ] Getting to Ring-3 (userspace)
- [ ] Multitasking (via round robin scheduling)
- [ ] Advanced/other drivers (video, SB16, RTC, Ethernet)
- [ ] UEFI support
- [ ] ELF parsing
- [ ] System calls
- [ ] GUI
- [ ] POSIX and ANSI specification compatibility
