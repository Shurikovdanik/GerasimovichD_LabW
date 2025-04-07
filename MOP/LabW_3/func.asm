.386
.MODEL FLAT, C
EXTERN printf:PROC       ; внешний прототип функции printf из CRT

.DATA
; Формат вывода с переходом строки (CR/LF) и завершающим 0 (null)
fmtStr db "2*%d + 3*%d = 50", 13, 10, 0

.CODE
PUBLIC FindSolutions
;---------------------------------------------------------------------------------
; FindSolutions PROC
;   Перебирает натуральные x (от 1 до 24). Для каждого x:
;     - Вычисляет temp = 50 - 2*x.
;     - Если temp делится на 3 (остаток = 0), то y = temp/3 – решение.
;     - Выводит строку: "2*x + 3*y = 50"
;     - Увеличивает счётчик решений.
;   В конце возвращает количество найденных решений в регистре EAX.
;   Функция вызывается по соглашению C (__cdecl).
;---------------------------------------------------------------------------------
FindSolutions PROC
    push    ebp
    mov     ebp, esp
    sub     esp, 4             ; выделяем 4 байта для локальной переменной count
    mov     dword ptr [ebp-4], 0  ; count = 0

    ; Сохраняем калли-сейв регистры (EBX, ESI, EDI)
    push    ebx
    push    esi
    push    edi

    mov     ecx, 1            

Loop_Start:
    cmp     ecx, 25           ; x < 25 (так как 50 - 2*x > 0 при x <= 24)
    jge     Loop_End          

    ; Вычисляем: 50 - 2*x
    mov     eax, 50           
    mov     esi, ecx          
    shl     esi, 1            
    sub     eax, esi          
    
    ; Проверяем, делится ли (50-2*x) на 3: если да, то y = (50-2*x)/3
    mov     edx, 0           
    mov     esi, 3            
    div     esi              
    cmp     edx, 0            ; проверка остатка
    jne     NoSolution        ; если не делится

    ; Если делится, то найдено решение:
    mov     edi, eax         ; сохраняем y в EDI
    mov ebx, ecx
    push    edi              
    push    ecx              
    push    offset fmtStr    ;указатель на форматированную строку
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
    ; Возвращаем общее количество решений в EAX
    mov     eax, dword ptr [ebp-4]

    pop     edi
    pop     esi
    pop     ebx
    mov     esp, ebp
    pop     ebp
    ret
FindSolutions ENDP

END
