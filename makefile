CC = i386-elf-7.5.0-Linux-x86_64/bin/i386-elf-gcc
CFLAGS = -ffreestanding -g -Wall -Wextra -mno-sse -mno-mmx -mno-avx -march=i386 -c -I src/
LD = ld
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf
AR = i386-elf-7.5.0-Linux-x86_64/bin/i386-elf-ar

SRC_DIR = src
KERNEL_DIR = $(SRC_DIR)/kernel
LIBC_DIR = $(SRC_DIR)/libc
UTILS_DIR = $(SRC_DIR)/utils
DRIVERS_DIR = $(SRC_DIR)/drivers
PROGRAMS_DIR = $(SRC_DIR)/programs
INCLUDE_DIR = include
FONTS_DIR = $(INCLUDE_DIR)/fonts
OBJ_DIR = build

C_SOURCES = $(wildcard $(KERNEL_DIR)/*.c) $(wildcard $(LIBC_DIR)/*.c) $(wildcard $(UTILS_DIR)/*.c) $(wildcard $(DRIVERS_DIR)/*.c)
ASM_SOURCES = $(wildcard $(KERNEL_DIR)/*.s) $(wildcard $(LIBC_DIR)/*.s) $(wildcard $(UTILS_DIR)/*.s) $(wildcard $(DRIVERS_DIR)/*.s)
PROGRAM_SOURCES = $(wildcard $(PROGRAMS_DIR)/*.c)

OBJECTS = $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(C_SOURCES:.c=.o) $(ASM_SOURCES:.s=.o)) 
PROGRAM_OBJECTS = $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(PROGRAM_SOURCES:.c=.o))

TOOLCHAIN_SRC = https://newos.org/toolchains/i386-elf-7.5.0-Linux-x86_64.tar.xz
TOOLCHAIN_FILE = i386-elf-7.5.0-Linux-x86_64.tar.xz

FONT_OBJ = $(OBJ_DIR)/fonts/UniCyr_8x16.o
FONT_SRC = $(FONTS_DIR)/UniCyr_8x16.psf

all: $(OBJ_DIR) lib kernel.elf programs

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/kernel $(OBJ_DIR)/libc $(OBJ_DIR)/utils $(OBJ_DIR)/drivers $(OBJ_DIR)/fonts $(OBJ_DIR)/programs

lib: $(OBJECTS) $(FONT_OBJ)
	$(AR) rcs $(OBJ_DIR)/lib.a $(OBJECTS) $(FONT_OBJ)
	
kernel.elf: $(OBJECTS) $(FONT_OBJ)
	$(LD) $(LDFLAGS) $(OBJECTS) $(FONT_OBJ) -o kernel.elf

programs: $(PROGRAM_OBJECTS)
	@mkdir -p $(SRC_DIR)/initrd
	@for prog in $(PROGRAM_OBJECTS); do \
		base=$$(basename $$prog .o); \
		$(LD) -melf_i386 -T program.ld $$prog $(OBJ_DIR)/lib.a -o $(SRC_DIR)/initrd/$$base.bin; \
	done

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	$(AS) $(ASFLAGS) $< -o $@

$(FONT_OBJ): $(FONT_SRC) | $(OBJ_DIR)/fonts
	objcopy -O elf32-i386 -B i386 -I binary $(FONT_SRC) $(FONT_OBJ)

$(OBJ_DIR)/fonts:
	mkdir -p $(OBJ_DIR)/fonts

toolchain:
	wget $(TOOLCHAIN_SRC)
	tar xf $(TOOLCHAIN_FILE)

iso: kernel.elf initrd
	cp kernel.elf iso/boot/kernel.elf
	cp grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue iso -o blankos.iso	

initrd:
	mkdir -p iso/boot/grub
	tar -cf $(OBJ_DIR)/initrd.tar -C $(SRC_DIR)/initrd .
	cp $(OBJ_DIR)/initrd.tar iso/boot

run: iso
	qemu-system-i386 -drive file=blankos.iso,format=raw

debug:
	./debug.sh

clean:
	rm -rf $(OBJ_DIR) kernel.elf blankos.iso $(TOOLCHAIN_FILE) $(SRC_DIR)/initrd/*.bin

