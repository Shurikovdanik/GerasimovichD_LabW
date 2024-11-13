#include <iostream>
#include <vector>
#include <fstream>
#include "..\include\basicactions.h"
#include "..\include\classes.h"
#include "..\include\ID.h"
#include "..\include\operations.h"
#include "..\include\operationsWithF&SSt.h"
    std::vector <student::studentAfterSession> addMarksConsole::firstSemester (std::vector <student::studentBeginner> &array) {
        std::vector <student::studentAfterSession> res;
        std::cout << "Enter " << FIRST_SESSION_NUM << " marks of 1st session for each student. " << std::endl;
        for (int i = 0; i < array.size(); i++) {
            student::studentAfterSession temp = student::toFSession(array[i]);
            res.push_back(temp);
        }
        for (int i = 0; i < array.size(); i++) {
            marks::input (res[i], std::cin);
        }
        return res;
    }
    std::vector <student::studentAfterSecondSession> addMarksConsole::secondSemester (std::vector <student::studentAfterSession> &array) {
         std::vector <student::studentAfterSecondSession> res;
         std::cout << "Enter " << SECOND_SESSION_NUM << " marks of 2nd session for each student. " << std::endl;
        for (int i = 0; i < array.size(); i++) {
            student::studentAfterSecondSession temp = student::toSSession(array[i]);
            res.push_back(temp);
        }
        for (int i = 0; i < array.size(); i++) {
            marks::input(res[i], std::cin);
        }
        return res;
    } //Конверсация из studentBeginner в studentAfterSession, studentAfterSession в studentSecondAfterSession