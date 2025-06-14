;Laboratory 8 
;Text File Operations

;A file name (defined in data segment) is given. 
;Create a file with the given name;
; then read words from the keyboard until character '$' is read from 
;the keyboard. Write only the words that contain at least one digit to file.




bits 32 
global start   

; declare external functions needed by our program     
extern exit, fprintf, fscanf, fopen, fclose, printf

import exit msvcrt.dll
import fprintf msvcrt.dll
import fscanf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

;Read numbers (in base 10) in a loop until the digit '0' is read from the keyboard. 
;Determine and display the smallest number from those that have been read.
;
segment data use32 class=data
file_name db "exercitiu9.txt",0
access_mode db "r",0 ; this file will only be used for reading
file_descriptor_ex9 dd -1 
len equ 100
name_ex9 times len db 0 ; string to hold the text which is read from assignment_9

segment code use32 class=code
    start:
    
    push dword access_mode
    push dword file_name
    call [fopen]
   `
    
    
    push dword[0]
    call [exit]

