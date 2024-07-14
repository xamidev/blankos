# BlankOS

Rewritten monolithic version of Blank OS for the x86 processor architecture. Features a framebuffer, serial port driver, GDT, IDT. The OS relies on an old, legacy version of GRUB as the bootloader (eltorito). This *should* be GRUB 2 compatible. Emulation was tested on Arch Linux 6.9.7-arch1-1. The long-term goal of this OS is to be capable of running user programs and having its own complete kernel C library so that users can write their own C programs to be ran using the kernel.

Next steps for this project will be:
- ISRs and making the PIC work
- Keyboard driver
- User programs
- Shell
- Kernel libc
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

### ⚠️ Disclaimer

This is a hobbyist operating system kernel and it comes without any warranty whatsoever! It isn't capable of anything really.
