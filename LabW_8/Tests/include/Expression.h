#include <iostream>
#include <string>
#include "..\include\Operator.h"
#include "..\include\basicactions.h"
#include "..\include\Stack.h"
const char* OPERATORS_FIRST_SYMBOLS_LIST = "+-*/()";
namespace expression {
template <typename T>
class Expression {
    public:
    Expression(const std::string& given);
    T execute();
    custom::Stack<T> getnumbersStack;
    custom::Stack<char> getOperatorStack;
    private:
    void toPolishR();
    std::stringstream expression;
    custom::Stack<T> numbersStack;
    custom::Stack<std::string> operatorStack;
};
template <typename T>
Expression<T>::Expression(const std::string& given) {
    unsigned int begin = 0;
    unsigned int end;
    for (int i = 0; i < given.size() - 1; i++) {
        if (arrayAriphmetics::count<char>(OPERATORS_FIRST_SYMBOLS_LIST, given[i]) == arrayAriphmetics::count<char>(NUM_LIST, given[i + 1])) {
            end = i;
            expression << given.substr(begin, end - begin + 1);
            begin = end + 1;
        }
        T* newStackNum = new T;
        std::string* newOperatorStack = new std::string;
       custom::Stack<T> numbersStack1(newStackNum, newStackNum);
       numbersStack = numbersStack1;
       custom::Stack<std::string> operatorsStack(newOperatorStack, newOperatorStack); 
        operatorStack = operatorsStack;
    }
    T tmp[1];
    std::string tems[1];

}
template <typename T>
void Expression<T>::toPolishR() {
    bool isFirst = 1;
    std::stringstream tmpStream;
    while (expression >> tmpStream) {}
    std::string tmp;
    while (expression >> tmp) {
        if (arrayAriphmetics::count(NUM_LIST, tmp[0])) {
            numbersStack << stod(tmp);
            numbersStack >> expression;
        }
        if (arrayAriphmetics::count(OPERATORS_FIRST_SYMBOLS_LIST, tmp[0])) {
            Operator tempOperator (tmp);
            if (isFirst) {
                isFirst = 0;
                operatorStack << tempOperator;
            }
            else {
                Operator<T> stackOperator;
                operatorStack >> stackOperator;
                if (tmp == ")") {
                    unsigned int rightBracket = operatorStack.getLength() + 1;
                    Operator temp("(");
                     unsigned int leftBracket = arrayAriphmetics::findLastLooked(operatorStack.getAlloc(),temp);
                   for (int i = rightBracket - 1; i > leftBracket; i--) {
                    operatorStack >> expression;
                   }
                }
                if (stackOperator.getPriority() < stackOperator.getPriority()) {
                    expression << stackOperator.getSymbols();
                    operatorStack << tmp;
                }
            }
        }
    }
    Operator<T> temp;
    while (operatorStack >> temp) {
        expression << temp.getSymbols();
    }
}
template <typename T>
T Expression<T>::execute(){
    std::stringstream tempStream;
     std::string tem;
    while (expression >> tem) {
        tempStream << tem;
        }
        T* first1 = new T;
    T res;
    std::string temp;
    tempStream >> temp;;
    res = stod(temp);
    custom::Stack<T> numbers(first1, first1);
    while (expression >> temp) {
        if (arrayAriphmetics::count(NUM_LIST, temp[0])) {
            numbers << stod(temp);
        }
        else {
            T first, second;
            numbers >> second >> first;
            Operator<T> tempOperator(temp);
            numbers << tempOperator.execute(first, second);
        }
    }
    numbers >> res;
    return res;
}
}