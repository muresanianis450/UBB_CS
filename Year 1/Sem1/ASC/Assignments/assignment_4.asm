
bits 32 
global start
extern exit
import exit msvcrt.dll

segment data use32 class=data
	a10 db 256, -255
    a11 dw 256h-256
    a12 dw 256-256h
    a13 dw -256
    a14 dw -256h
    a15 db 2,5,6,25,6,56
    
    
segment code use32 class=code
    start:
    mov eax, 0
    mov ebx, 0
    mov ah, 129
    mov bh, 9Fh
    add ah,bh
    
    call [exit]