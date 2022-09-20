global main
extern scanf
extern printf


section .data
	string times 255 db 0		; declare the string 
					; times 255 -> size of string -> 255 bytes

	num dd 0			; declare int pointer
	scanFormat db "%d %s", 0	; format for scanf
	printFormat db "%d %s", 0x0a, 0	; format for printf (added newline at the end)


section .text

main:
					; lea: load effective address
					; rdi: destination index register
					; rsi: source index register
					; r: 64 bits, e: lower (least significant) 32 bits 

	push rbp			; push base pointer

	lea rdi, [scanFormat]		; load format for scanf in rdi 
	lea rsi, [num]			; load address of 'num' in rsi
	lea rdx, [string]		; load address of 'string' in rdx
	mov rax, 0			; rax = 0 when no float args are given		
	call scanf

	lea rdi, [printFormat]		; load format for printf in rdi
	mov rsi, [num]			; move value of 'num' to rsi
	mov rdx, string			; move value of s-pointer to rdx
	mov rax, 0			; rax = 0 when no float args are given
	call printf
	
	pop rbp				; pop base pointer
	ret				; return

	mov rax, 1			; set SysCall = sys_exit
	mov rbx, 0			; set exit_status to 0
	int 0x80			; raise the SysCall interrupt
