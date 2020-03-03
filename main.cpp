#include "Parser.h"
#include "Scanner.h"
#include "Token.h"
#include <iostream>

int main(int argc, char* argv[]) {

	string filename = "TestFiles/in62.txt";/*argv[1];*/
	Scanner s = Scanner(filename);
	s.Scan(filename);
	Parser p = Parser(s.GetTokenList());
	p.Parse();


	return 0;
}
