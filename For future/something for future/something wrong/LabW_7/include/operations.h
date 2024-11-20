#include <iostream>
#include <vector>
#include <fstream>
#include "..\include\basicactions.h"
#include "..\include\classes.h"
#include "..\include\ID.h"
#pragma once
namespace console {
    std::vector <student::studentBeginner> cin ();
    void cout (std::vector <student::studentBeginner> &given);
    void cout (std::vector <student::studentAfterSession> &given);
    void cout (std::vector <student::studentAfterSecondSession> &given);
}
namespace file {
    std::vector <student::studentBeginner> fin (char* fileName);
    void fout (std::vector <student::studentBeginner> &given, char* fileName);
}
namespace marks {
   void input (student::studentAfterSession &student, std::istream &inputStream);
   void input (student::studentAfterSecondSession &student, std::istream &inputStream);
   void output (const student::studentAfterSession &student, std::ostream &outputStream);
   void output (const student::studentAfterSecondSession &student, std::ostream &outputStream);
}
void inputFromStreamVector (std::istream &stream, std::vector <student::studentBeginner>&given, size_t num);
namespace outputSt {
    
}
namespace inputSt {
    std::vector <student::studentBeginner> cin ();
    student::studentBeginner generate(std::istream &stream); 
}
namespace middleMark {
    float vector (std::vector <student::studentAfterSession> &array);
    float vector (std::vector <student::studentAfterSecondSession> &array);
}
//TODO: переделать