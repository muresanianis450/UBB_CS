bits 32                ; assembling for the 32-bit architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit            ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll ; exit is a function that ends the calling process, defined in msvcrt.dll
                       ; msvcrt.dll contains exit, printf, and all the other important C-runtime functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data

;Given an array A of words, build two arrays of bytes:  
;- array B1 contains as elements the higher part of the words from A
;- array B2 contains as elements the lower part of the words from A

A dw ox1234, ox5678, ox9ABC, oxDEF0
L equ ($-A)/2
B1 times L db 0
B2 times L db 0
; our code starts here
segment code use32 class=code
    start:
       mov ecx, count 
       
       ;load the adress of the array into ESI and EDI
       lea esi, [A]
       lea edi, [B1]
       
       loop_start:
            ;store higher part of a into AX
            lodsw
            mov [edi],ah
            inc edi
            ;load adress of B2 and store lower part
            lea edi,[B2]
            mov [edi], al
       
       
       