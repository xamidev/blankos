; Kernel loader assembly stub and multiboot2 header
; Author: xamidev
; Licensed under the Unlicense. See the repo below.
; https//github.com/xamidev/blankos

global loader

section .multiboot_header

align 8

; ASM macros

MAGIC_NUMBER      equ 0xe85250d6  	; multiboot2 magic 
FLAGS             equ 0x0	  		; 32-bit protected mode for i386
HEADER_LEN	  	  equ 44 	  		; Tags=2+2+4+4+4+4+2+2+4=28
CHECKSUM          equ -(MAGIC_NUMBER + FLAGS + HEADER_LEN)

; Multiboot 2 header, according to specification (16bytes)

  dd MAGIC_NUMBER		; dd = 4 bytes = 32bits = u32
  dd FLAGS			
  dd HEADER_LEN
  dd CHECKSUM

; Tags? (28bytes)

; Tag 1 : set graphics mode (only recommended, can be overriden by GRUB)

  dw 5			; 2
  dw 0			; 2
  dd 20			; 4
  dd 1920		; 4
  dd 1080		; 4
  dd 32			; 4

; End of tags

  dw 0			; 2
  ;dw 0			; 2
  dd 8			; 4

; End of Multiboot 2 header

section .text:

KERNEL_STACK_SIZE equ 4096
extern kmain

loader:
  	cli
  	push ebx
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

global idt_load
extern idtp

idt_load:
	lidt [idtp]
	ret

%macro ISR_NOERRCODE 1
	global isr%1
	isr%1:
		cli
		push byte 0
		push byte %1
		jmp isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
	global isr%1
	isr%1:
		cli
		push byte %1
		jmp isr_common_stub
%endmacro

ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE 8
ISR_NOERRCODE 9
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

extern fault_handler

isr_common_stub:
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov eax, esp
	push eax
	mov eax, fault_handler
	call eax
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8
	iret

%macro IRQ 2
	global irq%1
	irq%1:
		cli
		push byte 0
		push byte %2
		jmp irq_common_stub
%endmacro

IRQ	0,	32
IRQ	1,	33
IRQ	2,	34
IRQ	3,	35
IRQ	4,	36
IRQ	5,	37
IRQ	6,	38
IRQ	7,	39
IRQ	8,	40
IRQ	9,	41
IRQ	10,	42
IRQ	11,	43
IRQ	12,	44
IRQ	13,	45
IRQ	14,	46
IRQ	15,	47

extern irq_handler

irq_common_stub:
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov eax, esp
	push eax
	mov eax, irq_handler
	call eax
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8
	iret

section .bss
align 4 
kernel_stack:
  	resb KERNEL_STACK_SIZE
  	mov esp, kernel_stack + KERNEL_STACK_SIZE
