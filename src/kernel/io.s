; Raw CPU port I/O kernel module
; Author: xamidev
; Licensed under the Unlicense. See the repo below.
; https://github.com/xamidev/blankos

global outb

outb:
    mov al, [esp + 8]
    mov dx, [esp + 4]
    out dx, al
    ret

global inb

inb:
    mov dx, [esp + 4]
    in al, dx
    ret

global x86_div64_32

x86_div64_32:
    push ebp
    mov ebp, esp

    ; Arguments:
    ; [ebp + 8]  - lower 32 bits of dividend (uint32_t)
    ; [ebp + 12] - upper 32 bits of dividend (uint32_t)
    ; [ebp + 16] - divisor (uint32_t)
    ; [ebp + 20] - pointer to quotient (uint64_t*)
    ; [ebp + 24] - pointer to remainder (uint32_t*)

    mov eax, [ebp + 8]
    mov edx, [ebp + 12]

    mov ecx, [ebp + 16]

    div ecx
    mov esi, [ebp + 20]
    mov [esi], eax

    mov dword [esi + 4], 0

    mov esi, [ebp + 24]
    mov [esi], edx

    pop ebp
    ret