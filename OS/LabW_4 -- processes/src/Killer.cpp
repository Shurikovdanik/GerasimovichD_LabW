#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <tlhelp32.h>

// Завершение процесса по PID
bool killById(DWORD pid)
{
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
    if (hProcess == nullptr)
        return false;
    bool result = TerminateProcess(hProcess, 0);
    CloseHandle(hProcess);
    return result;
}

// Завершение процессов по имени
bool killByName(const std::string &name)
{
    bool killed = false;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
        return false;

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);
    if (Process32First(hSnapshot, &pe))
    {
        do
        {
            if (name == pe.szExeFile)
            {
                killed |= killById(pe.th32ProcessID);
            }

        } while (Process32Next(hSnapshot, &pe));
    }
    CloseHandle(hSnapshot);
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
            DWORD pid = std::stoul(argv[++i]);
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
