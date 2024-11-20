#include <iostream>
#include "../include/operationsWithF&SSt.h"
#include "../include/fileManagement.h"
#include "../include/basicactions.h"
int fileManage::load (char* inputFileName, char* outputFileName) {
std::stringstream temp= input::finStreamString (inputFileName);
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