bits 32                global start        
extern exit            
import exit msvcrt.dll                        

segment data use32 class=data


;A character string S is given. Obtain the string D that contains all capital letters of the string S.
;Example:
;S: 'a', 'A', 'b', 'B', '2', '%', 'x', 'M'
;D: 'A', 'B', 'M'

S dw 'a', 'A', 'b', 'B', '2', '%', 'x', 'M'
D dw 0

; our code starts here
segment code use32 class=code
    start:
       
       mov ecx, lenS
       mov ESI, 0
       mov EBX, 0
       jecxz end_loop
       
       start_loop:
       
       
       
       
       
       end_loop:
       
        ; Exit the program
        push dword 0            
        call [exit]             