; asm_functions.asm
.386
.MODEL FLAT, C    ; ���������� ������� ������ ������ � ���������� C

.CODE
PUBLIC func    ; ������������ ������� ��� ������ �� C/C++

func PROC
    push ebp             ; ��������� ������� ���������
    mov ebp, esp         ; ������������� ����� ������� ���������
    ; �������� ���������:
    ; ������ �������� ��������� �� ������ [ebp+8]
    ; ������ �������� �� ������ [ebp+12]
    mov eax, [ebp+8]     ; ��������� ������ �������� � EAX
    imul eax, eax    ; ���������� ������ ��������
    mov ebx, eax
    imul ebx, [ebp+8]
    mov ecx, eax
    imul ecx, ebx
    ; x^2 - 4
    sub eax, 4
    ; 2 * (x^2-4)
    imul eax, 2
    ;2*(x^2-4) + x
    add eax, [ebp+8]
    ;x^5 + 2*(x^2-4)+x
    add eax, ecx
    div ebx
    pop ebp              ; ��������������� ������� ���������
    ret                  ; ������������ � ���������� �������
func ENDP

END
