global loader

MAGIC_NUMBER      equ 0x1BADB002   ; multiboot magic 
FLAGS             equ 0x0 
CHECKSUM          equ -MAGIC_NUMBER
KERNEL_STACK_SIZE equ 4096

section .text:
align 4
  dd MAGIC_NUMBER
  dd FLAGS
  dd CHECKSUM

extern kmain

loader:
  cli
  ; mov eax, 0xCAFEBABE
  push dword 42
  call kmain

.loop:
  jmp .loop

global gdt_flush
extern gp

gdt_flush:
	lgdt [gp]
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:flush2

flush2:
	ret

section .bss
align 4 
kernel_stack:
  resb KERNEL_STACK_SIZE
  mov esp, kernel_stack + KERNEL_STACK_SIZE
