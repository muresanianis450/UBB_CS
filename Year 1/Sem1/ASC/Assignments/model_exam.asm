bits 32
global start

; declare external functions needed by our program
extern exit, fopen, fread, fclose, printf
import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    file_name db "model_exam.txt", 0   ; filename to be read
    access_mode db "r", 0       ; file access mode:
                                ; r - opens a file for reading. The file must exist.
    file_descriptor dd -1       ; variable to hold the file descriptor
    len equ 200               ; maximum number of characters to read
    text times (len+1) db 0     ; string to hold the text which is read from file
    nb_bytes db "%d",0
    format db "%s",0
    nl db 10,0                  ;new line`
    
    space_count dd 0
    upper_case_message db "%s",0
    upper_case_text times(len+1) db 0
; our code starts here
segment code use32 class=code
    start:
        ; call fopen() to create the file
        ; fopen() will return a file descriptor in the EAX or 0 in case of error
        ; eax = fopen(file_name, access_mode)
        push dword access_mode     
        push dword file_name
        call [fopen]
        add esp, 4*2                ; clean-up the stack

        mov [file_descriptor], eax  ; store the file descriptor returned by fopen

        ; check if fopen() has successfully created the file (EAX != 0)
        cmp eax, 0
        je final

        ; read the text from file using fread()
        ; after the fread() call, EAX will contain the number of chars we've read 
        ; eax = fread(text, 1, len, file_descriptor)
        push dword [file_descriptor]
        push dword len
        push dword 1
        push dword text        
        call [fread]
        add esp, 4*4

        ; display the number of chars we've read 
        ; printf(nb_bytes,eax)
        push dword EAX
        push dword nb_bytes
        call [printf]
        add esp, 4*3

        
        push nl ;new line
        call [printf]
        add esp, 4*1
            
        push nl ;new line
        call [printf]
        add esp, 4*1
        
      
        ;count spaces
      
        xor ecx, ecx
        xor esi, esi
        
        count_loop:
       
        cmp byte[text+esi],0
        je display_space_count
        cmp byte[text+esi] , ' '
        jne skip_space

        inc ecx    
        skip_space:
        inc esi
        jmp count_loop
       
        display_space_count:
        mov[space_count],ecx
       
       
        ;print space_count`
        push dword [space_count]
        push dword nb_bytes
        call [printf]
        add esp,4*2
      
      
      
        push nl ;new line
        call [printf]
        add esp, 4*1
        
        ;uppercase string
        xor esi, esi
        
        uppercase_loop:
        
        cmp byte[text+esi],0
        je display_uppercase_text
        cmp byte[text+esi], ' '
        je skip_space1
        
        mov al,[text+esi]
        sub al,0x20 ; i transform it into an uppercase
        mov [text+esi],al ;i overwrite the lowercase with the uppercase
        skip_space1:; if it's a space, i skip this process and just increment esi
        inc esi
        
        jmp uppercase_loop ; repeat the loop
        
        
        
        display_uppercase_text:
        push dword text
        push dword upper_case_message
        call [printf]
        add esp, 4*2
        
        
        
        ;push dword text
        ;push dword format
        ;call [printf]
        ;add esp, 4*2
        ; call fclose() to close the file
        ; fclose(file_descriptor)
        push dword [file_descriptor]
        call [fclose]
        add esp, 4

      final:

        ; exit(0)
        push dword 0
        call [exit]