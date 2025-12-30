#include <iostream>
#include <cstdlib>
#include <unistd.h>

int main() {
    setenv("PROC_TO_KILL", "chrome,explorer,telegram", 1);

    std::cout << "Launching Killer with parameters...\n";

    system("./Killer --name WINWORD.EXE");

    system("./Killer --id 1234");

    system("./Killer");

    unsetenv("PROC_TO_KILL");

    std::cout << "Var PROC_TO_KILL deleted.\n";
    return 0;
}