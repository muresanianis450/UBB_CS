bits 32                ; assembling for the 32-bit architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit            ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll ; exit is a function that ends the calling process, defined in msvcrt.dll
                       ; msvcrt.dll contains exit, printf, and all the other important C-runtime functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data


; PROBLEM

;Two byte string S1 and S2 are given, having the same length. Obtain the string D by intercalating the elements of the two strings.
;Example:
;S1: 1, 3, 5, 7
;S2: 2, 6, 9, 4
;D: 1, 2, 3, 6, 5, 9, 7, 4

s1 dw '1','3','5','7'
s2 dw '2','4','6','8'
D dd 0

; our code starts here
segment code use32 class=code
    start:
       mov ESI, 0
       mov ECX, lens1+lens2
       mov EBX,0
       jecxz end_loop
;use AL AS INTERMIDIATE I CANNOT MOVE BETWEEN TWO MEMORY ADRESSES 
       repeat_lable:
       mov [D+EBX] , [s1+ESI]
       inc EBX
       mov [D+EBX], [s2+ESI]
       inc EBX
       inc ESI
       
       end_loop:
       
        ; Exit the program
        push dword 0            
        call [exit]             