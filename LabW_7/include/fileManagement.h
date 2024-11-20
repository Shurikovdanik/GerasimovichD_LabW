#include <iostream>
#include "operationsWithF&SSt.h"
#include "basicactions.h"
#pragma once
const unsigned int LENGTH_OF_FILENAME_STUDENTS = 12;
const unsigned int LENGTH_OF_FILENAME_MARKS = 10;
namespace fileManage {
    int load(char* inputFileName, char* outputFileName);
    int save (std::vector <student::studentAfterSecondSession> &given, char* saveFileName);
    std::string toDirectory (std::string fileName, std::string &directoryName);
}