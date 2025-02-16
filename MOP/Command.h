#pragma once
#include <vector>
#include <string>
class Command
{
public:
	virtual void exec(int&, int&, int&) = 0;
private:
	//Repo* data;
};
class Mov : public Command {
private:
	std::string name = "mov";
public:
	void exec(int&, int&, int&);
};

class Add : public Command {
private:
	std::string name = "add";
public:
	void exec(int&, int&, int&);
};

class Sub : public Command {
private:
	std::string name = "sub";
public:
	void exec(int&, int&, int&);
};

class Mul : public Command {
private:
	std::string name = "mul";
public:
	void exec(int&, int&, int&);
};

struct Div : public Command {
private:
	std::string name = "div";
public:
	void exec(int&, int&, int&);
};
