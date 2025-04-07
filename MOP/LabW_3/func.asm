.386
.MODEL FLAT, C
EXTERN printf:PROC       ; ������� �������� ������� printf �� CRT

.DATA
; ������ ������ � ��������� ������ (CR/LF) � ����������� 0 (null)
fmtStr db "2*%d + 3*%d = 50", 13, 10, 0

.CODE
PUBLIC FindSolutions
;---------------------------------------------------------------------------------
; FindSolutions PROC
;   ���������� ����������� x (�� 1 �� 24). ��� ������� x:
;     - ��������� temp = 50 - 2*x.
;     - ���� temp ������� �� 3 (������� = 0), �� y = temp/3 � �������.
;     - ������� ������: "2*x + 3*y = 50"
;     - ����������� ������� �������.
;   � ����� ���������� ���������� ��������� ������� � �������� EAX.
;   ������� ���������� �� ���������� C (__cdecl).
;---------------------------------------------------------------------------------
FindSolutions PROC
    push    ebp
    mov     ebp, esp
    sub     esp, 4             ; �������� 4 ����� ��� ��������� ���������� count
    mov     dword ptr [ebp-4], 0  ; count = 0

    ; ��������� �����-���� �������� (EBX, ESI, EDI)
    push    ebx
    push    esi
    push    edi

    mov     ecx, 1            

Loop_Start:
    cmp     ecx, 25           ; x < 25 (��� ��� 50 - 2*x > 0 ��� x <= 24)
    jge     Loop_End          

    ; ���������: 50 - 2*x
    mov     eax, 50           
    mov     esi, ecx          
    shl     esi, 1            
    sub     eax, esi          
    
    ; ���������, ������� �� (50-2*x) �� 3: ���� ��, �� y = (50-2*x)/3
    mov     edx, 0           
    mov     esi, 3            
    div     esi              
    cmp     edx, 0            ; �������� �������
    jne     NoSolution        ; ���� �� �������

    ; ���� �������, �� ������� �������:
    mov     edi, eax         ; ��������� y � EDI
    mov ebx, ecx
    push    edi              
    push    ecx              
    push    offset fmtStr    ;��������� �� ��������������� ������
    call    printf
    add     esp, 12
    mov ecx, ebx

    mov     eax, dword ptr [ebp-4]
    inc     eax
    mov     dword ptr [ebp-4], eax
NoSolution:

    inc     ecx            
    jmp     Loop_Start

Loop_End:
    ; ���������� ����� ���������� ������� � EAX
    mov     eax, dword ptr [ebp-4]

    pop     edi
    pop     esi
    pop     ebx
    mov     esp, ebp
    pop     ebp
    ret
FindSolutions ENDP

END
