#include "pch.h"
#include "include\Stack.h"
#include "include\Expression.h"
#include "lib\basicactions.cpp"
#include <iostream>
TEST(truth, Stack) {
	custom::Stack<int> stack;
	int* array = new int[1];
	array[0] = 1;
	custom::Stack<int> secondStack(array,1);
	EXPECT_EQ((stack << 1).getLength(), secondStack.getLength());
	EXPECT_EQ((stack << 1)[0],1);
	stack << 2;
	int tmp;
	stack >> tmp;
	stack >> tmp;
	EXPECT_EQ(tmp, 1);
	EXPECT_EQ(stack.getLength(), 1);
	EXPECT_EQ(secondStack[0], 1);
  EXPECT_TRUE(true);
}
TEST(truthSingle, Expression) {
	expression::Expression<int> case1("1+2");
	expression::Expression<int> case2("2-1");
	expression::Expression<int> case3("2*2");
	expression::Expression<int> case4("2/2");
	EXPECT_EQ(case1.getSymbols(), "1+2");
	EXPECT_EQ(case2.getSymbols(), "2-1");
	EXPECT_EQ(case3.getSymbols(), "2*2");
	EXPECT_EQ(case4.getSymbols(), "2/2");
	case1.toPolishR();
	case2.toPolishR();
	case3.toPolishR();
	case4.toPolishR();
	EXPECT_EQ(case1.getSymbolsPolish(), "12+");
	EXPECT_EQ(case2.getSymbolsPolish(), "21-");
	EXPECT_EQ(case3.getSymbolsPolish(), "22*");
	EXPECT_EQ(case4.getSymbolsPolish(), "22/");
	EXPECT_TRUE(true); //TODO: доделать
}
TEST(truthMulti, Expression) {
	expression::Expression<int> case1("2+2*1");
	expression::Expression<int> case2("2*2+1");
	expression::Expression<int> case3("2-2*1");
	expression::Expression<int> case4("2*2-1");
	expression::Expression<int> case5("2*2*1");
	expression::Expression<int> case6("2*2*1*2");
	expression::Expression<int> case7("2/2*1");
	expression::Expression<int> case8("2*2/1");
	expression::Expression<int> case9("2+2+1");
	expression::Expression<int> case10("2+2-1");
	expression::Expression<int> case11("2+2+1");
	expression::Expression<int> case12("2-2+1");
	EXPECT_EQ(case1.getSymbols(), "2+2*1");
	EXPECT_EQ(case2.getSymbols(), "2*2+1");
	EXPECT_EQ(case3.getSymbols(), "2-2*1");
	EXPECT_EQ(case4.getSymbols(), "2*2-1");
	EXPECT_EQ(case5.getSymbols(), "2*2*1");
	EXPECT_EQ(case6.getSymbols(), "2*2*1*2");
	EXPECT_EQ(case7.getSymbols(), "2/2*1");
	EXPECT_EQ(case8.getSymbols(), "2*2/1");
	EXPECT_EQ(case9.getSymbols(), "2+2+1");
	EXPECT_EQ(case10.getSymbols(), "2+2-1");
	EXPECT_EQ(case11.getSymbols(), "2+2+1");
	EXPECT_EQ(case12.getSymbols(), "2-2+1");
	case1.toPolishR();
	case2.toPolishR();
	case3.toPolishR();
	case4.toPolishR();
	case5.toPolishR();
	case6.toPolishR();
	case7.toPolishR();
	case8.toPolishR();
	case9.toPolishR();
	case10.toPolishR();
	case11.toPolishR();
	case12.toPolishR();
	EXPECT_EQ(case1.getSymbolsPolish(), "221*+");
	EXPECT_EQ(case2.getSymbolsPolish(), "22*1+");
	EXPECT_EQ(case3.getSymbolsPolish(), "221*-");
	EXPECT_EQ(case4.getSymbolsPolish(), "22*1-");
	EXPECT_EQ(case5.getSymbolsPolish(), "221**");
	EXPECT_EQ(case6.getSymbolsPolish(), "2212***");
	EXPECT_EQ(case7.getSymbolsPolish(), "221*/");
	EXPECT_EQ(case8.getSymbolsPolish(), "221/*");
	EXPECT_EQ(case9.getSymbolsPolish(), "221++");
	EXPECT_EQ(case10.getSymbolsPolish(), "221-+");
	EXPECT_EQ(case11.getSymbolsPolish(), "221++");
	EXPECT_EQ(case12.getSymbolsPolish(), "221+-");
	EXPECT_TRUE(true);
}
TEST(truthBrackets, Expression) {
	expression::Expression<int> case1("(2+2)*3");
	EXPECT_EQ(case1.getSymbols(), "(2+2)*3");
	case1.toPolishR();
	EXPECT_EQ(case1.getSymbolsPolish(), "22+(3*");
}
TEST(truthSingle, execute) {
	expression::Expression<int> case1("1+2");
	expression::Expression<int> case2("2-1");
	expression::Expression<int> case3("2*2");
	expression::Expression<int> case4("2/2");
	EXPECT_EQ(case1.execute(), 3);
	EXPECT_EQ(case2.execute(), 1);
	EXPECT_EQ(case3.execute(), 4);
	EXPECT_EQ(case4.execute(), 1);
	EXPECT_TRUE(true);
}
TEST(truthMulti, execute) {
	expression::Expression<int> temp3("2*2+2");
	expression::Expression<int> temp4("2+2*1");
	expression::Expression<int> temp5("2*3+2*3");
	EXPECT_EQ(temp3.execute(), 6);
	EXPECT_EQ(temp4.execute(), 4);
	EXPECT_EQ(temp5.execute(), 12);
	EXPECT_TRUE(true);
}
TEST(truthBrackets, execute) {
	expression::Expression<int> case1("(2+2)*3");
	expression::Expression<int> case2("3*(2+2)");
	expression::Expression<int> case3("3*(2+2)*(2+3)");
	EXPECT_EQ(case1.execute(), 12);
	EXPECT_EQ(case2.execute(), 12);
	EXPECT_EQ(case3.execute(), 60);
	EXPECT_TRUE(true);
}
TEST(false, execute) {
	expression::Expression<int> temp("1+");
	expression::Expression<int> temp1("2-");
	expression::Expression<int> temp2("2*");
	expression::Expression<int> temp3("2*+1");
	expression::Expression<int> temp4("2+1+");
	ASSERT_ANY_THROW(temp.execute());
	ASSERT_ANY_THROW(temp1.execute());
	ASSERT_ANY_THROW(temp2.execute());
	ASSERT_ANY_THROW(temp3.execute());
	ASSERT_ANY_THROW(temp4.execute());
	EXPECT_TRUE(true);
}
TEST(truth, Operator) {
	expression::Operator<int> operatora("+");
	EXPECT_EQ(operatora.execute(1, 2), 3);
	expression::Operator<int> operatora1("-");
	EXPECT_EQ(operatora1.execute(2, 1), 1);
	expression::Operator<int> operatora2("*");
	EXPECT_EQ(operatora2.execute(1, 2), 2);
	EXPECT_TRUE(true);
}
TEST(falseSingle, execute) {
	expression::Expression<int> temp("1/0");
	ASSERT_ANY_THROW(temp.execute());
	EXPECT_TRUE(true);
}
