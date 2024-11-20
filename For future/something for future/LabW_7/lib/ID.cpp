#include <vector>
#include "..\include\classes.h"
#include "..\include\ID.h"

bool hasSameID (student::studentBeginner first, student::studentBeginner second) {
    return (first.getID() == second.getID());
}
bool hasSameID (std::vector <student::studentBeginner> &someStudents) {
    for (int i = 0; i < someStudents.size() - 1; i++) {
        for (int j = i + 1; j < someStudents.size(); j++) {
            if(hasSameID(someStudents[i], someStudents[j])) {
                return 1;
            }
        }
    }
    return 0;
}
bool hasSameID (student::studentBeginner *someStudents) {
    for (int i = 0; i < sizeof(someStudents) / sizeof(someStudents[0]) - 1; i++) {
        for (int j = i + 1; j < sizeof(someStudents) / sizeof(someStudents[0]); j++) {
            if(hasSameID(someStudents[i], someStudents[j])) {
                return 1;
            }
        }
    }
    return 0;
}
bool hasSameID(std::vector <student::studentBeginner> &someStudents, student::studentBeginner student) {
    for (int i = 0; i < someStudents.size(); i++) {
            if(hasSameID(someStudents[i], student)) {
                return 1;
        }
    }
    return 0;
}
//DONE