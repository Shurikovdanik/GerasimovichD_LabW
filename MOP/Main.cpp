#include <iostream>
#include <string>
#include <vector>
#include "Main.h"
#include "IOfile.h"
#include "Parser.h"
#include "Repo.h"
#include "Interpretation.h"
int Main::execute() {
	std::cout << "Enter input and output filenames";
	std::string Ifile, Ofile;
	std::cin >> Ifile >> Ofile;
	IOFileTxt temp;
	std::vector<std::string> lines;
	lines = temp.read(Ifile);
	Parser temporary;
	Repo calc = temporary.interpretate(lines);
	calc.execCode();
	return 0;
}