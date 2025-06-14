bits 32 
global start        

;Read numbers (in base 10) in a loop until the digit '0' is read from the keyboard. 
;Determine and display the smallest number from those that have been read.
;



; declare external functions needed by our program
extern exit
import exit msvcrt.dll
;a dd 0a344dh , 30h,11223344h, 46ab89ch
;b dd 'a', 'b', 'c', 0
a dd 2030h, 0A344dh
segment data use32 class=data

; our code starts herze
segment code use32 class=code
    start:
     
    mov eax, ebx
    push dword 0 
    call [exit]