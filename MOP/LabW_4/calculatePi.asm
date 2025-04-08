.386
.model flat, stdcall
.stack 4096

PUBLIC CalculatePI       ; Экспортируем процедуру для использования в C++

.data
    result REAL8 9.869          ; Результат вычисления, инициализирован
    divisor REAL8 12.0         ; Делитель
    targetPrecision REAL8 0.001 ; Целевая точность
    currentSum REAL8 0.0       ; Текущая сумма ряда
    sign REAL8 1.0             ; Знак (-1)^k
    k REAL8 1.0                ; Индекс ряда
    three REAL8 3.0
.code
CalculatePI PROC
    finit                      ; Инициализация сопроцессора

calc_loop:
    ; Вычисление текущего члена ряда
    fld1                       
    fld k                      
    fdiv                       ; Деление: 1 / k
    fld k
    fdiv                       ; Доведение до 1 / k^2
    fld sign                   
    fmul                       ; Умножение sign * (1 / k)
    fld currentSum             
    fadd                       ; Добавление: currentSum + sign * (1 / k)
    fstp currentSum           

    ; Увеличение индекса и знака
    fld k
    fld1
    fadd                       
    fstp k                    
    fld sign
    fchs                       
    fstp sign                  

    ; Проверка точности
    fld currentSum            
    fld divisor               
    fmul                       
    fld result                 
    fsub                      
    fabs                      
    fld targetPrecision        
    fcompp                     
    fnstsw ax                 
    sahf                       
    jb calc_loop              
    
    ; Возвращаем результат
    fld currentSum
    fld divisor
    fmul                      
    fstp result                
    finit                      
    fld result
    fsqrt
    ret
CalculatePI ENDP

END
