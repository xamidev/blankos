# BlankOS

Rewritten monolithic version of Blank OS for the x86 processor architecture. Features a framebuffer, serial port driver, GDT, IDT. The OS relies on an old, legacy version of GRUB as the bootloader (eltorito). This *should* be GRUB 2 compatible. Emulation was tested on Arch Linux 6.9.7-arch1-1. The long-term goal of this OS is to be capable of running user programs and having its own complete kernel C library so that users can write their own C programs and expand the system!

Next steps for this project will be:
- User programs
- Completing the kernel libc
- Filesystem support

## Usage

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

## Building and running

```
git clone https://github.com/xamidev/blankos
make
make run
```

This will start a new Bochs debugger instance. To proceed with the kernel execution, you will have to type `c` in the shell spawning Bochs. Serial output will be saved under the `com1.out` file, this way you can debug the kernel by viewing its log messages. To quit, type `q`. Feel free to open issues or pull requests.

## Running on real hardware

To run the OS on real hardware, you'll first need to have a BIOS-compatible computer. Some of the new laptops with graphical "BIOSes" only support UEFI now. So make sure to get a computer that can boot into BIOS mode, **not UEFI mode**. Then, switch the boot mode to "Legacy" in your BIOS utility.

Then, use the Makefile target `real` to build a "real"-capable ISO disk image. The image will have GRUB2 installed on it, using the `grub-mkrescue` utility (make sure to install it before) which is dependent on `xorriso` (install it too).

Once the ISO file is generated, you can write it on a disk using this command:

```
sudo dd bs=4M if=blankos.iso of=/dev/sdX status=progress oflag=sync
```

Replace `sdX` with your USB drive name (you can find it by doing `sudo fdisk -l`).
Tada! You now have a working BlankOS USB stick. Go ahead and try it out!

## Post-install guides

Two documents are available to help you understand the project better. One is the User's Manual, labelled `USERS.md`, and the other one is the Developer's Manual, labelled `DEVELOPERS.md`. They are full of useful resources around Blank OS.

### ⚠️ Disclaimer

This is a hobbyist operating system kernel and it comes without any warranty whatsoever! It isn't capable of anything really. Feedback and contributions are highly appreciated!
