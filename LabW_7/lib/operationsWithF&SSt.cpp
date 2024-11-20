#include <iostream>
#include <vector>
#include <fstream>
#include "..\include\basicactions.h"
#include "..\include\classes.h"
#include "..\include\ID.h"
#include "..\include\operations.h"
#include "..\include\operationsWithF&SSt.h"
#include "..\include\fileManagement.h"
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
    } 
    std::vector <student::studentAfterSession> addMarksStream::firstSemester (std::vector <student::studentBeginner> &array, std::istream &inputStream) {
        std::vector <student::studentAfterSession> res;
        for (int i = 0; i < array.size(); i++) {
            student::studentAfterSession temp = student::toFSession(array[i]);
            res.push_back(temp);
        }
        for (int i = 0; i < array.size(); i++) {
            marks::input (res[i], inputStream);
        }
        return res;
    }
    std::vector <student::studentAfterSecondSession> addMarksStream::secondSemester (std::vector <student::studentAfterSession> &array, std::istream &inputStream) {
        std::vector <student::studentAfterSecondSession> res;
        for (int i = 0; i < array.size(); i++) {
            student::studentAfterSecondSession temp = student::toSSession(array[i]);
            res.push_back(temp);
        }
        for (int i = 0; i < array.size(); i++) {
            marks::input(res[i], inputStream);
        }
        return res;
    }
    int fullCycleOperations::fileApp (char* inputFilenameBeginners, char* inputFilenameMarksFirstSemester, char* inputFilenameMarksSecondSemester, char* outputFilename) {
        std::vector <student::studentBeginner> students;
        students = file::fin(inputFilenameBeginners);
        std::ifstream fin (inputFilenameMarksFirstSemester);
        std::vector <student::studentAfterSession> studentsA;
        std::stringstream temp = input::finStreamString(inputFilenameMarksFirstSemester);
        studentsA = addMarksStream::firstSemester(students, temp);
        std::vector <student::studentAfterSecondSession> studentsB;
        temp = input::finStreamString(inputFilenameMarksSecondSemester);
        studentsB = addMarksStream::secondSemester(studentsA, temp);
        students.clear();
        std::ofstream fout(outputFilename);
        if(fout.is_open()) {
        for (int i = 0; i < studentsB.size(); i++) {
          fout << studentsB[i] << " " << studentsA[i].mediumMark() << " " << studentsB[i].mediumMark() << "\n";
        }
        fout << middleMark::vector(studentsA) << " " << middleMark::vector(studentsB);
        }
        fileManage::save(studentsB, "save/save.txt");
        studentsA.clear();
        studentsB.clear();
        fout.close();
        //TODO: file management, documentation, example
        return 0;
    }