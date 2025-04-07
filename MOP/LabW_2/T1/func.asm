; asm_functions.asm
.386
.MODEL FLAT, C    ; используем плоскую модель памяти и соглашение C

.CODE
PUBLIC func    ; экспортируем функцию для вызова из C/C++

func PROC
    push ebp             ; сохраняем базовый указатель
    mov ebp, esp         ; устанавливаем новый базовый указатель
    ; Получаем аргументы:
    ; Первый аргумент находится по адресу [ebp+8]
    ; Второй аргумент по адресу [ebp+12]
    mov eax, [ebp+8]     ; загружаем первый параметр в EAX
    imul eax, eax    ; прибавляем второй параметр
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
    pop ebp              ; восстанавливаем базовый указатель
    ret                  ; возвращаемся в вызывающую функцию
func ENDP

END
