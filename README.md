![showcase](https://github.com/user-attachments/assets/0e3208db-e585-4086-9346-c00414d98646)

# BlankOS

Rewritten monolithic, ring 0, lower-half, single-threaded kernel for the x86 processor architecture, using GRUB (eltorito) as bootloader. Emulation was tested on Bochs and QEMU using Arch Linux 6.9.7-arch1-1, and on real hardware too.
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
- Some small working kernel-space programs!!

### Kernel-space programs

- A brainfuck interpreter
- An arithmetic calculator
- ROT13 and Morse cipher programs
- Conway's Game of Life
- And some more...

## Usage

Download the latest BlankOS ISO image from the "Releases" tab, and emulate it directly using the QEMU emulator:

```
qemu-system-i386 blankOS-i386-0.3.45.iso
```

Alternatively, burn the image on a USB stick and use it on a machine. (see section "Real Hardware"). *Note that the ISO images provided in the "Releases" tab are already real-hardware capable; no need to do anything except burning the image on a USB stick and running it on your machine.*

## Building from source

### Dependencies

For Debian-based distros:
```
sudo apt install gcc nasm make bochs
```

Then change `display-library` to `sdl2` in the `bochsrc.txt` file.

For Arch-based distros:
```
sudo pacman -S nasm gcc make
git clone https://aur.archlinux.org/bochs.git
```

Then follow [these](https://bbs.archlinux.org/viewtopic.php?id=178479) instructions to compile Bochs with X support. Alternatively you can use Bochs with SDL but you'll have to change the `bochsrc.txt` file accordingly.

### Cross Compiler

A cross-compiler is needed to build the system. More info on why [here](https://wiki.osdev.org/GCC_Cross-Compiler). In order for the build to work, you will need to download the i386-elf toolchain from [here](https://newos.org/toolchains/i386-elf-7.5.0-Linux-x86_64.tar.xz) and extract the root folder into the BlankOS root folder, or build it by youself if you're not lazy like me.

Why didn't I use one sooner? Can't tell. Maybe I was too lazy. This is actually problematic because I wasn't able to use some libraries and I had to put in a bunch of weird compilation flags. It's better like this.

To clone and build, do:

```
git clone https://github.com/xamidev/blankos
make
make run
```

This will start a new Bochs debugger instance. To proceed with the kernel execution, you will have to type `c` in the shell spawning Bochs. Serial output will be saved under the `com1.out` file, this way you can debug the kernel by viewing its log messages. To quit, type `q`.
You can try out QEMU too.

## Running on real hardware

To run the OS on real hardware, you'll first need to have a BIOS-compatible computer. Some of the new laptops with graphical "BIOSes" only support UEFI now. So make sure to get a computer that can boot into BIOS mode, **not UEFI mode**. Then, switch the boot mode to "Legacy" in your BIOS utility.

Then, use the Makefile target `real` to build a "real"-capable ISO disk image. The image will have GRUB2 installed on it, using the `grub-mkrescue` utility (make sure to install it before) which is dependent on `xorriso` (install it too).

Once the ISO file is generated, you can write it on a disk using this command:

```
sudo dd bs=4M if=blankos.iso of=/dev/sdX status=progress oflag=sync
```

Replace `sdX` with your USB drive name (you can find it by doing `sudo fdisk -l`).
Tada! You now have a working BlankOS USB stick. Go ahead and try it out!

## Post-install

Two documents are available to help you understand the project better. One is the User's Manual, labelled `USERS.md`, and the other one is the Developer's Manual, labelled `DEVELOPERS.md`. They are full of useful resources around Blank OS. You'll learn how to use the system and how to contribute to it.

### Next Steps?

Next steps for this project will be:

- User programs
- Completing the kernel libc
- Filesystem support

### Resources

- the [OSDev.org](https://wiki.osdev.org/Expanded_Main_Page) wiki and forums
- the [Nanobyte](https://www.youtube.com/watch?v=9t-SPC7Tczc&list=PLFjM7v6KGMpiH2G-kT781ByCNC_0pKpPN) YouTube channel
- the [Daedalus Community](https://www.youtube.com/@DaedalusCommunity) YouTube channel
- a great book named *Operating Systems: From 0 to 1*, by Tu, Do Hoang
- the Intel [64 and IA-32 Architectures Software Developer Manuals](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html)
- [Bran's Kernel Development Tutorial](http://www.osdever.net/bkerndev/index.php)

### ⚠️ Disclaimer

This is a hobbyist operating system kernel and it comes without any warranty whatsoever! It isn't capable of anything really. Feedback and contributions are highly appreciated!
