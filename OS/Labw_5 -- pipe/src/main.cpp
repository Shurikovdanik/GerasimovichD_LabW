#include <windows.h>
#include <iostream>
#include <vector>
#include <sstream>
struct ChildProcess {
    PROCESS_INFORMATION pi{};
};

ChildProcess runProcess(const wchar_t* prog, HANDLE inRead, HANDLE outWrite) {
    STARTUPINFOW si{};
    si.cb = sizeof(si);
    si.dwFlags |= STARTF_USESTDHANDLES;
    si.hStdInput  = inRead;
    si.hStdOutput = outWrite;
    si.hStdError  = GetStdHandle(STD_ERROR_HANDLE);

    PROCESS_INFORMATION pi{};
    if (!CreateProcessW(prog, nullptr, nullptr, nullptr, TRUE, 0, nullptr, nullptr, &si, &pi)) {
        std::wcerr << L"CreateProcess failed for " << prog << std::endl;
    }
    CloseHandle(pi.hThread);
    return {pi};
}

int main() {
    HANDLE pipe1Read, pipe1Write;
    HANDLE pipe2Read, pipe2Write;
    HANDLE pipe3Read, pipe3Write;
    HANDLE inputRead, inputWrite;
    SECURITY_ATTRIBUTES sa{sizeof(sa), nullptr, TRUE};

    // stdin for procM
    CreatePipe(&inputRead, &inputWrite, &sa, 0);
    SetHandleInformation(inputRead, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
    SetHandleInformation(inputWrite, HANDLE_FLAG_INHERIT, 0);

    // pipe M->A
    CreatePipe(&pipe1Read, &pipe1Write, &sa, 0);
    SetHandleInformation(pipe1Write, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
    SetHandleInformation(pipe1Read, HANDLE_FLAG_INHERIT, 0);

    // pipe A->P
    CreatePipe(&pipe2Read, &pipe2Write, &sa, 0);
    SetHandleInformation(pipe2Write, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
    SetHandleInformation(pipe2Read, HANDLE_FLAG_INHERIT, 0);

    // pipe P->S
    CreatePipe(&pipe3Read, &pipe3Write, &sa, 0);
    SetHandleInformation(pipe3Write, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
    SetHandleInformation(pipe3Read, HANDLE_FLAG_INHERIT, 0);

    auto pM = runProcess(L"procM.exe", inputRead, pipe1Write);
    CloseHandle(inputRead);
    CloseHandle(pipe1Write);

    SetHandleInformation(pipe1Read, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
    auto pA = runProcess(L"procA.exe", pipe1Read, pipe2Write);
    CloseHandle(pipe1Read);
    CloseHandle(pipe2Write);

    SetHandleInformation(pipe2Read, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
    auto pP = runProcess(L"procP.exe", pipe2Read, pipe3Write);
    CloseHandle(pipe2Read);
    CloseHandle(pipe3Write);

    SetHandleInformation(pipe3Read, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
    auto pS = runProcess(L"procS.exe", pipe3Read, GetStdHandle(STD_OUTPUT_HANDLE));
    CloseHandle(pipe3Read);

    std::vector<int> nums = {1,2,3,4,5};
    for (int x : nums) {
        std::ostringstream oss;
        oss << x << " ";
        std::string s = oss.str();
        DWORD written;
        WriteFile(inputWrite, s.c_str(), (DWORD)s.size(), &written, nullptr);
    }
    CloseHandle(inputWrite);

    WaitForSingleObject(pM.pi.hProcess, INFINITE);
    WaitForSingleObject(pA.pi.hProcess, INFINITE);
    WaitForSingleObject(pP.pi.hProcess, INFINITE);
    WaitForSingleObject(pS.pi.hProcess, INFINITE);

    CloseHandle(pM.pi.hProcess);
    CloseHandle(pA.pi.hProcess);
    CloseHandle(pP.pi.hProcess);
    CloseHandle(pS.pi.hProcess);

    return 0;
}
