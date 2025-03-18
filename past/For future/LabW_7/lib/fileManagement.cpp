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
const char* MARKS1_POSTFIX = "marks1.txt";
const char* MARKS2_POSTFIX = "marks2.txt";
const char* STUDENTS_POSTFIX = "students.txt";
    int tempPos = -1;
    char * directory = new char;
    toDirectory(saveFileName, directory);
    char * studentsFile = new char [sizeof(directory) / sizeof(directory[0]) + LENGTH_OF_FILENAME_STUDENTS];
    for (int i = 0; i < sizeof(directory) / sizeof(directory[0]); i++) {
        studentsFile[i] = directory[i];
    }
    for (int i = sizeof(directory) / sizeof(directory[0]); i <  sizeof(directory) / sizeof(directory[0]) + LENGTH_OF_FILENAME_STUDENTS; i++) {
        studentsFile[i] = STUDENTS_POSTFIX[i - (sizeof(directory) / sizeof(directory[0]))];
    }
    char * marks1File = new char [sizeof(directory) / sizeof(directory[0]) + LENGTH_OF_FILENAME_MARKS];
    for (int i = 0; i < sizeof(directory) / sizeof(directory[0]); i++) {
        marks1File[i] = directory[i];
    }
    for (int i = sizeof(directory) / sizeof(directory[0]); i <  sizeof(directory) / sizeof(directory[0]) + LENGTH_OF_FILENAME_STUDENTS; i++) {
        marks1File[i] = MARKS1_POSTFIX[i - (sizeof(directory) / sizeof(directory[0]))];
    }
    char * marks2File = new char [sizeof(directory) / sizeof(directory[0]) + LENGTH_OF_FILENAME_MARKS];
    for (int i = 0; i < sizeof(directory) / sizeof(directory[0]); i++) {
        marks2File[i] = directory[i];
    }
    for (int i = sizeof(directory) / sizeof(directory[0]); i <  sizeof(directory) / sizeof(directory[0]) + LENGTH_OF_FILENAME_STUDENTS; i++) {
        marks2File[i] = MARKS2_POSTFIX[i - (sizeof(directory) / sizeof(directory[0]))];
    }
    char * saveContain = new char[sizeof(studentsFile) / sizeof(studentsFile[0]) + 2 + sizeof(marks1File) / sizeof(marks1File[0]) + sizeof(marks2File) / sizeof(marks2File[0])];
    for (int i = 0; i < sizeof(studentsFile) / sizeof(studentsFile[0]); i++) {
        saveContain[i] = studentsFile[i];
    }
    saveContain[sizeof(studentsFile) / sizeof(studentsFile[0])] = ' ';
    for (int i = sizeof(studentsFile) / sizeof(studentsFile[0]) + 1; i < sizeof(studentsFile) / sizeof(studentsFile[0]) + 1 + sizeof(marks1File) / sizeof(marks1File[0]); i++) {
        saveContain[i] = marks1File[i - sizeof(studentsFile) / sizeof(studentsFile[0]) - 1];
    }
    saveContain[sizeof(studentsFile) / sizeof(studentsFile[0]) + 1 + sizeof(marks1File) / sizeof(marks1File[0])] = ' ';
    for (int i = sizeof(studentsFile) / sizeof(studentsFile[0]) + 2 + sizeof(marks1File) / sizeof(marks1File[0]); i < sizeof(studentsFile) / sizeof(studentsFile[0]) + 2 + sizeof(marks1File) / sizeof(marks1File[0]) + sizeof(marks2File) / sizeof(marks2File[0]); i++) {
        saveContain[i] = marks2File[i-sizeof(studentsFile) / sizeof(studentsFile[0]) - 2 - sizeof(marks1File) / sizeof(marks1File[0])];
    }
    std::ofstream fout (saveFileName);
    fout << saveContain;
    delete [] saveContain;
    fout.close();
    std::ofstream fout1 (studentsFile);
    for (int i = 0; i < given.size(); i++) {
        fout1 << given[i].getName() << " " << given[i].getForm() << " " << given[i].getGroup() << " " << given[i].getCardID() << "\n";
    }
    fout1.close();
    delete [] studentsFile;
    std::ofstream fout2 (marks1File);
    for (int i = 0; i < given.size(); i++) {
        for (int j = 0; j < FIRST_SESSION_NUM; j++) {
            fout2 << given[i].getMarks()[j] << " ";
        }
        fout2 << "\n";
    }
    delete [] marks1File;
    fout2.close();
    std::ofstream fout3 (marks2File);
    for (int i = 0; i < given.size(); i++) {
        for (int j = 0; j < SECOND_SESSION_NUM; j++) {
            fout3 << given[i].getMarksSecond()[j] << " ";
        }
        fout3 << "\n";
    }
    delete [] marks2File;
    fout3.close();
    return 0;
}
int fileManage::toDirectory (char* fileName, char * directoryName) {
    int tempPos = -1;
    for (int i = sizeof(fileName) / sizeof(fileName[0]) - 1; i >= 0; i--) {
        if (fileName[i] == '/') {
            tempPos = i;
            break;
        }
    }
    if (tempPos == -1) {
        char* directoryName = new char[0];
    }
    else {
        char* directoryName = new char[tempPos + 1];
        for (int i = 0; i < tempPos + 1; i++) {
            directoryName[i] = directoryName[i];
        }
    }
    return 0;
}