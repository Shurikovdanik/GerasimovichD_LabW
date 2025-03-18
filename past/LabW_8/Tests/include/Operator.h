#include "string"
#include <vector>
#include "..\include\basicactions.h"
const char* NUM_LIST = "0123456789";
std::vector <std::string> OPERATORS_LIST {"+","-","*","/","(",")"};
namespace expression {
    template <typename T>
    class Operator {
public:
Operator (const std::string&);
Operator() {};
T execute(T first, T second);
std::string getSymbols() const{return symbols;}
unsigned int getPriority() const {return priority;}
bool operator ==(const std::string& other) const { return getSymbols() == other;}
bool operator ==(const Operator& other) { return (other.getSymbols() == symbols); }
private:
void prioritize ();
std::string symbols;
unsigned int priority;
    };
    template <typename T>
    T Operator<T>::execute(T first, T second) {
        unsigned int tmp = arrayAriphmetics::findFirstLooked(OPERATORS_LIST, symbols, OPERATORS_LIST.size());
        switch(tmp) {
        case 0: return (first + second);
        case 1: return (first - second);
        case 2: return (first * second);
        case 3: {
            if (first - first == second) {
                throw std::exception("Division by zero");
            }
            return first / second;
        }
        case 4: { return first; }
        default: throw std::runtime_error("At least one operator from OPERATORS_LIST does not have realization");
    }
    return first;
    }
    template <typename T>
    void Operator<T>::prioritize () {
        unsigned int tmp;
        tmp = arrayAriphmetics::findFirstLooked(OPERATORS_LIST, symbols, OPERATORS_LIST.size());
        switch(tmp) {
        case 0: {
            priority = 1;
            break;
        }
        case 1: {
            priority = 1;
            break;
        }
        case 2: {
            priority = 2;
            break;
        }
         case 3: {
            priority = 2;
            break;
        }
        case 4: {
            priority = 0;
            break;
        }
        case 5: {
            priority = 0;
            break;
        }
        default: throw std::runtime_error("At least one operator from OPERATORS_LIST does not have realization");
    }
    }
    template <typename T>
    Operator<T>::Operator (const std::string &given) {
        symbols = given;
        prioritize();
    }


}