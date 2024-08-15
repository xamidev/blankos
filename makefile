CC = i386-elf-7.5.0-Linux-x86_64/bin/i386-elf-gcc
CFLAGS = -g -Wall -Wextra -Wno-builtin-declaration-mismatch -c -I src/
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

SRC_DIR = src
KERNEL_DIR = $(SRC_DIR)/kernel
LIBC_DIR = $(SRC_DIR)/libc
PROGRAMS_DIR = $(SRC_DIR)/programs
DRIVERS_DIR = $(SRC_DIR)/drivers
OBJ_DIR = build

C_SOURCES = $(wildcard $(KERNEL_DIR)/*.c) $(wildcard $(LIBC_DIR)/*.c) $(wildcard $(PROGRAMS_DIR)/*.c) $(wildcard $(DRIVERS_DIR)/*.c)
ASM_SOURCES = $(wildcard $(KERNEL_DIR)/*.s) $(wildcard $(LIBC_DIR)/*.s) $(wildcard $(PROGRAMS_DIR)/*.s) $(wildcard $(DRIVERS_DIR)/*.s)

OBJECTS = $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(C_SOURCES:.c=.o) $(ASM_SOURCES:.s=.o))

TOOLCHAIN_SRC = https://newos.org/toolchains/i386-elf-7.5.0-Linux-x86_64.tar.xz
TOOLCHAIN_FILE = i386-elf-7.5.0-Linux-x86_64.tar.xz

all: $(OBJ_DIR) kernel.elf

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/kernel $(OBJ_DIR)/libc $(OBJ_DIR)/programs $(OBJ_DIR)/drivers

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	$(AS) $(ASFLAGS) $< -o $@

toolchain:
	wget $(TOOLCHAIN_SRC)
	tar xf $(TOOLCHAIN_FILE)

blankos-fat.img:
	sudo ./setup.sh

run: blankos-fat.img
	qemu-system-i386 -drive file=blankos-fat.img,format=raw

debug:
	qemu-system-i386 -s -S -drive file=blankos-fat.img,format=raw

clean:
	rm -rf $(OBJ_DIR) kernel.elf blankos-fat.img $(TOOLCHAIN_FILE)
