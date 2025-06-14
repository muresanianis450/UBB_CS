bits 32
global start
;->Numele de fisier
;-> Un caracter special
;->Nr p ( pe pozitia p a fiecarui cuvant)


extern exit , fopen, fclose, fread,printf,scanf,fprintf
import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll
import fprintf msvcrt.dll

segment data use32 class=data
   
   message_1 db "Numele fisierului= ",0
   message_2 db "Caracterul special= " , 0
   message_3 db "Numar p = " , 0
   nl db 10,0
   
   
   format_text db "%s" , 0
   format_decimal db "%d", 0 
   
   file_name times 100 db 0 
   file_descriptor dd -1
   char db 0
   position dd 0
  
   access_mode_read db "r",0
   access_mode_write db "w",0
   len equ 100
  text1 times len db 0
  text2 times len db 0
   
   
segment code use32 class=code
   start:
   ;Read the file_name
   push dword message_1
   call [printf]
   add esp, 4

   
   push dword file_name
   push dword format_text
   call [scanf]
   add esp,4*2
   
   push nl
   call [printf]
   add esp,4
    
    ;push dword file_name
    ;push dword format_text
    ;call [printf]
    ;add esp,4
    
   ;Read the special character
   push dword message_2
   call [printf]
   add esp, 4
   
   
   push dword char
   push dword format_text
   call [scanf]
   add esp,4*2
   
  
   
   push nl 
   call [printf]
   add esp , 4
   
   
   ;Read the position
   push dword message_3
   call [printf]
   add esp, 4
   
   push dword position
   push dword format_decimal
   call [scanf]
   add esp,4*2

   
  
  xor eax, eax
 
 ;Open the file
  push dword access_mode_read
  push dword file_name
  call [fopen]
  add esp, 4*2
  mov [file_descriptor],eax
  
  
  cmp eax, 0
  je final
  
  
  
  
  push dword [file_descriptor]
  push dword len
  push dword 1
  push dword text1
  call [fread]
  add esp, 4*4
  
  
  
   mov ecx, eax             ; Set loop counter to the number of characters read
   mov esi, 0               ; Source index
   mov edi, 0               ; Word position index
   xor ebx, ebx             ; Destination index (for text2)

outer_loop:
   cmp ecx, 0               ; Check if there are characters left to process
   je final_loop

   mov al, [text1 + esi]    ; Load the current character

   cmp al, " "              ; Check if it's a space
   je reset_word_position

   cmp edi, [position]      ; Check if the current word position matches
   jne copy_character

   ; Insert the special character
   mov al, byte [char]
   mov [text2 + ebx], al
   inc ebx                  ; Increment destination index
   inc esi                  ; Increment source index
   inc edi                  ; Increment word position
   dec ecx                  ; Decrement loop counter
   jmp outer_loop

copy_character:
   mov [text2 + ebx], al    ; Copy the character
   inc ebx                  ; Increment destination index
   inc esi                  ; Increment source index
   inc edi                  ; Increment word position
   dec ecx                  ; Decrement loop counter
   jmp outer_loop

reset_word_position:
   mov [text2 + ebx], al    ; Copy the space character
   inc ebx                  ; Increment destination index
   inc esi                  ; Increment source index
   mov edi, 0               ; Reset word position
   dec ecx                  ; Decrement loop counter
   jmp outer_loop

final_loop:
   ; Null-terminate text2
   mov byte [text2 + ebx], 0

   push access_mode_write
   push dword file_name
   call [fopen]
   add esp,4*2
   
   mov[file_descriptor],eax
 
   cmp eax,0
   je final
   
   push dword text2
   push dword [file_descriptor]
   call[fprintf]
   add esp,4*2
   
   
   ; Print the modified text
   push dword text2
   push dword format_text
   call [printf]
   add esp, 4*2

   ; Close the file
   push dword [file_descriptor]
   call [fclose]

final:
   push dword 0
   call [exit]