#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <vector>


void runKiller(const std::vector<std::string> &args) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return;
    } else if (pid == 0) {
        std::vector<char*> argv;
        argv.push_back(const_cast<char*>("./Killer"));
        for (const auto &arg : args)
            argv.push_back(const_cast<char*>(arg.c_str()));
        argv.push_back(nullptr);

        execvp("./Killer", argv.data());
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        // Родительский процесс
        int status;
        waitpid(pid, &status, 0);
    }
}

int main() {
    setenv("PROC_TO_KILL", "chrome,explorer,telegram", 1);

    std::cout << "Launching Killer with parameters...\n";

    runKiller({"--name", "WINWORD.EXE"});
    runKiller({"--id", "1234"});
    runKiller({});  // без аргументов

    unsetenv("PROC_TO_KILL");

    std::cout << "Var PROC_TO_KILL deleted.\n";
    return 0;
}
