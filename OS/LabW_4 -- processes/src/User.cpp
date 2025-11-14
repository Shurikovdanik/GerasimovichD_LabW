#include <iostream>
#include <cstdlib>
#include <windows.h>

int main() {
    // Устанавливаем переменную окружения
    SetEnvironmentVariableA("PROC_TO_KILL", "chrome,explorer,telegram");

    std::cout << "Launching Killer with parameters...\n";

    // Пример запуска Killer по имени
    system("Killer.exe --name WINWORD.EXE");

    // Пример запуска Killer по PID (для демонстрации возьмём explorer.exe)
    // Обычно PID нужно получить заранее через Task Manager или API
    system("Killer.exe --id 1234");

    // Пример запуска Killer без параметров (будет использовать PROC_TO_KILL)
    system("Killer.exe");

    // Удаляем переменную окружения
    SetEnvironmentVariableA("PROC_TO_KILL", nullptr);

    std::cout << "Var PROC_TO_KILL deleted.\n";
    return 0;
}
