bits 32                ; assembling for the 32-bit architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit            ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll ; exit is a function that ends the calling process, defined in msvcrt.dll
                       ; msvcrt.dll contains exit, printf, and all the other important C-runtime functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 1
    b db 2
    c db 2
    e dd 1
;(a*b*25+c*3)/(a+b)+e; a,b,c-byte; e-doubleword
; our code starts here
segment code use32 class=code
    start:
        ;doing the (a*b*25) 
        mov eax,0 
        mov ebx,0
        mov al, byte[a]
        mov bl,[b]
        imul eax,ebx
        imul eax,25
        
        ;moving eax in ebx then doing the c*3
        mov ebx,0
        mov ebx, eax
        mov eax,0
        mov al,byte[c]
        mov ECX, 0
        mov CX,3
        imul CX
        
        add eax, ebx
        
        ;did the (a+b)+e
        mov ebx,0
        mov bl,byte[a]
        add bl,byte[b]
        add ebx,dword[e]
       

       ;clearing EDX register in order to store the remaining of the divison 
        mov edx,0
        idiv ebx
            

        ; Exit the program
        push dword 0            
        call [exit]             