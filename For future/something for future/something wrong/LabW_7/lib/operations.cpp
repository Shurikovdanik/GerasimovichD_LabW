#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "..\include\basicactions.h"
#include "..\include\operations.h"
#include "..\include\classes.h"
#include "..\include\ID.h"
std::vector <student::studentBeginner> console::cin () {
std::cout << "Number of elements: ";
unsigned int num;
std::cin >> num;
std::cout << std::endl;
std::vector <student::studentBeginner> res;
std::cout << "Enter name, form, group, card ID: ";
student::studentBeginner temp = inputSt::generate(std::cin);
res.push_back(temp);
for (int i = 1; i < num; i++) {
  
 student::studentBeginner tempN = inputSt::generate(std::cin);
  res.push_back(tempN);
}
return res;
}
void console::cout (std::vector <student::studentBeginner> &given) {
for (int i = 0; i < given.size(); i++) {
given[i] << std::cout;
}
}
void console::cout (std::vector <student::studentAfterSession> &given) {
  for (int i = 0; i < given.size(); i++) {
given[i] << std::cout;
}
}
void console::cout (std::vector <student::studentAfterSecondSession> &given) {
for (int i = 0; i < given.size(); i++) {
given[i] << std::cout;
}
}
std::vector <student::studentBeginner> file::fin (char* fileName) {
  std::vector <student::studentBeginner> res;
  std::vector <std::string> someStrings;
  std::ifstream fin;
  fin.open (fileName);
     if (fin.is_open()) {
        const int max = 300;    
    char buffer[max];
    std::string string; 
    while (fin)     
    {
        fin.getline(buffer, max);
        someStrings.push_back(buffer); 
    }
    }
    fin.close();
    for (int i = 0; i < someStrings.size(); i++) {
      std::stringstream stream{someStrings[i]};
      student::studentBeginner temp(0,0,0,0);
      if (hasSameID(res, temp)) {
    i--;
    }
      temp >> stream;
      res.push_back(temp);
    }
    return res;
}
void file::fout (std::vector <student::studentBeginner> &given, char* fileName) {
  std::ofstream fout(fileName);
  if (fout.is_open()) {
    for (int i = 0; i < given.size(); i++) {
given[i] << fout;
}
  }
}
void marks::output (const student::studentAfterSession &student, std::ostream &outputStream) {
  student::studentAfterSession temp = student;
  for (int i = 0;i < FIRST_SESSION_NUM; i++) {
    std::cout << temp.getMarks()[i];
  }
}
void marks::input (student::studentAfterSession &student, std::istream &inputStream) {
  std::array <unsigned int, FIRST_SESSION_NUM> res;
  for (int i = 0; i < FIRST_SESSION_NUM; i++) {
    res[i] = 0;
  }
  input::streamInputArray (res, inputStream);
  
  student.setMarks(res);
}
void marks::output (const student::studentAfterSecondSession &student, std::ostream &outputStream) {
  student::studentAfterSecondSession temp = student;
  for (int i = 0;i < SECOND_SESSION_NUM; i++) {
    std::cout << temp.getMarksSecond()[i];
  }
}
void marks::input (student::studentAfterSecondSession &student, std::istream &inputStream) {
  std::array <unsigned int, SECOND_SESSION_NUM> res;
  for (int i = 0; i < SECOND_SESSION_NUM; i++) {
    res[i] = 0;
  }
  input::streamInputArray (res, inputStream);
  student.setMarksSecond(res);
}
void inputFromStreamVector (std::istream &stream, std::vector <student::studentBeginner>&given, size_t num) {
std::vector <student::studentBeginner> res;
student::studentBeginner temp(0,0,0,0);
stream >> temp;
for (int i = 1; i < num; i++) {
  student::studentBeginner temp1(0,0,0,0);
  if (hasSameID(res, temp1)) {
    i--;
  }
  else {
    stream >> temp1;
    res.push_back(temp1);
  }
}
given = res;
}
std::vector <student::studentBeginner> inputSt::cin () {
  std::cout << "Number of elements: ";
unsigned int num;
std::cin >> num;
std::cout << std::endl;
std::vector <student::studentBeginner> res;
std::cout << "Enter name, form, group, cardID";
  inputFromStreamVector (std::cin, res, num);
  return res;
}
student::studentBeginner inputSt::generate(std::istream &inputStream) {
  std::string name;
      inputStream >> name;
      char* nameRes = new char(name.end() - name.begin());
      for (int i = 0; i < name.end() - name.begin(); i++) {
        nameRes[i] = name[i];
      }
   char form;
   unsigned int group;
   unsigned int cardID;
    inputStream >> form;
    inputStream >> group;
    inputStream >> cardID;
    student::studentBeginner res(nameRes, form, group, cardID);
    return res;
}
float middleMark::vector (std::vector <student::studentAfterSession> &array) {
  unsigned int sum = 0;
  for (int i = 0; i < array.size(); i++) {
    sum += arrayAriphmetics::sumOfArray(array[i].getMarks());
  }
  float res = (float)sum / ((FIRST_SESSION_NUM) * array.size());
  return res;
}
float middleMark::vector(std::vector <student::studentAfterSecondSession> &array) {
  unsigned int sum = 0;
  for (int i = 0; i < array.size(); i++) {
    sum += arrayAriphmetics::sumOfArray(array[i].getMarksSecond()) + arrayAriphmetics::sumOfArray(array[i].getMarks());
  }
  float res = (float)sum / ((FIRST_SESSION_NUM + SECOND_SESSION_NUM) * array.size());
  return res;
}