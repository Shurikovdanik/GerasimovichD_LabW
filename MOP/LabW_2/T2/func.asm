.386
.MODEL FLAT, C  

.CODE
PUBLIC SumLastDigits

SumLastDigits PROC
    push ebp
    mov ebp, esp
    push ebx        
    push esi       

    mov eax, [ebp+8]    
    mov ecx, [ebp+12]   
    xor ebx, ebx        
    mov esi, 10         

SumLoop:
    cmp ecx, 0        
    je LDone
    xor edx, edx      
    div esi           
                      
    add ebx, edx     
    dec ecx         
    jmp SumLoop       

LDone:
    mov eax, ebx      
    pop esi           
    pop ebx
    pop ebp
    ret
SumLastDigits ENDP

END
