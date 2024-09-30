#include <iostream>
#include <ctime>
#include <cstdlib>
void Input(char *a, int num) // функция ввода значений в массив (массив а)
{
    bool isAuto;
    std::cout << std::endl << "0 to manually fill array, 1 to fill it with random symbols: ";
    std::cin >> isAuto;
    if (isAuto)  { // Генерация случайных символов
        srand(static_cast<unsigned int>(time(0)));
        for (int i = 0; i < num - 1; i++) {
            a[i] = rand() % 255 + 1;
            std::cout << a[i];
        }
        a[num - 1] = 0;
    }
    else {
        for (int i = 0; i < num - 1; i++) { /* ручной ввод с консоли */
            std::cin >> a[i];
        }
        a[num - 1] = NULL;
    }
}
bool isDigit(char *string, int i) //проверка на принадлежность символа множеству цифр, символ в строке под индексом i
{
    return (string[i] >= '0' && string[i] <= '9');
}
bool isTwoDigitLessThan(char *string, int begin, char firstUpperDigit, char secondUpperDigit) 
// Проверка на содержание двузначного числа из символов в строке, начиная с символа с индекса begin, меньшим, чем число из firstUpperDigit, secondUpperDigit.
{
    bool isFirstTen, isLastTen, isBetweenBorderingTens;
    isFirstTen = (string[begin] == '0' && string[begin + 1] >= '1' && string[begin + 1] <= '9');
    isBetweenBorderingTens = (string[begin] >= '1' && string[begin] < firstUpperDigit && string[begin + 1] >= '0' && string[begin + 1] <= '9');
    isLastTen = (string[begin] == firstUpperDigit && string[begin + 1] >= '0' && string[begin + 1] <= secondUpperDigit);
    return (isFirstTen || isBetweenBorderingTens || isLastTen);
}
bool isLeap(char *string, int begin) //Проверка на високосность года, записанного символами в строке, начиная с символа begin
{
    int year = 1000 * string[begin] + 100 * string[begin + 1] + 10 * string[begin + 2] + string[begin + 3];
    return ((year % 4 == 0 && year % 25 != 0) || (year % 16 == 0));
}
bool isMonth(char *string, int begin) // Проверка записи из символов в строке, начиная с begin (2 символа) на принадлежность множеству месяцев
{
    return (isTwoDigitLessThan(string, begin, '1', '2'));
}
bool isYear(char *string, int begin) 
// Проверка на принадлежность записи из 4 символов в строке после индекса begin множеству всевозможных четырёхзначных записей года (от 0001 до 9999)
{
    return (isDigit(string, begin) && isDigit(string, begin + 1), isDigit(string, begin + 2) && isDigit(string, begin + 3) && string[begin + 3] > '0');
}
bool isDay(char *string, int begin, bool isLeap) 
//Проверка на принадлежность части строки с индекса begin и длины 2 на принадлежность множеству дней в месяце (в зависимости от месяца и года от 1 до 28, 29, 30, 31)
{

    if (string[begin + 3] == '0' && string[begin + 4] == '2') {
        if (isLeap) {
            return (isTwoDigitLessThan(string, begin, '2', '9'));
        }
        else
            return (isTwoDigitLessThan(string, begin, '2', '8'));
    }
    else if (string[begin + 3] == '0' && (string[begin + 4] == '4' || string[begin + 4] == '6' || string[begin + 4] == '9')) {
        return (isTwoDigitLessThan(string, begin, '3', '0'));
    }
    else {
        return (isTwoDigitLessThan(string, begin, '3', '1'));
    }
}
bool isDate(char *string, int begin) //Проверка записи из 10 символов, начиная с begin строки string на принадлежность множеству записей дат вида dd/mm/yyyy
{
    return (isYear(string, begin + 6) && isMonth(string, begin + 3) && isDay(string, begin, isLeap(string, begin + 6)) && (string[begin + 2] == '/') && (string[begin + 5] == '/'));
}
int numberOfDates(char *string, int num) //Подсчёт количества дат вида dd/mm/yyyy в строке string длины num
{
    int res = 0;
    for (int i = 0; i < num; i++) {
        if (isDate(string, i)) {
            res++;
        }
    }
    return res;
}
char *_strchr(char *string, int c) // Поиск первого вхождения символа с в строку string
{
    int res = -1;
    for (int i = 0; i < strlen(string); i++) {
        if (string[i] == c) {
            res = i;
            break;
        }
    }
    if (res == -1) {
        return NULL;
    }
    return &string[res];
}
void ccout(char *a, int num) // вывод строки а
{
    std::cout << std::endl;
    for (int i = 0; i < num; i++) {
        std::cout << a[i];
    }
    std::cout << std::endl;
}
int main()
{
    int numberOfElements;
    char symbol;
    std::cout << "How many elements does string have? ";
    std::cin >> numberOfElements;
    numberOfElements++;
    char *string = new char[numberOfElements];
    Input(string, numberOfElements);
    std::cout << "What simbol do you seek for: ";
    std::cin >> symbol;
    if (_strchr(string, symbol) != NULL) {
        char *found = _strchr(string, symbol);
        std::cout << "Symbol " << symbol << " is presented in string on position " << found - string + 1;
    }
    else {
        std::cout << "Symbol " << symbol << " is not presented in string.";
    }
    ccout(string, numberOfElements);
    std::cout << "There are " << numberOfDates(string, numberOfElements) << " dates in this string";
}
