bits 32                         
segment code use32 public code
global binary_conv

factorial:
	mov eax, 1
	mov ecx, [esp + 4]
	
	repeat: 
		mul ecx
	loop repeat
	ret 4 ; in this case, 4 represents the number of bytes that need to be cleared from the stack (the parameter of the function)

;int binary_conv(str *buffer)
;   return eax
binary_conv:
    ; Input: 
    ;   [esp+4] -> Pointer to the binary string (null-terminated, ends with 'b')
    ;   [esp+8] -> Pointer to the output buffer
    ; Output: eax has the number in dec
    ; Clobbered: eax, ebx, ecx, edx, esi, edi

    mov esi, [esp+4]     ; Load pointer to the binary string
    ;mov edi, [esp+8]     ; Load pointer to the output buffer
    xor eax, eax         ; Clear result (EAX)
    xor edx, edx
    mov ecx, 8        ; Clear bit counter but didnt actually need it

binary_loop:
    mov dl, [esi]        ; Load a byte from the string
    cmp dl, 0            ; Check for null terminator
    je finish            ; If null terminator, exit loop

    cmp dl, 'b'          ; Check for end-of-binary marker ('b')
    je finish            ; If found, exit loop

    cmp dl, '0'          ; Check if character is '0'
    jl skip              ; If less, skip (invalid character)
    cmp dl, '1'          ; Check if character is '1'
    jg skip              ; If greater, skip (invalid character)

    ; Process valid binary character
    inc ebx              ; Increment bit counter
    sub dl, '0'          ; Convert ASCII to binary (0 or 1)
    shl eax, 1           ; Shift result left by 1 (multiply by 2)
    or eax, edx          ; Add the current bit to the result

    skip:
    inc esi              ; Move to the next character
    loop binary_loop      ; Repeat loop

finish:
    ;mov [edi], eax       ; Store the result at the output buffer
    ret                ; Return to the caller
    ;atomic operations
