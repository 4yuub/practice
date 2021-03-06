; compile with "nasm -f elf *.asm; ld -m elf_i386 -s -o demo *.o"
global _start

section .text:

_start:
	mov eax, 0x4
	mov ebx, 1
	mov ecx, message
	mov edx, len
	int 0x80

	mov eax, 1
	mov ebx, 0
	int 0x80

section .data:
	message: db "Hello world!", 0xa
	len equ $-message
