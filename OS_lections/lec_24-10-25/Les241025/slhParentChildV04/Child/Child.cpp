// Child.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Windows.h"


//int main()
int main(int argc, char* argv[])
{
    std::cout << "Hello World!\n";
    if (argc != 4)
    {
        printf("\nError: argc:%d != 4 \n", argc);
        return 1;
    }
    DWORD dwFileHandle = 0, dwEventHandle=0;
        //HANDLE    dwHandle = 0;

    //1) Get the handle "hFile" and hEvent inherited from "Parent.exe"
    //
    sscanf_s(argv[1], "%u", &dwFileHandle);
    HANDLE hFile = (HANDLE)dwFileHandle;
    sscanf_s(argv[2], "%u", &dwEventHandle);
    HANDLE hEvent = (HANDLE)dwEventHandle;

    char* NameVarEvent = argv[3];
    LPSTR NameEvent = new char[300]{0, };
    DWORD lenNameEvent=GetEnvironmentVariableA(NameVarEvent, NameEvent, 300);
    if (lenNameEvent == 0) 
    {
        printf("\nUnable to Get Environment VariableA :%s  \n", NameVarEvent);
        std::cout << "Press Key Enter to quit\n";
        std::cin.get();
        return 1;
    }
    char fileName[] = "ResultFromChild.txt";
    HANDLE hFileByName = CreateFileA(fileName,               // file to open
        GENERIC_READ | GENERIC_WRITE,          // open for reading and writing
        FILE_SHARE_READ | FILE_SHARE_WRITE,       // share for reading and writing
        NULL,                  // default security
        OPEN_EXISTING,         // existing file only!!!!!!!!!!!
        FILE_ATTRIBUTE_NORMAL , // normal file
        NULL);                 // no attr. template

  //  It is no need to use CreateFileA because hFile is valid here as the inherited handle.
  // 
    if (hFileByName == INVALID_HANDLE_VALUE)
    {
       
        printf("\nUnable to open file \"%s\" .\n", fileName);
        return 1;
    }
    printf("\nhFile!= hFileByName: %d\n", hFile != hFileByName);

  

  

    HANDLE hEventByName = OpenEventA(EVENT_ALL_ACCESS, FALSE, NameEvent);

    printf("hEvent!= hEventByName: %d\n", hEvent != hEventByName);

    //std::cout << "Press Key Enter to run\n";
    //std::cin.get(); 
    //return 0;
    //
   
    DWORD dwEvent=WaitForSingleObject(hEvent, INFINITE);
    if (dwEvent == WAIT_FAILED)
    {
        std::cout << "WAIT_FAILED hEvent as It is Not Inheritable\n";

        std::cout << "First Wait hEventByName from Parent2.exe\nSo Child is blocked\n";
        WaitForSingleObject(hEventByName, INFINITE);//bManualReset==TRUE: Manual-reset event. The event remains signaled until explicitly reset using ResetEvent.

        SetEvent(hEventByName); //It doesn’t matter because the event is in a signaling state.This instruction is redundant.
        //ResetEvent(hEventByName);

        std::cout << "Second Wait hEventByName from Parent2.exe\n";
        WaitForSingleObject(hEventByName, INFINITE);
        ResetEvent(hEventByName);//Now hEventByName is in not signaled state!!!
    }

    //2) Get "fileSize" (The kernel object hFile has been opened by "Parent.exe" 

    SetFilePointer(hFileByName, 0, NULL, FILE_BEGIN); //hFile
    DWORD fileSize = GetFileSize(hFileByName, NULL);  //hFile

    std::cout << "\nfileSize before executing: " << fileSize << "\nPress Key Enter to run\n";
    //std::cin.get();

    //3)Read szQuery from the file (all the file is reading) 
    //
    DWORD bytesRead = 0;
    char szQuery[500] = {'\0', };
    bool bReadFile = ReadFile(hFileByName, szQuery, fileSize, &bytesRead, NULL);//hFileByName

    //Query executed by "Child.exe"
    // 
    //4) Get the command: op and argOp
    char op[40] = { '\0', };//name of function
    float argOp = 0;        //argument    
    sscanf_s(szQuery, "%s%f", &op, 40, &argOp );//White characters are no value

    printf("From Child:Query:\n%s\n", szQuery);
    printf("op:<%s> argOp:<%7.4f>\n", op, argOp );

    //5) Check what is a name of function 
    if (0 == strcmp(op, "sqrt"))
    {
        float fAnswer = sqrt(argOp); //Execute the command
        //
        char szfAnswer[21] = { '\0', };
        size_t sizeAnswer = sizeof("fAnswer:") + 7 + 1; //Including '\0' at the end of "szfAnswer"
        sprintf_s(szfAnswer, sizeAnswer,"fAnswer:%7.4f\n", fAnswer); //Get the answer to szQuery

        SetFilePointer(hFileByName, 0, NULL, FILE_END);//hFile//Set Pointer of the file at the file end
        DWORD dwBytesWritten = 0;

        printf("fAnswer::%7.4f\nPress Key Enter to run\n", fAnswer);
        //std::cin.get();

        //Append the answer 
        bool bErrorFlag = WriteFile(
            hFileByName,           // open file handle //hFile
            szfAnswer,      // start of data to write
            sizeAnswer-1,  // number of bytes to write ,//Excluding '\0' at the end of "szfAnswer"
            &dwBytesWritten, // number of bytes that were written
            NULL); // no overlapped structure
        
        fileSize = GetFileSize(hFileByName, NULL);//hFile

    }
    

    std::cout <<"\nfileSize after executing: "<< fileSize << "\nPress Key Enter to quit\n";
    std::cin.get();

    CloseHandle(hFile);//Decrease the user count by 1! Before it was 3!!!//Before it was 2!
    CloseHandle(hEvent); 
    CloseHandle(hEventByName);
    CloseHandle(hFileByName);//Decrease the user count by 1! Before it was 2!!!
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
