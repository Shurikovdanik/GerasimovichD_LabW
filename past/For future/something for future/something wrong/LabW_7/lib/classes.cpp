#include <array>
#include <iostream>
#include <string.h>
#include "..\include\classes.h"
#include "..\include\basicactions.h"
void student::studentBeginner::setName (char* name) {
this -> name = name;
}
void student::studentBeginner::setForm (char form) {
this -> form = form;
}
void student::studentBeginner::setGroup (unsigned int group) {
this -> group = group;
}
unsigned int student::studentBeginner::getID () {
return ID;
}
char* student::studentBeginner::getName () {
return name;
}
char student::studentBeginner::getForm() {
return form;
}
unsigned int student::studentBeginner::getGroup() {
return group;
}
unsigned int student::studentBeginner::getCardID() {
return cardID;
}
void student::studentAfterSession::setMarks (std::array <unsigned int, FIRST_SESSION_NUM> marks) {
this -> marks = marks;
}
std::array <unsigned int, FIRST_SESSION_NUM> student::studentAfterSession::getMarks() {
return marks;
}
void student::studentAfterSecondSession::setMarksSecond (std::array <unsigned int, SECOND_SESSION_NUM> marksSecond) {
this -> marksSecond = marksSecond;
}
std::array <unsigned int, SECOND_SESSION_NUM> student::studentAfterSecondSession::getMarksSecond() {
return marksSecond;
}
 void student::studentBeginner::operator >>(std::istream &inputStream) {
  std::string temp;
  std::cin >> temp;
   for (int i = 0; i < sizeof(temp) / sizeof(temp[0] - 1); i++) {
     name[i] = temp[i];
   }
    inputStream >> form;
    inputStream >> group;
 }
 void student::studentBeginner::operator <<(std::ostream &outputStream) {
    outputStream <<"ID: " << ID <<", name: " <<  name <<", form: " << form << ", group: "<< group <<", card ID: " << cardID << std::endl;
 }
 void student::studentAfterSession::operator << (std::ostream &outputStream) {
   outputStream <<"ID: " << getID() <<", name: " << getName() <<", form: " << getForm() << ", group: "<< getGroup() <<", card ID: " << getCardID() << ", 1st session marks: ";
   for (int i = 0; i < FIRST_SESSION_NUM; i++) {
      outputStream << marks[i] << " ";
   }
   outputStream << std::endl;
 }
 /*std::ostream student::operator << (std::ostream &outputStream, student::studentAfterSession &student) {
  outputStream <<"ID: " << student.getID() <<", name: " << student.getName() <<", form: " << student.getForm() << ", group: "<< student.getGroup() <<", card ID: " << student.getCardID() << ", 1st session marks: ";
   for (int i = 0; i < FIRST_SESSION_NUM; i++) {
      outputStream << student.getMarks()[i] << " ";
   } 
   return outputStream;
 }*/
 void student::studentAfterSecondSession::operator << (std::ostream &outputStream) {
   outputStream <<"ID: " << getID() <<", name: " << getName() <<", form: " << getForm() << ", group: "<< getGroup() <<", card ID: " << getCardID() << ", 1st session marks: ";
   std::array<unsigned int, FIRST_SESSION_NUM> tempArrray = getMarks();
   for (int i = 0; i < FIRST_SESSION_NUM; i++) {
      outputStream << tempArrray[i] << " ";
   }
   outputStream <<". 2nd session marks: ";
   for (int i = 0; i < SECOND_SESSION_NUM; i++) {
    outputStream << marksSecond[i] << " ";
   }
   outputStream << std::endl;
 }
    double student::studentAfterSession::mediumMark() {
      return arrayAriphmetics::sumOfArray (marks) / marks.size();
    }
    double student::studentAfterSecondSession::mediumMark(){
      return (arrayAriphmetics::sumOfArray (marksSecond) + arrayAriphmetics::sumOfArray(getMarks()))/ (marksSecond.size() + getMarks().size());
    }
    void student::studentBeginner::operator = (student::studentBeginner other) {
      delete name;
      ID = other.getID();
      cardID = other.getCardID();
      char name[ARRAY_LENGTH];
      strcpy(name, other.getName());
      form = other.getForm();
    }
    std::istream& student::operator >>(std::istream &inputStream, student::studentBeginner &given) {
      std::string name;
      inputStream >> name;
      char* nameRes = new char[name.end() - name.begin()];
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
    given = res;
    return inputStream;
    }
    student::studentAfterSession student::toFSession (student::studentBeginner given) {
      std::array <unsigned int, FIRST_SESSION_NUM> temp;
      for (int i = 0; i < FIRST_SESSION_NUM; i++) {
        temp[i]= 0;
      }
      student::studentAfterSession res (given.getName(), given.getForm(), given.getGroup(), given.getCardID(), temp, given.getID());
      return res;
    }
    student::studentAfterSecondSession student::toSSession(student::studentAfterSession given) {
      std::array <unsigned int, SECOND_SESSION_NUM> temp;
      for (int i = 0; i < SECOND_SESSION_NUM; i++) {
        temp[i]= 0;
      }
      student::studentAfterSecondSession res (given.getName(), given.getForm(), given.getGroup(), given.getCardID(), given.getMarks() , temp, given.getID());
      return res;
    }