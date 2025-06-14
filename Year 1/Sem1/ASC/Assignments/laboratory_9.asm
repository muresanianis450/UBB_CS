bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fprintf, fread, printf, scanf            ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fread msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    inp_handle dd 0
    access_mode_in db "r", 0
    inp_file times 101 db 0
    oup_handle dd 0 
    acces_mode_out db "w", 0
    oup_file times 101 db 0
    format_oup db "%s", 0
    s times 11 db 0
    msg_one db "Enter the name of the input file: ", 0
    msg_two db "Enter the name of the output file: ", 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
        push msg_one
        push format_oup
        call [printf]
        add esp, 4 * 2
        
        push inp_file
        push format_oup
        call [scanf]
        add esp, 4 * 2
        
        push msg_two
        push format_oup
        call [printf]
        add esp, 4 * 2
        
        push oup_file
        push format_oup
        call [scanf]
        add esp, 4 * 2
        
        push access_mode_in
        push inp_file
        call [fopen]
        mov dword [inp_handle], eax
        add esp, 4 * 2
        
        push acces_mode_out
        push oup_file 
        call [fopen]
        mov dword [oup_handle], eax
        add esp, 4 * 2
        
        mov ecx, 101
        repeat:
        
            push dword [inp_handle]
            push dword 10
            push dword 1
            push s
            call [fread]
            add esp, 4 * 4
            mov [s+eax], dword 0
            
            cmp eax, dword 0
            je outside
            
            push s
            push format_oup
            push dword [oup_handle]
            call [fprintf]
            add esp, 4 * 2
        jmp repeat

        outside:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program