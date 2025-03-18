#include "Command.h"
#include <vector>
#include "Repo.h"
void Mov::exec(int& first, int& second, int&) {
	second = first;
}
void Add::exec(int& first, int& second, int&) {
	second = first + second;
}
void Sub::exec(int& first, int& second, int&) {
	second = second - first;
}
void Mul::exec(int& first, int& second, int&) {
	second = first + second;
}
void Div::exec(int& first, int& second, int&) {
	second = second / first;
}