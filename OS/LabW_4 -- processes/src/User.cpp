#include <iostream>
#include <cstdlib>
#include <windows.h>

int main() {
    SetEnvironmentVariableA("PROC_TO_KILL", "chrome,explorer,telegram");

    std::cout << "Launching Killer with parameters...\n";

    system("Killer.exe --name WINWORD.EXE");

    system("Killer.exe --id 1234");

    system("Killer.exe");

    
    SetEnvironmentVariableA("PROC_TO_KILL", nullptr);

    std::cout << "Var PROC_TO_KILL deleted.\n";
    return 0;
}
