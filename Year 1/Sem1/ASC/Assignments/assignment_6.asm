bits 32
global start
extern exit
import exit msvcrt.dll

;Being given two alphabetical ordered strings of characters, 
;s1 and s2, build using merge sort the ordered string of bytes that
;contain all characters from s1 and s2.

;
segment data use32 class=data
s1 db 'acegikm', 0      
ls1 equ $-s1            
s2 db 'bdfhjlnpq', 0    
ls2 equ $-s2            
result resb ls1 + ls2 + 1 

segment code use32 class=code
    start:
    ; Initialize source and destination pointers
    mov esi, s1         ; ESI points to the start of s1
    mov edi, result         ; EDI points to the start of s2
    mov ebx, s2     ; EBX points to the start of the result buffer

merge:
    lodsb               ;load the current char. from s1 to AL 
    cmp al, 0           ;check if i have any more characters
    je copy_remaining_s2 ;if i don't have any characters left we load just the left ones i have in s2

    mov ah, [ebx]       ;load the char from s2 to ah
    cmp ah, 0           ;same as s1
    je copy_remaining_s1

    ;compare the character from s1 to s2
    cmp al, ah
    jbe copy_from_s1    ; if s1<=s2 we move s1 into result
    jmp copy_from_s2    ; move s2 otherwise

copy_from_s1:
    stosb               ;store the character from al into result (EBX) and
                        ;increment              
    dec esi             ; undo the `lodsb` increment for s2
    jmp merge           ; continue merging
    
    
    ;same thing for s2
copy_from_s2:
    mov al, ah          
    stosb               
    inc ebx             
    dec esi             
    jmp merge           

copy_remaining_s1:
    lodsb               ; load the next char into AL 
    stosb               ; store it
    cmp al, 0           ; check if i have any characters left
    jne copy_remaining_s1 ; repeat until it's over

    ;same for s2
copy_remaining_s2:
    lodsb               
    stosb               
    cmp al, 0           
    jne copy_remaining_s2 

terminate:
    mov byte [ebx], 0   
    
    ; Exit program
    push dword 0
    call [exit]
