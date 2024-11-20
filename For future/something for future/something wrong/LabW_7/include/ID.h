#pragma once
#include <vector>
#include "classes.h"
bool hasSameID (student::studentBeginner first, student::studentBeginner second);
bool hasSameID (std::vector <student::studentBeginner> &someStudents);
bool hasSameID (student::studentBeginner *someStudents);
bool hasSameID(std::vector <student::studentBeginner> &someStudents, student::studentBeginner student);