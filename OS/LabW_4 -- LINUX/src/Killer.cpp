#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <signal.h>
#include <dirent.h>
#include <fstream>
#include <sstream>

// Завершение процесса по PID
bool killById(pid_t pid)
{
    return (kill(pid, SIGKILL) == 0);
}

// Получение PID процесса по имени
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

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: Killer --id <pid> | --name <procname>\n";
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
    }

    char *env = getenv("PROC_TO_KILL");
    if (env)
    {
        std::string envStr(env);
        std::cout << "PROC_TO_KILL=" << envStr << "\n";
        size_t start = 0, end;
        while ((end = envStr.find(',', start)) != std::string::npos)
        {
            std::string proc = envStr.substr(start, end - start);
            killByName(proc);
            start = end + 1;
        }
        std::string last = envStr.substr(start);
        if (!last.empty())
            killByName(last);
    }

    return 0;
}