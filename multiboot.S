BITS 32

SECTION .text
  global start
  extern kmain

ALIGN 4
multiboot_header:
  dd 1badb002h
  dd 2h
  dd -(1badb002h + 2h)

start:
  mov esp, stack.top

  push eax
  push ebx
  call kmain
  add esp, 8

  hlt
;end:
;  jmp end

SECTION .data

SECTION .bss
stack: resb 1000h
.top:

