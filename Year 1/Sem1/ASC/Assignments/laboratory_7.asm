; The following program should read a number and print the message together with the number on the screen.
bits 32
global start        

; declaring extern functions used in the program
extern exit, printf, scanf            
import exit msvcrt.dll     
import printf msvcrt.dll     ; indicating to the assembler that the printf fct can be found in the msvcrt.dll library
import scanf msvcrt.dll      ; similar for scanf
                          
segment  data use32 class=data
	a db 0       
    b db 0
    result db 0
	message  db "Numarul citit este n= %d", 0  
	format  db "%d", 0  ; %d <=> a decimal number (base 10)
    
segment  code use32 class=code
    start:
        push byte a
        push byte format 
        call scanf
        add esp, 4*2
        
        push  dword 0     ; push the parameter for exit on the stack
        call  [exit]       ; call exit