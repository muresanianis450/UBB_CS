bits 32 
global start        

;Read numbers (in base 10) in a loop until the digit '0' is read from the keyboard. 
;Determine and display the smallest number from those that have been read.
;


; declare external functions needed by our program
extern exit, printf, scanf

import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data
n dd 0
maxim dd -2147483648
message db "The maximum value is %d", 0 
format db "%d",0
message_0 db "No numbers added before the final 0",0
; our code starts here
segment code use32 class=code
    start:
    
    mov ebx,-2147483648 ;smallest 32-bit integer
    mov eax,0
;firstly, we take the first number number and see if it's equal to zero, in this case we jump to zero_case:
        push dword n
        push dword format
        call [scanf]
        add esp, 4*2 ;clean the stack
        
        mov eax,[n]
        cmp eax,0
        je zero_case
        
    start_loop:
    
    ;even though for the first exemple we verify if it's 0 twice, for the rest of the elements it will not be the case
    ;load the value of n into eax   
        mov eax, [n]
        cmp eax, 0
        je endFor ;Exit the loop if the input is 0
        
    ;compare and update the maximul value
    
        cmp ebx,eax ;if maxim is smaller than my new number, ebx-eax (not stored)
            JGE next;if max is greater or equal than my number
        mov ebx, eax;update the maximul value

            next:;we read the next one
            push dword n
            push dword format
            call [scanf]
            add esp, 4*2 ;clean the stack
            loop start_loop;loop it again
  
 
zero_case:
    mov ebx,0
    mov [maxim],ebx ; if the first number is 0 then we reset ebx to 0 
    push dword message_0
    call [printf]
    add esp , 4
    push dword 0
    call [exit]

endFor:
    mov [maxim], ebx ; if the loop ended, we move our maxim which was stored into ebx,back into maxim and display it with a message
    push dword[maxim]
    push dword message
    call [printf]
    add esp, 4*2
    push dword 0
    call    [exit]  