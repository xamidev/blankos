CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -c -I src/
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf
SRC_DIR = src
OBJ_DIR = build

C_SOURCES = $(wildcard $(SRC_DIR)/*.c)
ASM_SOURCES = $(wildcard $(SRC_DIR)/*.s)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(C_SOURCES)) \
          $(patsubst $(SRC_DIR)/%.s, $(OBJ_DIR)/%.o, $(ASM_SOURCES))

all: $(OBJ_DIR) kernel.elf

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	$(AS) $(ASFLAGS) $< -o $@

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

run: os.iso
	bochs -f bochsrc.txt -q 

clean:
	rm -rf $(OBJ_DIR) *.o kernel.elf os.iso
