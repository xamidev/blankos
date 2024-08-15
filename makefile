CC = i386-elf-7.5.0-Linux-x86_64/bin/i386-elf-gcc
CFLAGS = -Wall -Wextra -Wno-builtin-declaration-mismatch -c -I src/
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
	wget https://newos.org/toolchains/i386-elf-7.5.0-Linux-x86_64.tar.xz
	tar xf i386-elf-7.5.0-Linux-x86_64.tar.xz

os.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	genisoimage -R                              \
							-b boot/grub/stage2_eltorito    \
							-no-emul-boot                   \
							-boot-load-size 4               \
							-A os                           \
							-input-charset utf8             \
							-quiet                          \
							-boot-info-table                \
							-o os.iso                       \
							iso

real: kernel.elf
	mkdir -p real/boot/grub
	cp kernel.elf real/boot/kernel.elf
	cp grub.cfg real/boot/grub/grub.cfg
	grub-mkrescue real -o blankos.iso

run: os.iso
	bochs -f bochsrc.txt -q 

clean:
	rm -rf $(OBJ_DIR) kernel.elf os.iso blankos.iso real

