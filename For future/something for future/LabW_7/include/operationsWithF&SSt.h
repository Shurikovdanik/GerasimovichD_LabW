#include <iostream>
#include <vector>
#include <fstream>
#include "..\include\basicactions.h"
#include "..\include\classes.h"
#include "..\include\ID.h"
#include "..\include\operations.h"
#pragma once
namespace addMarksConsole {
    std::vector <student::studentAfterSession> firstSemester (std::vector <student::studentBeginner> &array);
    std::vector <student::studentAfterSecondSession> secondSemester (std::vector <student::studentAfterSession> &array);
}
namespace addMarksStream {
    std::vector <student::studentAfterSession> firstSemester (std::vector <student::studentBeginner> &array, std::istream &inputStream);
    std::vector <student::studentAfterSecondSession> secondSemester (std::vector <student::studentAfterSession> &array, std::istream &inputStream);
}
namespace fullCycleOperations {
    int fileApp (char* inputFilename,  char* inputFilenameMarksFirstSemester, char* inputFilenameMarksSecondSemester, char* outputFilename);
}