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
  mov eax, [bp+8]
  mov ecx, [bp+12]
  xor edx, edx
  div ecx

  mov bx, [bp+16]
  mov [bx+4], eax

  mov eax, [bp+4]
  div ecx

  mov [bx], eax
  mov bx, [bp+18]
  mov [bx], edx

  ret
