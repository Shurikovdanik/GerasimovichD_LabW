#include <iostream>
#include <vector>
#include "..\include\operations.h"
#include "..\include\classes.h"
#include "..\include\operationsWithF&SSt.h"
#include "..\include\app.h"
#include "..\include\fileManagement.h"
int application::app::main(){
    std::vector <student::studentBeginner> array;
    array= console::cin();
    console::cout(array);
    std::vector <student::studentAfterSession> array2;
    array2 = addMarksConsole::firstSemester (array);
    console::cout(array2);
    std::vector <student::studentAfterSecondSession> array3;
    array3 = addMarksConsole::secondSemester (array2);
    console::cout(array3);
    for (int i = 0; i < array3.size(); i++) {
        std::cout << array2[i].mediumMark() << ";" << array3[i].mediumMark() << std::endl;
    }
    std::cout << "Total 1st semester middle mark: " << middleMark::vector(array2)  
    << ". Total 2nd semester middle mark: " << middleMark::vector(array3);
    return 0;
}
int application::app::fileApp() {
    std::cout << fileManage::load ("data/save.txt", "data/output/output.txt"); //Выводит 0 в консоль при нормальной работе
    return 0;
}
