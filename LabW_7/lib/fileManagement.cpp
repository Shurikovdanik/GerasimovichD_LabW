#include <iostream>
#include "../include/operationsWithF&SSt.h"
#include "../include/fileManagement.h"
#include "../include/basicactions.h"
int fileManage::load (char* inputFileName, char* outputFileName) {
std::stringstream temp = input::finStreamString (inputFileName);
std::string students, marks1, marks2;
temp >> students;
temp >> marks1;
temp >> marks2;
char* studentsA = new char[sizeof(students) / sizeof(students[0])];
for (int i = 0; i < sizeof(students) / sizeof(students[0]); i++) {
    studentsA[i] = students[i];
}
char* marks1A = new char[sizeof(marks1) / sizeof(marks1[0])];
for (int i = 0; i < sizeof(marks1) / sizeof(marks1[0]); i++) {
    marks1A[i] = marks1[i];
}
char* marks2A = new char[sizeof(marks2) / sizeof(marks2[0])];
for (int i = 0; i < sizeof(marks2) / sizeof(marks2[0]); i++) {
    marks2A[i] = marks2[i];
}
fullCycleOperations::fileApp (studentsA, marks1A, marks2A, outputFileName);
return 0;
}
int fileManage::save (std::vector <student::studentAfterSecondSession> &given, char* saveFileName) {
    std::string directoryStr;
    directoryStr = toDirectory (saveFileName, directoryStr);
    std::string toSaveData = directoryStr + "students.txt " + directoryStr + "marks1.txt " + directoryStr + "marks2.txt";
    std::ofstream fout (saveFileName);
    fout << toSaveData;
    fout.close();
    fout.open(directoryStr + "students.txt");
    for (int i = 0; i < given.size(); i++) {
        fout << given[i].getName() << " " << given[i].getForm() << " " << given[i].getGroup() << " " << given[i].getCardID() << "\n";
    }
    fout.close();
    fout.open(directoryStr + "marks1.txt");
    for (int i = 0; i < given.size(); i++) {
        for (int j = 0; j < FIRST_SESSION_NUM; j++) {
            fout << given[i].getMarks()[j] << " ";
        }
        fout << "\n";
    }
    fout.close();
    fout.open(directoryStr + "marks2.txt");
    for (int i = 0; i < given.size(); i++) {
        for (int j = 0; j < SECOND_SESSION_NUM; j++) {
            fout << given[i].getMarksSecond()[j]<< " ";
        }
        fout << "\n";
    }
    fout.close();
    return 0;
}
std::string fileManage::toDirectory (std::string fileName, std::string &directoryName) {
    int tempPos = -1;
    for (int i = sizeof(fileName) / sizeof(fileName[0]); i >= 0; i--) {
        if (fileName[i] == '/') {
            tempPos = i;
            break;
        }
    }
    if (tempPos == -1) {
        directoryName = "";
    }
    else {
        for (int i = 0; i < tempPos; i++) {
            directoryName = fileName.substr(0, tempPos) + "/";
        }
    }
    return directoryName;
}