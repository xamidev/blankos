![Screenshot_20240826_160940](https://github.com/user-attachments/assets/a4d2af98-7c7e-4a7f-a64c-31b0325d99d7)

> [!WARNING]
> The project is currently paused, after months of work around the subject. I've had enough for now, and I'll surely come back in some time to implement the more advanced stuff I had planned. For now, enjoy the latest alpha version.
> This is a hobbyist operating system, and it comes without any warranty whatsoever! See the license for more info. Feedback and contributions are highly appreciated.

# BlankOS

Rewritten monolithic, ring 0, lower-half, singletasking kernel for the x86 processor architecture, using GRUB 2 as bootloader. Emulation was tested on QEMU using Arch Linux 6.9.7-arch1-1, and on real hardware (UEFI and BIOS).
The long-term goal of this OS is to be capable of running user programs and having its own complete kernel C library so that users can write their own C programs and expand the system!

## Usage

Download the latest BlankOS disk image from the "Releases" tab, and start it using the QEMU emulator:

```
qemu-system-i386 blankOS-i386-0.3.55.iso
```

> [!NOTE]
> Know that the latest release is not always up-to-date with the source code. To get the most up-to-date version, instead build from source as shown below.

## Building from source

```
git clone https://github.com/xamidev/blankos
make toolchain
make
make run
```

The `toolchain` target will download the appropriate cross-compiling tools, and the `run` target will make a disk image for emulation or real hardware testing. *Some operations require root access. Always audit the code yourself before running anything as root!*

## Running on real hardware

The OS is now both UEFI and BIOS compatible! Burn your image file onto a USB stick:
```
sudo dd bs=4M if=blankos.iso of=/dev/sdX status=progress oflag=sync
```

Replace `sdX` with your USB drive name (you can find it by doing `sudo fdisk -l`).
Tada! You now have a working BlankOS USB stick. Go ahead and try it out!
(*Might not work properly on monitors that aren't Full HD*)

## Documentation

Two other documents are available to help you understand the project better. One is the User's Manual, labelled [USERS.md](docs/USERS.md), and the other one is the Developer's Manual, labelled [DEVELOPERS.md](docs/DEVELOPERS.md). They are full of useful resources: you'll learn how to use the system and how to contribute to it. *(The docs might not always be up-to-date)*

### Resources

- the [OSDev.org](https://wiki.osdev.org/Expanded_Main_Page) wiki and forums
- the [Nanobyte](https://www.youtube.com/watch?v=9t-SPC7Tczc&list=PLFjM7v6KGMpiH2G-kT781ByCNC_0pKpPN) YouTube channel
- the [Daedalus Community](https://www.youtube.com/@DaedalusCommunity) YouTube channel
- a great book named *Operating Systems: From 0 to 1*, by Tu, Do Hoang
- the Intel [64 and IA-32 Architectures Software Developer Manuals](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html)
- [Bran's Kernel Development Tutorial](http://www.osdever.net/bkerndev/index.php)
- Ralf Brown's Interrupt List
- the [little book about OS development](https://littleosbook.github.io/) by Erik Helin and Adam Renberg

### Features / Roadmap

- [X] Booting with GRUB
- [X] Common basic structures (IDT, GDT, ISRs, IRQs)
- [X] Common drivers (framebuffer, keyboard, serial, timer, RTC, ATA PIO)
- [X] Kernel-space utilities (shell, simple programs)
- [ ] Filesystem (FAT32 or VFS ramdisk)
- [ ] Changing the default VGA font
- [ ] Dynamic memory allocator (get memmap from GRUB?)
- [ ] Paging/Page Frame Allocation
- [ ] TCP/IP Network stack
- [ ] Getting to Ring-3 (userspace)
- [ ] Multitasking (via round robin scheduling)
- [ ] Advanced/other drivers (video, SB16, RTC, Ethernet)
- [X] UEFI support
- [ ] ELF parsing
- [ ] System calls
- [ ] GUI
- [ ] POSIX and ANSI specification compatibility
