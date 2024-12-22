#pragma once
const char* NUM_LIST_ = "0123456789";
const char* OPERATORS_FIRST_SYMBOLS_LIST_ = "+-*/";
const char* BRACKETS_LIST = "()";
namespace check {
	bool isLastSymbol(std::string given, size_t index) {
		int firstCheck = arrayAriphmetics::count(NUM_LIST_, given[index]);
		int secondCheck = arrayAriphmetics::count(OPERATORS_FIRST_SYMBOLS_LIST_, given[index]) * 2;
		int thirdCheck = arrayAriphmetics::count(BRACKETS_LIST, given[index]) * 3;
		int firstCheckNext = arrayAriphmetics::count(NUM_LIST_, given[index + 1]);
		int secondCheckNext = arrayAriphmetics::count(OPERATORS_FIRST_SYMBOLS_LIST_, given[index + 1]) * 2;
		int thirdCheckNext = arrayAriphmetics::count(BRACKETS_LIST, given[index + 1]) * 3;
		return ((firstCheck + secondCheck + thirdCheck) != (firstCheckNext + secondCheckNext + thirdCheckNext));
	}
}