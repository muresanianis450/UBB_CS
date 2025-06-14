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
la equ $-a 
b db 4,5,-5,-7,-6,-2,1
lb equ $-b

r resb la
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
             cmp al, bl ; we compare the element with 0 
             JGE pos_end ; if the CF=1 then it means  0-AL is negative -> al >0 
             mov bl, 1
             test al,bl
             jnz pos_end
             mov[r+edx], al ; we found one negative element
             inc edx
             pos_end:
             inc esi; we go further
        loop repeta_a
        sf_a:
        
        mov ecx, lb ; we put the len of a in ecx for the first loop
        mov esi, 0  ; for the index of a and b
        jecxz sf_b ; if we don't have anything in a then we jump to the
        repeta_b:          
             mov al, [b+esi] ; we move one element in a
             mov bl, 0
             cmp al, bl ; we compare the element with 0 
             JGE pos_endb ; if the CF=1 then it means  0-AL is negative -> al >0 
             mov bl, 1
             test al,bl
             jnz pos_endb
             mov[r+edx], al ; we found one negative element
             inc edx
             pos_endb:
             inc esi; we go further
        loop repeta_b
        sf_b:
        
        
        
        
       push dword 0            
       call [exit]             