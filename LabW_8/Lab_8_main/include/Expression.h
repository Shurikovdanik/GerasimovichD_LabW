#pragma once
#include <iostream>
#include <string>
#include "..\include\Operator.h"
#include "..\include\basicactions.h"
#include "..\include\Stack.h"
#include "..\include\check.h"
const char* OPERATORS_FIRST_SYMBOLS_LIST = " +-*/()";
namespace expression {
template <typename T>
class Expression {
    public:
    Expression(const std::string& given);
    T execute();
    custom::Stack<T> getnumbersStack;
    custom::Stack<char> getOperatorStack;
    std::string getSymbols() {
        std::string res = "";
        for (int i = 0; i < expression.getLength(); i++) {
            res += expression[i];
        }
        return res;
    }
    void toPolishR();
    std::string getSymbolsPolish() {
        std::string res = "";
        for (int i = 0; i < expressionOther.getLength(); i++) {
            res += expressionOther[i];
        }
        return res;
    }
    private:
    custom::Stack<std::string> Expression<T>::getExpression();
    custom::Stack<std::string> expression;
    custom::Stack<Operator<T>> operatorStack;
    custom::Stack<std::string> expressionOther;
};
template <typename T>
custom::Stack<std::string> getExpression() {
    return expression;
}
template <typename T>

Expression<T>::Expression(const std::string& given) {
    unsigned int begin = 0;
    unsigned int end = 0;
    int counter = 1;
    for (int i = 0; i < given.size() - 1; i++) {
        if (check::isLastSymbol(given, i)) {
            counter++;
        }
    }
    std::string* stringArray = new std::string[counter];
    int counter1 = 0;
    for (int i = 0; i < given.size() - 1; i++) {
        if (check::isLastSymbol(given, i)) {
            end = i + 1;
            stringArray[counter1] = given.substr(begin, end - begin);
            begin = end;
            counter1++;
        }
    }
    stringArray[counter1] = given.substr(begin, given.size() - begin);
    custom::Stack<std::string> strings(stringArray, counter);
    expression = strings;
}
template <typename T>
void Expression<T>::toPolishR() { //К обратной польской записи(в второй стек выражения)
    std::string tmp;
    expression.selfreverse(); 
        while ((expression >> tmp).getLength() > 0) { 
        if (arrayAriphmetics::count(NUM_LIST, tmp[0])) {
            expressionOther << tmp; 
        }
        else if (arrayAriphmetics::count(OPERATORS_FIRST_SYMBOLS_LIST, tmp[0])) {  
                Operator<T> stackOperator(tmp);
                Operator<T> tmpOperator(tmp);
                if (tmp == ")") {
                    unsigned int rightBracket = operatorStack.getLength() + 1;
                    Operator<T> temp("(");
                     unsigned int leftBracket = arrayAriphmetics::findLastLooked<Operator<T>*, Operator<T>>(operatorStack.getAlloc(), temp, operatorStack.getLength());
                     for (int i = rightBracket - 1; i > leftBracket; i--) {

                      operatorStack >> tmpOperator;
                      
                      expressionOther << tmpOperator.getSymbols();
                   }
                }
                else if (operatorStack.getLength() > 0) {
                    operatorStack >> stackOperator;
                    if (tmpOperator.getPriority() < stackOperator.getPriority() && tmpOperator.getSymbols() != "(") {
                        expressionOther << stackOperator.getSymbols();
                        operatorStack << tmpOperator;
                    }
                    else {
                        operatorStack << stackOperator;
                        operatorStack << tmpOperator;
                    }
                }
                else {
                    operatorStack << stackOperator;
                    operatorStack << tmpOperator;
                }
        }
       
    }
        if (arrayAriphmetics::count(NUM_LIST, tmp[0])) {
            expressionOther << tmp;
        }
        else if (arrayAriphmetics::count(OPERATORS_FIRST_SYMBOLS_LIST, tmp[0])) {
                Operator<T> stackOperator(tmp);
                Operator<T> tmpOperator(tmp);
                if (tmp == ")") {
                    unsigned int rightBracket = operatorStack.getLength() + 1;
                    Operator<T> temp("(");
                    unsigned int leftBracket = arrayAriphmetics::findLastLooked<Operator<T>*, Operator<T>>(operatorStack.getAlloc(), temp, operatorStack.getLength());
                    for (int i = rightBracket - 1; i > leftBracket; i--) {
                        operatorStack >> tmpOperator;
                        expressionOther << tmpOperator.getSymbols();
                    }
                }
                else if (operatorStack.getLength() > 0) {
                    operatorStack >> stackOperator;
                    if (tmpOperator.getPriority() < stackOperator.getPriority() && tmpOperator.getSymbols() != "(") {
                        expressionOther << stackOperator.getSymbols();
                        operatorStack << tmpOperator;
                    }
                    else {
                        operatorStack << stackOperator;
                        operatorStack << tmpOperator;
                    }
                }
                else {
                    operatorStack << stackOperator;
                }
        }
    Operator<T> temp;
    while ((operatorStack >> temp).getLength() > 0) {
            expressionOther << temp.getSymbols();
          
    }
}
template <typename T>
T Expression<T>::execute(){
    toPolishR();
    expressionOther.selfreverse();
   //TODO: çäåñü ïðîáëåìà
    T res = 0;
    std::string temp;
    custom::Stack<T> numbers;
    while ((expressionOther >> temp).getLength() > 0) {
       
        if (arrayAriphmetics::count(NUM_LIST, temp[0])) {
            numbers << stod(temp);
        }
        else {
            if (temp != "(") {
                T first, second;
                numbers >> first >> second;
                Operator<T> tempOperator(temp);
                res = tempOperator.execute(second, first);
                numbers << res;
            }
        }
    }
    T first, second;
  
    numbers >> first;
    second = numbers[0];
    Operator<T> tempOperator(temp);
    if (temp != "(") {
        res = tempOperator.execute(second, first);
    }
    return res;
}
}
