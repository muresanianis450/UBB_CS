bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        


;A string containing n binary representations on 8 bits is given as a character string.
;Obtain the string containing the numbers corresponding to the given binary representations.
;Example:
;Given: '10100111b', '01100011b', '110b', '101011b', 0
;Obtain: 10100111b, 01100011b, 110b, 101011b
; 167, 92, 6,
; declare external functions needed by our program
extern exit,printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll

extern binary_conv
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    sir db '10100111b', '01100011b', '110b', '101011b' , 0
    len equ $-sir
    n db 4
    result resb len
    buffer resb 16
    output_format db "%s -> %d", 10, 0 

; our code starts here
segment code use32 class=code
    start:
    ;mov esi, sir  ; Pointer to the binary string
    ;mov edi, result   ; Pointer to the result buffer
    xor eax,eax
    xor ebx,ebx
    xor ecx,ecx
    mov cl, [n]
    mov esi, sir
    
    process_numbers:
    mov edi, buffer
    xor eax,eax
    xor ebx,ebx
    storing_b:
    mov al, [esi]
    inc esi
    cmp al, 'b'
    je st_end
        mov [edi], al
        inc edi
    jmp storing_b
    st_end:
    mov [edi], byte 0
    push esi
    push ecx
    ;push edi                 ; Pass the address for storing the result
    push buffer                 
    call binary_conv         ; Call the conversion subroutine
    add esp, 4             ; Clean up the stack
    mov [result] , eax
    pop ecx
    pop esi
    ; Display the result
    push esi
    push ecx
    push dword [result]       ; Push the decimal result
    push dword buffer      ; Push the binary string (current position)
    push output_format       ; Push the format string
    call [printf]              ; Print the result
    add esp, 4*3              ; Clean up the stack
    pop ecx
    pop esi
    ; Move to the next binary number
    loop process_numbers
   
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
