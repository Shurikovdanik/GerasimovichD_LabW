#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <csignal>
#include <dirent.h>
#include <fstream>
#include <unistd.h>

// Завершение процесса по PID
bool killById(pid_t pid)
{
    return (kill(pid, SIGKILL) == 0);
}

// Получение PID процесса по имени через /proc
std::vector<pid_t> getPidsByName(const std::string &name)
{
    std::vector<pid_t> pids;
    DIR* dir = opendir("/proc");
    if (!dir)
        return pids;

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr)
    {
        if (entry->d_type != DT_DIR)
            continue;

        std::string dirName = entry->d_name;
        if (dirName.find_first_not_of("0123456789") != std::string::npos)
            continue;

        pid_t pid = std::stoi(dirName);
        std::string path = "/proc/" + dirName + "/comm";
        std::ifstream commFile(path);

        if (commFile)
        {
            std::string procName;
            std::getline(commFile, procName);
            if (procName == name)
            {
                pids.push_back(pid);
            }
        }
    }
    closedir(dir);
    return pids;
}

// Завершение процессов по имени
bool killByName(const std::string &name)
{
    bool killed = false;
    std::vector<pid_t> pids = getPidsByName(name);

    for (pid_t pid : pids)
    {
        if (killById(pid))
        {
            std::cout << "Killed process " << name << " with PID " << pid << "\n";
            killed = true;
        }
    }
    return killed;
}


bool startProcess(const std::string &path, const std::vector<std::string> &args = {})
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return false;
    }
    else if (pid == 0)
    {
        // Дочерний процесс
        std::vector<char*> argv;
        argv.push_back(const_cast<char*>(path.c_str()));
        for (const auto &arg : args)
            argv.push_back(const_cast<char*>(arg.c_str()));
        argv.push_back(nullptr);

        execvp(path.c_str(), argv.data());
        perror("execvp");
        exit(EXIT_FAILURE);
    }
    else
    {
        // Родительский процесс
        std::cout << "Started process " << path << " with PID " << pid << "\n";
        return true;
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: Killer --id <pid> | --name <procname> | --start <path> [args...]\n";
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];
        if (arg == "--id" && i + 1 < argc)
        {
            pid_t pid = std::stoi(argv[++i]);
            if (killById(pid))
                std::cout << "Killed process with PID " << pid << "\n";
            else
                std::cout << "Failed to kill PID " << pid << "\n";
        }
        else if (arg == "--name" && i + 1 < argc)
        {
            std::string name = argv[++i];
            if (killByName(name))
                std::cout << "Killed processes with name " << name << "\n";
            else
                std::cout << "No processes with name " << name << "\n";
        }
        else if (arg == "--start" && i + 1 < argc)
        {
            std::string path = argv[++i];
            std::vector<std::string> args;
            while (i + 1 < argc)
                args.push_back(argv[++i]);
            startProcess(path, args);
        }
    }

    return 0;
}
