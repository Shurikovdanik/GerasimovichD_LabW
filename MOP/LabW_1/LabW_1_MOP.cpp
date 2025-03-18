#include <iostream>
#include <iomanip>
#include <cstdint>

int main() {
    short A1, A2, A3, B1, B2, B3, C1, C2, C3;
    std::cin >> A1 >> A2 >> A3;
    std::cout << std::endl;
    std::cin >> B1 >> B2 >> B3;
    std::cout << std::endl;
    _asm {
        mov ax, A1
        add ax, B1
        mov C1, ax
        mov dx, 0
        jc carry1
        jmp midwords
        carry1 :
        inc dx
            midwords :
        mov ax, A2
        add ax, B2
        add ax, dx
        mov C2, ax
        mov dx, 0
        jc carry2
        jmp highwords
        carry2 :
        inc dx
            highwords :
        mov ax, A3
        add ax, B3
        add ax, dx
        mov C3, ax
   }
    std::cout << C1 << C2 << C3;
    return 0;
}
