#include <iostream>
#include <fstream>
#include "Main.h"
#include "include\Expression.h"
 int ConMain::execute() {
	 std::string simbols;
	 std::cout << "Enter expression: ";
	 std::cin >> simbols;
	 std::cout << "Enter 1 for integers calculation, 0 for floats: ";
	 bool isInt;
	 std::cin >> isInt;
	 if (isInt) {
		 expression::Expression<int> expr(simbols);
		 std::cout << "\n" << "Result is: " << expr.execute();
	 }
	 else {
		 expression::Expression<double> expr(simbols);
		 std::cout << "\n" << "Result is: " << expr.execute();
	 }
	 return 1;
}
 int FileMain::execute() {
	 bool isInt;
	 std::string expression;
	 std::ifstream fin("data/input.txt");
	 fin >> isInt >> expression;
	 fin.close();
	 std::ofstream fout("data/output.txt");
	 if (isInt) {
		 expression::Expression<int> temp(expression);
		 fout << expression << "=" << temp.execute();
	 }
	 else {
		 expression::Expression<double> temp(expression);
		 fout << expression << "=" << temp.execute();
	 }
	 return 1;
 }