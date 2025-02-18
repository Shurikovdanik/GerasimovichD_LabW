#include "Command.h"
#include <vector>
#include <iostream>
#include "Repo.h"
void Mov::exec(int& first, int& second, int& third) {
	first = second;
}
void Add::exec(int& first, int& second, int& third) {
	first = first + second;
}
void Sub::exec(int& first, int& second, int& third) {
	first = second - first;
	
}
void Mul::exec(int& first, int& second, int& third) {
	first *= second;
}
void Div::exec(int& first, int& second, int& third) {
	first = second / first;
}