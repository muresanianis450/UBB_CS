bits 32
global start

extern exit, fopen, fclose, fread, printf, fprintf
import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
import fprintf msvcrt.dll

segment data use32 class=data
input db "input.txt", 0
output db "output.txt", 0
len equ 100

access_mode_read db "r", 0
access_mode_write db "w", 0

string times len db 0
person times len db 0
length dd 0
number db 0
future_number dd 0
gender db "M", 0 ; Default gender is male

format_decimal db "%d", 0
format_string db "%s", 0

input_file_descriptor dd -1
output_file_descriptor dd -1
nl db 10, 0 ; Newline character

segment code use32 class=code

start:
    ; Open the input file in read mode
    push dword access_mode_read
    push dword input
    call [fopen]
    cmp eax, 0
    je no_existing_file
    mov [input_file_descriptor], eax

    ; Read the text from the input file
    push dword [input_file_descriptor]
    push dword len
    push dword 1
    push dword string
    call [fread]
    add esp, 4*4

    mov [length], eax ; Store the number of characters read

    ; Add null-terminator to the string
    mov byte [string + eax], 0

    ; Extract the name (first word) from the string
    mov esi, string       ; Source pointer
    mov edi, person       ; Destination pointer
repeat_name:
    mov al, [esi]
    cmp al, " "           ; Check for space
    je end_name
    cmp al, 0             ; Check for end of string
    je end_name
    mov [edi], al
    inc esi
    inc edi
    jmp repeat_name
end_name:
    mov byte [edi], 0     ; Null-terminate the name

    ; Determine gender based on the last character of the name
    dec edi               ; Point to the last character of the name
    mov al, [edi]
    cmp al, 'a'
    jne male
    mov byte [gender], 'F' ; If the last character is 'a', set gender to Female
male:

    ; Extract the number (N) from the string
    add esi, 5            ; Skip " has "
    mov al, [esi]
    sub al, '0'           ; Convert ASCII to integer
    movzx eax, al
    mov [number], eax

    ; Calculate future number (N + 10)
    mov eax, [number]
    add eax, 10
    mov [future_number], eax

    ; Open the output file in write mode
    push dword access_mode_write
    push dword output
    call [fopen]
    cmp eax, 0
    je no_existing_file
    mov [output_file_descriptor], eax

    ; Write the length of the text to the output file
    push dword [length]
    push dword format_decimal
    push dword [output_file_descriptor]
    call [fprintf]
    add esp, 4*3

    ; Write a newline
    push dword nl
    push dword [output_file_descriptor]
    call [fprintf]
    add esp, 4*2

    ; Write the extracted name to the output file
    push dword person
    push dword format_string
    push dword [output_file_descriptor]
    call [fprintf]
    add esp, 4*3

    ; Write a newline
    push dword nl
    push dword [output_file_descriptor]
    call [fprintf]
    add esp, 4*2

    ; Write the future number (N + 10) to the output file
    push dword [future_number]
    push dword format_decimal
    push dword [output_file_descriptor]
    call [fprintf]
    add esp, 4*3

    ; Write a newline
    push dword nl
    push dword [output_file_descriptor]
    call [fprintf]
    add esp, 4*2

    ; Write the gender to the output file
    push dword gender
    push dword format_string
    push dword [output_file_descriptor]
    call [fprintf]
    add esp, 4*3

    ; Write a newline
    push dword nl
    push dword [output_file_descriptor]
    call [fprintf]
    add esp, 4*2

    ; Close the files
    push dword [input_file_descriptor]
    call [fclose]
    push dword [output_file_descriptor]
    call [fclose]

no_existing_file:
    push dword 0
    call [exit]
