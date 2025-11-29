// Square.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>


using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	float x,y;
	int i=0;
	char sTail[100];
	
	ZeroMemory(sTail,sizeof(sTail));
	//cerr <<':' << "sizeof(sTail)" <<':'<< sizeof(sTail)<<sizeof(char)<< endl;
	
	while(!cin.eof())
	{
		i++;
		sTail[0]=0;
		cin >> x;
		if(cin.fail())
		{
			
			if(cin.eof())
				break;			
			cin.clear(0);//all error flags are cleared.

			cin.getline(sTail,100,'\n'); //What is in the error-line i?
			//cerr << i <<':' << "Error" <<':'<<(int)(sTail[0])<< endl;
			cerr << i <<':' << "Error" <<':'<< sTail<< endl;


			continue;
		}

		cin.getline(sTail,100,'\n');//'\n' - delimiter after a number
		if(sTail[0]!=0)//Is it the empty string after a number?
		{
			//cerr << i <<':' << "Error" <<':'<<(int)(sTail[0])<< endl;
			cerr << i <<':' << "Error" <<':'<< sTail<< endl;

			continue;
		}

		y=x*x;
		
		cout <<y << endl;
		
	};
	
	return 0;
}


#include <fstream>
void fread(void)
{
	int x;
  char line[20];
  ifstream rfile;
  rfile.open("path-to-txt-file");
  if (rfile.is_open()) {
	  rfile >> line  >> x;
	while (rfile.getline(line, 20)) {
		std::cout << line << std::endl;
	}
	rfile.close();
  }
}
