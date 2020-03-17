#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "Interpreter.h"
#include <iostream>

int main(int argc, char* argv[]) {

	string filename = "TestFiles/in62.txt";/*argv[1];*/
	Scanner s = Scanner(filename);
	s.Scan(filename);
	Parser p = Parser(s.GetTokenList());
	Interpreter i = p.Parse();
	i.Interpret();

	return 0;
}
