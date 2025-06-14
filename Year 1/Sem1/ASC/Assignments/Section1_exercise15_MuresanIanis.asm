bits 32                ; assembling for the 32-bit architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit            ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll ; exit is a function that ends the calling process, defined in msvcrt.dll
                       ; msvcrt.dll contains exit, printf, and all the other important C-runtime functions

why is it saying "the targed does not exist"

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 2
    b db 2
; our code starts here
segment code use32 class=code
    start:
        mov al, 0 
        mov al,a 
        add al,b

        ; Exit the program
        push dword 0            
        call [exit]             