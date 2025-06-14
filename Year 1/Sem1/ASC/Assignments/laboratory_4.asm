bits 32                ; assembling for the 32-bit architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit            ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll ; exit is a function that ends the calling process, defined in msvcrt.dll
                       ; msvcrt.dll contains exit, printf, and all the other important C-runtime functions
bits 32                
global start        
import exit msvcrt.dll 
;PROBLEM

;Two byte strings A and B are given. Obtain the string R that contains only the even negative elements of the two strings.
;Example:
;A: 2, 1, 3, -3, -4, 2, -6
;B: 4, 5, -5, 7, -6, -2, 1
;R: -4, -6, -6, -2

a db 2,1, 3, -3, -4, 2, -6
b db 4,5,-5,-7,-6,-2,1

la equ $-a 
lb equ $-b

r times la+lb db 0
; our code starts here
segment code use32 class=code
    start:
        mov ecx, la ; we put the len of a in ecx for the first loop
        mov esi, 0  ; for the index of a and b
        mov edx,0 ; for the number of elements in r
        jecxz sf_a ; if we don't have anything in a then we jump to the next loop 
        repeta_a:
                       
             mov al, [a+esi] ; we move one element in a
             mov bl, 0
             test bl, al ; we compare the element with 0 
             JL positive_1 ; if the CF=1 then it means  0-AL is negative -> al >0 
             mov[r+edx], al ; we found one negative element
             inc edx
             positive_1:
             inc esi; we go further
        loop repeta_a
        sf_a:
        
        
        mov esi,0
        mov ecx, lb
        jecxz sf_b
        repeta_b:
            mov al,[b+esi] ;same thing here
            mov bl, 0
            test al, bl
            JL positive_2
            mov[r+edx], al
            inc ebx
            positive_2:
            inc esi
        loop repeta_b
        sf_b:
          
       push dword 0            
        call [exit]             