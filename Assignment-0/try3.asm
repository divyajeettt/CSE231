global main
extern scanf
extern printf


section .data
	string times 255 db 0		; declare the string 
					; times 255 -> size of string -> 255 bytes
	scanFormat db "%s", 0	 	; format for scanf
	printFormat db "%s", 0x0a, 0	; format for printf


section .text

main:
					; rdi: destination index register
					; rsi: source index register
					; r: 64 bits, e: lower (least significant)  32 bits 

	push rbp			; push base pointer

	mov rdi, scanFormat 		; store address of 'format' in rdi		
	mov rsi, string 		; store address of 'string' in rdx
	mov rax, 0			
	call scanf

	mov rdi, printFormat
	mov rsi, string
	mov rax, 0
	call printf
	
	pop rbp				; pop base pointer
	ret				

	mov rax, 1			; set SysCall = sys_exit
	mov rbx, 0			; set exit_status to 0
	int 0x80			; raise the SysCall interrupt
