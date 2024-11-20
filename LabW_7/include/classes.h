#pragma once
#include <array>
#include <iostream>
#include <string.h>
#include "..\include\basicactions.h"
const size_t FIRST_SESSION_NUM = 4;
const size_t SECOND_SESSION_NUM = 5;
const unsigned int RAND_RANGE = 999999;
const unsigned int ARRAY_LENGTH = 30;
const unsigned int NUM_OF_ARGS = 4;
namespace student {
    class studentBeginner {
        private: 
        unsigned int ID;
        char* name;
        char form;
        unsigned int group;
        unsigned int cardID;
        public: 
        studentBeginner(char* name, char form, unsigned int group, unsigned int cardID) {
            this -> name = name;
            this -> form = form;
            this -> group = group;
            this -> cardID = cardID;
            this -> ID = rand () % RAND_RANGE + 1;
        }
        studentBeginner(const studentBeginner &student) {
            this -> name = student.name;
            this -> form = student.form;
            this -> group = student.group;
            this -> cardID = student.cardID;
            this -> ID = rand () % RAND_RANGE + 1;
        }
        void setName (char* name);
        void setForm (char form);
        void setGroup (unsigned int group);
        unsigned int getID ();
        char* getName ();
        char getForm();
        unsigned int getGroup();
        unsigned int getCardID();
        void operator >>(std::istream &inputStream);
        void operator <<(std::ostream &outputStream);
        virtual double mediumMark();
        void operator = (studentBeginner other);
        void toStream(std::ostream &stream);
    };
    std::ostream& operator << (std::ostream &outputStream, const studentBeginner &given);
    std::istream& operator >>(std::istream &inputStream, studentBeginner &given);
    class studentAfterSession : public studentBeginner {
        private:
        std::array <unsigned int, FIRST_SESSION_NUM> marks;
        public:
        studentAfterSession (char* name, char form, unsigned int group, unsigned int cardID, std::array <unsigned int, 4> marks, unsigned int ID): studentBeginner(name, form, group, cardID) {
            this -> marks = marks;
        }
        void setMarks (std::array <unsigned int, FIRST_SESSION_NUM> marks);
        std::array <unsigned int, FIRST_SESSION_NUM> getMarks();
        void operator << (std::ostream &outputStream);
        double mediumMark() override;
    };
    std::ostream& operator << (std::ostream &outputStream, studentAfterSession &student);
    studentAfterSession toFSession(studentBeginner given);
    class studentAfterSecondSession : public studentAfterSession {
        private:
        std::array <unsigned int, SECOND_SESSION_NUM> marksSecond;
        public: 
        studentAfterSecondSession (char* name, char form, unsigned int group, unsigned int cardID, std::array <unsigned int, FIRST_SESSION_NUM> marks, std::array <unsigned int, SECOND_SESSION_NUM> marksSecond, unsigned int ID): studentAfterSession(name, form, group, cardID, marks, ID) {
            this -> marksSecond = marksSecond;
        }
        void setMarksSecond (std::array <unsigned int, SECOND_SESSION_NUM> marks);
        std::array <unsigned int, SECOND_SESSION_NUM> getMarksSecond();
        void operator << (std::ostream &outputStream);
        double mediumMark();
    };
    std::ostream & operator << (std::ostream & stream, student::studentAfterSecondSession student);
    studentAfterSecondSession toSSession(studentAfterSession given);
}   