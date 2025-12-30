#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

struct ChildProcess {
    pid_t pid;
    int stdinfd = -1;
    int stdoutfd = -1;
};

ChildProcess runProcess(const char* prog, int in_fd, int out_fd) {
    pid_t pid = fork();
    if (pid == 0) {
        // Дочерний процесс
        if (in_fd != STDIN_FILENO) {
            dup2(in_fd, STDIN_FILENO);
            close(in_fd);
        }
        if (out_fd != STDOUT_FILENO) {
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
        }
        
        for (int fd = 3; fd < 1024; fd++) {
            close(fd);
        }
        
        execl(prog, prog, (char*)nullptr);
        perror("execl failed");
        _exit(1);
    } else if (pid > 0) {
        // Родительский процесс
        if (in_fd != STDIN_FILENO) close(in_fd);
        if (out_fd != STDOUT_FILENO) close(out_fd);
        return {pid, -1, -1};
    } else {
        perror("fork failed");
        return {-1, -1, -1};
    }
}

int main() {
    int pipe1[2];  
    int pipe2[2];  
    int pipe3[2];  
    
    if (pipe(pipe1) < 0 || pipe(pipe2) < 0 || pipe(pipe3) < 0) {
        perror("pipe failed");
        return 1;
    }
    
    int input_pipe[2];
    if (pipe(input_pipe) < 0) {
        perror("input pipe failed");
        return 1;
    }
    
    auto pM = runProcess("./procM", input_pipe[0], pipe1[1]);
    close(input_pipe[0]);
    close(pipe1[1]);
    
    auto pA = runProcess("./procA", pipe1[0], pipe2[1]);
    close(pipe1[0]);
    close(pipe2[1]);
    
    auto pP = runProcess("./procP", pipe2[0], pipe3[1]);
    close(pipe2[0]);
    close(pipe3[1]);
    
    auto pS = runProcess("./procS", pipe3[0], STDOUT_FILENO);
    close(pipe3[0]);
    
    std::vector<int> nums = {1, 2, 3, 4, 5};
    for (int x : nums) {
        std::ostringstream oss;
        oss << x << " ";
        std::string s = oss.str();
        write(input_pipe[1], s.c_str(), s.size());
    }
    close(input_pipe[1]);
    
    waitpid(pM.pid, nullptr, 0);
    waitpid(pA.pid, nullptr, 0);
    waitpid(pP.pid, nullptr, 0);
    waitpid(pS.pid, nullptr, 0);
    
    return 0;
}