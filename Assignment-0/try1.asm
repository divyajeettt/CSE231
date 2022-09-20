global main
extern scanf
extern printf

default rel

section .data
	string times 255 db 0		; declare the string 
					; times 255 -> size of string -> 255 bytes
	format db "%s", 0		; format

section .text

main:					; lea: load effective address
	push rbp

	lea rdi, [format]		; store address of 'format' in rdi		
	lea rsi, [string] 		; store address of 'string' in rdx

	mov rax, 0
	call scanf
	
	pop rbp

;	mov eax, 1			; set SysCall = sys_exit
;	mov ebx, 0			; set exit_status to 0
;	int 0x80			; raise the SysCall interrupt

	ret
