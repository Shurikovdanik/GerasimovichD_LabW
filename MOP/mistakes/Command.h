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
	
public:
	void exec(int&, int&, int&);
};

class Add : public Command {
private:
	
public:
	void exec(int&, int&, int&);
};

class Sub : public Command {
private:

public:
	void exec(int&, int&, int&);
};

class Mul : public Command {
private:

public:
	void exec(int&, int&, int&);
};

struct Div : public Command {
private:
	
public:
	void exec(int&, int&, int&);
};
