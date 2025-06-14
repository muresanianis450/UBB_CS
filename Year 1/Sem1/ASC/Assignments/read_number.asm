bits 32
global start
;->Numele de fisier
;-> Un caracter special
;->Nr p ( pe pozitia p a fiecarui cuvant)

extern exit , fopen, fclose, fread,printf,scanf
import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll


segment data use32 class=data

x dw 256h
segment code use32 class=code

start:
    
    
    
   push dword 0
    call [exit]